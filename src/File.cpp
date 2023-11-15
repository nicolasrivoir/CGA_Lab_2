// Allow unsafe functions used by std_image library
#define _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS_GLOBALS

// Define these only in *one* .cc file.
#define TINYGLTF_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
// #define TINYGLTF_NOEXCEPTION // optional. disable exception handling.
#include <tiny_gltf.h>
#include <iostream>
#include <fstream>

#include "File.h"
#include "MeshObject.h"

using namespace File;
using namespace math;

using BYTE = unsigned char;

/* Auxiliary method */
template <typename T>
std::vector<T> extract_from_accessor(const tinygltf::Model& model, const tinygltf::Accessor& accessor) {

	auto& buffer_view = model.bufferViews[accessor.bufferView];
	auto& buffer = model.buffers[buffer_view.buffer];

	const T* buffer_data = reinterpret_cast<const T*>(&buffer.data[buffer_view.byteOffset + accessor.byteOffset]);

	return std::vector<T>(buffer_data, buffer_data + accessor.count);
}


struct File::GLTF_t {
	tinygltf::Model model;
};

GLTF_t* File::loadGLB(std::string path)
{
	tinygltf::Model m_model;
	tinygltf::TinyGLTF loader;
	std::string err;
	std::string warn;

	bool ret = loader.LoadBinaryFromFile(&m_model, &err, &warn, path); // for binary glTF(.glb)

	if (!warn.empty()) {
		printf("Warning: %s\n", warn.c_str());
	}

	if (!err.empty()) {
		printf("Error: %s\n", err.c_str());
	}

	if (!ret) {
		printf("Failed to parse glTF\n");
		abort();
	}

	return new GLTF_t{ m_model };
}

std::vector<MeshObject> File::extractMeshes(GLTF_t* file, unsigned int scene_index)
{
	std::vector<MeshObject> objects;

	auto& scene = file->model.scenes[scene_index];

	for (int node_index : scene.nodes) {

		auto& node = file->model.nodes[node_index];

		if (node.mesh >= 0) {

			math::Matrix<4, 4> transform = math::identity<4>();

			if (node.scale.size() == 3) {
				transform[0][0] = static_cast<float>(node.scale[0]);
				transform[1][1] = static_cast<float>(node.scale[1]);
				transform[2][2] = static_cast<float>(node.scale[2]);
			}

			if (node.rotation.size() == 4) {
				Matrix<4, 1> quaternion{};
				quaternion[0][0] = static_cast<float>(node.rotation[0]);
				quaternion[1][0] = static_cast<float>(node.rotation[1]);
				quaternion[2][0] = static_cast<float>(node.rotation[2]);
				quaternion[3][0] = static_cast<float>(node.rotation[3]);

				auto R = math::quaternion_to_rotation_matrix(quaternion);

				transform = R * transform;
			}

			if (node.translation.size() == 3) {
				Matrix<4, 4> T = identity<4>();
				T[0][3] = static_cast<float>(node.translation[0]);
				T[1][3] = static_cast<float>(node.translation[1]);
				T[2][3] = static_cast<float>(node.translation[2]);
				transform = T * transform;
			}

			MeshObject mesh_object(transform);

			auto& mesh = file->model.meshes[node.mesh];

			for (auto& primitive : mesh.primitives) {

				auto mesh_ptr = new geometry::Mesh();
				geometry::Mesh& new_mesh = *mesh_ptr;

				const int positions_index = primitive.attributes["POSITION"];
				if (positions_index >= 0) {
					const tinygltf::Accessor& positions_accessor = file->model.accessors[positions_index];
					new_mesh.positions = extract_from_accessor<math::Vector3>(file->model, positions_accessor);
				}

				const int normals_index = primitive.attributes["NORMAL"];
				if (normals_index >= 0) {
					const tinygltf::Accessor& normals_accessor = file->model.accessors[normals_index];
					new_mesh.normals = extract_from_accessor<math::Vector3>(file->model, normals_accessor);
				}

				const int texcoords_index = primitive.attributes["TEXCOORD"];
				if (texcoords_index >= 0) {
					const tinygltf::Accessor& texcoords_accessor = file->model.accessors[texcoords_index];
					new_mesh.texcoords = extract_from_accessor<math::Vector2>(file->model, texcoords_accessor);
				}

				const int indices_index = primitive.indices;
				if (indices_index >= 0) {
					const tinygltf::Accessor& indices_accessor = file->model.accessors[indices_index];
					if (indices_accessor.componentType == TINYGLTF_COMPONENT_TYPE_UNSIGNED_SHORT) {
						auto indices_ushort = extract_from_accessor<unsigned short>(file->model, indices_accessor);
						new_mesh.indices = std::vector<unsigned int>(indices_ushort.begin(), indices_ushort.end());
					}
					else { // UNSIGNED INT CASE
						new_mesh.indices = extract_from_accessor<unsigned int>(file->model, indices_accessor);
					}
				}

				const int material_index = primitive.material;
				Material new_material;
				if (material_index >= 0) {
					tinygltf::Material mat = file->model.materials[material_index];
					new_material.basecolor.x = mat.pbrMetallicRoughness.baseColorFactor[0];
					new_material.basecolor.y = mat.pbrMetallicRoughness.baseColorFactor[1];
					new_material.basecolor.z = mat.pbrMetallicRoughness.baseColorFactor[2];

					new_material.metallic = mat.pbrMetallicRoughness.metallicFactor;
					new_material.roughness = mat.pbrMetallicRoughness.roughnessFactor;

					new_material.emission.x = mat.emissiveFactor[0];
					new_material.emission.y = mat.emissiveFactor[1];
					new_material.emission.z = mat.emissiveFactor[2];

					auto transmission_extension = mat.extensions.find("KHR_materials_transmission");
					if (transmission_extension != mat.extensions.end()) {
						auto transmission_object = transmission_extension->second.Get("transmissionFactor");
						new_material.transmission = transmission_object.GetNumberAsDouble();
					}

				}

				mesh_object.addSubMesh(new_mesh, new_material);
			}
			objects.push_back(mesh_object);
		}
	}

	return objects;
}

std::vector<CamConstructorData> File::extractCameras(GLTF_t* file, unsigned int scene_index)
{
	std::vector<CamConstructorData> cameras;

	auto& scene = file->model.scenes[scene_index];

	for (int node_index : scene.nodes) {

		auto& node = file->model.nodes[node_index];

		CamConstructorData camera_data;

		for (auto& child_index : node.children) {
			auto& child = file->model.nodes[child_index];
			if (child.camera >= 0) {

				auto& cam = file->model.cameras[child.camera];

				if (cam.type == "orthographic") {
					continue;
				}

				if (node.rotation.size() == 4) {
					Matrix<4, 1> quaternion{};
					quaternion[0][0] = static_cast<float>(node.rotation[0]);
					quaternion[1][0] = static_cast<float>(node.rotation[1]);
					quaternion[2][0] = static_cast<float>(node.rotation[2]);
					quaternion[3][0] = static_cast<float>(node.rotation[3]);
					camera_data.eye_rotation = quaternion;
				}

				if (node.translation.size() == 3) {
					Vector3 T;
					T.x = static_cast<float>(node.translation[0]);
					T.y = static_cast<float>(node.translation[1]);
					T.z = static_cast<float>(node.translation[2]);
					camera_data.eye_translation = T;
				}

				camera_data.yfov = cam.perspective.yfov;
				camera_data.znear = cam.perspective.znear;
				camera_data.zfar = cam.perspective.zfar;

				cameras.push_back(camera_data);
			}
			if (child.rotation.size() == 4) {
				camera_data.orientation[0][0] = child.rotation[0];
				camera_data.orientation[1][0] = child.rotation[1];
				camera_data.orientation[2][0] = child.rotation[2];
				camera_data.orientation[3][0] = child.rotation[3];
			}
		}
	}

	return cameras;
}

std::vector<Scene> File::extractScenes(GLTF_t* file)
{
	std::vector<Scene> scenes;

	auto fileScenes = file->model.scenes;
	for (unsigned int scene_index = 0; scene_index < fileScenes.size(); scene_index++) {
		Scene scene;
		auto meshes = extractMeshes(file, scene_index);
		for (auto& mesh : meshes) {
			scene.addObject(mesh);
		}
		scenes.push_back(scene);
	}

	return scenes;
}

const BYTE* File::loadFile(std::string fname)
{
	int size;
	char* memblock = NULL;

	// file read based on example in cplusplus.com tutorial
	// ios::ate opens file at the end
	std::ifstream file(fname, std::ios::in | std::ios::binary | std::ios::ate);
	if (file.is_open())
	{
		size = (int)file.tellg(); // get location of file pointer i.e. file size
		memblock = new char[size + 1]; // create buffer with space for null char
		file.seekg(0, std::ios::beg);
		file.read(memblock, size);
		file.close();
		memblock[size] = 0;
		std::cout << "file " << fname << " loaded" << std::endl;
	}
	else
	{
		std::cout << "Unable to open file " << fname << std::endl;
		// should ideally set a flag or use exception handling
		// so that calling function can decide what to do now
	}
	return reinterpret_cast<BYTE*>(memblock);
}

/* GLSL */

File::GLSL::GLSL(std::string fname)
{
	source = loadFile(fname);
}

File::GLSL::~GLSL()
{
	delete source;
}

#include "MeshObject.h"

using namespace math;

MeshObject::MeshObject(math::Matrix<4, 4> transform) : transform(transform) {}

void MeshObject::add_mesh(geometry::Mesh &mesh)
{
	meshes.push_back(std::shared_ptr<geometry::Mesh>(&mesh));
}

void MeshObject::add_material(Material material)
{
	materials.push_back(material);
}

void MeshObject::commit_object()
{
	for (auto &mesh : meshes) {
		for (auto& v : mesh->positions) {
			Matrix<4, 1> homogeneous_pos;
			homogeneous_pos[0][0] = v.x;
			homogeneous_pos[1][0] = v.y;
			homogeneous_pos[2][0] = v.z;
			homogeneous_pos[3][0] = 1.0f;

			homogeneous_pos = transform * homogeneous_pos;

			v.x = homogeneous_pos[0][0];
			v.y = homogeneous_pos[1][0];
			v.z = homogeneous_pos[2][0];
		}
		for (auto& n : mesh->normals) {
			Matrix<4, 1> homogeneous_norm;
			homogeneous_norm[0][0] = n.x;
			homogeneous_norm[1][0] = n.y;
			homogeneous_norm[2][0] = n.z;
			homogeneous_norm[3][0] = 1.0f;

			auto rotation = transform;
			rotation[0][3] = 0.0f;
			rotation[1][3] = 0.0f;
			rotation[2][3] = 0.0f;

			homogeneous_norm = rotation * homogeneous_norm;

			n.x = homogeneous_norm[0][0];
			n.y = homogeneous_norm[1][0];
			n.z = homogeneous_norm[2][0];

			n = normalize(n);
		}

	}
}

std::vector<std::shared_ptr<geometry::Mesh>> MeshObject::get_meshes() {
	return meshes;
}

std::vector<Material> MeshObject::get_materials()
{
	return materials;
}

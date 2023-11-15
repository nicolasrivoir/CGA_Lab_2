#ifndef FILELOADER_H
#define FILELOADER_H

#include <string>
#include "utils.h"
#include "Scene.h"
#include "MeshObject.h"
#include "Camera.h"

namespace File
{
	using BYTE = unsigned char;

	struct GLTF_t;

	GLTF_t* loadGLB(std::string path);

	std::vector<MeshObject> extractMeshes(GLTF_t* file, unsigned int scene_index = 0);

	std::vector<CamConstructorData> extractCameras(GLTF_t* file, unsigned int scene_index = 0);

	std::vector<Scene> extractScenes(GLTF_t* file);

	const BYTE* loadFile(std::string fname);

	class GLSL {

	private:

		const BYTE* source;

	public:

		GLSL(std::string fname);

		~GLSL();

	};

}

#endif


#ifndef GLTF_H
#define GLTF_H

#include <string_view>
#include "utils.h"
#include "Scene.h"
#include "MeshObject.h"
#include "Camera.h"

namespace GLTF
{
	using BYTE = unsigned char;

	struct GLTF_t;

	GLTF_t* loadGLB(std::string_view path);

	std::vector<MeshObject> extractMeshes(GLTF_t* file, unsigned int scene_index = 0);

	std::vector<CamConstructorData> extractCameras(GLTF_t* file, unsigned int scene_index = 0);

	std::vector<Scene> extractScenes(GLTF_t* file);


}


#endif
#ifndef MESH_H
#define MESH_H

#include <vector>

#include "utils.h"

using namespace math;

struct Mesh
{
	std::vector<Vector3> vertices;
	std::vector<Vector2> texture_map;
	std::vector<Vector3> normals;
};

#endif

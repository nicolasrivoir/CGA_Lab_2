#include "MeshObject.h"

using namespace math;

MeshObject::MeshObject(math::Matrix<4, 4> transformation) : transformation(transformation) {}

void MeshObject::addSubMesh(geometry::Mesh &mesh, Material mat)
{
	meshes.push_back(std::shared_ptr<geometry::Mesh>(&mesh));
	materials.push_back(mat);
	ids.push_back(0);
}

void MeshObject::render() {

}

#ifndef MESHOBJECT_H
#define MESHOBJECT_H

#include "utils.h"

#define DEFAULT_MATERIAL {}

class MeshObject
{
private:

	friend class Renderer;

	math::Matrix<4, 4> transformation;

	std::vector<std::shared_ptr<geometry::Mesh>> meshes;

	std::vector<Material> materials;

	std::vector<unsigned int> ids;

public:

	MeshObject(math::Matrix<4,4> transformation = math::identity<4>());

	void addSubMesh(geometry::Mesh &mesh, Material mat = DEFAULT_MATERIAL);

	void transform(math::Matrix<4, 4> trs);

	void translate(float dx, float dy, float dz);

	void rotate(float angle, const math::Vector3& axis);

};

#endif


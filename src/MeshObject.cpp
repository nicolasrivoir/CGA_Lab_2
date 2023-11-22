#include "MeshObject.h"

using namespace math;

MeshObject::MeshObject(math::Matrix<4, 4> transformation) : transformation(math::identity<4>()) {
	transform(transformation);
}

void MeshObject::addSubMesh(geometry::Mesh &mesh, Material mat)
{
	meshes.push_back(std::shared_ptr<geometry::Mesh>(&mesh));
	materials.push_back(mat);
	ids.push_back(0);
}

void MeshObject::transform(math::Matrix<4, 4> trs)
{
	transformation = transpose(transformation);
	transformation = trs * transformation;
	transformation = transpose(transformation);
}

void MeshObject::translate(float dx, float dy, float dz)
{
	Matrix<4, 4> t = identity<4>();
	t[0][3] = dx;
	t[1][3] = dy;
	t[2][3] = dz;
	transform(t);
}

void MeshObject::rotate(float angle, const Vector3& axis)
{
	const float a = angle * pi/180.0f;
	const float cos_a = cos(a);
	const float sin_a = sin(a);

	Vector3 n = normalize(axis);
	Vector3 temp = (1.0f - cos_a) * n;

	Matrix<4, 4> r = identity<4>();
	r[0][0] = cos_a + temp.x * axis.x;
	r[0][1] = temp.x * axis.y + sin_a * axis.z;
	r[0][2] = temp.x * axis.z - sin_a * axis.y;

	r[1][0] = temp.y * axis.x - sin_a * axis.z;
	r[1][1] = cos_a + temp.y * axis.y;
	r[1][2] = temp.y * axis.z + sin_a * axis.x;

	r[2][0] = temp.z * axis.x + sin_a * axis.y;
	r[2][1] = temp.z * axis.y - sin_a * axis.x;
	r[2][2] = cos_a + temp.z * axis.z;

	transform(r);
}

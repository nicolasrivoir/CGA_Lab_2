#include "Object.h"

#include "Renderer.h"


Object::Object(){}

Object::Object(const Vector3 position, const Mesh &mesh, Texture* texture) : position(position), mesh(mesh), texture(texture) {

    // Calculate the colide box
    float minX, minY, minZ, maxX, maxY, maxZ;
	minX = minY = minZ = maxX = maxY = maxZ = 0.0f;

    for (unsigned int i = 0; i < mesh.vertices.size(); i++) {
		Vector3 vertex = mesh.vertices[i];
		if (vertex.x < minX) minX = vertex.x;
		if (vertex.y < minY) minY = vertex.y;
		if (vertex.z < minZ) minZ = vertex.z;
		if (vertex.x > maxX) maxX = vertex.x;
		if (vertex.y > maxY) maxY = vertex.y;
		if (vertex.z > maxZ) maxZ = vertex.z;
	}

    Vector3 min = Vector3(minX, minY, minZ);
    Vector3 max = Vector3(maxX, maxY, maxZ);

    this->colideBox = make_pair(min, max);
}

Vector3 Object::getPosition() {
    return this->position;
}

void Object::setPosition(Vector3 position) {
    this->position = position;
}

pair<Vector3, Vector3> Object::getColideBox() {
	return make_pair(this->colideBox.first + this->position, this->colideBox.second + this->position);
}

void Object::draw() {
	Vector3 position = this->getPosition();
	Renderer::get_instance()->draw(position, mesh, texture);
}
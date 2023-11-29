#include "Scene.h"
#include "utils.h"

using namespace math;


void Scene::addObject(MeshObject &obj)
{
	objects.push_back(obj);
}

void Scene::render(Renderer &renderer)
{
	for (auto& obj : objects) {
		renderer.draw(obj);
	}
}

void Scene::update() {
	//objects[0].translate(0.0f, 0.001f, 0.0f);
	//objects[0].rotate(1, Vector3(0, 0, 1));
	//objects[0].rotate(2, Vector3(0, 1, 0));
}

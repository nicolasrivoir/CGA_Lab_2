#include "Scene.h"

Scene::Scene() {
	renderer = std::make_unique<Renderer>();
}

void Scene::addObject(MeshObject obj)
{
	objects.push_back(obj);
}

void Scene::render()
{
	for (auto& obj : objects) {
		renderer->draw(obj);
	}
	renderer->clear();
}

void Scene::update() {
}
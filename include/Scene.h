#ifndef SCENE_H
#define SCENE_H

#include "Renderer.h"
#include "MeshObject.h"
#include "Camara.h"

class Scene
{
private:

	std::shared_ptr<Renderer> renderer;

	std::vector<MeshObject> objects;

	//cam::Camara camera;

public:

	Scene();

	void addObject(MeshObject obj);

	//void setCamera(cam::Camara cam);

	void update();

	void render();

};

#endif
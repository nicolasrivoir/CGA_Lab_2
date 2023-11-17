#ifndef SCENE_H
#define SCENE_H

#include "Renderer.h"
#include "MeshObject.h"
#include "Camara.h"

class Scene
{
private:

	std::vector<MeshObject> objects;

	//cam::Camara camera;

public:

	void addObject(MeshObject obj);

	//void setCamera(cam::Camara cam);

	void update();

	void render(Renderer& renderer);

};

#endif
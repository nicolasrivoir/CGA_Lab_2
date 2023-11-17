#ifndef RENDERER_H
#define RENDERER_H

#include "Window.h"
#include "utils.h"
#include "Scene.h"
#include "MeshObject.h"

#include <memory>

class Renderer
{
private:

	Window* window;

	GLuint shaderprogram; // handle for shader program

	bool normalInterpolationEnabled;

	bool texturesEnabled;

	bool wireframeEnabled;

	void initShaders(std::string vertexShaderFile, std::string fragmentShaderFile);

	void initObject(MeshObject& obj);

public:

	Renderer(Window& window);

	Renderer(const Renderer&) = delete;

	Renderer operator=(const Renderer&) = delete;

	void toogleNormalInterpolation();

	void toggleTextures();

	void toggleWireframes();

	void draw(MeshObject& obj);

	/*
	* Clears depth-buffer and draws object on top
	*/
	void drawOnTop(MeshObject& obj);

	void clear();

};

#endif


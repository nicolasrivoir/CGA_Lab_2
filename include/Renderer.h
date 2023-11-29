#ifndef RENDERER_H
#define RENDERER_H

#include "Window.h"
#include "ShaderProgram.h"
#include "utils.h"
#include "MeshObject.h"
#include "glm/glm.hpp"
#include "glm/matrix.hpp"
#include <glm/gtc/type_ptr.hpp>

#include <memory>

class Renderer
{
private:

	Window* window;

	ShaderProgram shaderProgram;

	bool normalInterpolationEnabled;

	bool texturesEnabled;

	bool wireframeEnabled;

	void initObject(MeshObject& obj);

public:

	glm::mat4 view;

	Renderer(Window& window);

	Renderer(const Renderer&) = delete;

	Renderer operator=(const Renderer&) = delete;

	ShaderProgram getShaderProgram();

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


#ifndef RENDERER_H
#define RENDERER_H

#include "glad/glad.h"
#include "SDL.h"
#include "SDL_opengl.h"

#include "utils.h"
#include "Scene.h"
#include "MeshObject.h"

#include <memory>

class Renderer
{
private:

	SDL_Window* window;

	SDL_GLContext context;

	GLuint shaderprogram; // handle for shader program

	bool normalInterpolationEnabled;

	bool texturesEnabled;

	bool wireframeEnabled;

	void initShaders(std::string vertexShaderFile, std::string fragmentShaderFile);

	void initObject(MeshObject& obj);

public:

	Renderer();

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

	~Renderer();

};

#endif


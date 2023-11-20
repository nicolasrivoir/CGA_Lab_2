#ifndef APPLICATION_H
#define APPLICATION_H

#include "Window.h"
#include "Renderer.h"
#include "GUI.h"

#include <memory>

class Application
{

private:

	Window window; // window has to be declared first, it is used to initialize renderer and GUI

	Renderer renderer;

	GUI gui;

	bool running = true;

	int framerateLimit = 60; //fps

	void handleEvent(SDL_Event& e);

	void quit();

public:

	Application();

	void mainLoop();

};

#endif
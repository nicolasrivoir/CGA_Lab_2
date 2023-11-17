#ifndef APPLICATION_H
#define APPLICATION_H

#include "Window.h"
#include "Renderer.h"

#include <memory>

class Application
{

private:

	Window window; // window has to be declared first, it is used to initialize renderer

	Renderer renderer;

public:

	Application();

	void mainLoop();

};

#endif
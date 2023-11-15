#ifndef APPLICATION_H
#define APPLICATION_H

#include "Window.h"
#include "Renderer.h"

#include <memory>

class Application
{

private:

	Renderer renderer;

	Window window;


public:

	void mainLoop();

};

#endif
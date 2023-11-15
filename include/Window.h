#ifndef WINDOW_H
#define WINDOW_H

#include "glad/glad.h"
#include "SDL.h"

class Window
{

private:

	SDL_Window* window;

	SDL_GLContext context;

public:

	Window();

	void swapBuffers();

	~Window();

};

#endif


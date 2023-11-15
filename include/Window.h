#ifndef WINDOW_H
#define WINDOW_H

#include "glad/glad.h"
#include "SDL.h"

class Window
{

public:

	Window();

	void swapBuffers();

	~Window();

private:

	SDL_Window* window;

	SDL_GLContext context;

};

#endif


#include "Window.h"

Window::Window()
{
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) != 0) {
		SDL_Log("Failed to initialize SDL: %s", SDL_GetError());
		return;
	}
	window = SDL_CreateWindow("RealTimeRendering",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		600, 600,
		SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
	context = SDL_GL_CreateContext(window);

	SDL_GL_SetSwapInterval(0);
	gladLoadGLLoader(SDL_GL_GetProcAddress);

	glClearColor(0.8f, 0.9f, 1.0f, 1.0f);
}

void Window::swapBuffers()
{
	SDL_GL_SwapWindow(window);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

Window::~Window()
{
	SDL_GL_DeleteContext(context);
	SDL_DestroyWindow(window);
	SDL_Quit();
}
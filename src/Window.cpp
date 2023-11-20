#include "Window.h"

#include "imgui.h"
#include "backends/imgui_impl_sdl2.h"
#include "backends/imgui_impl_opengl3.h"

Window::Window()
{
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) != 0) {
		SDL_Log("Failed to initialize SDL: %s", SDL_GetError());
		return;
	}
	
	window = SDL_CreateWindow("RealTimeRendering",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		700, 700,
		SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
	context = SDL_GL_CreateContext(window);

	gladLoadGLLoader(SDL_GL_GetProcAddress);

	SDL_GL_SetSwapInterval(0);
	glClearColor(0.8f, 0.9f, 1.0f, 1.0f);

	ImGui::CreateContext();
	ImGui_ImplSDL2_InitForOpenGL(window, context);
	ImGui_ImplOpenGL3_Init("#version 400");

	ImGuiIO& io = ImGui::GetIO();
	io.IniFilename = "./data/gui/imgui.ini";

}

void Window::swapBuffers()
{
	SDL_GL_SwapWindow(window);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Window::resize(unsigned int width, unsigned int height)
{
	glViewport(0, 0, (GLsizei)width, (GLsizei)height);
}

unsigned int Window::getWidth()
{
	int w;
	SDL_GetWindowSize(window, &w, nullptr);
	return w;
}

unsigned int Window::getHeight()
{
	int h;
	SDL_GetWindowSize(window, nullptr, &h);
	return h;
}

Window::~Window()
{
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplSDL2_Shutdown();
	ImGui::DestroyContext();

	SDL_GL_DeleteContext(context);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

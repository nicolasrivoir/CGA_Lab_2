#include "Application.h"

#include "GLTF.h"
#include "timer.h"

#include <Windows.h>
#include "imgui.h"
#include "backends/imgui_impl_sdl2.h"
#include "backends/imgui_impl_opengl3.h"

void Application::handleEvent(SDL_Event& e)
{
	ImGui_ImplSDL2_ProcessEvent(&e);
	switch (e.type) {
	case SDL_QUIT:
		quit();
		break;
	case SDL_WINDOWEVENT:
		if (e.window.event == SDL_WINDOWEVENT_SIZE_CHANGED) {
			window.resize(e.window.data1, e.window.data2);
		}
		break;
	//KEYBOARD EVENTS
	case SDL_KEYDOWN:
		if (e.key.keysym.sym == SDLK_ESCAPE) {
			quit();
		}
	}
}

void Application::quit()
{
	running = false;
}

Application::Application() : renderer(window), gui(window)
{
}

void Application::mainLoop()
{
	auto file = GLTF::loadGLB("data/models/truck.glb");
	Scene scene = GLTF::extractScenes(file)[0];

	Timer* timer = Timer::getInstance();
	timer->reset();

	SDL_Event sdlEvent;  // variable to detect SDL events

	while (running) {
		if (SDL_PollEvent(&sdlEvent))
		{
			handleEvent(sdlEvent);
		}
		timer->tick();
		if (timer->getDeltaTime() >= 1.0f / framerateLimit) {
			scene.update();
			scene.render(renderer);
			gui.shaderPreview(renderer.getShaderProgram(), scene.objects[0]);
			renderer.clear();
			timer->reset();
			Sleep(8);
		}
	}
}

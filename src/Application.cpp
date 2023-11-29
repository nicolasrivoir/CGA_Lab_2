#include "Application.h"

#include "GLTF.h"
#include "timer.h"

#include <Windows.h>
#include "imgui.h"
#include "backends/imgui_impl_sdl2.h"
#include "backends/imgui_impl_opengl3.h"
#include "utils.h"

#include "glm/glm.hpp"
#include "glm/matrix.hpp"
#include <glm/gtc/type_ptr.hpp>

using namespace math;

void Application::handleEvent(SDL_Event& e)
{
	Timer* timer = Timer::getInstance();
	float MOUSE_SENSITIVITY = 10.f;
	float delta_time = timer->getDeltaTime();

	ImGui_ImplSDL2_ProcessEvent(&e);
	switch (e.type) {
	case SDL_MOUSEMOTION:
	
		camera.yaw += float(e.motion.xrel) * MOUSE_SENSITIVITY * delta_time;
		camera.pitch -= float(e.motion.yrel) * MOUSE_SENSITIVITY * delta_time;

		break;
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
		switch (e.key.keysym.sym) {
		case SDLK_ESCAPE:
			quit();
			break;
		case SDLK_m:
			std::cout << "Pitch: " << camera.pitch << "; Yaw: " << camera.yaw << std::endl;
			break;
		case SDLK_o:
			SDL_SetRelativeMouseMode(SDL_TRUE);
			break;
		case SDLK_p:
			SDL_SetRelativeMouseMode(SDL_FALSE);
			break;
		}
	}

	const Uint8* keystate = SDL_GetKeyboardState(NULL);

	float delta_move = 50.f;
	// Inside your main loop, after SDL_PollEvent
	if (keystate[SDL_SCANCODE_W]) {
		// Move forward
		camera.position = camera.position + camera.getForward() * delta_move * delta_time;
		std::cout << "Camera position : " << camera.position.x << "; " << camera.position.y << "; " << camera.position.z << "Pitch: " << camera.pitch << "; Yaw: " << camera.yaw << std::endl;
	}
	if (keystate[SDL_SCANCODE_S]) {
		// Move backward
		camera.position = camera.position - camera.getForward() * delta_move * delta_time;
		//std::cout << "Camera position : " << camera.position.x << "; " << camera.position.y << "; " << camera.position.z << "Pitch: " << camera.pitch << "; Yaw: " << camera.yaw << std::endl;
	}
	if (keystate[SDL_SCANCODE_A]) {
		// Move left
		camera.position = camera.position - camera.getRight() * delta_move * delta_time;
		//std::cout << "Camera position : " << camera.position.x << "; " << camera.position.y << "; " << camera.position.z << "Pitch: " << camera.pitch << "; Yaw: " << camera.yaw << std::endl;
	}
	if (keystate[SDL_SCANCODE_D]) {
		// Move right
		camera.position = camera.position + camera.getRight() * delta_move * delta_time;
		//std::cout << "Camera position : " << camera.position.x << "; " << camera.position.y << "; " << camera.position.z << "Pitch: " << camera.pitch << "; Yaw: " << camera.yaw << std::endl;
	}
	if (keystate[SDL_SCANCODE_SPACE]) {
		// Move up or jump
		camera.position.y += delta_move * delta_time;
		//std::cout << "Camera position : " << camera.position.x << "; " << camera.position.y << "; " << camera.position.z << "Pitch: " << camera.pitch << "; Yaw: " << camera.yaw << std::endl;
	}
	if (keystate[SDL_SCANCODE_LSHIFT]) {
		// Move down or crouch
		camera.position.y -= delta_move * delta_time;
		//std::cout << "Camera position : " << camera.position.x << "; " << camera.position.y << "; " << camera.position.z << "Pitch: " << camera.pitch << "; Yaw: " << camera.yaw << std::endl;
	}
	if (keystate[SDL_SCANCODE_LEFT]) {
		// Rotate or move left
		camera.position.y -= delta_move * delta_time;
		//std::cout << "Camera position : " << camera.position.x << "; " << camera.position.y << "; " << camera.position.z << "Pitch: " << camera.pitch << "; Yaw: " << camera.yaw << std::endl;
	}
	if (keystate[SDL_SCANCODE_RIGHT]) {
		// Rotate or move right
	}
	if (keystate[SDL_SCANCODE_UP]) {
		// Rotate or move up
	}
	if (keystate[SDL_SCANCODE_DOWN]) {
		// Rotate or move down
	}
}

void Application::quit()
{
	running = false;
}

Application::Application() : renderer(window), gui(window)
{
	SDL_SetRelativeMouseMode(SDL_TRUE);
	camera = PlayerCamera(Vector3(0.f,-.7f,-3.8f), 15.5f, 6927.02f);
}

void Application::mainLoop()
{
	auto file = GLTF::loadGLB("data/models/fantasyForest.glb");
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
			renderer.view = camera.updateView();
			//gui.shaderPreview(renderer.getShaderProgram(), scene.objects[0]);
			renderer.clear();
			timer->reset();
			Sleep(8);
		}
	}
}
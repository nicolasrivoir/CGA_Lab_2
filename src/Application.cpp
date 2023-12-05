#include "Application.h"

#include "GLTF.h"
#include "timer.h"

#include <Windows.h>
#include "imgui.h"
#include "backends/imgui_impl_sdl2.h"
#include "backends/imgui_impl_opengl3.h"
#include "utils.h"
#include "Physics.h"

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

	float delta_move = 10000.f;
	bool isCameraMoving = false;
	Vector3 direction;
	// Inside your main loop, after SDL_PollEvent
	if (keystate[SDL_SCANCODE_W]) {
		// Move forward
		direction = direction + camera.getForward() * delta_move * delta_time;
		isCameraMoving = true;
		//std::cout << "Camera position : " << camera.position.x << "; " << camera.position.y << "; " << camera.position.z << "Pitch: " << camera.pitch << "; Yaw: " << camera.yaw << std::endl;
	}
	if (keystate[SDL_SCANCODE_S]) {
		// Move backward
		direction = direction - camera.getForward() * delta_move * delta_time;
		isCameraMoving = true;
		//std::cout << "Camera position : " << camera.position.x << "; " << camera.position.y << "; " << camera.position.z << "Pitch: " << camera.pitch << "; Yaw: " << camera.yaw << std::endl;
	}
	if (keystate[SDL_SCANCODE_A]) {
		// Move left
		camera.position = camera.position - camera.getRight() * delta_move * delta_time;
		direction = direction - camera.getRight() * delta_move * delta_time;
		isCameraMoving = true;
		//std::cout << "Camera position : " << camera.position.x << "; " << camera.position.y << "; " << camera.position.z << "Pitch: " << camera.pitch << "; Yaw: " << camera.yaw << std::endl;
	}
	if (keystate[SDL_SCANCODE_D]) {
		// Move right
		camera.position = camera.position - camera.getRight() * delta_move * delta_time;
		direction = direction + camera.getRight() * delta_move * delta_time;
		isCameraMoving = true;
		//std::cout << "Camera position : " << camera.position.x << "; " << camera.position.y << "; " << camera.position.z << "Pitch: " << camera.pitch << "; Yaw: " << camera.yaw << std::endl;
	}
	if (keystate[SDL_SCANCODE_SPACE]) {
		// Move up or jump
		direction = direction +  Vector3(0, delta_move * delta_time, 0);
		isCameraMoving = true;
		//std::cout << "Camera position : " << camera.position.x << "; " << camera.position.y << "; " << camera.position.z << "Pitch: " << camera.pitch << "; Yaw: " << camera.yaw << std::endl;
	}
	if (keystate[SDL_SCANCODE_LSHIFT]) {
		// Move down or crouch
		direction = direction - Vector3(0, delta_move * delta_time, 0);
		isCameraMoving = true;
		//std::cout << "Camera position : " << camera.position.x << "; " << camera.position.y << "; " << camera.position.z << "Pitch: " << camera.pitch << "; Yaw: " << camera.yaw << std::endl;
	}
	if (keystate[SDL_SCANCODE_LEFT]) {
		// Rotate or move left
		direction = direction - Vector3(0, delta_move * delta_time, 0);
		isCameraMoving = true;
		//std::cout << "Camera position : " << camera.position.x << "; " << camera.position.y << "; " << camera.position.z << "Pitch: " << camera.pitch << "; Yaw: " << camera.yaw << std::endl;
	}

	if (!isCameraMoving) {
		btVector3 velocity(0,0,0);
		camera.fallRigidBody->setLinearVelocity(velocity);
	}
	else {
		btVector3 velocity(direction.x, direction.y, direction.z);
		camera.fallRigidBody->setLinearVelocity(velocity);
	}
}

void Application::quit()
{
	running = false;
}

Application::Application() : renderer(window), gui(window), physics(new Physics()), camera(Vector3(0.f, -.7f, -3.8f), 15.5f, 6927.02f, physics->dynamicsWorld), gravity(false)
{
	SDL_SetRelativeMouseMode(SDL_TRUE);
}

void Application::mainLoop()
{
	auto file = GLTF::loadGLB("data/models/fantasyForest.glb");
	Scene scene = GLTF::extractScenes(file)[0];

	Timer* timer = Timer::getInstance();
	timer->reset();

	Physics* physics = new Physics();
	camera = PlayerCamera(Vector3(0.f, 100.f, -3.8f), 15.5f, 6927.02f, physics->dynamicsWorld);

	SDL_Event sdlEvent;  // variable to detect SDL events


	// Iterate over the objects in the scene
	for (auto& object : scene.objects) {
		// Extract mesh data from each object
		// This is just an example, you'll need to adjust this according to how your Mesh data is structured
		btTriangleMesh* bulletTriMesh = new btTriangleMesh();
		for (auto& mesh : object.meshes) {
			// Create the btTriangleMesh

			// Add triangles to the bulletTriMesh
			for (int i = 0; i < mesh->indices.size(); i += 3) {
				btVector3 vertex0(mesh->positions[mesh->indices[i]].x, mesh->positions[mesh->indices[i]].y, mesh->positions[mesh->indices[i]].z);
				btVector3 vertex1(mesh->positions[mesh->indices[i + 1]].x, mesh->positions[mesh->indices[i + 1]].y, mesh->positions[mesh->indices[i + 1]].z);
				btVector3 vertex2(mesh->positions[mesh->indices[i + 2]].x, mesh->positions[mesh->indices[i + 2]].y, mesh->positions[mesh->indices[i + 2]].z);

				bulletTriMesh->addTriangle(vertex0, vertex1, vertex2);
			}
		}

		// Create the btBvhTriangleMeshShape using the bulletTriMesh
		btBvhTriangleMeshShape* triMeshShape = new btBvhTriangleMeshShape(bulletTriMesh, true);

		// Create a static rigid body and add it to the dynamics world
		btScalar mass = 0;
		btVector3 localInertia(0, 0, 0);
		btDefaultMotionState* motionState = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(0, 0, 0)));
		btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, motionState, triMeshShape, localInertia);
		btRigidBody* meshRigidBody = new btRigidBody(rbInfo);

		physics->dynamicsWorld->addRigidBody(meshRigidBody);
	}


	while (running) {
		if (SDL_PollEvent(&sdlEvent))
		{
			handleEvent(sdlEvent);

		}

		timer->tick();
		float deltaTime = timer->getDeltaTime();
		if (deltaTime >= 1.0f / framerateLimit) {
			physics->Update(deltaTime);
			scene.update();//Now this do nothing
			scene.render(renderer);
			renderer.view = camera.updateView();
			//gui.shaderPreview(renderer.getShaderProgram(), scene.objects[0]);
			renderer.clear();
			timer->reset();
			Sleep(8);
		}
	}
}
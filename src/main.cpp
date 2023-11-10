#include "File.h"
#include "Renderer.h"
#include "Timer.h"
#include "utils.h"

using namespace std;
using namespace geometry;

int main(int argc, char* argv[]) {

	auto file = File::loadGLB("data/models/bosque.glb");
	Scene scene = File::extractScenes(file)[0];

	bool running = true;

	int framerate = 60;

	Timer* timer = Timer::getInstance();
	timer->reset();

	SDL_Event sdlEvent;  // variable to detect SDL events

	while (running) {
		if (SDL_PollEvent(&sdlEvent))
		{
			if (sdlEvent.type == SDL_QUIT) {
				running = false;
			}
		}
		timer->tick();
		if (timer->getDeltaTime() >= 1.0f / framerate) {
			scene.update();
			scene.render();
		}
	}

	return 0;
}
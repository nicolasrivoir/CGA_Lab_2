// World.cpp
#include "World.h"
#include <iostream>
#include <utility>
#include "Utils.h"
#include "Mesh.h"
#include "FileLoader.h"
#include "Renderer.h"
#include "Camara.h"

World::World() : player(Vector3(0, 0, 0), FileLoader::load_OBJ("data/models/Doodler.obj"), new Texture(FileLoader::load_PNG("data/textures/Doodler.png")), -0.6f, 0.7f, 0.2f, -13.0f, 13.0f) {

    //Vector3 player_position = Vector3(0, 0, 0);

    Vector3 camera_eye = Vector3(0, 0, 0);      // Posición de la cámara
    Vector3 camera_center = Vector3(0, 0, 0);   // Punto hacia el que se mira
    Vector3 camera_up = Vector3(0, 1, 0);       // Dirección "arriba"

    //Mesh player_mesh = FileLoader::load_OBJ("Models/Doodler.obj");
    platform_mesh = FileLoader::load_OBJ("data/models/Platform.obj");

    //Texture* player_texture = new Texture(FileLoader::load_PNG("Textures/Doodler.png"));
    platform_texture = new Texture(FileLoader::load_PNG("data/textures/Platform.png"));

    boundLeft = -10; // starting value
    boundRight= 10;   // stopping value
    double increment = 2.5f;  // increment value

    platformsInterspace = 5;
    heightTolerance = 27;
    cameraShiftDown = 5;
    platformVisibilityDistance = 50;
    gameIsPaused = false;
    bounceTolerance = 1;
    camara.cameraMode = NORMAL;
    camara.cameraSmoothness = 1.f;
    camara.lookingPoint = Vector3(0.f, 0.f, -50.f);
    camara.up = Vector3(0, 1, 0);
    camara.center = Vector3(0, 0, 0);
    wireframeActivated = false;
    texturesActivated = true;
    smoothShadingActivated = true;

    for (double x = boundLeft; x <= boundRight; x += increment) {
        addPlatform(Vector2(x, 0));
    }

    // Seed the random number generator with the current time
    std::srand(static_cast<unsigned int>(std::time(nullptr)));

}

void World::addPlatform(Vector2 position) {
    Vector3 platform_position = Vector3(position.x, position.y, 0);
    Platform platform = Platform(platform_position, platform_mesh, platform_texture);
    platforms.push_back(platform);
}

bool World::isCollision(std::pair<Vector3, Vector3> playerBox, std::pair<Vector3, Vector3> platformBox, Vector3 increment) {

    // Calculate the new position of the player's box after making the move
    Vector3 newPlayerBoxMin = playerBox.first + increment;
    Vector3 newPlayerBoxMax = playerBox.second + increment;
    std::pair<Vector3, Vector3> newPlayerBox = std::make_pair(newPlayerBoxMin, newPlayerBoxMax);

    // Check if the new player box collides with the platform box
    if (newPlayerBox.second.x < platformBox.first.x || newPlayerBox.first.x > platformBox.second.x)
        return false;
    if (newPlayerBox.second.y < platformBox.first.y || newPlayerBox.first.y > platformBox.second.y)
        return false;
    if (newPlayerBox.second.z < platformBox.first.z || newPlayerBox.first.z > platformBox.second.z)
        return false;

    // If all tests pass, then there is a collision
    return playerBox.first.y > platformBox.first.y - bounceTolerance;
    //return true;
}

void World::toggle_nightmode()
{
    //Renderer renderer = *Renderer::get_instance();
    is_nighttime = !is_nighttime;
    //if (is_nighttime) {
    //    renderer.light(0, Vector3(0, maxHeight + 50, 50), Vector3(0.0f, 0.0f, 1));
    //    renderer.light(1, Vector3(0, maxHeight + 50, 50), Vector3(0.0f, 0.0f, 1));
    //}
    //else {
    //    renderer.light(0, Vector3(0, maxHeight + 50, 50), Vector3(1, 1, 1));
    //    renderer.light(1, Vector3(0, maxHeight + 50, 50), Vector3(1, 1, 1));
    //}
}

void World::update() {
    manageEvents();
    
    Vector3 position = player.getPosition();
    Vector3 playernextpos = player.getNextPosition();
    Vector3 increment = playernextpos - position;

    pair<Vector3, Vector3> playerBox = player.getColideBox();

    if (playernextpos.y < maxHeight - heightTolerance) {
        std::cout << "Game Over" << std::endl;
        gameOver = true;
    }

    // get the next position of the player

    Vector3 newplayerboxmin = playerBox.first + increment;
    Vector3 newplayerboxmax = playerBox.second + increment;
    std::pair<Vector3, Vector3> newplayerbox = std::make_pair(newplayerboxmin, newplayerboxmax);

    float bigBox_min_x = std::min(playerBox.first.x, newplayerbox.first.x);
    float bigBox_min_y = std::min(playerBox.first.y, newplayerbox.first.y);
    float bigBox_min_z = std::min(playerBox.first.z, newplayerbox.first.z);

    float bigBox_max_x = std::max(playerBox.second.x, newplayerbox.second.x);
    float bigBox_max_y = std::max(playerBox.second.y, newplayerbox.second.y);
    float bigBox_max_z = std::max(playerBox.second.z, newplayerbox.second.z);

    newplayerbox = std::make_pair(Vector3(bigBox_min_x, bigBox_min_y, bigBox_min_z), Vector3(bigBox_max_x, bigBox_max_y, bigBox_max_z));

    if (increment.y < 0) {

        // iterate through all platforms to check for collisions
        for (Platform platform : platforms) { // assuming 'platforms' is a collection of some sort

            std::pair<Vector3, Vector3> platformBox = platform.getColideBox();

            // check for collisions between the player and the platform
            if (isCollision(newplayerbox, platformBox, Vector3(0, 0, 0))) {
                // if there is a collision, call player.jump()
                std::cout << "Jump" << std::endl;
                player.jump();
                draw();
                return;
            }
        }
    }

    //std::cout << "Update Position" << std::endl;
    // if there are no collisions -> update position
    player.updatePosition();
    if (score < player.position.y) {
		score = player.position.y;
	}

    //Draw platforms and player (...etc)
    draw();

    if (position.y > maxHeight) {
        maxHeight = position.y;
        minHeight = maxHeight - heightTolerance;
        updatePlatforms();
        updateLight();
        updateCamara();

    }
}

void World::updatePlatforms() {

    platforms.erase(std::remove_if(platforms.begin(), platforms.end(), [&](const Platform& platform) {
        return platform.position.y < minHeight;
    }), platforms.end());

    float first_platform = platforms.back().position.y + platformsInterspace;

    for (double y = first_platform; y <= minHeight + platformVisibilityDistance; y += platformsInterspace) {
        double random = static_cast<double>(std::rand()) / RAND_MAX;
        float x = random * boundLeft + (1 - random) * boundRight;
        //std::cout << "rand : " << x << std::endl;
        addPlatform(Vector2(x, y));
    }

}

void World::draw() {
    for (Platform& platform : platforms) {
        platform.draw();
    }
    if (camara.cameraMode == NORMAL) {
        player.draw_on_top();
    }
    else {
        player.draw();
    }
    

    Renderer renderer = *Renderer::get_instance();

}

void World::updateLight() {

    Vector3 playerPosition = player.getPosition();
    Renderer renderer = *Renderer::get_instance();
    if (is_nighttime) {
        glClearColor(0.1f, 0.0f, 0.5f, 1.0f);
        renderer.light(0, Vector3(0, maxHeight + 50, 50), Vector3(0.6f, 0.6f, 1));
        renderer.light(1, Vector3(0, maxHeight + -50, 50), Vector3(0.f, 0.f, 1));
    }
    else {
        glClearColor(1.0f,0.9f,0.9f,1.0f);
        renderer.light(0, Vector3(0, maxHeight + 50, 50), Vector3(1, 1, 1));
        renderer.light(1, Vector3(0, maxHeight + -50, 50), Vector3(1, 1, 1));
    }
}

void World::updateCamara() {
    //Vector3 playerPosition = player.getPosition();
    switch (camara.cameraMode) {
    case NORMAL:
        camara.lookingPoint = Vector3(0.f, 0.f, -50.f);
        camara.eye = Vector3(0, maxHeight - cameraShiftDown, 50);     // Posición de la cámara
        //camara.center = Vector3(0, maxHeight - cameraShiftDown, 0);   // Punto hacia el que se mira
        camara.update(Vector3(0, maxHeight - cameraShiftDown, 0));
        break;
    case FREE_MODE:
        camara.update();
        break;
    case PLAYER_CENTERED:
        camara.update(player.position.y);
        camara.update();
        break;
    }

    
}

void World::rotateCamera(float x, float y) {
    switch (camara.cameraMode) {
    case NORMAL:
        break;
    case FREE_MODE:
        camara.rotate(x, y);
        break;
    case PLAYER_CENTERED:
        camara.rotateAroundCharacter(player.getPosition(), camara.eye, y, x);
        break;
    }
}

void World::manageEvents() {

    const Uint8* keyState = SDL_GetKeyboardState(NULL);

    SDL_Event evento;
    Timer* timer = Timer::getInstance();
    while (SDL_PollEvent(&evento)) {
        switch (evento.type) {
        case SDL_QUIT:
            gameOver = true;
        case SDL_MOUSEMOTION:
            rotateCamera(-evento.motion.yrel, evento.motion.xrel);
            break;
        case SDL_KEYDOWN:
            if (evento.key.repeat == 0) { // check if this is a repeated keydown event
                switch (evento.key.keysym.sym) {
                case SDLK_LEFT:
                    if (!gameIsPaused) {
                        std::cout << "Left 1" << std::endl;
                        player.moveLeft();
                    }
                    break;
                case SDLK_RIGHT:
                    if (!gameIsPaused) {
                        std::cout << "Right 1" << std::endl;
                        player.moveRight();
                    }
                    break;
                case SDLK_p:
                    gameIsPaused = !gameIsPaused;
                    timer->reset();
                    if (gameIsPaused) {
						timer->pause();
					}
                    else {
						timer->resume();
					}
                    break;
                case SDLK_q:
                    gameOver = true;
                case SDLK_v:
                    camara.getNextCameraMode();
                    if (camara.cameraMode != NORMAL) {
                        SDL_SetRelativeMouseMode(SDL_TRUE);
                    }
                    else {
                        SDL_SetRelativeMouseMode(SDL_FALSE);
                    }
                    std::cout << "Camera Mode : " << camara.cameraMode << std::endl;
                    break;
                case SDLK_UP:
                    timer->speed += .1f;
                    std::cout << "Speed : " << Timer::getInstance()->speed << std::endl;
                    break;
                case SDLK_DOWN:{
                    float speed = timer->getSpeed() - .1f;
                    timer->speed = std::max(0.f, speed);
                    std::cout << "Speed : " << Timer::getInstance()->speed << std::endl;
                    break;
                }
                case SDLK_a:
                    camara.move(0., -1., 0.);
                    break;
                case SDLK_d:
                    camara.move(0., 1., 0.);
                    break;
                case SDLK_w:
                    camara.move(1., 0., 0.);
                    break;
                case SDLK_s:
                    camara.move(-1., 0., 0.);
                    break;
                case SDLK_SPACE:
                    camara.move(0., 0., 1.);
                    break;
                case SDLK_z:
                    camara.move(0., 0., -1.);
                    break;
                case SDLK_r: {
                    wireframeActivated = !wireframeActivated;
                    Renderer::get_instance()->enable_wireframes(wireframeActivated);
                    std::cout << "Wireframe : " << wireframeActivated << std::endl;
                    break;
                }
                case SDLK_t: {
                    texturesActivated = !texturesActivated;
                    Renderer::get_instance()->enable_textures(texturesActivated);
                    std::cout << "Textures : " << texturesActivated << std::endl;
                    break;
                }
                case SDLK_y: {
                    smoothShadingActivated = !smoothShadingActivated;
                    std::cout << "Smooth Shading : " << smoothShadingActivated << std::endl;
                    Renderer::get_instance()->smooth_shading(smoothShadingActivated);
                    break;
                }
                case SDLK_u: {
                    toggle_nightmode();
                    updateLight();
                    std::cout << "Nightmode : " << is_nighttime << std::endl;
                    break;
                }
                }

            }
            break;
        case SDL_KEYUP:
            switch (evento.key.keysym.sym) {
            case SDLK_ESCAPE:
                std::cout << "Escape" << std::endl;
                break;
            case SDLK_LEFT:
                if (!gameIsPaused) {
                    std::cout << "Left 2" << std::endl;
                    player.moveLeft();
                }
                break;
            case SDLK_RIGHT:
                if (!gameIsPaused) {
                    std::cout << "Right 2" << std::endl;
                    player.moveRight();
                }
                break;
            }
        }
    }
    if (!gameIsPaused) {

        // check for key states outside of event polling
        if (keyState[SDL_SCANCODE_LEFT]) {
            player.moveLeft();
        }
        if (keyState[SDL_SCANCODE_RIGHT]) {
            player.moveRight();
        }
        if (!gameIsPaused) {

            // check for key states outside of event polling
            if (keyState[SDL_SCANCODE_LEFT]) {
                player.moveLeft();
            }
            if (keyState[SDL_SCANCODE_RIGHT]) {
                player.moveRight();
            }

            if (keyState[SDL_SCANCODE_W]) {
                camara.move(1., 0., 0.);
            }
            if (keyState[SDL_SCANCODE_S]) {
                camara.move(-1., 0., 0.);
            }
            if (keyState[SDL_SCANCODE_A]) {
                camara.move(0., -1., 0.);
            }
            if (keyState[SDL_SCANCODE_D]) {
                camara.move(0., 1., 0.);
            }
            if (keyState[SDL_SCANCODE_SPACE]) {
                camara.move(0., 0., 1.);
            }
            if (keyState[SDL_SCANCODE_LSHIFT]) {
                camara.move(0., 0., -1.);
            }
        }
        if (keyState[SDL_SCANCODE_SPACE]) {
            camara.move(0., 0., 1.);
        }
        if (keyState[SDL_SCANCODE_LSHIFT]) {
            camara.move(0., 0., -1.);
        }
    }
 
}

string World::getCameraMode() {
    switch (camara.cameraMode) {
	case NORMAL:
		return "NORMAL";
    case PLAYER_CENTERED:
		return "PLAYER FOCUS";
    case FREE_MODE:
        return "FREE MODE";
	}
}

// World.h
#ifndef WORLD_H
#define WORLD_H

#include <string>
#include <vector>
#include "Platform.h"
#include "Utils.h"
#include "Player.h"
#include "Timer.h"
#include "Camara.h"
#include "Hud.h"

#include <iostream>

using namespace std;
using namespace math;
using namespace cam;

class World {
public:

    Mesh platform_mesh;

    Texture* platform_texture;

    World();

    void update();

    void addPlatform(Vector2 position);

    void manageEvents();

    void updateCamara();

    void updateLight();

    void updatePlatforms();

    void rotateCamera(float x, float y);

    //maxima altura alcanzada
    double maxHeight;
    double heightTolerance;
    double minHeight;// = maxHeight - heightTolerance
    double cameraShiftDown;
    double platformVisibilityDistance;
    double boundLeft;
    double boundRight;

    float bounceTolerance;

    bool gameOver;
    bool wireframeActivated;
    bool texturesActivated;

    //Espacio entre las plataformas
    double platformsInterspace;

    void addPlatform(double height, double x_position);

    //std::vector<Plataforma> platforms;
    std::vector<Platform> platforms;

    //Monstruos, Agujeros, Powerups, Plataformas
    std::vector<double> objetosInteractuables;

    // calcular Collit
    void calculateCollisions(); // Retorna lista de Objetos

    //For each object in the world -> object.draw()
    void draw();

    Player player;
 
    double fps;

    double gameIsPaused;

    bool wireFrameModeActivated;

    bool smoothShadingActivated;

    //Camara camara;
    cam::Camara camara;

    Hud* hud;

    //Light light;
    float light;

    void toggle_nightmode();

    bool is_nighttime = false;

    string getCameraMode();

private:
    bool isCollision(std::pair<Vector3, Vector3> playerBox, std::pair<Vector3, Vector3> platformBox, Vector3 increment);

    float score = 0;
};

#endif // WORLD_H

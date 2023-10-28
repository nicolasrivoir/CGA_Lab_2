// Camara.h
#ifndef CAMARA_H
#define CAMARA_H

#include <utility>
#include "Utils.h"
#include <iostream>

using namespace std;
using namespace math;

namespace cam {

    enum ProyectionType {
        PERSPECTIVE,    // 0
        ISOMETRIC,      // 1
    };

    enum CameraMode {
        NORMAL,
        PLAYER_CENTERED,
        FREE_MODE,
        ENUM_SIZE  // This will always be the last value, representing the size of the enum
    };



    class Camara {
    public:
        Camara();

        void update(Vector3 position);
        void update();
        void update(float y);

        ProyectionType proyectionType;

        void getNextCameraMode();

        void rotate(float x, float y);

        void move(float x, float y, float z);

        CameraMode cameraMode;

        Vector3 eye;

        Vector3 center;

        Vector3 up;

        Vector3 lookingPoint;

        void rotateAroundCharacter(Vector3 characterPos, Vector3 cameraPos, float x, float y);

        float maxDistance;
        float mindistance;
        float cameraSmoothness;

    };
};
#endif // CAMARA_H
// Camara.h
#ifndef PLAYERCAMERA_H
#define PLAYERCAMERA_H

#include <utility>
#include "Utils.h"
#include <iostream>

#include "glm/glm.hpp"
#include "glm/matrix.hpp"
#include <glm/gtc/type_ptr.hpp>

#include "bullet/btBulletDynamicsCommon.h"

using namespace::math;

class PlayerCamera {
public:
 
    //coordenadas esféricas
    float pitch;
    float yaw;
    Vector3 position;

    PlayerCamera();
    PlayerCamera(Vector3 position, float pitch, float yaw, btDiscreteDynamicsWorld* dynamicsWorld);

    glm::mat4 updateView();
    Vector3 getForward();
    Vector3 getRight();

    //phyisics
    btDiscreteDynamicsWorld* dynamicsWorld;
    btRigidBody* fallRigidBody;

};

#endif // PLAYER_CAMERA_H
#ifndef PLAYER_H
#define PLAYER_H

#include "Object.h"
#include <iostream>
#include "Timer.h"

using namespace std;

class Player : public Object {
private:
    float gravity;
    float horizontalSpeed;
    float verticalSpeed;
    float jumpSpeed; // The speed that will be added to the vertical speed when the player jumps
    float boundLeft;
    float boundRight;

    bool facing_left = false;

    float scale_y = 1.0f;

    float jumpduration;

public:
    Player();
    Player(Vector3 position, const Mesh& mesh, Texture* texture, float gravity, float jumpSpeed, float horizontalSpeed, float boundLeft, float boundRight);
    void jump();
    bool isFalling();
    Vector3 getNextPosition();
    void updatePosition(); // Move the player to the next position depending on the gravity and speed
    void moveLeft();
    void moveRight();
    void draw();
    void draw_on_top();
};

#endif

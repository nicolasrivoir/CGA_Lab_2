#include "Player.h"
#include "Timer.h"
#include "Math.h";
#include "Renderer.h"

using namespace std;
using namespace math;

Player::Player(){}

Player::Player(Vector3 position, const Mesh& mesh, Texture* texture, float gravity, float jumpSpeed, float horizontalSpeed, float boundLeft, float boundRight) : Object(position, mesh, texture) {
    this->gravity = gravity;
    this->jumpSpeed = jumpSpeed;
    this->horizontalSpeed = 0;
    this->verticalSpeed = 0;
    this->boundLeft = boundLeft;
    this->boundRight = boundRight;
    this->horizontalSpeed = horizontalSpeed;
}

void Player::jump() {
    this->verticalSpeed = jumpSpeed;
    jumpduration = 0.0f;
}

bool Player::isFalling() {
    return this->verticalSpeed < 0;
}

Vector3 Player::getNextPosition() {
    const float deltaTime = Timer::getInstance()->getWorldDeltaTime();
    this->verticalSpeed += -.01f *60.f * deltaTime;

    Vector3 nextPosition = this->getPosition();

    nextPosition.y += this->verticalSpeed *60.f * deltaTime;
    return nextPosition;
}

void Player::updatePosition() {
    this->setPosition(this->getNextPosition());
    float deltaTime = Timer::getInstance()->getDeltaTime();
    jumpduration += deltaTime;
    if (jumpduration < 0.20f) {
        scale_y -= 0.03f;
    }
    else if (jumpduration < 0.40f) {
        scale_y += 0.04f;
    }
    else if (jumpduration < 0.5f) {
        scale_y -= 0.02f;
    }
    else {
        scale_y = 1.0f;
    }
}

void Player::moveLeft() {
    facing_left = true;
    float deltaTime = Timer::getInstance()->getWorldDeltaTime();
    float newX = position.x - horizontalSpeed *60 * deltaTime;
    this->position.x = clamped_interpolation(boundLeft, newX, boundRight);
    //std::cout << "newX : " << newX << " -> " << this->position.x << " br: " << boundRight << " bl: " << boundLeft << std::endl;
}

void Player::moveRight() {
    facing_left = false;
    float deltaTime = Timer::getInstance()->getWorldDeltaTime();
    float newX = position.x + horizontalSpeed *60 * deltaTime;
    this->position.x = clamped_interpolation(boundLeft, newX, boundRight);
    //std::cout << "newX : " << newX << " -> "  << this->position.x << " br: " << boundRight << " bl: " << boundLeft << std::endl;
}

void Player::draw()
{
    Vector3 position = this->getPosition();
    Renderer::get_instance()->draw(position, mesh, texture, facing_left, scale_y);
}

void Player::draw_on_top()
{
    Vector3 position = this->getPosition();
    Renderer::get_instance()->draw_on_top(position, mesh, texture, facing_left, scale_y);
}

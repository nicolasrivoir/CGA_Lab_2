#include "Platform.h"

Platform::Platform() {}
Platform::Platform(const Vector3 position, const Mesh& mesh, Texture* texture) : Object(position, mesh, texture) {}

//Platform::Platform(Vector3 position, const Mesh& mesh, Texture* texture, float gravity, float jumpSpeed, float horizontalSpeed, float boundLeft, float boundRight) : Object(position, mesh, texture) {
//    this->gravity = gravity;
//    this->jumpSpeed = jumpSpeed;
//    this->horizontalSpeed = 0;
//    this->verticalSpeed = 0;
//    this->boundLeft = boundLeft;
//    this->boundRight = boundRight;
//    this->horizontalSpeed = horizontalSpeed;
//}
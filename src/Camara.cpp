//#include "Camara.h"
//#include "Utils.h"
//
//#include "Renderer.h"
//
//#include "Timer.h"
//
//using namespace cam;
//using namespace std;
//using namespace math;
//
//Camara::Camara(){};
//
//void Camara::update(Vector3 position) {
//
//    center = eye + lookingPoint;
//
//	eye = Vector3(0, position.y, 50);     // Posición de la cámara
//	center = Vector3(0, position.y, 0);   // Punto hacia el que se mira
//	up = Vector3(0, 1, 0);                // Dirección "arriba"
//
//	update();
//
//}
//
//void Camara::update(float y) {
//    eye.y = y;
//    center = eye + lookingPoint;
//}
//
//void Camara::update() {
//
//    lookAt(eye.x, eye.y, eye.z, center.x, center.y, center.z, up.x, up.y, up.z);
//}
//
//void Camara::getNextCameraMode() {
//    // If the current mode is the last actual mode in the enum, loop back to the first mode.
//    // Otherwise, just go to the next mode.
//    if (cameraMode == FREE_MODE) {
//        cameraMode = NORMAL;
//    }
//    else {
//        cameraMode = static_cast<CameraMode>(static_cast<int>(cameraMode) + 1);
//    }
//}
//
//void Camara::move(float x, float y, float z) {
//    Vector3 right_v = nicoDotProduct(lookingPoint, up);
//    Vector3 up_v = normalize(up);
//    Vector3 front_v = normalize(lookingPoint);
//    
//
//    float deltaTime = Timer::getInstance()->getWorldDeltaTime();
//    eye = eye + front_v * cameraSmoothness * x * deltaTime * 60.f;
//    eye = eye + right_v * cameraSmoothness * y * deltaTime * 60.f;
//    eye = eye + up_v * cameraSmoothness * z * deltaTime * 60.f;
//    center = eye + lookingPoint;
//
//    //Vector3 right = math::dotProduct(up,center);
//    //eye = eye + right*y;
//}
//
////void Camara::rotate(float x, float y) {
//    //center = center + Vector3(x,y,0);
////}
//void Camara::rotate(float xRotation, float yRotation) {
//
//    float deltaTime = Timer::getInstance()->getWorldDeltaTime();
//
//    xRotation *= deltaTime * 60.f;
//    yRotation *= deltaTime * 60.f;
//
//    // Convert degrees to radians
//
//    if (eye.z < 0) {
//        xRotation *= -1;
//    }
//
//    float xRad = xRotation * M_PI / 180.0f;
//    float yRad = yRotation * M_PI / 180.0f;
//
//    // Rotate around y-axis
//    float newX = lookingPoint.x * cos(yRad) - lookingPoint.z * sin(yRad);
//    float newZ = lookingPoint.x * sin(yRad) + lookingPoint.z * cos(yRad);
//
//    // Rotate around x-axis
//    float newY = lookingPoint.y * cos(xRad) - newZ * sin(xRad);
//    newZ = lookingPoint.y * sin(xRad) + newZ * cos(xRad);
//
//    lookingPoint = Vector3(newX, newY, newZ);
//    center = eye + lookingPoint;
//
//    std::cout << "Eye X : " << eye.x << " Y : " << eye.y << " Z : " << eye.z << std::endl;
//}
//
//
//void Camara::lookAt(float eyeX, float eyeY, float eyeZ, float centerX, float centerY, float centerZ, float upX, float upY, float upZ) {
//    Vector3 right, up, forward;
//    forward = -normalize(Vector3(centerX - eyeX, centerY - eyeY, centerZ - eyeZ));
//    up = Vector3(upX, upY, upZ);
//    right = normalize(cross_product(up, forward));
//    up = normalize(cross_product(forward, right));
//
//    const GLfloat mat[16] =
//    { right.x, up.x,   forward.x,   0,
//     right.y,  up.y,   forward.y,   0,
//     right.z,  up.z,   forward.z,   0,
//     0,     0,      0,      1 };
//    glMultMatrixf(mat);
//    glTranslated(-eyeX, -eyeY, -eyeZ);
//}
//
//
//
//void Camara::rotateAroundCharacter(Vector3 characterPos, Vector3 cameraPos, float xRotation, float yRotation) {
//    Vector3 characterToCamera = cameraPos - characterPos;
//
//    // Convert rotations from degrees to radians
//    float xRotationRad = xRotation * (M_PI / 180.0f);
//    float yRotationRad = yRotation * (M_PI / 180.0f);
//
//    // Rotate horizontally around the character
//    Vector3 rotated;
//    rotated.x = characterToCamera.x * cos(xRotationRad) - characterToCamera.z * sin(xRotationRad);
//    rotated.y = characterToCamera.y;
//    rotated.z = characterToCamera.x * sin(xRotationRad) + characterToCamera.z * cos(xRotationRad);
//
//    cameraPos = characterPos + rotated;
//
//    eye = cameraPos;
//    lookingPoint = normalize(characterPos - cameraPos);
//    center = eye + lookingPoint;
//}
//
//
//

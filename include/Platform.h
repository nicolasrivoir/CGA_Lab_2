#ifndef PLATFORM_H
#define PLATFORM_H

#include "Object.h"
#include "Mesh.h"
#include "Utils.h"
#include <iostream>

class Platform : public Object {
public:
    Platform();
    Platform(const Vector3 position, const Mesh& mesh, Texture* texture);
};

#endif // PLATFORM_H

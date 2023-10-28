#ifndef OBJECT_H
#define OBJECT_H

#include <iostream>
#include "SDL.h"
#include "SDL_opengl.h"
#include <GL/glu.h>
#include "utils.h"
#include "Mesh.h"
#include "Texture.h"

using namespace std;
using namespace math;

class Object {
    public:
        Vector3 position;
        Mesh mesh;
        Texture* texture;
        pair<Vector3, Vector3> colideBox; // Max and min point of the colide box. To get the real colide box, add the position to the points

    //public:
        Object();
        Object(const Vector3 position, const Mesh &mesh, Texture* texture = nullptr);
        Vector3 getPosition();
        void setPosition(Vector3 position);
        pair<Vector3, Vector3> getColideBox();
	    void draw();
};

#endif

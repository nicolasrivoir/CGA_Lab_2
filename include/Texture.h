#ifndef TEXTURE_H
#define TEXTURE_H

#include "SDL.h"
#include "SDL_opengl.h"
#include "FreeImage.h"
#include <GL/glu.h>

struct Texture {
	const unsigned int id;
	const BYTE* data;
	const unsigned int width;
	const unsigned int height;
};

#endif
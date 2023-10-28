#ifndef FILE_LOADER_H
#define FILE_LOADER_H

#include "SDL.h"
#include "SDL_opengl.h"
#include <GL/glu.h>

#include "utils.h"
#include "Mesh.h"
#include "Texture.h"

using namespace math;

class FileLoader
{
public:

	/*
	 * Returns a 'Mesh' object with the data specified in a wavefront .obj file located at 'path'.
	 * In case of failure throws 'std::runtime_error'.
	 */
	static Mesh load_OBJ(std::string path);

	/* 
	 * Returns a 'Texture' object with the data specified in a .png file located at 'path'.
	 */
	static Texture load_PNG(std::string path);

};

#endif
#ifndef RENDERER_H
#define RENDERER_H

#include "glad/glad.h"
#include "SDL.h"
#include "SDL_opengl.h"

#include "utils.h"
#include "Mesh.h"
#include "Texture.h"

using namespace math;

class Renderer
{
private:

	static Renderer* instance;

	static SDL_Window* window;

	static SDL_GLContext context;

	static bool smooth_shading_enabled;

	static bool textures_enabled;

	static bool wireframe_enabled;

	Renderer();

public:

	static Renderer* get_instance();

	static void init(int* argcp, char** argv);

	static void setPerspective(float yFov, float aspectRatio, float zNear, float zFar);

	void smooth_shading(bool enabled = true);

	void enable_textures(bool enabled = true);

	void enable_wireframes(bool enabled = true);

	void light(int index, const Vector3 &pos, const Vector3 &color);

	void enable_nightmode(bool enabled = true);

	void draw(const Vector3 position, const Mesh &mesh, Texture* texture, bool mirrored = false, float scale = 1.0f);

	/*
	* Clears depth-buffer and draws object on top
	*/
	void draw_on_top(const Vector3 position, const Mesh &mesh, Texture* texture, bool mirrored = false, float scale = 1.0f);

	void clear();

	void free();

	bool is_wireframe_enabled();

	bool is_smooth_shading_enabled();

	bool are_textures_enabled();

};

#endif


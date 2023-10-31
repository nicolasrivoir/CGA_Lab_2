#include "Renderer.h"

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

Renderer* Renderer::instance = nullptr;

SDL_Window* Renderer::window = nullptr;

SDL_GLContext Renderer::context = nullptr;

bool Renderer::smooth_shading_enabled = true;

bool Renderer::textures_enabled = true;

bool Renderer::wireframe_enabled = false;

Renderer::Renderer() {}

void Renderer::init(int* argcp, char** argv)
{
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) != 0) {
		SDL_Log("Failed to initialize SDL: %s", SDL_GetError());
		return;
	}
	window = SDL_CreateWindow("RealTimeRendering",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
	context = SDL_GL_CreateContext(window);

	SDL_GL_SetSwapInterval(0);
	gladLoadGLLoader(SDL_GL_GetProcAddress);

	glLoadIdentity();
	glEnable(GL_CULL_FACE);
	glEnable(GL_LIGHTING);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

	glMatrixMode(GL_PROJECTION);

	glClearColor(1.0f, 0.9f, 0.9f, 1.0f);

	setPerspective(45, 640 / 480.f, 0.1, 100);
	glEnable(GL_DEPTH_TEST);
	glMatrixMode(GL_MODELVIEW);
}

void Renderer::setPerspective(float fovY, float aspect, float zNear, float zFar)
{
	GLdouble fW, fH;

	//fH = tan( (fovY / 2) / 180 * pi ) * zNear;
	fH = tan(fovY / 360 * M_PI) * zNear;
	fW = fH * aspect;

	glFrustum(-fW, fW, -fH, fH, zNear, zFar);
}

Renderer* Renderer::get_instance()
{
	if (instance == nullptr) {
		instance = new Renderer();
	}
	return instance;
}

void Renderer::smooth_shading(bool enabled)
{
	if (enabled) {
		glShadeModel(GL_SMOOTH);
	}
	else {
		glShadeModel(GL_FLAT);
	}
	smooth_shading_enabled = enabled;
}

void Renderer::enable_textures(bool enabled)
{
	textures_enabled = enabled;
}

void Renderer::enable_wireframes(bool enabled)
{
	wireframe_enabled = enabled;
	int mode = enabled ? GL_LINE : GL_FILL;
	glPolygonMode(GL_FRONT_AND_BACK, mode);
}

void Renderer::light(int index, const Vector3& pos, const Vector3& color)
{
	int selected_light = GL_LIGHT0 + (index % 8);
	GLfloat luz_posicion[4] = { pos.x, pos.y, pos.z, 1 };
	GLfloat colorLuz[4] = { color.x, color.y, color.z, 1 };
	GLfloat luz_direccion[4] = { 1.f, 0.f, 0.f, 1.f };
	glEnable(selected_light);
	glLightfv(selected_light, GL_POSITION, luz_posicion);
	glLightfv(selected_light, GL_DIFFUSE, colorLuz);
	glLightfv(selected_light, GL_SPOT_DIRECTION, colorLuz);

}

void Renderer::draw(const Vector3 position, const Mesh& mesh, Texture* texture, bool mirrored, float scale) {
	if (textures_enabled && texture != nullptr) {
		glBindTexture(GL_TEXTURE_2D, texture->id);
		glEnable(GL_TEXTURE_2D);
	}
	else {
		glBindTexture(GL_TEXTURE_2D, 0);
		glDisable(GL_TEXTURE_2D);
		glEnable(GL_COLOR_MATERIAL);
		glColor3f(0.6f, 0.6f, 0.6f);
	}
	float degrees = mirrored ? 180.0f : 0.0f;
	glPushMatrix();
	glTranslatef(position.x, position.y, position.z);
	glScalef(1.0f, scale, 1.0f);
	glRotatef(degrees, 0.0f, 1.0f, 0.0f);
	glBegin(GL_TRIANGLES);
	for (unsigned int i = 0; i < mesh.vertices.size(); i++) {
		Vector3 vertex = mesh.vertices[i];
		Vector2 texture_map = mesh.texture_map[i];
		Vector3 normal = mesh.normals[i];
		glNormal3f(normal.x, normal.y, normal.z);
		glTexCoord2f(texture_map.x, texture_map.y);
		glVertex3f(vertex.x, vertex.y, vertex.z);
	}
	glEnd();
	glPopMatrix();
}

void Renderer::draw_on_top(const Vector3 position, const Mesh& mesh, Texture* texture, bool mirrored, float scale) {
	glClear(GL_DEPTH_BUFFER_BIT);
	draw(position, mesh, texture, mirrored, scale);
}

void Renderer::clear()
{
	SDL_GL_SwapWindow(window);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::free() {
	SDL_GL_DeleteContext(context);
	SDL_DestroyWindow(window);
	SDL_Quit();
	delete instance;
}

bool Renderer::is_wireframe_enabled()
{
	return wireframe_enabled;
}

bool Renderer::are_textures_enabled()
{
	return textures_enabled;
}

bool Renderer::is_smooth_shading_enabled()
{
	return smooth_shading_enabled;
}
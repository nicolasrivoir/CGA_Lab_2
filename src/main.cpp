#include "Renderer.h"
#include "World.h"
#include "Timer.h"

using namespace std;

int main(int argc, char *argv[]) {

	Renderer renderer = *Renderer::get_instance();
	renderer.init(&argc, argv);

	World world = World();

	bool fin = false;
	bool rotate = false;

	Vector3 player_position = Vector3(0, 2, 0);
	Vector3 platform_position = Vector3(0, 0, 0);

	//FIN INICIALIZACION

	int framerate = 60;

	Timer* timer = Timer::getInstance();
	timer->reset();
	 
	//LOOP PRINCIPAL
	do{
		if (world.gameOver) {
			break;
		}

		if (world.gameIsPaused) {
			glLoadIdentity();
			renderer.clear();
			world.manageEvents();
			continue;
		}

		timer->tick();
		if (timer->getDeltaTime() >= 1.0f / framerate) {
			timer->reset();

			glLoadIdentity();

			world.updateCamara();

			world.update();

			renderer.clear();

		}
	} while (!fin);

	renderer.free();

	return 0;
}


/////////////////////////////////////////////
//#include <windows.h>
//
//#include <glad/glad.h>
//#include "SDL.h"
//#include "SDL_opengl.h"
//#include "FreeImage.h"
//
//#include <glm/glm.hpp>
//#include <glm/gtc/matrix_transform.hpp>
//#include <glm/gtc/type_ptr.hpp>
//
//#include <iostream>
//#include <fstream>
//#include "File.h"
//
//using namespace std;
//
//// global variables - normally would avoid globals, using in this demo
//GLuint shaderprogram; // handle for shader program
//GLuint vao, vbo[2]; // handles for our VAO and two VBOs
//float r = 0;
//
//
//// loadFile - loads text file into char* fname
//// allocates memory - so need to delete after use
//const char* loadFile(char* fname)
//{
//	int size;
//	char* memblock = NULL;
//
//	// file read based on example in cplusplus.com tutorial
//	// ios::ate opens file at the end
//	ifstream file(fname, ios::in | ios::binary | ios::ate);
//	if (file.is_open())
//	{
//		size = (int)file.tellg(); // get location of file pointer i.e. file size
//		memblock = new char[size + 1]; // create buffer with space for null char
//		file.seekg(0, ios::beg);
//		file.read(memblock, size);
//		file.close();
//		memblock[size] = 0;
//		cout << "file " << fname << " loaded" << endl;
//	}
//	else
//	{
//		cout << "Unable to open file " << fname << endl;
//		// should ideally set a flag or use exception handling
//		// so that calling function can decide what to do now
//	}
//	return memblock;
//}
//
//
//// Something went wrong - print SDL error message and quit
//void exitFatalError(char* message)
//{
//	cout << message << " ";
//	cout << SDL_GetError();
//	SDL_Quit();
//	exit(1);
//}
//
//
//
//// printShaderError
//// Display (hopefully) useful error messages if shader fails to compile or link
//void printShaderError(GLint shader)
//{
//	int maxLength = 0;
//	int logLength = 0;
//	GLchar* logMessage;
//
//	// Find out how long the error message is
//	if (glIsShader(shader))
//		glGetProgramiv(shader, GL_INFO_LOG_LENGTH, &maxLength);
//	else
//		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);
//
//	if (maxLength > 0) // If message has length > 0
//	{
//		logMessage = new GLchar[maxLength];
//		if (glIsShader(shader))
//			glGetProgramInfoLog(shader, maxLength, &logLength, logMessage);
//		else
//			glGetShaderInfoLog(shader, maxLength, &logLength, logMessage);
//		cout << "Shader Info Log:" << endl << logMessage << endl;
//		delete[] logMessage;
//	}
//}
//
//
//GLuint initShaders(char* vertFile, char* fragFile)
//{
//	GLuint p, f, v;	// Handles for shader program & vertex and fragment shaders
//
//	v = glCreateShader(GL_VERTEX_SHADER); // Create vertex shader handle
//	f = glCreateShader(GL_FRAGMENT_SHADER);	// " fragment shader handle
//
//	const char* vertSource = loadFile(vertFile); // load vertex shader source
//	const char* fragSource = loadFile(fragFile);  // load frag shader source
//
//	// Send the shader source to the GPU
//	// Strings here are null terminated - a non-zero final parameter can be
//	// used to indicate the length of the shader source instead
//	glShaderSource(v, 1, &vertSource, 0);
//	glShaderSource(f, 1, &fragSource, 0);
//
//	GLint compiled, linked; // return values for checking for compile & link errors
//
//	// compile the vertex shader and test for errors
//	glCompileShader(v);
//	glGetShaderiv(v, GL_COMPILE_STATUS, &compiled);
//	if (!compiled)
//	{
//		cout << "Vertex shader not compiled." << endl;
//		printShaderError(v);
//	}
//
//	// compile the fragment shader and test for errors
//	glCompileShader(f);
//	glGetShaderiv(f, GL_COMPILE_STATUS, &compiled);
//	if (!compiled)
//	{
//		cout << "Fragment shader not compiled." << endl;
//		printShaderError(f);
//	}
//
//	p = glCreateProgram(); 	// create the handle for the shader program
//	glAttachShader(p, v); // attach vertex shader to program
//	glAttachShader(p, f); // attach fragment shader to program
//
//	glBindAttribLocation(p, 0, "in_Position"); // bind position attribute to location 0
//	glBindAttribLocation(p, 1, "in_Color"); // bind color attribute to location 1
//
//	glLinkProgram(p); // link the shader program and test for errors
//	glGetProgramiv(p, GL_LINK_STATUS, &linked);
//	if (!linked)
//	{
//		cout << "Program not linked." << endl;
//		printShaderError(p);
//	}
//
//	glUseProgram(p);  // Make the shader program the current active program
//
//	delete[] vertSource; // Don't forget to free allocated memory
//	delete[] fragSource; // We allocated this in the loadFile function...
//
//	return p; // Return the shader program handle
//}
//
//void init(void)
//{
//	auto file = File::load_glb("./data/models/cube.glb");
//	auto cube_ptr = File::extract_meshes(file)[0].get_meshes()[0];
//	geometry::Mesh& cube = *cube_ptr.get();
//	const size_t face_count = cube.indices.size();
//	const size_t vertex_count = 3 * face_count;
//
//	GLfloat* vertices = new GLfloat[vertex_count];
//	for (int i = 0; i < face_count; i++) {
//		int index = cube.indices[i];
//		vertices[3 * i] = cube.positions[index].x;
//		vertices[3 * i + 1] = cube.positions[index].y;
//		vertices[3 * i + 2] = cube.positions[index].z;
//	}
//
//	GLfloat* colors = new GLfloat[vertex_count];
//	for (int i = 0; i < vertex_count; i++) {
//		colors[i] = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
//	}
//
//	shaderprogram = initShaders((char*)"./shaders/simple.vert", (char*)"./shaders/simple.frag"); // Create and start shader program
//	glGenVertexArrays(1, &vao); // allocate & assign a Vertex Array Object (VAO)
//	glBindVertexArray(vao); // bind VAO as current object
//	glGenBuffers(2, vbo); // allocate two Vertex Buffer Objects (VBO)
//
//	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]); // bind first VBO as active buffer object
//	glBufferData(GL_ARRAY_BUFFER, vertex_count * sizeof(GLfloat), vertices, GL_STATIC_DRAW);
//	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
//	glEnableVertexAttribArray(0);     // Enable attribute index 0 (position)
//
//	glBindBuffer(GL_ARRAY_BUFFER, vbo[1]); // bind second VBO as active buffer object
//	glBufferData(GL_ARRAY_BUFFER, vertex_count * sizeof(GLfloat), colors, GL_STATIC_DRAW);
//	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
//	glEnableVertexAttribArray(1);    // Enable attribute index 1 (color)
//
//	glEnable(GL_DEPTH_TEST); // enable depth testing
//	//glEnable(GL_CULL_FACE); // enable back face culling - try this and see what happens!
//}
//
//
//void draw(SDL_Window* window)
//{
//	glClearColor(1.0, 1.0, 1.0, 1.0); // set background colour
//	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // clear window
//
//	// Create perspective projection matrix
//	glm::mat4 projection = glm::perspective(45.0f, 1.0f, 1.0f, 100.f);
//
//	// Create view matrix for the camera
//	r += 0.001; //for camera rotation
//	glm::mat4 view(1.0);
//	view = glm::translate(view, glm::vec3(0.0f, 0.0f, -4.0f));
//	view = glm::rotate(view, r, glm::vec3(0.0f, 1.0f, 0.0f));
//
//	// Create model matrix for model transformations
//	glm::mat4 model(1.0);
//
//	// pass model as uniform into shader
//	int projectionIndex = glGetUniformLocation(shaderprogram, "projection");
//	glUniformMatrix4fv(projectionIndex, 1, GL_FALSE, glm::value_ptr(projection));
//	// pass model as uniform into shader
//	int viewIndex = glGetUniformLocation(shaderprogram, "view");
//	glUniformMatrix4fv(viewIndex, 1, GL_FALSE, glm::value_ptr(view));
//	// pass model as uniform into shader
//	int modelIndex = glGetUniformLocation(shaderprogram, "model");
//	glUniformMatrix4fv(modelIndex, 1, GL_FALSE, glm::value_ptr(model));
//
//	glDrawArrays(GL_TRIANGLES, 0, 108); // draw the pyramid
//
//	SDL_GL_SwapWindow(window); // swap buffers
//}
//
//
//void cleanup(void)
//{
//	glUseProgram(0);
//	glDisableVertexAttribArray(0);
//	glDisableVertexAttribArray(1);
//	// could also detach shaders
//	glDeleteProgram(shaderprogram);
//	glDeleteBuffers(2, vbo);
//	glDeleteVertexArrays(1, &vao);
//}
//
//
//int main(int argc, char* argv[]) {
//	//INICIALIZACION
//	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) != 0) {
//		SDL_Log("Failed to initialize SDL: %s", SDL_GetError());
//		return 1;
//	}
//
//	SDL_Window* window = NULL;
//	SDL_GLContext gl_context;
//
//	window = SDL_CreateWindow("Ventana", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
//		800, 800, SDL_WINDOW_OPENGL);
//
//	gl_context = SDL_GL_CreateContext(window);
//	//disable limit of 60fps
//	SDL_GL_SetSwapInterval(0);
//	// Check OpenGL properties
//	printf("OpenGL loaded\n");
//	gladLoadGLLoader(SDL_GL_GetProcAddress);
//	printf("Vendor:   %s\n", glGetString(GL_VENDOR));
//	printf("Renderer: %s\n", glGetString(GL_RENDERER));
//	printf("Version:  %s\n", glGetString(GL_VERSION));
//
//	init();
//
//	bool running = true; // set running to true
//	SDL_Event sdlEvent;  // variable to detect SDL events
//
//	while (running)		// the event loop
//	{
//		while (SDL_PollEvent(&sdlEvent))
//		{
//			if (sdlEvent.type == SDL_QUIT)
//				running = false;
//		}
//		//update();
//		draw(window); // call the draw function
//	}
//
//	cleanup();
//
//	//FIN LOOP PRINCIPAL
//	SDL_GL_DeleteContext(gl_context);
//	SDL_DestroyWindow(window);
//	SDL_Quit();
//	return 0;
//}
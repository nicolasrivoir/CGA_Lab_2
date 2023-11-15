#include "Renderer.h"

#include "glm/glm.hpp"
#include "glm/matrix.hpp"
#include <glm/gtc/type_ptr.hpp>

#include "FreeImage.h"

#include "File.h"

using namespace math;
using namespace geometry;

float r = 0;

void Renderer::initShaders(std::string vertexShaderFile, std::string fragmentShaderFile)
{
	// Shader initialization
	GLuint p, f, v;	// Handles for shader program & vertex and fragment shaders

	v = glCreateShader(GL_VERTEX_SHADER); // Create vertex shader handle
	f = glCreateShader(GL_FRAGMENT_SHADER);	// " fragment shader handle

	const char* vertSource = (const char*)File::loadFile(vertexShaderFile); // load vertex shader source
	const char* fragSource = (const char*)File::loadFile(fragmentShaderFile);  // load frag shader source

	// Send the shader source to the GPU
	// Strings here are null terminated - a non-zero final parameter can be
	// used to indicate the length of the shader source instead
	glShaderSource(v, 1, &vertSource, 0);
	glShaderSource(f, 1, &fragSource, 0);

	GLint compiled, linked; // return values for checking for compile & link errors

	// compile the vertex shader and test for errors
	glCompileShader(v);
	glGetShaderiv(v, GL_COMPILE_STATUS, &compiled);

	// compile the fragment shader and test for errors
	glCompileShader(f);
	glGetShaderiv(f, GL_COMPILE_STATUS, &compiled);

	p = glCreateProgram(); 	// create the handle for the shader program
	glAttachShader(p, v); // attach vertex shader to program
	glAttachShader(p, f); // attach fragment shader to program

	glBindAttribLocation(p, 0, "in_Position"); // bind position attribute to location 0
	glBindAttribLocation(p, 1, "in_Color"); // bind color attribute to location 1

	glLinkProgram(p); // link the shader program and test for errors
	glGetProgramiv(p, GL_LINK_STATUS, &linked);

	glUseProgram(p);  // Make the shader program the current active program

	delete[] vertSource; // Don't forget to free allocated memory
	delete[] fragSource; // We allocated this in the loadFile function...

	shaderprogram = p;
}

void Renderer::initObject(MeshObject& obj)
{
	for (int i = 0; i < obj.ids.size(); i++) {
		auto& mesh = *obj.meshes[i];

		const size_t vertexCount = mesh.positions.size();
		const size_t faceCount = mesh.indices.size();

		

		GLfloat* colors = new GLfloat[3 * vertexCount];
		for (int i = 0; i < 3 * vertexCount; i++) {
			colors[i] = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
		}

		initShaders((char*)"./shaders/simple.vert", (char*)"./shaders/simple.frag"); // Create and start shader program

		GLuint vertexArray;
		GLuint buffers[3];
		glGenVertexArrays(1, &vertexArray); // allocate & assign a Vertex Array Object (VAO)
		glBindVertexArray(vertexArray); // bind VAO as current object
		glGenBuffers(3, buffers); // allocate two Vertex Buffer Objects (VBO)

		GLfloat* positions = reinterpret_cast<GLfloat*>(mesh.positions.data());
		glBindBuffer(GL_ARRAY_BUFFER, buffers[0]); // bind first VBO as active buffer object
		glBufferData(GL_ARRAY_BUFFER, 3 * vertexCount * sizeof(GLfloat), positions, GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(0);     // Enable attribute index 0 (position)

		GLfloat* indices = reinterpret_cast<GLfloat*>(mesh.indices.data());
		const unsigned int indexCount = mesh.indices.size();
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffers[1]); // bind second VBO as active buffer object
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexCount * sizeof(GLuint), indices, GL_STATIC_DRAW);

		glBindBuffer(GL_ARRAY_BUFFER, buffers[2]); // bind second VBO as active buffer object
		glBufferData(GL_ARRAY_BUFFER, 3 * vertexCount * sizeof(GLfloat), colors, GL_STATIC_DRAW);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(1);    // Enable attribute index 1 (color)

		glEnable(GL_DEPTH_TEST); // enable depth testing
		//glEnable(GL_CULL_FACE); // enable back face culling - try this and see what happens!

		obj.ids[i] = vertexArray;
	}
	
}

Renderer::Renderer() :window(new Window())
{
}


void Renderer::toogleNormalInterpolation()
{
	normalInterpolationEnabled = !normalInterpolationEnabled;
	if (normalInterpolationEnabled) {
		glShadeModel(GL_SMOOTH);
	}
	else {
		glShadeModel(GL_FLAT);
	}
}

void Renderer::toggleTextures()
{
	texturesEnabled = !texturesEnabled;
}

void Renderer::toggleWireframes()
{
	wireframeEnabled = !wireframeEnabled;
	int mode = wireframeEnabled ? GL_LINE : GL_FILL;
	glPolygonMode(GL_FRONT_AND_BACK, mode);
}

void Renderer::draw(MeshObject& obj) {

	for (int i = 0; i < obj.ids.size(); i++) {
		if (obj.ids[i] == 0) {
			initObject(obj);
		}
		else {
			glBindVertexArray(obj.ids[i]);
		}

		// Create perspective projection matrix
		glm::mat4 projection = glm::perspective(45.0f, 1.0f, 1.0f, 100.f);

		// Create view matrix for the camera
		r += 0.001; //for camera rotation
		glm::mat4 view(1.0);
		view = glm::translate(view, glm::vec3(0.0f, 0.0f, -4.0f));
		view = glm::rotate(view, r, glm::vec3(0.0f, 1.0f, 0.0f));

		// Create model matrix for model transformations
		glm::mat4 model = reinterpret_cast<glm::mat4&>(obj.transformation);

		// pass model as uniform into shader
		int projectionIndex = glGetUniformLocation(shaderprogram, "projection");
		glUniformMatrix4fv(projectionIndex, 1, GL_FALSE, glm::value_ptr(projection));
		// pass model as uniform into shader
		int viewIndex = glGetUniformLocation(shaderprogram, "view");
		glUniformMatrix4fv(viewIndex, 1, GL_FALSE, glm::value_ptr(view));
		// pass model as uniform into shader
		int modelIndex = glGetUniformLocation(shaderprogram, "model");
		glUniformMatrix4fv(modelIndex, 1, GL_FALSE, glm::value_ptr(model));

		unsigned int count = 3* obj.meshes[i]->indices.size();
		glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, reinterpret_cast<void*>(0)); // draw the mesh
	}
	
}

void Renderer::drawOnTop(MeshObject& obj) {
	glClear(GL_DEPTH_BUFFER_BIT);
	draw(obj);
}

void Renderer::clear()
{
	window->swapBuffers();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

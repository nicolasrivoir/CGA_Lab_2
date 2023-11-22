#include "Renderer.h"

#include "glm/glm.hpp"
#include "glm/matrix.hpp"
#include <glm/gtc/type_ptr.hpp>

#include "FreeImage.h"

#include "GLSL.h"

using namespace math;
using namespace geometry;

float r = 0;

void Renderer::initObject(MeshObject& obj)
{
	for (int i = 0; i < obj.ids.size(); i++) {
		auto& mesh = *obj.meshes[i];

		const size_t vertexCount = mesh.positions.size();
		const size_t faceCount = mesh.indices.size();

		GLuint vertexArray;
		GLuint buffers[4];
		glGenVertexArrays(1, &vertexArray); // allocate & assign a Vertex Array Object (VAO)
		glBindVertexArray(vertexArray); // bind VAO as current object
		glGenBuffers(4, buffers); // allocate the Vertex Buffer Objects (VBO)

		GLfloat* positions = reinterpret_cast<GLfloat*>(mesh.positions.data());
		glBindBuffer(GL_ARRAY_BUFFER, buffers[0]); // bind first VBO as active buffer object
		glBufferData(GL_ARRAY_BUFFER, 3 * vertexCount * sizeof(GLfloat), positions, GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(0);     // Enable attribute index 0 (position)


		GLfloat* normals = reinterpret_cast<GLfloat*>(mesh.normals.data());
		glBindBuffer(GL_ARRAY_BUFFER, buffers[1]); // bind second VBO as active buffer object
		glBufferData(GL_ARRAY_BUFFER, 3 * vertexCount * sizeof(GLfloat), normals, GL_STATIC_DRAW);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(1);    // Enable attribute index 1 (normal)

		GLfloat* texcoords = reinterpret_cast<GLfloat*>(mesh.texcoords.data());
		glBindBuffer(GL_ARRAY_BUFFER, buffers[2]); // bind second VBO as active buffer object
		glBufferData(GL_ARRAY_BUFFER, 2 * vertexCount * sizeof(GLfloat), texcoords, GL_STATIC_DRAW);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(2);    // Enable attribute index 2 (texcoords)

		GLfloat* indices = reinterpret_cast<GLfloat*>(mesh.indices.data());
		const unsigned int indexCount = mesh.indices.size();
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffers[3]); // bind second VBO as active buffer object
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexCount * sizeof(GLuint), indices, GL_STATIC_DRAW);

		glEnable(GL_DEPTH_TEST); // enable depth testing
		//glEnable(GL_CULL_FACE); // enable back face culling - try this and see what happens!

		obj.ids[i] = vertexArray;
	}
	
}

Renderer::Renderer(Window& window) : window(&window), shaderProgram(GLSL("./shaders/simple.vert"), GLSL("./shaders/simple.frag"))
{
	shaderProgram.setGamma(2.2f);
}


ShaderProgram Renderer::getShaderProgram()
{
	return shaderProgram;
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
		unsigned int width = window->getWidth();
		unsigned int height = window->getHeight();
		height = (height == 0) ? 1 : height;
		float aspect = static_cast<float>(width) / height;
		glm::mat4 projection = glm::perspective(45.0f, aspect, 1.0f, 100.f);

		// Create view matrix for the camera
		//r += 0.03; //for camera rotation
		glm::mat4 view(1.0);
		view = glm::translate(view, glm::vec3(0.0f, 0.0f, -4.0f));
		view = glm::rotate(view, 0.5f, glm::vec3(1.0f, 0.0f, 0.0f));
		view = glm::rotate(view, r, glm::vec3(0.0f, 1.0f, 0.0f));

		// Create model matrix for model transformations
		glm::mat4 model = reinterpret_cast<glm::mat4&>(obj.transformation);

		// pass model as uniform into shader
		int projectionIndex = glGetUniformLocation(shaderProgram.getId(), "projection");
		glUniformMatrix4fv(projectionIndex, 1, GL_FALSE, glm::value_ptr(projection));
		// pass model as uniform into shader
		int viewIndex = glGetUniformLocation(shaderProgram.getId(), "view");
		glUniformMatrix4fv(viewIndex, 1, GL_FALSE, glm::value_ptr(view));
		// pass model as uniform into shader
		int modelIndex = glGetUniformLocation(shaderProgram.getId(), "model");
		glUniformMatrix4fv(modelIndex, 1, GL_FALSE, glm::value_ptr(model));

		shaderProgram.setCurrentMaterial(obj.materials[i]);

		obj.materials[i].diffuseTexture.bind();

		int lightPosIndex = glGetUniformLocation(shaderProgram.getId(), "lightPosition");
		auto lightPos = view * glm::vec4(2.0f, 2.0f, 2.0f, 1.0f);
		glUniform3fv(lightPosIndex, 1, &lightPos.x);

		int lightColIndex = glGetUniformLocation(shaderProgram.getId(), "lightColor");
		auto lightCol = Vector3(1.0f, 1.0f, 1.0f);;
		glUniform3fv(lightColIndex, 1, &lightCol.x);

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

#include "ShaderProgram.h"
#include "Window.h"

#include <algorithm>

ShaderProgram::ShaderProgram(GLSL vertexShader, GLSL fragmentShader)
{
	// Shader initialization
	GLuint p, f, v;	// Handles for shader program & vertex and fragment shaders

	v = glCreateShader(GL_VERTEX_SHADER); // Create vertex shader handle
	f = glCreateShader(GL_FRAGMENT_SHADER);	// " fragment shader handle

	const char* vertSource = reinterpret_cast<const char*>(vertexShader.getSource()); // load vertex shader source
	const char* fragSource = reinterpret_cast<const char*>(fragmentShader.getSource());  // load frag shader source

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

	glLinkProgram(p); // link the shader program and test for errors
	glGetProgramiv(p, GL_LINK_STATUS, &linked);

	glUseProgram(p);  // Make the shader program the current active program

	id = p;
}

unsigned int ShaderProgram::getId()
{
	return id;
}

float ShaderProgram::getGamma()
{
	return gamma;
}

Material ShaderProgram::getCurrentMaterial()
{
	return currentMaterial;
}

void ShaderProgram::setCurrentMaterial(const Material& material)
{
	int colorIndex = glGetUniformLocation(id, "objectColor");
	glUniform3fv(colorIndex, 1, &material.basecolor.x);

	int kdIndex = glGetUniformLocation(id, "diffuseCoefficient");
	float kd = 1.1f - material.metallic;
	glUniform1f(kdIndex, kd);

	int ksIndex = glGetUniformLocation(id, "specularCoefficient");
	glUniform1f(ksIndex, 1 - material.roughness);

	int nIndex = glGetUniformLocation(id, "specularExponent");
	glUniform1f(nIndex, 2.0 + (1 - material.roughness) * 128.0);

	int metalIndex = glGetUniformLocation(id, "metalnessFactor");
	glUniform1f(metalIndex, material.metallic);

	currentMaterial = material;
}

void ShaderProgram::setGamma(float value)
{
	int index = glGetUniformLocation(id, "gamma");
	glUniform1f(index, value);
	gamma = value;
}

ShaderProgram::~ShaderProgram()
{
}

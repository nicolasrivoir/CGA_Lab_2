#ifndef SHADERPROGRAM_H
#define SHADERPROGRAM_H

#include "GLSL.h"

class ShaderProgram
{
public:

	ShaderProgram(GLSL vertexShader, GLSL fragmentShader);

	unsigned int getId();

	//void setAmbientCoefficient(float ka);

	~ShaderProgram();

private:

	unsigned int id;

};

#endif
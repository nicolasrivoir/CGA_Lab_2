#ifndef SHADERPROGRAM_H
#define SHADERPROGRAM_H

#include "GLSL.h"

class ShaderProgram
{

private:

	unsigned int id;

	float gamma;

public:

	ShaderProgram(GLSL vertexShader, GLSL fragmentShader);

	unsigned int getId();

	//void setAmbientCoefficient(float ka);

	~ShaderProgram();

};

#endif
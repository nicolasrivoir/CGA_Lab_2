#ifndef SHADERPROGRAM_H
#define SHADERPROGRAM_H

#include "File.h"

class ShaderProgram
{
public:

	ShaderProgram(File::GLSL vertexShader, File::GLSL fragmentShader);

	//void setAmbientCoefficient(float ka);

	~ShaderProgram();

private:

	unsigned int id;

};

#endif
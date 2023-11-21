#ifndef SHADERPROGRAM_H
#define SHADERPROGRAM_H

#include "GLSL.h"
#include "utils.h"

class ShaderProgram
{

private:

	unsigned int id;

	float gamma;

	Material currentMaterial;

public:

	ShaderProgram(GLSL vertexShader, GLSL fragmentShader);

	unsigned int getId();

	float getGamma();

	Material getCurrentMaterial();

	//void setAmbientCoefficient(float ka);

	void setCurrentMaterial(const Material& material);

	void setGamma(float value);

	~ShaderProgram();

};

#endif
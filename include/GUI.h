#ifndef GUI_H
#define GUI_H

#include "Window.h"
#include "ShaderProgram.h"
#include "MeshObject.h"

class GUI
{
private:

	void foo() {}

public:

	GUI(Window& window);

	void shaderPreview(ShaderProgram s, MeshObject &obj);

};

#endif
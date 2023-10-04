#pragma once

#include "imgui.h"
#include "imgui_impl_opengl3.h"
#include "imgui_impl_glfw.h"
//#include <GL\glew.h>
//#include <GLFW\glfw3.h>

class Gui
{
public:
	Gui() {};
	
	void initialise(GLFWwindow* window);
	void update(bool* useTexture,
				float* translation, float* scaling, float* rotation,
				float* viewPosition, float* viewFront,
				bool* usePerspective);
	void render();

	~Gui() {};
};


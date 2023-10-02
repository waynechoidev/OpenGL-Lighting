#pragma once

#include "stdio.h"

#include <GL\glew.h>
#include <GLFW\glfw3.h>

class Window
{
public:
	Window(GLint windowWidth, GLint windowHeight);

	Window() : Window(800, 600) {}

	void Initialise();

	GLint getBufferWidth() { return _bufferWidth; }
	GLint getBufferHeight() { return _bufferHeight; }

	bool getShouldClose() { return glfwWindowShouldClose(_mainWindow); }

	void swapBuffers() { glfwSwapBuffers(_mainWindow); }

	~Window();

private:
	GLFWwindow* _mainWindow;

	GLint _width, _height;
	GLint _bufferWidth, _bufferHeight;
};
#include "Window.h"

Window::Window(GLint windowWidth, GLint windowHeight)
{
	_width = windowWidth;
	_height = windowHeight;
	
	_bufferWidth = _bufferHeight = 0;
	_mainWindow = 0;
}

void Window::Initialise()
{
	if (!glfwInit())
	{
		printf("Error Initialising GLFW");
		glfwTerminate();
	}

	// Setup GLFW Windows Properties
	// OpenGL version
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	// Core Profile
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	// Allow forward compatiblity
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	// Create the window
	_mainWindow = glfwCreateWindow(_width, _height, "OpenGL Lighting", NULL, NULL);

	if (!_mainWindow)
	{
		printf("Error creating GLFW window!");
		glfwTerminate();
	}

	// Get buffer size information
	glfwGetFramebufferSize(_mainWindow, &_bufferWidth, &_bufferHeight);

	// Set the current context
	glfwMakeContextCurrent(_mainWindow);
	
	// Allow modern extension access
	glewExperimental = GL_TRUE;

	GLenum error = glewInit();
	if (error != GLEW_OK)
	{
		printf("Error: %s", glewGetErrorString(error));
		glfwDestroyWindow(_mainWindow);
		glfwTerminate();
	}

	glEnable(GL_DEPTH_TEST);

	// Create Viewport
	glViewport(0, 0, _bufferWidth, _bufferHeight);

	glfwSetWindowUserPointer(_mainWindow, this);
}

Window::~Window()
{
	glfwDestroyWindow(_mainWindow);
	glfwTerminate();
}
#include <iostream>
#include "Window.h"

Window mainWindow;

int main()
{
	mainWindow = Window(1366, 768);
	mainWindow.Initialise();

	while (!mainWindow.getShouldClose())
	{
		// Get + Handle user input events
		glfwPollEvents();

		// Clear window
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		mainWindow.swapBuffers();
	}
}


#include <iostream>
#include "Window.h"
#include "Gui.h"

Window mainWindow;
Gui gui;

bool boolean;

int main()
{
	mainWindow = Window(1366, 768);
	mainWindow.initialise();
	
	gui = Gui();
	gui.initialise(mainWindow.getWindow());

	while (!mainWindow.getShouldClose())
	{
		// Get + Handle user input events
		glfwPollEvents();

		gui.update(&boolean);

		// Clear window
		glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		gui.render();

		mainWindow.swapBuffers();
	}
}


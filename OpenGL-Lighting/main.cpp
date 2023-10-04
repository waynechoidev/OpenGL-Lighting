#include <iostream>
#include "Window.h"
#include "Gui.h"
#include "Box.h"
#include "Program.h"

#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>
#include "Texture.h"

#include "imgui.h"
#include "imgui_impl_opengl3.h"
#include "imgui_impl_glfw.h"

Window mainWindow;
Gui gui;
Box box;
Program program;
Texture texture;

int main()
{
	mainWindow = Window(1366, 768);
	mainWindow.initialise();

	gui = Gui();
	gui.initialise(mainWindow.getWindow());
	
	box = Box();
	box.initialise();

	program = Program();
	program.createFromFiles("shader.vert", "shader.frag");

	texture = Texture();
	texture.initialise("box.jpg");

	glm::mat4 projection = glm::perspective(glm::radians(45.0f), (GLfloat)mainWindow.getBufferWidth() / mainWindow.getBufferHeight(), 0.1f, 100.0f);

	bool useTexture = true;

	float translation[3] = { 0.0f, 0.0f, 0.0f };
	float scaling[3] = { 0.5f, 0.5f, 0.5f };
	float rotation[3] = { 0.0f, 0.0f, 0.0f };

	glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec3 front = glm::vec3(0.0f, 0.0f, -1.0f);
	glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);

	while (!mainWindow.getShouldClose())
	{
		// Get + Handle user input events
		glfwPollEvents();

		gui.update(&useTexture, translation, scaling, rotation);

		mainWindow.clear(0.0f, 0.0f, 0.0f, 1.0f);

		glm::mat4 model(1.0f);
		model = glm::translate(model, glm::vec3(translation[0],translation[1],translation[2]-2.5f));
		model = glm::scale(model, glm::vec3(scaling[0],scaling[1],scaling[2]));
		model = glm::rotate(model, rotation[0], glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::rotate(model, rotation[1], glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, rotation[2], glm::vec3(0.0f, 0.0f, 1.0f));
		
		glm::mat4 view = glm::lookAt(position, position + front, up);

		program.use(useTexture, model, projection, view);

		texture.use();

		box.render();

		gui.render();

		glUseProgram(0);

		mainWindow.swapBuffers();
	}
}


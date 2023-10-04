#include <iostream>
#include <vector>

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

	glm::vec3 translation = { 0.0f, 0.0f, 0.0f };
	glm::vec3 scaling = { 0.5f, 0.5f, 0.5f };
	glm::vec3 rotation = { 0.0f, 0.0f, 0.0f };

	glm::vec3 position = { 0.0f, 0.0f, 0.0f };
	glm::vec3 front = { 0.0f, 0.0f, -1.0f };
	glm::vec3 up = { 0.0f, 1.0f, 0.0f };

	while (!mainWindow.getShouldClose())
	{
		// Get + Handle user input events
		glfwPollEvents();

		gui.update(&useTexture, &translation.x, &scaling.x, &rotation.x);

		mainWindow.clear(0.0f, 0.0f, 0.0f, 1.0f);

		glm::mat4 model(1.0f);
		model = glm::translate(model, glm::vec3(translation.x,translation.y,translation.z-2.5f));
		model = glm::scale(model, scaling);
		model = glm::rotate(model, rotation.x, glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::rotate(model, rotation.y, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, rotation.z, glm::vec3(0.0f, 0.0f, 1.0f));
		
		glm::mat4 view = glm::lookAt(position, position + front, up);

		program.use(useTexture, model, projection, view);

		texture.use();

		box.render();

		gui.render();

		glUseProgram(0);

		mainWindow.swapBuffers();
	}
}


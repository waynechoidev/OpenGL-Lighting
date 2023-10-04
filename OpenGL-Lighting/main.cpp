#include <iostream>
#include "Window.h"
#include "Gui.h"
#include "Mesh.h"
#include "Program.h"

#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>
#include "Texture.h"

Window mainWindow;
Gui gui;
Mesh box;
Program program;
Texture texture;


bool boolean;

int main()
{
	mainWindow = Window(1366, 768);
	mainWindow.initialise();
	
	gui = Gui();
	gui.initialise(mainWindow.getWindow());

	box = Mesh();

	GLfloat vertices[] = {
		//   x      y      z          u     v         nx     ny     nz
		// Top
		   -1.0f,  1.0f, -1.0f,     0.0f, 0.0f,      0.0f,  1.0f,  0.0f,
		   -1.0f,  1.0f,  1.0f,     1.0f, 0.0f,      0.0f,  1.0f,  0.0f,
			1.0f,  1.0f,  1.0f,     1.0f, 1.0f,      0.0f,  1.0f,  0.0f,
			1.0f,  1.0f, -1.0f,     0.0f, 1.0f,      0.0f,  1.0f,  0.0f,

		// Bottom
		   -1.0f, -1.0f, -1.0f,     0.0f, 0.0f,      0.0f, -1.0f,  0.0f,
			1.0f, -1.0f, -1.0f,     1.0f, 0.0f,      0.0f, -1.0f,  0.0f,
			1.0f, -1.0f,  1.0f,     1.0f, 1.0f,      0.0f, -1.0f,  0.0f,
		   -1.0f, -1.0f,  1.0f,     0.0f, 1.0f,      0.0f, -1.0f,  0.0f,

	    // Front
		   -1.0f, -1.0f, -1.0f,     0.0f, 0.0f,      0.0f,  0.0f, -1.0f,
	 	   -1.0f,  1.0f, -1.0f,     1.0f, 0.0f,      0.0f,  0.0f, -1.0f,
	 	    1.0f,  1.0f, -1.0f,     1.0f, 1.0f,      0.0f,  0.0f, -1.0f,
	 	    1.0f, -1.0f, -1.0f,     0.0f, 1.0f,      0.0f,  0.0f, -1.0f,

		// Back
		   -1.0f, -1.0f,  1.0f,     0.0f, 0.0f,      0.0f,  0.0f,  1.0f,
		    1.0f, -1.0f,  1.0f,     1.0f, 0.0f,      0.0f,  0.0f,  1.0f,
			1.0f,  1.0f,  1.0f,     1.0f, 1.0f,      0.0f,  0.0f,  1.0f,
		   -1.0f,  1.0f,  1.0f,     0.0f, 1.0f,      0.0f,  0.0f,  1.0f,

		// Left
		   -1.0f, -1.0f,  1.0f,     0.0f, 0.0f,     -1.0f,  0.0f,  0.0f,
		   -1.0f,  1.0f,  1.0f,     1.0f, 0.0f,     -1.0f,  0.0f,  0.0f,
		   -1.0f,  1.0f, -1.0f,     1.0f, 1.0f,     -1.0f,  0.0f,  0.0f,
		   -1.0f, -1.0f, -1.0f,     0.0f, 1.0f,     -1.0f,  0.0f,  0.0f,

		// Right
			1.0f, -1.0f,  1.0f,     0.0f, 0.0f,      1.0f,  0.0f,  0.0f,
			1.0f, -1.0f, -1.0f,     1.0f, 0.0f,      1.0f,  0.0f,  0.0f,
			1.0f,  1.0f, -1.0f,     1.0f, 1.0f,      1.0f,  0.0f,  0.0f,
			1.0f,  1.0f,  1.0f,     0.0f, 1.0f,      1.0f,  0.0f,  0.0f
	};

	unsigned int indices[] = {
		0,  1,  2,  0,  2,  3,  // Top
		4,  5,  6,  4,  6,  7,  // Bottom
		8,  9,  10, 8,  10, 11, // Front
		12, 13, 14, 12, 14, 15, // Back
		16, 17, 18, 16, 18, 19, // Left
		20, 21, 22, 20, 22, 23  // Right
	};

	box.initialise(vertices, indices, 192, 36);

	program = Program();
	program.createFromFiles("shader.vert", "shader.frag");

	GLuint uniformProjection = 0, uniformModel = 0, uniformView = 0;

	glm::mat4 projection = glm::perspective(glm::radians(45.0f), (GLfloat)mainWindow.getBufferWidth() / mainWindow.getBufferHeight(), 0.1f, 100.0f);

	auto position = glm::vec3(0.0f, 0.0f, 0.0f);
	auto front = glm::vec3(0.0f, 0.0f, -1.0f);
	auto up = glm::vec3(0.0f, 1.0f, 0.0f);

	texture = Texture();
	texture.initialise("box.jpg");

	while (!mainWindow.getShouldClose())
	{
		// Get + Handle user input events
		glfwPollEvents();

		gui.update(&boolean);

		// Clear window
		glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glm::mat4 model(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, -2.5f));
		model = glm::scale(model, glm::vec3(0.4f, 0.4f, 0.4f));
		model = glm::rotate(model, glm::radians(30.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::rotate(model, glm::radians(30.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		
		auto view = glm::lookAt(position, position + front, up);

		// Program
		program.use();
		glUniformMatrix4fv(program.getModelLocation(), 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(program.getProjectionLocation(), 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(program.getViewLocation(), 1, GL_FALSE, glm::value_ptr(view));

		texture.use();

		box.render();

		gui.render();

		glUseProgram(0);

		mainWindow.swapBuffers();
	}
}


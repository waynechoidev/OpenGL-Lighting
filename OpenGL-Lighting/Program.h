#pragma once

#include <stdio.h>
#include <string>
#include <fstream>
#include <iostream>

#include <GL\glew.h>

#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>

class Program
{
public:
	Program();

	void createFromString(const char* vertexCode, const char* fragmentCode);
	void createFromFiles(const char* vertexLocation, const char* fragmentLocation);

	std::string readFile(const char* fileLocation);

	void use(bool useTexture, glm::mat4 model, glm::mat4 projection, glm::mat4 view);
	void clear();

	~Program();

private:
	GLuint _programID;
	GLuint _uniformUseTexture;
	GLuint _uniformProjection, _uniformModel, _uniformView;

	void compileShader(const char* vertexCode, const char* fragmentCode);
	void addShader(GLuint theProgram, const char* shaderCode, GLenum shaderType);
};

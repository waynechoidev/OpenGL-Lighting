#pragma once

#include "Common.h"
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

	void use(bool useTexture, glm::mat4 model, glm::mat4 projection, glm::mat4 view, Material** material, Light** light);
	void clear();

	~Program();

private:
	GLuint _programID;
	GLuint _uniformUseTexture;
	GLuint _uniformProjection, _uniformModel, _uniformView;
	GLuint _uniformMaterialAmbient, _uniformMaterialShininess, _uniformMaterialDiffuse, _uniformMaterialSpecular;
	GLuint _uniformLightPosition, _uniformLightDirection, _uniformLightStrength, _uniformLightFallOffStart, _uniformLightFallOffEnd, _uniformLightSpotPower, _uniformLightIsDirectional, _uniformLightIsPoint, _uniformLightIsSpot;

	void compileShader(const char* vertexCode, const char* fragmentCode);
	void addShader(GLuint theProgram, const char* shaderCode, GLenum shaderType);
};

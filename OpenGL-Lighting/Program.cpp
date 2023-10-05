#include "Program.h"

Program::Program()
{
	_programID = 0;
	clear();
}

void Program::createFromString(const char* vertexCode, const char* fragmentCode)
{
	compileShader(vertexCode, fragmentCode);
}

void Program::createFromFiles(const char* vertexLocation, const char* fragmentLocation)
{
	std::string vertexString = readFile(vertexLocation);
	std::string fragmentString = readFile(fragmentLocation);
	const char* vertexCode = vertexString.c_str();
	const char* fragmentCode = fragmentString.c_str();

	compileShader(vertexCode, fragmentCode);
}

std::string Program::readFile(const char* fileLocation)
{
	std::string content;
	std::ifstream fileStream(fileLocation, std::ios::in);

	if (!fileStream.is_open()) {
		std::cout << "Failed to read %s! File doesn't exist." << fileLocation;
		return "";
	}

	std::string line = "";
	while (!fileStream.eof())
	{
		std::getline(fileStream, line);
		content.append(line + "\n");
	}

	fileStream.close();
	return content;
}

void Program::compileShader(const char* vertexCode, const char* fragmentCode)
{
	_programID = glCreateProgram();

	if (!_programID)
	{
		std::cout << "Error creating shader program!\n";
		return;
	}

	addShader(_programID, vertexCode, GL_VERTEX_SHADER);
	addShader(_programID, fragmentCode, GL_FRAGMENT_SHADER);

	GLint result = 0;
	GLchar eLog[1024] = { 0 };

	glLinkProgram(_programID);
	glGetProgramiv(_programID, GL_LINK_STATUS, &result);
	if (!result)
	{
		glGetProgramInfoLog(_programID, sizeof(eLog), NULL, eLog);
		std::cout << "Error linking program: '%s'\n" << eLog;
		return;
	}

	glValidateProgram(_programID);
	glGetProgramiv(_programID, GL_VALIDATE_STATUS, &result);
	if (!result)
	{
		glGetProgramInfoLog(_programID, sizeof(eLog), NULL, eLog);
		std::cout << "Error validating program: '%s'\n" << eLog;
		return;
	}

	_uniformUseTexture = glGetUniformLocation(_programID, "useTexture");

	_uniformProjection = glGetUniformLocation(_programID, "projection");
	_uniformModel = glGetUniformLocation(_programID, "model");
	_uniformView = glGetUniformLocation(_programID, "view");

	_uniformMaterialAmbient = glGetUniformLocation(_programID, "material.ambient");
	_uniformMaterialShininess = glGetUniformLocation(_programID, "material.shininess");
	_uniformMaterialDiffuse = glGetUniformLocation(_programID, "material.diffuse");
	_uniformMaterialSpecular = glGetUniformLocation(_programID, "material.specular");

	_uniformLightPosition = glGetUniformLocation(_programID, "light.position");
	_uniformLightDirection = glGetUniformLocation(_programID, "light.direction");
	_uniformLightStrength = glGetUniformLocation(_programID, "light.strength");
	_uniformLightFallOffStart = glGetUniformLocation(_programID, "light.fallOffStart");
	_uniformLightFallOffEnd = glGetUniformLocation(_programID, "light.fallOffEnd");
	_uniformLightSpotPower = glGetUniformLocation(_programID, "light.spotPower");
	_uniformLightIsDirectional = glGetUniformLocation(_programID, "light.isDirectional");
	_uniformLightIsPoint = glGetUniformLocation(_programID, "light.isPoint");
	_uniformLightIsSpot = glGetUniformLocation(_programID, "light.isSpot");
}

void Program::use(bool useTexture, glm::mat4 model, glm::mat4 projection, glm::mat4 view, Material** material, Light** light)
{
	glUseProgram(_programID);

	glUniform1i(_uniformUseTexture, useTexture);

	glUniformMatrix4fv(_uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	glUniformMatrix4fv(_uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
	glUniformMatrix4fv(_uniformView, 1, GL_FALSE, glm::value_ptr(view));

	glUniform1f(_uniformMaterialAmbient, (*material)->ambient);
	glUniform1f(_uniformMaterialShininess, (*material)->shininess);
	glUniform1f(_uniformMaterialDiffuse, (*material)->diffuse);
	glUniform1f(_uniformMaterialSpecular, (*material)->specular);
	
	glUniform3f(_uniformLightPosition, (*light)->position.x, (*light)->position.y, (*light)->position.z);
	glUniform3f(_uniformLightDirection, (*light)->direction.x, (*light)->direction.y, (*light)->direction.z);
	glUniform1f(_uniformLightStrength, (*light)->strength);
	glUniform1f(_uniformLightFallOffStart, (*light)->fallOffStart);
	glUniform1f(_uniformLightFallOffEnd, (*light)->fallOffEnd);
	glUniform1f(_uniformLightSpotPower, (*light)->spotPower);
	glUniform1i(_uniformLightIsDirectional, (*light)->isDirectional);
	glUniform1i(_uniformLightIsPoint, (*light)->isPoint);
	glUniform1i(_uniformLightIsSpot, (*light)->isSpot);
}

void Program::clear()
{
	if (_programID != 0)
	{
		glDeleteProgram(_programID);
		_programID = 0;
	}

	_uniformUseTexture = 0;

	_uniformModel = 0;
	_uniformProjection = 0;
	_uniformView = 0;
}


void Program::addShader(GLuint theProgram, const char* shaderCode, GLenum shaderType)
{
	GLuint theShader = glCreateShader(shaderType);

	const GLchar* theCode[1];
	theCode[0] = shaderCode;

	GLint codeLength[1];
	codeLength[0] = strlen(shaderCode);

	glShaderSource(theShader, 1, theCode, codeLength);
	glCompileShader(theShader);

	GLint result = 0;
	GLchar eLog[1024] = { 0 };

	glGetShaderiv(theShader, GL_COMPILE_STATUS, &result);
	if (!result)
	{
		glGetShaderInfoLog(theShader, sizeof(eLog), NULL, eLog);
		std::cout << "Error compiling the %d shader: '%s'\n" << shaderType << eLog;
		return;
	}

	glAttachShader(theProgram, theShader);
}

Program::~Program()
{
	clear();
}

#pragma once

#include <GL\glew.h>

class Mesh
{
public:
	Mesh();

	void initialise(GLfloat* vertices, unsigned int* indices, unsigned int numOfVertices, unsigned int numOfIndices);
	void render();
	void clear();

	~Mesh();

private:
	GLuint _VAO, _VBO, _IBO;
	GLsizei _indexCount;
};


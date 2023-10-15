#pragma once

#include "Mesh.h"
#include "Common.h"

class Box: public Mesh
{
public:
	Box():Mesh(){};
	void initialise();

private:
	std::vector<Vertex> vertices;
	std::vector<GLuint> indices;
};


#pragma once
#include <vector>
#include "Vertex.h"

class Face
{
private:
	std::vector<Vertex> vertices;
	std::vector<Vertex> normals;

public:
	std::vector<Vertex> getVertices();

	void setVertices(std::vector<Vertex>& vertices);

	std::vector<Vertex> getNormals();

	void setNormals(std::vector<Vertex>& normals);
};


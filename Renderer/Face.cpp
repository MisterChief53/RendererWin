#include "Face.h"

std::vector<Vertex> Face::getVertices() {
	return vertices;
}

void Face::setVertices(std::vector<Vertex>& vertices) {
	this->vertices = vertices;
}

std::vector<Vertex> Face::getNormals() {
	return normals;
}

void Face::setNormals(std::vector<Vertex>& normals) {
	this->normals = normals;
}

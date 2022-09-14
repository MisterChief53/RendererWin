#include "Parser.h"
#include <fstream>
#include <iostream>
#include <sstream>

void Parser::parse(std::vector<Face>& faces, std::string path) {
	std::ifstream file(path);
	std::string buffer;

	std::vector<Vertex> vertices;
	std::vector<Vertex> normals;

	//std::vector<Face> faces;

	while (std::getline(file, buffer)) {
		if (buffer[0] == 'v' && buffer[1] == 'n') {//Is a vertex normal
			float x, y, z;
			Vertex vertex;

			buffer.erase(0, 2);

			std::stringstream ss(buffer);

			ss >> x;
			ss >> y;
			ss >> z;

			vertex.setX(x);
			vertex.setY(y);
			vertex.setZ(z);
			normals.push_back(vertex);
		}
		else if (buffer[0] == 'v') {//Is a vertex
			buffer.erase(0, 1);

			float x, y, z;
			Vertex vertex;

			std::stringstream ss(buffer);

			ss >> x;
			ss >> y;
			ss >> z;

			vertex.setX(x);
			vertex.setY(y);
			vertex.setZ(z);
			vertices.push_back(vertex);
		}
		else if (buffer[0] == 'f') {//Is a face
			buffer.erase(0, 1);

			Face face;
			std::vector<Vertex> faceVertices;
			std::vector<Vertex> faceNormals;

			//This assumes all faces are triangulated!
			for (int i = 0; i < buffer.size(); i++) {
				if (buffer[i] == '/') {//Replace /'s with spaces
					buffer[i] = ' ';
				}
			}

			std::stringstream ss(buffer);
			int vertexIndex, uvIndex, normalIndex;

			for (int i = 0; i < 3; i++) {
				ss >> vertexIndex;
				ss >> uvIndex;
				ss >> normalIndex;

				faceVertices.push_back(vertices[vertexIndex - 1]);
				faceNormals.push_back(normals[normalIndex - 1]);
			}

			face.setNormals(faceNormals);
			face.setVertices(faceVertices);

			faces.push_back(face);

		}
	}

	file.close();
}
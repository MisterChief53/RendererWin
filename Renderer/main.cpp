#include "GL\glew.h"
#include "GL\glut.h" //o glut
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "Parser.h"

void display(void)
{
	/*  clear all pixels  */
	glClear(GL_COLOR_BUFFER_BIT);

	glColor3f(1.0, 1.0, 1.0);
	/*
	glBegin(GL_TRIANGLES);
	glVertex3f(0.25, 0.25, 5.0);
	glVertex3f(0.75, 0.25, 5.0);
	glVertex3f(0.75, 0.75, 5.0);
	//glVertex3f(0.25, 0.75, 0.0);		
	glEnd();
	*/
	
	/*
	std::vector<float> cubeVertices{-1,1,10,	2,2,11,		1,1,10,
									2,2,11,		0,0,11,		2,0,11,
									0,2,11,		-1,-1,10,	0,0,11,
									1,-1,10,	0,0,11,		-1,-1,10,
									1,1,10,		2,0,11,		1,-1,10,
									-1,1,10,	1,-1,10,	-1,-1,10,
									-1,1,10,	0,2,11,		2,2,11,
									2,2,11,		0,2,11,		0,0,11,
									0,2,11,		-1,1,10,	-1,-1,10,
									1,-1,10,	2,0,11,		0,0,11,
									1,1,10,		2,2,11,		2,0,11,
									-1,1,10,	1,1,10,		1,-1,10,
									};

	int pos = 0;
	glBegin(GL_TRIANGLES);
	for (int i = 0; i < cubeVertices.size()/9; i++) {
		glVertex3f(cubeVertices[pos], cubeVertices[pos + 1], cubeVertices[pos + 2]);
		pos += 3;
		glVertex3f(cubeVertices[pos], cubeVertices[pos + 1], cubeVertices[pos + 2]);
		pos += 3;
		glVertex3f(cubeVertices[pos], cubeVertices[pos + 1], cubeVertices[pos + 2]);
		pos += 3;
	}
	glEnd();
	*/

	std::vector<Face> faces;
	std::string path = "C:\\Users\\soder\\OneDrive\\Documentos\\cube.obj";

	Parser::parse(faces, path);

	glBegin(GL_TRIANGLES);
	for (int i = 0; i < faces.size(); i++) {
		std::vector <Vertex> vertices = faces[i].getVertices();
		for (int j = 0; j < 3; j++) {
			glVertex3f(vertices[j].getX(), vertices[j].getY(), vertices[j].getZ());
		}
	}
	glEnd();

	glFlush();
}

void init(void)
{
	/*  select clearing (background) color       */
	glClearColor(0.0, 0.0, 0.0, 0.0);

	/*  initialize viewing values  */
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	//glOrtho(0.0, 1.0, 0.0, 1.0, -1.0, 1.0);
	gluPerspective(45.0, 800/600, 0.1, 100.0);
	//gluOrtho2D(0.0, 1.0, 0.0, 1.0);

	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	gluLookAt(0.0, 0.0, 0.0, 0.0, 0.0, 20.0, 0.0, 1.0, 0.0);
}

/*
 *  Declare initial window size, position, and display mode
 *  (single buffer and RGBA).  Open window with "hello"
 *  in its title bar.  Call initialization routines.
 *  Register callback function to display graphics.
 *  Enter main loop and process events.
 */
int main(int argc, char** argv)
{
	
	
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(800, 600);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("hello");
	init();
	glutDisplayFunc(display);
	glutMainLoop();
	
	/*
	std::vector<Face> faces;
	std::string path = "C:\\Users\\soder\\OneDrive\\Documentos\\cube.obj";

	Parser::parse(faces, path);
	
	for (int i = 0; i < faces.size(); i++) {
		std::vector <Vertex> normals = faces[i].getNormals();
		std::vector <Vertex> vertices = faces[i].getVertices();

		std::cout << "Face " << i << ":" << std::endl;

		std::cout << "\t" << "Vertices:" << std::endl;
		for (int j = 0; j < vertices.size(); j++) {
			std::cout << "\t" << vertices[j].getX() << " " << vertices[j].getY() << " " << vertices[j].getZ();
		}
		std::cout << std::endl;

		std::cout << "\t" << "Normals:" << std::endl;
		for (int j = 0; j < normals.size(); j++) {
			std::cout << "\t" << normals[j].getX() << " " << normals[j].getY() << " " << normals[j].getZ();
		}
		std::cout << std::endl;

	}
	*/

	std::cout << "hello" << std::endl;
	

	return 0;   /* ISO C requires main to return int. */
}

#include "GL\glew.h"
#include "GL\glut.h" //o glut
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <random>

#include "Parser.h"

std::vector<Face> faces;
std::string path = "C:\\Users\\soder\\OneDrive\\Documentos\\chango.obj";


float grados = 0;
void display(void)
{
	/*  clear all pixels  */
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glColor3f(1.0, 1.0, 1.0);
	glRotatef(grados, 1, 1, 1);

	glBegin(GL_TRIANGLES);
	for (int i = 0; i < faces.size(); i++) {
		std::vector <Vertex> vertices = faces[i].getVertices();

		std::random_device rd;
		std::mt19937 mt(rd());
		std::uniform_int_distribution<int> dist(100, 255);
		glColor3ub(dist(mt), dist(mt), dist(mt));

		for (int j = 0; j < 3; j++) {
			glVertex3f(vertices[j].getX(), vertices[j].getY(), vertices[j].getZ());
		}
	}
	glEnd();

	grados += 0.0002;
	if (grados > 360) { grados = 0; }

	glutSwapBuffers();
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
	Parser::parse(faces, path);
	
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(800, 600);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("hello");
	init();
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	glutDisplayFunc(display);
	glutIdleFunc(display);
	glutMainLoop();
	

	for (int i = 0; i < faces.size(); i++) {
		std::vector <Vertex> vertices = faces[i].getVertices();
		std::cout << "Face: " << i + 1 << " Vertex: ";
		for (int j = 0; j < 3; j++) {
			std::cout << vertices[j].getX() << " " << vertices[j].getY() << " " << vertices[j].getZ() << " ";
		}
		std::cout << std::endl;
	}

	

	std::cout << "hello" << std::endl;
	

	return 0;   /* ISO C requires main to return int. */
}

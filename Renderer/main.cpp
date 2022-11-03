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
		std::vector <Vertex> vertices = faces[i].vertices;

		std::random_device rd;
		std::mt19937 mt(rd());
		std::uniform_int_distribution<int> dist(100, 255);
		glColor3ub(dist(mt), dist(mt), dist(mt));

		for (int j = 0; j < 3; j++) {
			glVertex3f(vertices[j].x, vertices[j].y, vertices[j].z);
		}
	}
	glEnd();

	grados += 0.02;
	//t += 0.00001f;
	if (grados > 360) { grados = 0; }

	glutSwapBuffers();
	glFlush();
}

/*

void bezier() {
	int p1, p2, p3, p4;//En realidad estos solo son los puntos que tenemos, los podemos poner globales
	float nx, ny, nz;
	float t = 0.0f;

	nx = pow((t - 1), 2) * p1.x + 3 * (1 - t) * p2.x) + termino + termino; En realidad ponemos la ecuacion real aqui
	/*ny = pow((t - 1), 2) * p1.y + 3 * (1 - t) * p2.y) + termino + termino;En realidad ponemos la ecuacion real aqui
	/*nz = pow((t - 1), 2) * p1.z + 3 * (1 - t) * p2.z)+ termino + termino;En realidad ponemos la ecuacion real aqui

	//luego regresamos y etc.  El punto es calcular cada punto de los que generan la curva de bezier. 
	//Luego con estos puntos usamos una matriz de traslacion para transladar los puntos a donde dice bezier
}
*/
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
		std::vector <Vertex> vertices = faces[i].vertices;
		std::cout << "Face: " << i + 1 << " Vertex: ";
		for (int j = 0; j < 3; j++) {
			std::cout << vertices[j].x << " " << vertices[j].y << " " << vertices[j].z << " ";
		}
		std::cout << std::endl;
	}

	

	std::cout << "hello" << std::endl;
	

	return 0;   /* ISO C requires main to return int. */
}

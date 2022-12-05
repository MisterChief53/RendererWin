#include "GL\glew.h"
#include "GL\glut.h" //o glut
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <random>
#include <cmath>

#include "Parser.h"
#include "Mesh.h"
std::vector<Face> faces;
std::string path = "C:\\Users\\soder\\OneDrive\\Documentos\\chango.obj";
std::vector<Mesh> meshes(2);

float grados = 0;
float bulletX = 0, bulletY = 0, bulletZ = 0;
float t = 0.0f;
float degreeX = 0.00f, degreeY = 0.00f, degreeZ = 0.00f;
float centerX = -8, centerY = -10, centerZ = 20;
int frames = 30;
int count = 0;


void bezier();

float rotateX(float degreeX, float x);
std::vector<float> pistolRecoil(float x, float y, float z);

void display(void)
{
	/*  clear all pixels  */
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glColor3f(1.0, 1.0, 1.0);
	//glRotatef(grados, 1, 1, 1);

	glBegin(GL_TRIANGLES);
	
	for (int i = 0; i < meshes[0].faces.size(); i++) {
		std::vector <Vertex> vertices = meshes[0].faces[i].vertices;

		glColor3ub(255, 10, 10);

		for (int j = 0; j < 3; j++) {
			std::vector<float> points = pistolRecoil(vertices[j].x, vertices[j].y, vertices[j].z);
			glVertex3f(vertices[j].x + (points[0] - vertices[j].x), vertices[j].y + (points[1] - vertices[j].y), vertices[j].z + (points[2] - vertices[j].z));
		}
	}
	

	for (int i = 0; i < meshes[1].faces.size(); i++) {
		std::vector <Vertex> vertices = meshes[1].faces[i].vertices;

		glColor3ub(10, 255, 10);
		for (int j = 0; j < 3; j++) {
			glVertex3f(vertices[j].x + bulletX, vertices[j].y + bulletY, vertices[j].z + bulletZ);
		}
	}
	glEnd();

	bezier();
	if (t <= 0.9) {
		t += 0.01f;
	}

	if (count < frames) {
		//degreeX += 0.01f;
		//degreeY += 0.01f;
		degreeZ += 0.01f;
	}
	
	count++;

	glutSwapBuffers();
	glFlush();
}

void flatShading(std::vector <Vertex> vertices, float& factor) {
	for (int i = 0; i < vertices.size(); i++) {

	}
}



std::vector<float> pistolRecoil(float x, float y, float z) {
	float nx = x - centerX;
	float ny = y - centerY;
	float nz = z - centerZ;

	x = nx;
	y = ny;
	z = nz;

	
	nx = x;
	ny = (cos(degreeX) * y) - (sin(degreeX) * z);
	nz = (sin(degreeX) * y) + (cos(degreeX) * z);
	

	
	x = nx;
	y = ny;
	z = nz;
	

	
	nx = (cos(degreeY) * x) + (sin(degreeY) * z);
	ny = y;
	nz = ( - sin(degreeY) * x) + (cos(degreeY) * z);
	
	
	x = nx;
	y = ny;
	z = nz;
	

	nx = (cos(degreeZ) * x) - (sin(degreeZ) * y);
	ny = (sin(degreeZ) * x) + (cos(degreeZ) * y);
	nz = z;
	

	nx = nx + centerX;
	ny = ny + centerY;
	nz = nz + centerZ;

	std::vector<float> points = { nx,ny,nz };
	return points;
}

void bezier() {
	//int p1, p2, p3, p4;//En realidad estos solo son los puntos que tenemos, los podemos poner globales
	float x0 = 0, x1 = 7, x2 = 10, x3 = 14;
	float y0 = 0, y1 = -1, y2 = -3, y3 = -5;
	float z0 = 0, z1 = 0, z2 = 0, z3 = 0;

	bulletX = pow(1 - t, 3) * x0 + 3 * pow(1 - t, 2) * t * x1 + 3 * (1 - t) * pow(t, 2) * x2 + pow(t, 3) * x3;
	bulletY = pow(1 - t, 3) * y0 + 3 * pow(1 - t, 2) * t * y1 + 3 * (1 - t) * pow(t, 2) * y2 + pow(t, 3) * y3;
	bulletZ = pow(1 - t, 3) * z0 + 3 * pow(1 - t, 2) * t * z1 + 3 * (1 - t) * pow(t, 2) * z2 + pow(t, 3) * z3;
}

float pistolX = 0, pistolY = 0, pistolZ = 0;




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

	gluLookAt(0.0, 0.0, -10.0, 0.0, 0.0, 20.0, 0.0, 1.0, 0.0);
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
	
	Parser::parse(meshes[0].faces, "C:\\Users\\soder\\OneDrive\\Documentos\\pistol.obj");
	Parser::parse(meshes[1].faces, "C:\\Users\\soder\\OneDrive\\Documentos\\bullet.obj");
	
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
	
	/*
	for (int i = 0; i < faces.size(); i++) {
		std::vector <Vertex> vertices = faces[i].vertices;
		std::cout << "Face: " << i + 1 << " Vertex: ";
		for (int j = 0; j < 3; j++) {
			std::cout << vertices[j].x << " " << vertices[j].y << " " << vertices[j].z << " ";
		}
		std::cout << std::endl;
	}
	*/

	

	std::cout << "hello" << std::endl;
	

	return 0;   /* ISO C requires main to return int. */
}

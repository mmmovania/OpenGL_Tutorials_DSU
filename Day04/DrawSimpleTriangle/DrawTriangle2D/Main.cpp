#include <gl/freeglut.h>
#include <iostream>
#include <vector>

using namespace std;

int WIDTH = 500;
int HEIGHT = 500;
   
void DrawGraph() {
	glBegin(GL_LINES);

	//draw Minor grid lines
	glColor3f(0.75, 0.75, 0.75);

	for (int i = 0; i <= WIDTH; i += 5) {
		if (i % 50 == 0)
			continue; 
		glVertex2i(i, 0);	glVertex2i(i, HEIGHT); 
	}

	for (int i = 0; i <= HEIGHT; i += 5) {
		if (i % 50 == 0)
			continue; 

		glVertex2i(0, i);	glVertex2i(WIDTH, i);
	}

	//major grid lines
	glColor3f(0.5, 0.5, 0.5);
	for (int i = 0; i <= WIDTH; i += 50) {
		glVertex2i(i, 0);	glVertex2i(i, HEIGHT);
	}
	for (int i = 0; i <= HEIGHT; i += 50) {
		glVertex2i(0, i);	glVertex2i(WIDTH, i);
	}
	glEnd();
}
  
void OnResize(int nw, int nh) {
	glViewport(0, 0, nw, nh);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	WIDTH = nw;
	HEIGHT = nh;
	glOrtho(0, WIDTH, 0, HEIGHT, 0, 1);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void OnRender(void) {
	glClear(GL_COLOR_BUFFER_BIT); 
	DrawGraph(); 

	//a simple gradient triangle
	/*
	int x1 = WIDTH >> 1;
	int y1 = HEIGHT >> 1;
	int x2 = x1 + 100;
	int x3 = x1 + 50;
	int y2 = y1;
	int y3 = y1 + 100;

	glBegin(GL_TRIANGLES);
		glColor3f(1, 0., 0.);	glVertex2i(x1, y1);
		glColor3f(0, 1., 0.);	glVertex2i(x2, y2);
		glColor3f(0, 0., 1.);	glVertex2i(x3, y3);
	glEnd();
	*/

	//full triangle
	int x1 = 0;
	int y1 = 0;
	int x2 = WIDTH;
	int x3 = WIDTH >> 1; 
	int y2 = 0;
	int y3 = HEIGHT;

	glBegin(GL_TRIANGLES);
		glColor3f(1, 0., 0.);	glVertex2i(x1, y1);
		glColor3f(0, 1., 0.);	glVertex2i(x2, y2);
		glColor3f(0, 0., 1.);	glVertex2i(x3, y3);
		glEnd();
	glutSwapBuffers();
}
void OnInit() {
	glClearColor(1, 1, 1, 1);
	glPointSize(5);
	glEnable(GL_POINT_SMOOTH); 
}
 

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
	glutInitWindowSize(WIDTH, HEIGHT);
	glutCreateWindow("Drawing Simple 2D Triangle");

	glutDisplayFunc(OnRender);
	glutReshapeFunc(OnResize); 

	OnInit();

	glutMainLoop();
	return 0;
}
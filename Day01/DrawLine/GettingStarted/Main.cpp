#include <gl/freeglut.h>
#include <iostream>

using namespace std;

const int WIDTH = 512;
const int HEIGHT = 512;

void OnRender(void) {
	glClear(GL_COLOR_BUFFER_BIT);

	//draw line 
	
	glBegin(GL_LINES);
		//diagonal line from center to upper right
		//glVertex2f(0, 0);		glVertex2f(1, 1);
		

		//horizontal line
		//glVertex2f(-1, 0);		glVertex2f(1, 0);
		for (int i = -5; i <= 5; ++i) {
			float x = float(i) / 5;
			glVertex2f(x, -1);			glVertex2f(x,  1);
			glVertex2f(-1, x);			glVertex2f(1, x);
		}
	glEnd();

	glutSwapBuffers();
}
void OnInit() {
	glClearColor(0.5, 0.5, 1, 1);
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
	glutInitWindowSize(WIDTH, HEIGHT);
	glutCreateWindow("Getting Started with OpenGL");

	glutDisplayFunc(OnRender);

	OnInit();
	glutMainLoop();
	return 0;
}
#include <gl/freeglut.h>
#include <iostream>

using namespace std;

const int WIDTH = 512;
const int HEIGHT = 512;

void DrawGraph() {
	glBegin(GL_LINES);
	for (int i = -100; i <= 100; i += 2) {
		if (i % 10 == 0)
			glColor3f(0.5, 0.5, 0.5);
		else
			glColor3f(0.75, 0.75, 0.75);

		float x = i / 100.0f;
		glVertex2f(x, -1);	glVertex2f(x, 1);
		glVertex2f(-1, x);	glVertex2f(1, x);
	}
	glEnd();
}

void OnRender(void) {
	glClear(GL_COLOR_BUFFER_BIT);
	 	
	DrawGraph();

	glutSwapBuffers();
}
void OnInit() {
	glClearColor(1, 1, 1, 1);
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
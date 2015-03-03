#include <gl/freeglut.h>
#include <iostream>

using namespace std;

const int WIDTH = 512;
const int HEIGHT = 512;

void OnRender(void) {
	glClear(GL_COLOR_BUFFER_BIT);
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
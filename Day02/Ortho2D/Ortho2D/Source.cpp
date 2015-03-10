#include <gl/freeglut.h>

const int width = 512;
const int height = 512;

void OnRender() {
	glClear(GL_COLOR_BUFFER_BIT);
	
	glBegin(GL_LINES);
		//glColor3f(1, 0, 0);  glVertex2f(-1, -1);
		//glColor3f(0, 1, 0);  glVertex2f(1, 1);

		glColor3f(1, 0, 0);  glVertex2f(0,0);
		glColor3f(0, 1, 0);  glVertex2f(width, height);
	glEnd();
	
	glutSwapBuffers(); 
}

void OnResize(int w, int h) {
	glViewport(0, 0, w, h);
	
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glOrtho(0, w, 0, h, 0, 1);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void OnInit() {
	//glClearColor(0.5, 0.5, 1, 0);
}

int main(int argc, char** argv) {

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize(width, height);
	glutCreateWindow("Testing Orthographic Projection");

	glutDisplayFunc(OnRender);
	glutReshapeFunc(OnResize);

	OnInit();

	glutMainLoop();
	return 0;
}
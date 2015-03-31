#include <gl/freeglut.h>

const int width = 800;
const int height = 800;
int angle = 0;
void OnRender() {
	glClear(GL_COLOR_BUFFER_BIT);
	/*
	glBegin(GL_LINES);
		glColor3f(1, 0, 0);
		glVertex2f(0,0);
	 	glVertex2f(1, 1);
	glEnd();
	*/

	//glRectf(-0.5, -0.5, 0.5, 0.5);
	glLoadIdentity();

	//glTranslatef(-0.5, -0.5, 0);
	//glRectf(0, 0, 1, 1);

	glRotatef(angle+=5, 0, 0, 1); 
	glRectf(-0.5, -0.5, 0.5, 0.5);

	//glScalef(0.25, 0.25, 1);
	//glRectf(-0.5, -0.5, 0.5, 0.5);

	glutSwapBuffers();
}

void OnInit() {
	glClearColor(0.5, 0.5, 1.0f, 1.0f);
}

void OnIdle() {
	glutPostRedisplay();
}

int main(int argc, char** argv) {

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
	glutInitWindowSize(width, height);
	glutCreateWindow("Test Translation");

	glutDisplayFunc(OnRender);
	glutIdleFunc(OnIdle);

	OnInit();

	glutMainLoop();

	return 0;
}
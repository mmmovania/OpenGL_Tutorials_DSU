#include <GL/freeglut.h>

const int width = 512;
const int height = 512;
int angle = 0;
void DrawGrid(int size = 10) {
	glBegin(GL_LINES);
	glColor3f(0.75, 0.75, 0.75);
	for (int i = -size; i <= size; i++) {
		glVertex3f(-size, 0, i);
		glVertex3f( size, 0, i);

		glVertex3f(i, 0, -size);
		glVertex3f(i , 0, size);
	}
	 
	glEnd();
}

void OnRender() {
	glClear(GL_COLOR_BUFFER_BIT);
	glLoadIdentity();

	gluLookAt(0, 1, 5, 0, 0, 0, 0, 1, 0);	
	DrawGrid();
	
	glColor3f(0, 1, 0);

	//glTranslatef(1, 0, 0);
	
	//glRotatef(angle++, 0, 1, 0);
	//glutWireCube(1);

	//order of transforms
	
	//glScalef(angle*0.01, 1, 1);
	/*
	glRotatef(angle++, 0, 1, 0);
	glTranslatef(1, 0, 0);	
	glutWireCube(1);
	*/
	
	glTranslatef(1, 0, 0);
	glRotatef(angle++, 0, -1, 0);	
	glScalef(angle*0.01, 1, 1);
	glutWireCube(1);
	
	//glutSolidCube(1);

	glutSwapBuffers();
}

void OnInit() {
	glClearColor(0.5, 0.5, 1, 1); 
}

void OnResize(int nw, int nh) {
	glViewport(0, 0, nw, nh);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60, float(nw) / nh, 0.1f, 100);

	glMatrixMode(GL_MODELVIEW);	 
}


void OnIdle() {
	glutPostRedisplay();
}
int main(int argc, char** argv) {

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
	glutInitWindowSize(width, height);
	glutCreateWindow("Test 3D");

	glutDisplayFunc(OnRender);
	glutReshapeFunc(OnResize);
	glutIdleFunc(OnIdle);

	OnInit();

	glutMainLoop();

	return 0;
}
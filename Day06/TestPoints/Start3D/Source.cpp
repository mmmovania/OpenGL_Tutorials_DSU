#include <GL/freeglut.h>
#include <cmath>

const int width = 512;
const int height = 512;
int angle = 0;
const int N = 5;
float t = 0;
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

	gluLookAt(0, 1, N, 0, 0, 0, 0, 1, 0);	
	DrawGrid();
	
	glScalef(0.2, 0.2, 0.2);
	glBegin(GL_POINTS);
	for (int z = -N; z <= N; ++z) {
		for (int x = -N; x <= N; ++x) {
			float r = (x + N) / (2.0f*N);
			float b = (z + N) / (2.0f*N);
			glColor3f(r, 1, b);
			float y = sinf(x+t);
			//float y = sinf(z + t);
			//float y = sinf(x + z + t);
			//float y = sinf(10*sqrtf(x*x + z*z)+t);
			glVertex3f(x, y, z);
		}
	}
	glEnd();

	glutSwapBuffers();
}

void OnInit() {
	glClearColor(0.5, 0.5, 1, 1); 
	glPointSize(10);
}

void OnResize(int nw, int nh) {
	glViewport(0, 0, nw, nh);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60, float(nw) / nh, 0.1f, 100);

	glMatrixMode(GL_MODELVIEW);	 
}


void OnIdle() {
	t += 0.1f;
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
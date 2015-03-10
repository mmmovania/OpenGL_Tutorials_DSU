#include <gl/freeglut.h>

const int width = 512;
const int height = 512;

int endX = 0;
int endY = 0;
int startX = 0;
int startY = 0;

void OnRender() {
	glClear(GL_COLOR_BUFFER_BIT);
	
	glBegin(GL_LINES);

		//drawing graph
		//minor grid lines
		glColor3f(0.75f, 0.75f, 0.75f);
		for (int i = -50; i <= 50; ++i) {
			float t = ((float(i) / 50) + 1.0) * 0.5;
			float x = t * width;
			float y = t * height;
			glVertex2f(x, 0);			glVertex2f(x, height);
			glVertex2f(0, y);			glVertex2f(width, y);
		}

		//major grid lines
		glColor3f(0.5f, 0.5f, 0.5f);
		for (int i = -5; i <= 5; ++i) {
			float t = ((float(i) / 5) + 1.0) * 0.5;
			float x = t * width;
			float y = t * height;
			glVertex2f(x, 0);			glVertex2f(x, height);
			glVertex2f(0, y);			glVertex2f(width, y);
		}
		
		//drawing our line
		glColor3f(0, 0, 1);		glVertex2i(startX,startY);		glVertex2i(endX, endY);
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
void OnMouseMove(int x, int y) {
	endX = x;
	endY = height-y; 
	glutPostRedisplay();
}

void OnMouseDown(int button, int state, int x, int y) {
	// only start motion if the left button is pressed
	if (button == GLUT_LEFT_BUTTON) {

		// when the button is released
		if (state == GLUT_UP) {
			startX = x;
			startY = height-y;
		} 
	}
}

void OnInit() {
	glClearColor(1, 1, 1, 1);
}

int main(int argc, char** argv) {

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize(width, height);
	glutCreateWindow("Testing Orthographic Projection");

	glutDisplayFunc(OnRender);
	glutReshapeFunc(OnResize);

	glutMotionFunc(OnMouseMove);
	glutMouseFunc(OnMouseDown);

	OnInit();

	glutMainLoop();
	return 0;
}
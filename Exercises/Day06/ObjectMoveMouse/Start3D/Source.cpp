#define _USE_MATH_DEFINES
#include <cmath>

#include <GL/freeglut.h>

//#define ROTATE_XZ_PLANE

const int width = 512;
const int height = 512;

//object spherical coordinates
float theta = 0;
float phi = 0;
float radius = 5;

float oldX = 0, oldY = 0;
int state = -1;

float objPosition[3];

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

void DrawLocalAxes(int size = 1) {
	glBegin(GL_LINES);
		glColor3f(1, 0, 0); glVertex3f(0, 0, 0); glVertex3f(size, 0, 0);
		glColor3f(0, 1, 0); glVertex3f(0, 0, 0); glVertex3f(0, size, 0);
		glColor3f(0, 0, 1); glVertex3f(0, 0, 0); glVertex3f(0, 0, size);
	glEnd();
}

void OnRender() {
	glClear(GL_COLOR_BUFFER_BIT);
	glLoadIdentity();

	gluLookAt(0, 3, 10, 0, 0, 0, 0, 1, 0);	
	DrawGrid();
	
	glColor3f(0, 1, 0);
	 	
	//this will cause object to rotate at y=0 plane in a circular path on XZ plane
	#ifdef ROTATE_XZ_PLANE 
	glTranslatef(objPosition[0], objPosition[1], objPosition[2]);
	glRotatef(-theta*57.3, 0, 1, 0);
	#else 
	glTranslatef(objPosition[0], objPosition[1], objPosition[2]);
	glRotatef(-theta*57.3, 0, 1, 0);
	glRotatef(  -phi*57.3, 0, 0, 1);
	#endif 

	DrawLocalAxes();
	glColor3f(1, 1, 1);
	glutWireCube(1);

	glutSwapBuffers();
}

void OnInit() {
	//modify the object position
	#ifdef ROTATE_XZ_PLANE
	objPosition[0] = radius * cosf(theta); 
	objPosition[1] = 0; 
	objPosition[2] = radius * sinf(theta); 
	#else
	objPosition[0] = radius * cosf(theta) *sinf(phi);
	objPosition[1] = radius * cosf(phi);
	objPosition[2] = radius * sinf(theta) *sinf(phi);
	#endif
	glClearColor(0.5, 0.5, 1, 1); 
}
//mouse down event handler
void OnMouseDown(int button, int s, int x, int y)
{
	if (s == GLUT_DOWN)
	{
		oldX = x;
		oldY = y;
	}

	if (button == GLUT_LEFT_BUTTON)
		state = 0; 
	else
		state = 1;	
}

//mouse move event handler
void OnMouseMove(int x, int y)
{
	if (state == 0) { 
		theta += (oldX - x) / 60.0f;
		phi += (y - oldY) / 60.0f;

		//modify the object position
		#ifdef ROTATE_XZ_PLANE
		objPosition[0] = radius * cosf(theta); 
		objPosition[1] = 0; 
		objPosition[2] = radius * sinf(theta); 
		#else
		objPosition[0] = radius * cosf(theta)*sinf(phi);
		objPosition[1] = radius * cosf(phi);
		objPosition[2] = radius * sinf(theta)*sinf(phi); 
		#endif
	} 

	oldX = x;
	oldY = y;

	glutPostRedisplay();
}
void OnResize(int nw, int nh) {
	glViewport(0, 0, nw, nh);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60, float(nw) / nh, 0.1f, 100);

	glMatrixMode(GL_MODELVIEW);	 
} 

int main(int argc, char** argv) {

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
	glutInitWindowSize(width, height);
	glutCreateWindow("Rotate 3D Object using Mouse");

	glutDisplayFunc(OnRender);
	glutReshapeFunc(OnResize); 
	glutMouseFunc(OnMouseDown);
	glutMotionFunc(OnMouseMove);

	OnInit();

	glutMainLoop();

	return 0;
}
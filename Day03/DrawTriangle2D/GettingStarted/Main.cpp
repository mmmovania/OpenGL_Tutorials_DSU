#include <gl/freeglut.h>
#include <iostream>
#include <vector>

using namespace std;

int WIDTH = 500;
int HEIGHT = 500;

struct Triangle { int x1, y1, x2, y2, x3, y3; bool bDone; } t;
vector<Triangle> triangles;

bool bMouseDown = false;
int iSnapMode = 1; 
int iFactor = 5; 
int iCounter = 0; 

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

void OnMouseDown(int button, int state, int x, int y) {
	if (button == GLUT_LEFT_BUTTON) {
		if (state == GLUT_DOWN) {
			++iCounter;
			if (iSnapMode != 0) {
				int s = x / iFactor;
				x = iFactor * s;
				s = y / iFactor;
				y = iFactor * s;
			}
			
			
			if (iCounter == 1) {
				t.bDone = false;  
				t.x1 = x;
				t.y1 = HEIGHT - y;  
			}
			if (iCounter == 2) {
				t.x2 = x;
				t.y2 = HEIGHT - y; 
			}

			if (iCounter == 3) {
				t.x3 = x;
				t.y3 = HEIGHT - y; 
				t.bDone = true;
				iCounter = 0;
				triangles.push_back(t);
				glutPostRedisplay();
			}

			bMouseDown = true;
		} 
	} 
} 

void DrawTriangles() {
	if (triangles.size() > 0) {

		//fill zone of triangle
		glBegin(GL_TRIANGLES);
			glColor3f(0, 0, 1);
			for (size_t i = 0; i < triangles.size(); ++i) {			
				Triangle t = triangles[i];
				if (t.bDone) {
					glVertex2i(t.x1, t.y1);
					glVertex2i(t.x2, t.y2);
					glVertex2i(t.x3, t.y3);
				}
			}
		glEnd();

		//border 
		glColor3f(0, 0, 0);
		for (size_t i = 0; i < triangles.size(); ++i) {
			Triangle t = triangles[i];
			glBegin(GL_LINE_LOOP);
			if (t.bDone) {
				glVertex2i(t.x1, t.y1);
				glVertex2i(t.x2, t.y2);
				glVertex2i(t.x3, t.y3);
			}
			glEnd();
		} 

		//draw points (vertices)
		glBegin(GL_POINTS);
		glColor3f(1, 0, 0);
		for (size_t i = 0; i < triangles.size(); ++i) {
			Triangle t = triangles[i];
			if (t.bDone) {
				glVertex2i(t.x1, t.y1);
				glVertex2i(t.x2, t.y2);
				glVertex2i(t.x3, t.y3);
			}
		}
		glEnd();
	}
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
	DrawTriangles();

	//for displaying current triangle
	if (!t.bDone) {
		glBegin(GL_TRIANGLES);
			glColor3f(0.75f, 0.75f, 0.75f);
			glVertex2i(t.x1, t.y1);
			glVertex2i(t.x2, t.y2);
			glVertex2i(t.x3, t.y3);
		glEnd();
	}

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
	glutCreateWindow("Drawing 2D Triangle");

	glutDisplayFunc(OnRender);
	glutReshapeFunc(OnResize);
	glutMouseFunc(OnMouseDown); 

	OnInit();

	glutMainLoop();
	return 0;
}
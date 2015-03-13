#include <gl/freeglut.h>
#include <iostream>
#include <vector>

using namespace std;

int WIDTH = 500;
int HEIGHT = 500;

struct Line { int x1, y1, x2, y2; };
vector<Line> lines; 

bool bMouseDown = false;
int iSnapMode = 0; 
int factor = 1;

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
			if (iSnapMode != 0) {
				int s = x / factor;
				x = factor * s;
				s = y / factor;
				y = factor * s;
			}
			Line line;
			line.x1 = x;
			line.y1 = HEIGHT - y;	

			lines.push_back(line);
			bMouseDown = true;
		} else {
			if (iSnapMode != 0) {
				int s = x / factor;
				x = factor * s;
				s = y / factor;
				y = factor * s;
			}
			lines[lines.size()-1].x2 = x;
			lines[lines.size() - 1].y2 = HEIGHT - y;
			bMouseDown = false;
		} 
	} 
}

void OnMouseMove(int x, int y) {
	if (bMouseDown) {
		if (iSnapMode!=0) {
			int s = x / factor;
			x = factor*s;
			s = y / factor;
			y = factor*s;
		}
		lines[lines.size() - 1].x2 = x;
		lines[lines.size() - 1].y2 = HEIGHT - y;
	}
	glutPostRedisplay();
}

void DrawLines() {
	if (lines.size() > 0) {
		glBegin(GL_LINES);
			glColor3f(0, 0, 1);
			for (size_t i = 0; i < lines.size(); ++i) {
				Line line = lines[i];
				glVertex2i(line.x1, line.y1);
				glVertex2i(line.x2, line.y2);
			}
		glEnd();

		//draw end points
		glBegin(GL_POINTS);
			glColor3f(1, 0, 0);
			for (size_t i = 0; i < lines.size(); ++i) {
				Line line = lines[i];
				glVertex2i(line.x1, line.y1);
				glVertex2i(line.x2, line.y2);
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
	DrawLines();
	glutSwapBuffers();
}
void OnInit() {
	glClearColor(1, 1, 1, 1);
	glPointSize(5);
	glEnable(GL_POINT_SMOOTH);
}

void OnKey(unsigned char key, int x, int y) {
	if (key == '1') {
		iSnapMode = 1;
		factor = 50;
		glutSetWindowTitle("Getting Started with OpenGL [Snapping ON: Major Grid Points]");
	} else if (key == '2') {
		iSnapMode = 2;
		factor = 5;
		glutSetWindowTitle("Getting Started with OpenGL [Snapping ON: Minor Grid Points]");
	} else {
		iSnapMode = 0;
		factor = 1;
		glutSetWindowTitle("Getting Started with OpenGL [Snapping Off]");
	}
	glutPostRedisplay();
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
	glutInitWindowSize(WIDTH, HEIGHT);
	glutCreateWindow("Getting Started with OpenGL [Snapping Off]");

	glutDisplayFunc(OnRender);
	glutReshapeFunc(OnResize);
	glutMouseFunc(OnMouseDown);
	glutMotionFunc(OnMouseMove);
	glutKeyboardFunc(OnKey);

	OnInit();

	glutMainLoop();
	return 0;
}
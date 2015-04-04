#define _USE_MATH_DEFINES
#include <cmath>

#include <gl/freeglut.h>
#include <iostream>

const int width = 512;
const int height = 512;

int		numSides	= 6;	//number of vertices of the polygon
float	N			= 40;	//number of polygons to draw
float	invN = 1.0f / N;	
float	dTheta = float(numSides);	//change in rotation angle for each new polygon
float	dScale = 0.95f;		//change in scale for each new polygon
float	colors[4][3] = { { 1, 0, 0 }, { 0, 1, 0 }, { 0, 0, 1 }, { 1, 0, 1 } };	//colors of polygons
int		index = numSides - 3;	//index of polygon for choosing the color

void FillNGon(float x0=0, float y0=0, float radius=1, int numSegments = 3) {
	float dTheta = float(2 * M_PI) / numSegments;
	float theta = float(M_PI / 2.0f);
	glBegin(GL_TRIANGLE_FAN);
	for (int i = 0; i < numSegments; ++i) {
		float x_prime = x0 + radius * cos(theta);
		float y_prime = y0 + radius * sin(theta);
		theta += dTheta;
		glVertex2f(x_prime, y_prime);
	}
	glEnd();
}

void DrawNGon(float x0 = 0, float y0 = 0, float radius = 1, int numSegments = 3) {
	float dTheta = float(2 * M_PI) / numSegments;
	float theta = float(M_PI / 2.0f);
	glBegin(GL_LINE_LOOP);
	for (int i = 0; i < numSegments; ++i) {
		float x_prime = x0 + radius * cos(theta);
		float y_prime = y0 + radius * sin(theta);
		theta += dTheta;
		glVertex2f(x_prime, y_prime);
	}
	glEnd();
}

void OnRender() {
	glClear(GL_COLOR_BUFFER_BIT);
	 
	//clear modelview matrix
	glLoadIdentity();
	 
	for (int i = 0; i < N; ++i) {
		glColor4f(colors[index][0], colors[index][1], colors[index][2], i*invN);
		FillNGon(0, 0, 1, numSides);

		glColor4f(0.0, 0.0, 0.0, 1);
		DrawNGon(0, 0, 1, numSides); 

		glRotatef(dTheta, 0, 0, 1);
		glScalef(dScale, dScale, dScale);
	}
	glutSwapBuffers();
}

void OnInit() {
	glClearColor(1, 1, 1, 1);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_LINE_SMOOTH); 
}
 
void OnKey(unsigned char k, int x, int y) {
	if (k == '-') numSides--; 
	if (k == '=') numSides++;  

	numSides = (int)(fminf(6.0f, fmaxf(3.0f, float(numSides))));
 	index = numSides - 3;

	if (numSides == 3)
		dScale = 0.925f;
	else if (numSides == 4 )
		dScale = 0.935f;
	else
		dScale = 0.95f;
	
	dTheta = float(numSides);
	
	glutPostRedisplay();
}
int main(int argc, char** argv) {

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
	glutInitWindowSize(width, height);
	glutCreateWindow("Twisted Polygons");

	glutDisplayFunc(OnRender); 
	glutKeyboardFunc(OnKey);

	OnInit();

	std::cout << "Press '-' key to reduce and '=' to increase number of vertices" << std::endl;
	
	glutMainLoop();

	return 0;
}
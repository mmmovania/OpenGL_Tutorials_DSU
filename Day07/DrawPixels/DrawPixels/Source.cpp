#include <GL/freeglut.h>

const int WIDTH = 512;
const int HEIGHT = 512; 

const int H_WIDTH = WIDTH >> 1;
const int H_HEIGHT = HEIGHT >> 1;

//global array to contain our image pixels
GLubyte g_pixels[HEIGHT][WIDTH];

void OnRender() {
	glClear(GL_COLOR_BUFFER_BIT);
	glLoadIdentity();

	glDrawPixels(WIDTH, HEIGHT, GL_LUMINANCE, GL_UNSIGNED_BYTE, g_pixels);
	 
	glutSwapBuffers();
}

void OnInit() {
	glClearColor(0.5, 0.5, 1, 1); 

	//fill the image with checker pattern
	for (int i = 0; i < HEIGHT; ++i) {
		for (int j = 0; j < WIDTH; ++j) {
			g_pixels[i][j] = ((i<H_HEIGHT && j<H_WIDTH) || (i>H_HEIGHT && j>H_WIDTH)) ? 255 : 0;
		}
	}
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
	glutInitWindowSize(WIDTH, HEIGHT);
	glutCreateWindow("Draw Pixels in OpenGL");

	glutDisplayFunc(OnRender);  

	OnInit();

	glutMainLoop();

	return 0;
}
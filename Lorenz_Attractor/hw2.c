/* Colin O'Connell, HW2 Lorenz Attractor
Code taken from: 
	* professor's example files (ex6) and lorenz.c - most functions taken right from this
	* use of Lorenz function taken from https://github.com/untra/lorenz/blob/master/lorenz.c
*/

#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#define GL_GLEXT_PROTOTYPES
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

/*  Lorenz Parameters  */
double s = 10;
double b = 2.6666;
double r = 28;

//  Globals
int th = 125;      // Azimuth of view angle
int ph = 20;       // Elevation of view angle
int mode = 1;      // Dimension (1-4)
double z = 0;      // Z variable
double w = 0.04;   // W variable
double dim = 2;    // Dimension of orthogonal box
char* text[] = { "","2D","3D constant Z","3D","4D" };  // Dimension display text

int n = 50000; //sets n time steps to be 50,000
double lz[50000][3]; //stores all the values for the actual attractor

/*
 *  Convenience routine to output raster text
 *  Use VARARGS to make this more flexible
 */
#define LEN 8192  // Maximum length of text string
void Print(const char* format, ...)
{
	char    buf[LEN];
	char*   ch = buf;
	va_list args;
	//  Turn the parameters into a character string
	va_start(args, format);
	vsnprintf(buf, LEN, format, args);
	va_end(args);
	//  Display the characters one at a time at the current raster position
	while (*ch)
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *ch++);
}

// The Lorenz Attractor function that assigns the coordinates for the attractor, modified from professor's code
void lorenzattract() {
	/*  Coordinates  */
	double x = 1;
	double y = 1;
	double z = 1;
	/*  Time step  */
	double dt = 0.001;

	/*
	 *  Integrate 50,000 steps (50 time units with dt = 0.001)
	 *  Explicit Euler integration
	 */
	for (int i = 0; i < n; i++){
		double dx = s * (y - x);
		double dy = x * (r - z) - y;
		double dz = x * y - b * z;
		x += dt * dx;
		y += dt * dy;
		z += dt * dz;

		//Store the values in the global lorenz array
		lz[i][0] = x * w;
		lz[i][1] = y * w;
		lz[i][2] = z * w;
	}
}

/*
 *  Display the scene
 */
void display()
{
	//Call the Lorenz Attractor function
	lorenzattract();
	//  Clear the image
	glClear(GL_COLOR_BUFFER_BIT);
	//  Reset previous transforms
	glLoadIdentity();
	//  Set view angle
	glRotated(ph, 1, 0, 0);
	glRotated(th, 0, 1, 0);

	glBegin(GL_LINE_STRIP);
	double rgb[3] = { 0, 0, 0 };
	for (int i = 0; i < n; i++) {
		glColor3dv(rgb); //assigns the color value to that vertex
		glVertex3dv(lz[i]); //assigns the lorenz value to where the line is drawn

		// Fun way of coloring the line
		if (i % 5 == 0) { //if it's divisible of 5, increment the red value
			rgb[0] += 0.001;
		}
		if (i % 3 == 0) { //if it's divisible of 3, increment the green value
			rgb[1] += 0.001;
		}
		else{ //otherwise increment the blue value
			rgb[2] += 0.001;
		}

		//Now check to make sure each value hasn't gone over 1 and if so put it back to 0
		if (rgb[0] > 1) {
			rgb[0] = 0;
		}
		if (rgb[1] > 1) {
			rgb[1] = 0;
		}
		if (rgb[2] > 1) {
			rgb[2] = 0;
		}
	}
	glEnd();

	//  Draw axes in white
	glColor3f(1, 1, 1);
	glBegin(GL_LINES);
	glVertex3d(0, 0, 0);
	glVertex3d(1, 0, 0);
	glVertex3d(0, 0, 0);
	glVertex3d(0, 1, 0);
	glVertex3d(0, 0, 0);
	glVertex3d(0, 0, 1);
	glEnd();
	//  Label axes
	glRasterPos3d(1, 0, 0);
	Print("X");
	glRasterPos3d(0, 1, 0);
	Print("Y");
	glRasterPos3d(0, 0, 1);
	Print("Z");
	//  Display parameters
	glWindowPos2i(5, 5);
	Print("View Angle=%d,%d  %s", th, ph, text[mode]);
	if (mode == 2)
		Print("  z=%.1f", z);
	else if (mode == 4)
		Print("  w=%.1f", w);
	//  Flush and swap
	glFlush();
	glutSwapBuffers();
}

/*
 *  GLUT calls this routine when the window is resized
 */
void reshape(int width, int height)
{
	//  Ratio of the width to the height of the window
	double w2h = (height > 0) ? (double)width / height : 1;
	//  Set the viewport to the entire window
	glViewport(0, 0, width, height);
	//  Tell OpenGL we want to manipulate the projection matrix
	glMatrixMode(GL_PROJECTION);
	//  Undo previous transformations
	glLoadIdentity();
	//  Orthogonal projection box adjusted for the
	//  aspect ratio of the window
	glOrtho(-dim * w2h, +dim * w2h, -dim, +dim, -dim, +dim);
	//  Switch to manipulating the model matrix
	glMatrixMode(GL_MODELVIEW);
	//  Undo previous transformations
	glLoadIdentity();
}

/*
 *  GLUT calls this routine when an arrow key is pressed
 */
void special(int key, int x, int y)
{
	//  Right arrow key - increase azimuth by 5 degrees
	if (key == GLUT_KEY_RIGHT)
		th += 5;
	//  Left arrow key - decrease azimuth by 5 degrees
	else if (key == GLUT_KEY_LEFT)
		th -= 5;
	//  Up arrow key - increase elevation by 5 degrees
	else if (key == GLUT_KEY_UP)
		ph += 5;
	//  Down arrow key - decrease elevation by 5 degrees
	else if (key == GLUT_KEY_DOWN)
		ph -= 5;
	//  Keep angles to +/-360 degrees
	th %= 360;
	ph %= 360;
	//  Tell GLUT it is necessary to redisplay the scene
	glutPostRedisplay();
}

/*
 *  GLUT calls this routine when a key is pressed
 */
void key(unsigned char ch, int x, int y)
{
	//  Exit on ESC
	if (ch == 27)
		exit(0);
	//  Reset view angle
	else if (ch == '0')
		th = ph = 0;
	//  Increase w/z by 0.001 (smoother) - ZOOM IN
	else if (ch == '+'){
		if (mode == 2)
			z += 0.001;
		else
			w += 0.001;
	}
	//  Decrease w/z by 0.001 (smoother) - ZOOM OUT
	else if (ch == '-'){
		if (mode == 2)
			z -= 0.001;
		else
			w -= 0.001;
	}
	//Increase sigma value by 0.1
	else if (ch == 'a') {
		s+=0.1;
	}
	//Decrease sigma value by 0.1
	else if (ch == 'z') {
		s-=0.1;
	}
	//Increase beta value by 0.01
	else if (ch == 's') {
		b += 0.01;
	}
	//Decrease beta value by 0.01
	else if (ch == 'x') {
		b -= 0.01;
	}
	//Increase rho value by 0.1
	else if (ch == 'd') {
		r+=0.1;
	}
	//Decrease rho value by 0.1
	else if (ch == 'c') {
		r-=0.1;
	}
	//Reset sigma, beta, rho values to original
	else if (ch == 'r') {
		s = 10;
		b = 2.6666;
		r = 28;
	}
	//  Tell GLUT it is necessary to redisplay the scene
	glutPostRedisplay();
}

int main(int argc, char* argv[]) {
	//  Initialize GLUT and process user parameters
	glutInit(&argc, argv);
	//  Request double buffered, true color window 
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
	//  Request 500 x 500 pixel window
	glutInitWindowSize(500, 500);
	//  Create the window
	glutCreateWindow("Assignment 2: Colin O'Connell");
	//  Tell GLUT to call "display" when the scene should be drawn
	glutDisplayFunc(display);
	//  Tell GLUT to call "reshape" when the window is resized
	glutReshapeFunc(reshape);
	//  Tell GLUT to call "special" when an arrow key is pressed
	glutSpecialFunc(special);
	//  Tell GLUT to call "key" when a key is pressed
	glutKeyboardFunc(key);
	//  Pass control to GLUT so it can interact with the user
	glutMainLoop();
	//  Return code
	return 0;
}




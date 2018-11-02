/*	Colin O'Connell HW4
	**Some functions and code taken from professor's example files - especially ex9.c
	**Some code taken and edited from https://github.com/taylorjandrews
	**Objects created taken from my own HW3 assignment
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <math.h>
 //  OpenGL with prototypes for glext
#define GL_GLEXT_PROTOTYPES
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

int th = 45.0;      //  Azimuth of view angle
int ph = 45.0;      //  Elevation of view angle
int mode = 0;       //  Projection mode
int fov = 55;       //  Field of view (for perspective)
int fp = 0;			//  First person
double asp = 1;     //  Aspect ratio
double dim = 3.0;   //  Size of world

//  Macro for sin & cos in degrees
#define Cos(th) cos(3.1415926/180*(th))
#define Sin(th) sin(3.1415926/180*(th))

// rotation variable for first person
int rotation = 0.0; 

// eye coordinates
double Ex = 0.0;
double Ey = 0.0;
double Ez = 5.0;

// camera coordinates
double Cx = 0.0;
double Cz = 0.0;

/*
 *  Convenience routine to output raster text
 *  Use VARARGS to make this more flexible
 */
#define LEN 8192  //  Maximum length of text string
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

/*
 *  Set projection
 */
static void Project()
{
	//  Tell OpenGL we want to manipulate the projection matrix
	glMatrixMode(GL_PROJECTION);
	//  Undo previous transformations
	glLoadIdentity();
	//  Perspective transformation
	if (fp) { //First person
		gluPerspective(fov, asp, dim / 4, dim * 4);
	}
	else {
		if (mode)
			gluPerspective(fov, asp, dim / 4, 4 * dim); //same used for first person
		//  Orthogonal projection
		else
			glOrtho(-asp * dim, +asp * dim, -dim, +dim, -dim, +dim);
	}
	//  Switch to manipulating the model matrix
	glMatrixMode(GL_MODELVIEW);
	//  Undo previous transformations
	glLoadIdentity();
}

//Draw a chair object
static void chair(double x, double y, double z, double dx, double dy, double dz, double th) {
	
	// Translations
	glTranslated(x, y, z);
	glRotated(th, 0, 1, 0);
	glScaled(dx, dy, dz);

	glBegin(GL_QUADS);

	glColor3f(0.71f, 0.65f, 0.26f);
	//Front of chair seat
	glVertex3f(-0.5f, -0.05f, 0.5f);
	glVertex3f(0.5f, -0.05f, 0.5f);
	glVertex3f(0.5f, 0.05f, 0.5f);
	glVertex3f(-0.5f, 0.05f, 0.5f);

	
	//Right side of chair seat
	glVertex3f(0.5f, -0.05f, -0.5f);
	glVertex3f(0.5f, 0.05f, -0.5f);
	glVertex3f(0.5f, 0.05f, 0.5f);
	glVertex3f(0.5f, -0.05f, 0.5f);

	
	//Back side of chair seat
	glVertex3f(-0.5f, -0.05f, -0.5f);
	glVertex3f(-0.5f, 0.05f, -0.5f);
	glVertex3f(0.5f, 0.05f, -0.5f);
	glVertex3f(0.5f, -0.05f, -0.5f);

	
	//Left side of chair seat
	glVertex3f(-0.5f, -0.05f, -0.5f);
	glVertex3f(-0.5f, -0.05f, 0.5f);
	glVertex3f(-0.5f, 0.05f, 0.5f);
	glVertex3f(-0.5f, 0.05f, -0.5f);

	//Top of chair seat
	glVertex3f(0.5f, 0.05f, 0.5f);
	glVertex3f(-0.5f, 0.05f, 0.5f);
	glVertex3f(-0.5f, 0.05f, -0.5f);
	glVertex3f(0.5f, 0.05f, -0.5f);

	
	//Bottom of chair seat
	glVertex3f(0.5f, -0.05f, 0.5f);
	glVertex3f(-0.5f, -0.05f, 0.5f);
	glVertex3f(-0.5f, -0.05f, -0.5f);
	glVertex3f(0.5f, -0.05f, -0.5f);


	glColor3f(0.9f, 0.91f, 0.98f);
	//Front right leg

	//Front side
	glVertex3f(0.45f, -0.05f, 0.4f);
	glVertex3f(0.35f, -0.05f, 0.4f);
	glVertex3f(0.35f, -0.75f, 0.4f);
	glVertex3f(0.45f, -0.75f, 0.4f);
	
	//Back side
	glVertex3f(0.45f, -0.05f, 0.3f);
	glVertex3f(0.35f, -0.05f, 0.3f);
	glVertex3f(0.35f, -0.75f, 0.3f);
	glVertex3f(0.45f, -0.75f, 0.3f);
	
	//Right side
	glVertex3f(0.45f, -0.05f, 0.4f);
	glVertex3f(0.45f, -0.05f, 0.3f);
	glVertex3f(0.45f, -0.75f, 0.3f);
	glVertex3f(0.45f, -0.75f, 0.4f);

	//Left side
	glVertex3f(0.35f, -0.05f, 0.4f);
	glVertex3f(0.35f, -0.05f, 0.3f);
	glVertex3f(0.35f, -0.75f, 0.3f);
	glVertex3f(0.35f, -0.75f, 0.4f);

	//Back Right Leg

	//Front side
	glVertex3f(0.45f, -0.05f, -0.3f);
	glVertex3f(0.35f, -0.05f, -0.3f);
	glVertex3f(0.35f, -0.75f, -0.3f);
	glVertex3f(0.45f, -0.75f, -0.3f);
	
	//Back side
	glVertex3f(0.45f, -0.05f, -0.4f);
	glVertex3f(0.35f, -0.05f, -0.4f);
	glVertex3f(0.35f, -0.75f, -0.4f);
	glVertex3f(0.45f, -0.75f, -0.4f);

	//Right side
	glVertex3f(0.45f, -0.05f, -0.4f);
	glVertex3f(0.45f, -0.05f, -0.3f);
	glVertex3f(0.45f, -0.75f, -0.3f);
	glVertex3f(0.45f, -0.75f, -0.4f);

	//Left side
	glVertex3f(0.35f, -0.05f, -0.4f);
	glVertex3f(0.35f, -0.05f, -0.3f);
	glVertex3f(0.35f, -0.75f, -0.3f);
	glVertex3f(0.35f, -0.75f, -0.4f);

	//Front Left Leg
	
	//Front side
	glVertex3f(-0.45f, -0.05f, 0.4f);
	glVertex3f(-0.35f, -0.05f, 0.4f);
	glVertex3f(-0.35f, -0.75f, 0.4f);
	glVertex3f(-0.45f, -0.75f, 0.4f);
	
	//Back side

	glVertex3f(-0.45f, -0.05f, 0.3f);
	glVertex3f(-0.35f, -0.05f, 0.3f);
	glVertex3f(-0.35f, -0.75f, 0.3f);
	glVertex3f(-0.45f, -0.75f, 0.3f);

	//Right side

	glVertex3f(-0.45f, -0.05f, 0.4f);
	glVertex3f(-0.45f, -0.05f, 0.3f);
	glVertex3f(-0.45f, -0.75f, 0.3f);
	glVertex3f(-0.45f, -0.75f, 0.4f);

	//Left side

	glVertex3f(-0.35f, -0.05f, 0.4f);
	glVertex3f(-0.35f, -0.05f, 0.3f);
	glVertex3f(-0.35f, -0.75f, 0.3f);
	glVertex3f(-0.35f, -0.75f, 0.4f);

	//Back Left Leg

	//Front side
	glVertex3f(-0.45f, -0.05f, -0.3f);
	glVertex3f(-0.35f, -0.05f, -0.3f);
	glVertex3f(-0.35f, -0.75f, -0.3f);
	glVertex3f(-0.45f, -0.75f, -0.3f);
	
	//Back side
	glVertex3f(-0.45f, -0.05f, -0.4f);
	glVertex3f(-0.35f, -0.05f, -0.4f);
	glVertex3f(-0.35f, -0.75f, -0.4f);
	glVertex3f(-0.45f, -0.75f, -0.4f);

	//Right side
	glVertex3f(-0.45f, -0.05f, -0.4f);
	glVertex3f(-0.45f, -0.05f, -0.3f);
	glVertex3f(-0.45f, -0.75f, -0.3f);
	glVertex3f(-0.45f, -0.75f, -0.4f);

	//Left side
	glVertex3f(-0.35f, -0.05f, -0.4f);
	glVertex3f(-0.35f, -0.05f, -0.3f);
	glVertex3f(-0.35f, -0.75f, -0.3f);
	glVertex3f(-0.35f, -0.75f, -0.4f);

	glColor3f(0.65f, 0.50f, 0.39f);
	//Chair Back

	//Front side
	glVertex3f(-0.45f, 0.05f, -0.45f);
	glVertex3f(0.45f, 0.05f, -0.45f);
	glVertex3f(0.45f, 0.875f, -0.45f);
	glVertex3f(-0.45f, 0.875f, -0.45f);
	
	//Back side
	glVertex3f(-0.45f, 0.05f, -0.5f);
	glVertex3f(0.45f, 0.05f, -0.5f);
	glVertex3f(0.45f, 0.875f, -0.5f);
	glVertex3f(-0.45f, 0.875f, -0.5f);

	//Left side
	glVertex3f(-0.45f, 0.05f, -0.5f);
	glVertex3f(-0.45f, 0.875f, -0.5f);
	glVertex3f(-0.45f, 0.875f, -0.45f);
	glVertex3f(-0.45f, 0.05f, -0.45f);
	
	//Right side
	glVertex3f(0.45f, 0.05f, -0.5f);
	glVertex3f(0.45f, 0.875f, -0.5f);
	glVertex3f(0.45f, 0.875f, -0.45f);
	glVertex3f(0.45f, 0.05f, -0.45f);
	
	//Top
	glVertex3f(-0.45f, 0.875f, -0.5f);
	glVertex3f(-0.45f, 0.875f, -0.45f);
	glVertex3f(0.45f, 0.875f, -0.45f);
	glVertex3f(0.45f, 0.875f, -0.5f);

	glEnd();
}

//Draw a bench object
static void bench(double x, double y, double z, double dx, double dy, double dz, double th) {

	// Translations
	glTranslated(x, y, z);
	glRotated(th, 0, 1, 0);
	glScaled(dx, dy, dz);

	glBegin(GL_QUADS);

	glColor3f(0.91f, 0.76f, 0.65f);
	//Front of bench
	glVertex3f(-0.5f, -0.05f, 0.5f);
	glVertex3f(0.5f, -0.05f, 0.5f);
	glVertex3f(0.5f, 0.05f, 0.5f);
	glVertex3f(-0.5f, 0.05f, 0.5f);


	//Right side of bench
	glVertex3f(0.5f, -0.05f, -0.5f);
	glVertex3f(0.5f, 0.05f, -0.5f);
	glVertex3f(0.5f, 0.05f, 0.5f);
	glVertex3f(0.5f, -0.05f, 0.5f);


	//Back side of bench
	glVertex3f(-0.5f, -0.05f, -0.5f);
	glVertex3f(-0.5f, 0.05f, -0.5f);
	glVertex3f(0.5f, 0.05f, -0.5f);
	glVertex3f(0.5f, -0.05f, -0.5f);


	//Left side of bench
	glVertex3f(-0.5f, -0.05f, -0.5f);
	glVertex3f(-0.5f, -0.05f, 0.5f);
	glVertex3f(-0.5f, 0.05f, 0.5f);
	glVertex3f(-0.5f, 0.05f, -0.5f);

	//Top of bench
	glVertex3f(0.5f, 0.05f, 0.5f);
	glVertex3f(-0.5f, 0.05f, 0.5f);
	glVertex3f(-0.5f, 0.05f, -0.5f);
	glVertex3f(0.5f, 0.05f, -0.5f);


	//Bottom of bench
	glVertex3f(0.5f, -0.05f, 0.5f);
	glVertex3f(-0.5f, -0.05f, 0.5f);
	glVertex3f(-0.5f, -0.05f, -0.5f);
	glVertex3f(0.5f, -0.05f, -0.5f);


	glColor3f(0.52f, 0.37f, 0.26f);
	//Front right leg

	//Front side
	glVertex3f(0.45f, -0.05f, 0.4f);
	glVertex3f(0.35f, -0.05f, 0.4f);
	glVertex3f(0.35f, -0.75f, 0.4f);
	glVertex3f(0.45f, -0.75f, 0.4f);

	//Back side
	glVertex3f(0.45f, -0.05f, 0.3f);
	glVertex3f(0.35f, -0.05f, 0.3f);
	glVertex3f(0.35f, -0.75f, 0.3f);
	glVertex3f(0.45f, -0.75f, 0.3f);

	//Right side
	glVertex3f(0.45f, -0.05f, 0.4f);
	glVertex3f(0.45f, -0.05f, 0.3f);
	glVertex3f(0.45f, -0.75f, 0.3f);
	glVertex3f(0.45f, -0.75f, 0.4f);

	//Left side
	glVertex3f(0.35f, -0.05f, 0.4f);
	glVertex3f(0.35f, -0.05f, 0.3f);
	glVertex3f(0.35f, -0.75f, 0.3f);
	glVertex3f(0.35f, -0.75f, 0.4f);

	//Back Right Leg

	//Front side
	glVertex3f(0.45f, -0.05f, -0.3f);
	glVertex3f(0.35f, -0.05f, -0.3f);
	glVertex3f(0.35f, -0.75f, -0.3f);
	glVertex3f(0.45f, -0.75f, -0.3f);

	//Back side
	glVertex3f(0.45f, -0.05f, -0.4f);
	glVertex3f(0.35f, -0.05f, -0.4f);
	glVertex3f(0.35f, -0.75f, -0.4f);
	glVertex3f(0.45f, -0.75f, -0.4f);

	//Right side
	glVertex3f(0.45f, -0.05f, -0.4f);
	glVertex3f(0.45f, -0.05f, -0.3f);
	glVertex3f(0.45f, -0.75f, -0.3f);
	glVertex3f(0.45f, -0.75f, -0.4f);

	//Left side
	glVertex3f(0.35f, -0.05f, -0.4f);
	glVertex3f(0.35f, -0.05f, -0.3f);
	glVertex3f(0.35f, -0.75f, -0.3f);
	glVertex3f(0.35f, -0.75f, -0.4f);

	//Front Left Leg

	//Front side
	glVertex3f(-0.45f, -0.05f, 0.4f);
	glVertex3f(-0.35f, -0.05f, 0.4f);
	glVertex3f(-0.35f, -0.75f, 0.4f);
	glVertex3f(-0.45f, -0.75f, 0.4f);

	//Back side

	glVertex3f(-0.45f, -0.05f, 0.3f);
	glVertex3f(-0.35f, -0.05f, 0.3f);
	glVertex3f(-0.35f, -0.75f, 0.3f);
	glVertex3f(-0.45f, -0.75f, 0.3f);

	//Right side

	glVertex3f(-0.45f, -0.05f, 0.4f);
	glVertex3f(-0.45f, -0.05f, 0.3f);
	glVertex3f(-0.45f, -0.75f, 0.3f);
	glVertex3f(-0.45f, -0.75f, 0.4f);

	//Left side

	glVertex3f(-0.35f, -0.05f, 0.4f);
	glVertex3f(-0.35f, -0.05f, 0.3f);
	glVertex3f(-0.35f, -0.75f, 0.3f);
	glVertex3f(-0.35f, -0.75f, 0.4f);

	//Back Left Leg

	//Front side
	glVertex3f(-0.45f, -0.05f, -0.3f);
	glVertex3f(-0.35f, -0.05f, -0.3f);
	glVertex3f(-0.35f, -0.75f, -0.3f);
	glVertex3f(-0.45f, -0.75f, -0.3f);

	//Back side
	glVertex3f(-0.45f, -0.05f, -0.4f);
	glVertex3f(-0.35f, -0.05f, -0.4f);
	glVertex3f(-0.35f, -0.75f, -0.4f);
	glVertex3f(-0.45f, -0.75f, -0.4f);

	//Right side
	glVertex3f(-0.45f, -0.05f, -0.4f);
	glVertex3f(-0.45f, -0.05f, -0.3f);
	glVertex3f(-0.45f, -0.75f, -0.3f);
	glVertex3f(-0.45f, -0.75f, -0.4f);

	//Left side
	glVertex3f(-0.35f, -0.05f, -0.4f);
	glVertex3f(-0.35f, -0.05f, -0.3f);
	glVertex3f(-0.35f, -0.75f, -0.3f);
	glVertex3f(-0.35f, -0.75f, -0.4f);

	glEnd();
}


/*
 *  OpenGL (GLUT) calls this routine to display the scene
 */
void display()
{
	//  Erase the window and the depth buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//  Enable Z-buffering in OpenGL
	glEnable(GL_DEPTH_TEST);
	//  Undo previous transformations
	glLoadIdentity();

	//First person
	if (fp) {
		//Adjust camera variables based on rotation
		Cx = +2 * dim*Sin(rotation);
		Cz = -2 * dim*Cos(rotation);
		//Define the viewing transformation
		gluLookAt(Ex, Ey, Ez, Cx + Ex, Ey, Cz + Ez, 0, 1, 0);
	}
	else {
		//Perspective - adjust the eye position variables
		if (mode) {
			double px = -2 * dim*Sin(th)*Cos(ph);
			double py = +2 * dim*Sin(ph);
			double pz = +2 * dim*Cos(th)*Cos(ph);
			gluLookAt(px, py, pz, 0, 0, 0, 0, Cos(ph), 0);
		}
		//Orthogonal - set view angle (like normal)
		else {
			glRotatef(ph, 1, 0, 0);
			glRotatef(th, 0, 1, 0);
		}
	}

	//Draw the first normal chair
	chair(0,0,0,1,1,1,0);
	//Draw the second smaller, offset chair
	chair(1.5, -0.35, 1.5, 0.4, 0.75, 0.5, -30);
	//Draw bench item
	bench(-2, 0, 1.5, 4, 1, 1, 0);

	//  Display parameters
	glWindowPos2i(5, 5);
	if (fp) { //for first person
		Print("1stPerson On View Angle=%d", rotation);
	}
	else { //for non-first person
		Print("1stPerson Off Angle=%d,%d  Dim=%.1f FOV=%d Projection=%s", th, ph, dim, fov, mode ? "Perpective" : "Orthogonal");
	}
	//  Render the scene
	glFlush();
	//  Make the rendered scene visible
	glutSwapBuffers();
}

/*
 *  GLUT calls this routine when an arrow key is pressed
 */
void special(int key, int x, int y)
{
	if (!fp) { //only if not in first person
		//  Right arrow key - increase angle by 5 degrees
		if (key == GLUT_KEY_RIGHT)
			th += 5;
		//  Left arrow key - decrease angle by 5 degrees
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
	}
	//  Update projection
	Project();
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
	//  Toggle first person
	else if (ch == 'f') {
		fp = 1 - fp;
	}
	if (fp) {
		//Update eye variables based on camera variables
		double dt = 0.05;
		//Move 'forward'
		if (ch == 'i') {
			Ex += Cx * dt; 
			Ez += Cz * dt;
		}
		//Rotate view left
		else if (ch == 'j') {
			rotation -= 3;
		}
		//Move 'backward'
		else if (ch == 'k') {
			Ex -= Cx * dt;
			Ez -= Cz * dt;
		}
		//Rotate view right
		else if (ch == 'l') {
			rotation += 3;
		}
		//Keep angles to +/-360 degrees
		rotation %= 360;
	}
	else {
		//Reset view angle
		if (ch == '0')
			th = ph = 45;
		//Switch display mode
		else if (ch == 'm')
			mode = 1 - mode;
		//Change field of view angle
		else if (ch == '+')
			fov--; //zoom in
		else if (ch == '-')
			fov++; //zoom out
	}
	//  Update projection
	Project();
	//  Tell GLUT it is necessary to redisplay the scene
	glutPostRedisplay();
}

/*
 *  GLUT calls this routine when the window is resized
 */
void reshape(int width, int height)
{
	//  Ratio of the width to the height of the window
	asp = (height > 0) ? (double)width / height : 1;
	//  Set the viewport to the entire window
	glViewport(0, 0, width, height);
	//  Update projection
	Project();
}


/*
 *  Start up GLUT and tell it what to do
 */
int main(int argc, char* argv[])
{
	//  Initialize GLUT and process user parameters
	glutInit(&argc, argv);
	//  Request double buffered, true color window with Z buffering at 600x600
	glutInitWindowSize(600, 600);
	glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
	//  Create the window
	glutCreateWindow("Assignment 4: Colin O'Connell");
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
	return 0;
}

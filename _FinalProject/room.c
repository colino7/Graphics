/*	Colin O'Connell Final Project

	** Some code taken from Professor Schre�der's example files
	** Some code taken from https://www.codeproject.com/Articles/987274/%2FArticles%2F987274%2FMy-first-OpenGL-Project-A-D-House

 */
#include "CSCIx229.h"

int th = 45.0;      // Azimuth of view angle
int ph = 45.0;      // Elevation of view angle
int move = 1;       // Move light
int light = 1;      // Lighting
double asp = 1;     // Aspect ratio
double dim = 500.0; // Size of world

int m = 1;			// Projection mode

// Light values
int one = 1;		// Unit value
int distance = 800;	// Light distance
int smooth = 1;		// Smooth/Flat shading
int local = 0;		// Local Viewer Model
int ambient = 30;	// Ambient intensity (%)
int diffuse = 100;  // Diffuse intensity (%)
int specular = 0;	// Specular intensity (%)
int zh = 90;		// Light azimuth
float ylight = 100;	// Elevation of light
int emission = 0;	// Emission intensity (%)
int shininess = 0;  // Shininess (power of two)
float shiny = 1;	// Shininess (value)
int inc = 10;		// Ball increment

int fp = 0;			// First person

int tv_on = 0;		// Turn the tv on
int w = 0;			// Turn the walls on

//  Macro for sin & cos in degrees
#define Cos(th) cos(3.1415926/180*(th))
#define Sin(th) sin(3.1415926/180*(th))

// Rotation variable for first person
int rotation = 0.0;

// Eye coordinates
double Ex = 70.0;
double Ey = 70.0;
double Ez = 70.0;

// Camera coordinates
double Cx = 0.0;
double Cz = 0.0;

// Texture values
int mode = 0;    // Texture mode
unsigned int texture[17];  // Texture names

// Draw the room walls
static void walls() {
	
	//Enable textures
	glEnable(GL_TEXTURE_2D);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, mode ? GL_REPLACE : GL_MODULATE);
	glColor3f(1, 1, 1);
	glBindTexture(GL_TEXTURE_2D, texture[11]);

	glBegin(GL_QUADS);

	//Floor
	
	glColor3f(1.0, 1.0, 1.0);
	glNormal3f(0.0f, 1.0f, 0.0f);
	glTexCoord2f(0, 0); glVertex3f(-500, 0, -500);
	glTexCoord2f(1, 0); glVertex3f(500, 0, -500);
	glTexCoord2f(1, 1); glVertex3f(500, 0, 500);
	glTexCoord2f(0, 1); glVertex3f(-500, 0, 500);
	glColor3f(1.0, 1.0, 1.0);

	glEnd();
	glDisable(GL_TEXTURE_2D);
	
	
	if(w){
		glEnable(GL_TEXTURE_2D);
		glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, mode ? GL_REPLACE : GL_MODULATE);
		glColor3f(1, 1, 1);
		glBindTexture(GL_TEXTURE_2D, texture[10]);

		glBegin(GL_QUADS);

		//Ceiling
		glNormal3f(0.0f, -1.0f, 0.0f);
		glTexCoord2f(0, 0); glVertex3f(-500, 500, -500);
		glTexCoord2f(1, 0); glVertex3f(500, 500, -500);
		glTexCoord2f(1, 1); glVertex3f(500, 500, 500);
		glTexCoord2f(0, 1); glVertex3f(-500, 500, 500);
		glColor3f(1.0, 1.0, 1.0);
		
		//Walls

		//Front wall
	
		glNormal3f(0.0f, 0.0f, -1.0f);
		glTexCoord2f(0, 0); glVertex3f(-500, 0, 500);
		glTexCoord2f(1, 0); glVertex3f(500, 0, 500);
		glTexCoord2f(1, 1); glVertex3f(500, 500, 500);
		glTexCoord2f(0, 1); glVertex3f(-500, 500, 500);
		glColor3f(1.0, 1.0, 1.0);
	
		//Back wall
	
		glNormal3f(0.0f, 0.0f, 1.0f);
		glTexCoord2f(0, 0); glVertex3f(-500, 0, -500);
		glTexCoord2f(1, 0); glVertex3f(500, 0, -500);
		glTexCoord2f(1, 1); glVertex3f(500, 500, -500);
		glTexCoord2f(0, 1); glVertex3f(-500, 500, -500);
		glColor3f(1.0, 1.0, 1.0);

		//Right wall
		glNormal3f(-1.0f, 0.0f, 0.0f);
		glTexCoord2f(0, 0); glVertex3f(500, 500, 500);
		glTexCoord2f(1, 0); glVertex3f(500, 0, 500);
		glTexCoord2f(1, 1); glVertex3f(500, 0, -500);
		glTexCoord2f(0, 1); glVertex3f(500, 500, -500);
		glColor3f(1.0, 1.0, 1.0);

		//Left wall
		glNormal3f(1.0f, 0.0f, 0.0f);
		glTexCoord2f(0, 0); glVertex3f(-500, 500, 500);
		glTexCoord2f(1, 0); glVertex3f(-500, 0, 500);
		glTexCoord2f(1, 1); glVertex3f(-500, 0, -500);
		glTexCoord2f(0, 1); glVertex3f(-500, 500, -500);

		glEnd();
		glDisable(GL_TEXTURE_2D);
	}
}

// Draw the outside walls
static void o_walls() {

	//Enable textures
	glEnable(GL_TEXTURE_2D);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, mode ? GL_REPLACE : GL_MODULATE);
	glColor3f(1, 1, 1);
	glBindTexture(GL_TEXTURE_2D, texture[14]);

	glBegin(GL_QUADS);

	//Floor

	glColor3f(1.0, 1.0, 1.0);
	glNormal3f(0.0f, 1.0f, 0.0f);
	glTexCoord2f(0, 0); glVertex3f(-505, -5, -505);
	glTexCoord2f(1, 0); glVertex3f(505, -5, -505);
	glTexCoord2f(1, 1); glVertex3f(505, -5, 505);
	glTexCoord2f(0, 1); glVertex3f(-505, -5, 505);
	glColor3f(1.0, 1.0, 1.0);

	// Ceiling

	glNormal3f(0.0f, -1.0f, 0.0f);
	glTexCoord2f(0, 0); glVertex3f(-505, 505, -505);
	glTexCoord2f(1, 0); glVertex3f(505, 505, -505);
	glTexCoord2f(1, 1); glVertex3f(505, 505, 505);
	glTexCoord2f(0, 1); glVertex3f(-505, 505, 505);
	glColor3f(1.0, 1.0, 1.0);

	// Walls
	//front wall

	glNormal3f(0.0f, 0.0f, -1.0f);
	glTexCoord2f(0, 0); glVertex3f(-505, -5, 505);
	glTexCoord2f(1, 0); glVertex3f(505, -5, 505);
	glTexCoord2f(1, 1); glVertex3f(505, 505, 505);
	glTexCoord2f(0, 1); glVertex3f(-505, 505, 505);
	glColor3f(1.0, 1.0, 1.0);

	//Back wall

	glNormal3f(0.0f, 0.0f, 1.0f);
	glTexCoord2f(0, 0); glVertex3f(-505, -5, -505);
	glTexCoord2f(1, 0); glVertex3f(505, -5, -505);
	glTexCoord2f(1, 1); glVertex3f(505, 505, -505);
	glTexCoord2f(0, 1); glVertex3f(-505, 505, -505);
	glColor3f(1.0, 1.0, 1.0);

	//Right wall
	glNormal3f(-1.0f, 0.0f, 0.0f);
	glTexCoord2f(0, 0); glVertex3f(505, 505, 505);
	glTexCoord2f(1, 0); glVertex3f(505, -5, 505);
	glTexCoord2f(1, 1); glVertex3f(505, -5, -505);
	glTexCoord2f(0, 1); glVertex3f(505, 505, -505);
	glColor3f(1.0, 1.0, 1.0);

	//Left wall
	glNormal3f(1.0f, 0.0f, 0.0f);
	glTexCoord2f(0, 0); glVertex3f(-505, 505, 505);
	glTexCoord2f(1, 0); glVertex3f(-505, -5, 505);
	glTexCoord2f(1, 1); glVertex3f(-505, -5, -505);
	glTexCoord2f(0, 1); glVertex3f(-505, 505, -505);

	glEnd();
	glDisable(GL_TEXTURE_2D);
}

//Draw the surrounding sky
static void sky() {

	//Enable textures
	glEnable(GL_TEXTURE_2D);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, mode ? GL_REPLACE : GL_MODULATE);
	glColor3f(1, 1, 1);
	glBindTexture(GL_TEXTURE_2D, texture[15]);

	glBegin(GL_QUADS);

	//Bottom

	glColor3f(1.0, 1.0, 1.0);
	glNormal3f(0.0f, 1.0f, 0.0f);
	glTexCoord2f(0, 0); glVertex3f(-2000, -2000, -2000);
	glTexCoord2f(1, 0); glVertex3f(2000, -2000, -2000);
	glTexCoord2f(1, 1); glVertex3f(2000, -2000, 2000);
	glTexCoord2f(0, 1); glVertex3f(-2000, -2000, 2000);
	glColor3f(1.0, 1.0, 1.0);

	//Top

	glNormal3f(0.0f, -1.0f, 0.0f);
	glTexCoord2f(0, 0); glVertex3f(-2000, 2000, -2000);
	glTexCoord2f(1, 0); glVertex3f(2000, 2000, -2000);
	glTexCoord2f(1, 1); glVertex3f(2000, 2000, 2000);
	glTexCoord2f(0, 1); glVertex3f(-2000, 2000, 2000);
	glColor3f(1.0, 1.0, 1.0);

	//Front

	glNormal3f(0.0f, 0.0f, -1.0f);
	glTexCoord2f(0, 0); glVertex3f(-2000, -2000, 2000);
	glTexCoord2f(1, 0); glVertex3f(2000, -2000, 2000);
	glTexCoord2f(1, 1); glVertex3f(2000, 2000, 2000);
	glTexCoord2f(0, 1); glVertex3f(-2000, 2000, 2000);
	glColor3f(1.0, 1.0, 1.0);

	//Back

	glNormal3f(0.0f, 0.0f, 1.0f);
	glTexCoord2f(0, 0); glVertex3f(-2000, -2000, -2000);
	glTexCoord2f(1, 0); glVertex3f(2000, -2000, -2000);
	glTexCoord2f(1, 1); glVertex3f(2000, 2000, -2000);
	glTexCoord2f(0, 1); glVertex3f(-2000, 2000, -2000);
	glColor3f(1.0, 1.0, 1.0);

	//Right
	glNormal3f(-1.0f, 0.0f, 0.0f);
	glTexCoord2f(0, 0); glVertex3f(2000, 2000, 2000);
	glTexCoord2f(1, 0); glVertex3f(2000, -2000, 2000);
	glTexCoord2f(1, 1); glVertex3f(2000, -2000, -2000);
	glTexCoord2f(0, 1); glVertex3f(2000, 2000, -2000);
	glColor3f(1.0, 1.0, 1.0);

	//Left
	glNormal3f(1.0f, 0.0f, 0.0f);
	glTexCoord2f(0, 0); glVertex3f(-2000, 2000, 2000);
	glTexCoord2f(1, 0); glVertex3f(-2000, -2000, 2000);
	glTexCoord2f(1, 1); glVertex3f(-2000, -2000, -2000);
	glTexCoord2f(0, 1); glVertex3f(-2000, 2000, -2000);

	glEnd();
	glDisable(GL_TEXTURE_2D);
}

// First helper function for drawing some standard points
static void points(double x, double y, double z) {
	glBegin(GL_QUADS);
	glNormal3d(0, 0, 1);
	glTexCoord2d(0, 0);
	glVertex3d(-x, y, z);
	glTexCoord2d(0, y * 2 / 100);
	glVertex3d(-x, -y, z);
	glTexCoord2d(x * 2 / 100, y * 2 / 100);
	glVertex3d(x, -y, z);
	glTexCoord2d(x * 2 / 100, 0);
	glVertex3d(x, y, z);

	glNormal3d(1, 0, 0);
	glTexCoord2d(0, 0);
	glVertex3d(x, y, z);
	glTexCoord2d(0, y * 2 / 100);
	glVertex3d(x, -y, z);
	glTexCoord2d(z * 2 / 100, y * 2 / 100);
	glVertex3d(x, -y, -z);
	glTexCoord2d(z * 2 / 100, 0);
	glVertex3d(x, y, -z);

	glNormal3d(0, 0, -1);
	glTexCoord2d(x * 2 / 100, 0);
	glVertex3d(x, y, -z);
	glTexCoord2d(x * 2 / 100, y * 2 / 100);
	glVertex3d(x, -y, -z);
	glTexCoord2d(0, y * 2 / 100);
	glVertex3d(-x, -y, -z);
	glTexCoord2d(0, 0);
	glVertex3d(-x, y, -z);

	glNormal3d(-1, 0, 0);
	glTexCoord2d(0, y * 2 / 100);
	glVertex3d(-x, y, -z);
	glTexCoord2d(0, 0);
	glVertex3d(-x, -y, -z);
	glTexCoord2d(z * 2 / 100, 0);
	glVertex3d(-x, -y, z);
	glTexCoord2d(z * 2 / 100, y * 2 / 100);
	glVertex3d(-x, y, z);

	glNormal3d(0, 1, 0);
	glTexCoord2d(0, 0);
	glVertex3d(-x, y, z);
	glTexCoord2d(x * 2 / 100, 0);
	glVertex3d(x, y, z);
	glTexCoord2d(x * 2 / 100, z * 2 / 100);
	glVertex3d(x, y, -z);
	glTexCoord2d(0, z * 2 / 100);
	glVertex3d(-x, y, -z);

	glNormal3d(0, -1, 0);
	glTexCoord2d(0, z * 2 / 100);
	glVertex3d(-x, -y, -z);
	glTexCoord2d(x * 2 / 100, z * 2 / 100);
	glVertex3d(x, -y, -z);
	glTexCoord2d(x * 2 / 100, 0);
	glVertex3d(x, -y, z);
	glTexCoord2d(0, 0);
	glVertex3d(-x, -y, z);
	glEnd();
}


// Second helper function
static void points2(float x, float y, float z, float cant) {
	float width = 2 * x;
	float height = 2 * y;
	float depth = 2 * z;

	glBegin(GL_QUADS);
	// Front Face
	glNormal3d(0, 0, -1);
	glTexCoord2f(cant, cant);					// top right of texture
	glVertex3f(width / 2, height / 2, -depth / 2);	// top right of quad
	glTexCoord2f(0.0f, cant);					// top left of texture
	glVertex3f(-width / 2, height / 2, -depth / 2);	// top left of quad
	glTexCoord2f(0.0f, 0.0f);					// bottom left of texture
	glVertex3f(-width / 2, -height / 2, -depth / 2);	// bottom left of quad
	glTexCoord2f(cant, 0.0f);					// bottom right of texture
	glVertex3f(width / 2, -height / 2, -depth / 2);	// bottom right of quad

	// Back Face
	glNormal3d(0, 0, 1);
	glTexCoord2f(cant, cant);					// top right of texture
	glVertex3f(width / 2, height / 2, depth / 2);	// top right of quad
	glTexCoord2f(0.0f, cant);					// top left of texture
	glVertex3f(-width / 2, height / 2, depth / 2);	// top left of quad
	glTexCoord2f(0.0f, 0.0f);					// bottom left of texture
	glVertex3f(-width / 2, -height / 2, depth / 2);	// bottom left of quad
	glTexCoord2f(cant, 0.0f);					// bottom right of texture
	glVertex3f(width / 2, -height / 2, depth / 2);	// bottom right of quad

	// Right Face
	glNormal3d(1, 0, 0);
	glTexCoord2f(cant, cant);					// top right of texture
	glVertex3f(width / 2, height / 2, -depth / 2);	// top right of quad
	glTexCoord2f(0.0f, cant);					// top left of texture
	glVertex3f(width / 2, height / 2, depth / 2);	// top left of quad
	glTexCoord2f(0.0f, 0.0f);					// bottom left of texture
	glVertex3f(width / 2, -height / 2, depth / 2);	// bottom left of quad
	glTexCoord2f(cant, 0.0f);					// bottom right of texture
	glVertex3f(width / 2, -height / 2, -depth / 2);	// bottom right of quad

	// Left Face
	glNormal3d(-1, 0, 0);
	glTexCoord2f(cant, cant);					// top right of texture
	glVertex3f(-width / 2, height / 2, -depth / 2);	// top right of quad
	glTexCoord2f(0.0f, cant);					// top left of texture
	glVertex3f(-width / 2, height / 2, depth / 2);	// top left of quad
	glTexCoord2f(0.0f, 0.0f);					// bottom left of texture
	glVertex3f(-width / 2, -height / 2, depth / 2);	// bottom left of quad
	glTexCoord2f(cant, 0.0f);					// bottom right of texture
	glVertex3f(-width / 2, -height / 2, -depth / 2);	// bottom right of quad
	glEnd();
}

// Third helper function
static void points3(float x, float y, float z, float cant) {
	glBegin(GL_QUADS);

	glNormal3d(0, 0, 1);
	glTexCoord2f(cant, cant);
	glVertex3f(-1 * x, 0 * y, -1 * z);
	glTexCoord2f(0.0f, cant);
	glVertex3f(-1 * x, 0 * y, 1 * z);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(1 * x, 0 * y, 1 * z);
	glTexCoord2f(cant, 0.0f);
	glVertex3f(1 * x, 0 * y, -1 * z);

	glEnd();
}

// Draw the tv stand
static void tvstand(double x, double y, double z, double dx, double dy, double dz, double th, double rx, double ry, double rz) {

	glTranslated(x, y, z);
	glRotated(th, rx, ry, rz);
	glScaled(dx, dy, dz);

	glColor3d(0.4, 0.4, 0.4);
	points2(0.5f * 70, 0.04f * 70, 0.7f * 70, 1);
	glPushMatrix();
	glTranslated(0, 0.04f * 70, 0);
	points3(0.5f * 70, 0, 0.7f * 70, 1);
	glPopMatrix();
	glPushMatrix();
	glTranslated(0, -0.04f * 70, 0);
	points3(0.5f * 70, 0, 0.7f * 70, 1);
	glPopMatrix();

	glPushMatrix();
	glTranslated(0.4f * 70, 0, 0.6f * 70);
	glRotated(90, 1, 0, 0);
	gluCylinder(gluNewQuadric(), 0.05f * 70, 0.03f * 70, 0.8f * 70, 20, 20);
	glPopMatrix();

	glPushMatrix();
	glTranslated(-0.4f * 70, 0, 0.6f * 70);
	glRotated(90, 1, 0, 0);
	gluCylinder(gluNewQuadric(), 0.05f * 70, 0.03f * 70, 0.8f * 70, 20, 20);
	glPopMatrix();

	glPushMatrix();
	glTranslated(0.4f * 70, 0, -0.6f * 70);
	glRotated(90, 1, 0, 0);
	gluCylinder(gluNewQuadric(), 0.05f * 70, 0.03f * 70, 0.8f * 70, 20, 20);
	glPopMatrix();

	glPushMatrix();
	glTranslated(-0.4f * 70, 0, -0.6f * 70);
	glRotated(90, 1, 0, 0);
	gluCylinder(gluNewQuadric(), 0.05f * 70, 0.03f * 70, 0.8f * 70, 20, 20);
	glPopMatrix();

	glPushMatrix();
	glTranslated(0, -0.4f * 70, 0);
	points2(0.45f * 70, 0.02f * 70, 0.65f * 70, 1);
	glPopMatrix();
}

// Draw the couch
static void couch(double x, double y, double z, double dx, double dy, double dz, double th, double rx, double ry, double rz) {
	double h = 37;
	double l = 40;
	double c = 7;

	double a = 5;

	glTranslated(x, y, z);
	glRotated(th, rx, ry, rz);
	glScaled(dx, dy, dz);

	glEnable(GL_TEXTURE_2D);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, mode ? GL_REPLACE : GL_MODULATE);

	glColor3d(1, 1, 1);
	glBindTexture(GL_TEXTURE_2D, texture[1]);
	glTranslated(-l - 2, 0, 0);
	points(2, h, h);
	glTranslated(2 * l + 4, 0, 0);
	points(2, h, h);
	glTranslated(-l - 2, 0, 0);
	glRotated(a, -1, 0, 0);
	int i = 10;
	glTranslated(0, -1, i - 10);
	points(l, 2, h - i);

	glBindTexture(GL_TEXTURE_2D, texture[0]);
	glTranslated(0, c, 3);
	points(l - 1, c, h - i - 4);
	glBindTexture(GL_TEXTURE_2D, 0);
	glTranslated(0, -c, -3);

	glTranslated(0, h - i, -(h - i) + 2);
	glRotated(90, -1, 0, 0);
	glBindTexture(GL_TEXTURE_2D, texture[1]);
	points(l, 2, h - i);
	glBindTexture(GL_TEXTURE_2D, texture[0]);
	glTranslated(0, -c, 3);
	points(l - 1, c, h - i - 4);

	glBindTexture(GL_TEXTURE_2D, 0);

}

// Draw the armchair
static void seat(double x, double y, double z, double dx, double dy, double dz, double th, double rx, double ry, double rz) {
	double h = 37;
	double l = 40;
	double c = 7;

	double a = 5;

	glTranslated(x, y, z);
	glRotated(th, rx, ry, rz);
	glScaled(dx, dy, dz);

	glEnable(GL_TEXTURE_2D);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, mode ? GL_REPLACE : GL_MODULATE);

	glColor3d(1, 1, 1);
	glBindTexture(GL_TEXTURE_2D, texture[12]);
	glTranslated(-l - 2, 0, 0);
	points(2, h, h);
	glTranslated(2 * l + 4, 0, 0);
	points(2, h, h);
	glTranslated(-l - 2, 0, 0);
	glRotated(a, -1, 0, 0);
	int i = 10;
	glTranslated(0, -1, i - 10);
	points(l, 2, h - i);

	glBindTexture(GL_TEXTURE_2D, texture[0]);
	glTranslated(0, c, 3);
	points(l - 1, c, h - i - 4);
	glBindTexture(GL_TEXTURE_2D, 0);
	glTranslated(0, -c, -3);

	glTranslated(0, h - i, -(h - i) + 2);
	glRotated(90, -1, 0, 0);
	glBindTexture(GL_TEXTURE_2D, texture[12]);
	points(l, 2, h - i);
	glBindTexture(GL_TEXTURE_2D, texture[0]);
	glTranslated(0, -c, 3);
	points(l - 1, c, h - i - 4);

	glBindTexture(GL_TEXTURE_2D, 0);

}

// Draw the tv
static void tv(double x, double y, double z, double dx, double dy, double dz, double th, double rx, double ry, double rz) {
	
	//  Set specular color to white
	float white[] = { 1,1,1,1 };
	float black[] = { 0,0,0,1 };
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shiny);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, white);
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, black);

	// Translations
	glTranslated(x, y, z);
	glRotated(th, rx, ry, rz);
	glScaled(dx, dy, dz);

	//Enable textures
	glEnable(GL_TEXTURE_2D);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, mode ? GL_REPLACE : GL_MODULATE);
	glColor3f(1, 1, 1);
	if (tv_on) {
		glBindTexture(GL_TEXTURE_2D, texture[3]);
	}
	else {
		glBindTexture(GL_TEXTURE_2D, texture[6]);
	}

	glBegin(GL_QUADS);

	glColor3f(1.0f, 1.0f, 1.0f);

	//Back side
	glNormal3f(0.0f, 0.0f, -1.0f);

	glTexCoord2f(0, 0); glVertex3f(-52, 6, -57);
	glTexCoord2f(1, 0); glVertex3f(52, 6, -57);
	glTexCoord2f(1, 1); glVertex3f(52, 100, -57);
	glTexCoord2f(0, 1); glVertex3f(-52, 100, -57);

	glEnd();
	glDisable(GL_TEXTURE_2D);

	glEnable(GL_TEXTURE_2D);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, mode ? GL_REPLACE : GL_MODULATE);
	glColor3f(1, 1, 1);
	glBindTexture(GL_TEXTURE_2D, texture[5]);
	glBegin(GL_QUADS);
	glColor3f(1.0f, 1.0f, 1.0f);

	//Front side
	glNormal3f(0.0f, 0.0f, 1.0f);

	glTexCoord2f(0, 0); glVertex3f(-52, 6, -52);
	glTexCoord2f(1, 0); glVertex3f(52, 6, -52);
	glTexCoord2f(1, 1); glVertex3f(52, 100, -52);
	glTexCoord2f(0, 1); glVertex3f(-52, 100, -52);


	//Left side
	glNormal3f(-1.0f, 0.0f, 0.0f);

	glTexCoord2f(0, 0); glVertex3f(-52, 6, -57);
	glTexCoord2f(1, 0); glVertex3f(-52, 100, -57);
	glTexCoord2f(1, 1); glVertex3f(-52, 100, -52);
	glTexCoord2f(0, 1); glVertex3f(-52, 6, -52);

	//Right side
	glNormal3f(1.0f, 0.0f, 0.0f);

	glTexCoord2f(0, 0); glVertex3f(52, 6, -57);
	glTexCoord2f(1, 0); glVertex3f(52, 100, -57);
	glTexCoord2f(1, 1); glVertex3f(52, 100, -52);
	glTexCoord2f(0, 1); glVertex3f(52, 6, -52);

	//Top
	glNormal3f(0.0f, 1.0f, 0.0f);

	glTexCoord2f(0, 0); glVertex3f(-52, 100, -57);
	glTexCoord2f(1, 0); glVertex3f(-52, 100, -52);
	glTexCoord2f(1, 1); glVertex3f(52, 100, -52);
	glTexCoord2f(0, 1); glVertex3f(52, 100, -57);

	glEnd();
	glDisable(GL_TEXTURE_2D);
}

// Small helper function
void p(double h){
	GLUquadric *q = gluNewQuadric();
	gluQuadricTexture(q, GL_TRUE);
	glTranslated(0, -h, 0);
	glRotated(90, -1, 0, 0);
	gluCylinder(q, 5, 8, 2 * h, 20, 20);
	glRotated(-90, -1, 0, 0);
	glTranslated(0, h, 0);
	gluDeleteQuadric(q);
}

// Draw the ping pong table
static void table(double x, double y, double z, double dx, double dy, double dz, double th, double rx, double ry, double rz) {

	// Translations
	glTranslated(x, y, z);
	glRotated(th, rx, ry, rz);
	glScaled(dx, dy, dz);

	glColor3d(.3, .3, .3);
	double h = 45;
	glPushMatrix();
	glTranslated(-40, 0, -90);
	p(h);
	glPopMatrix();
	glPushMatrix();
	glTranslated(40, 0, -90);
	p(h);
	glPopMatrix();
	glPushMatrix();
	glTranslated(-40, 0, 90);
	p(h);
	glPopMatrix();
	glPushMatrix();
	glTranslated(40, 0, 90);
	p(h);
	glPopMatrix();

	glEnable(GL_TEXTURE_2D);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, mode ? GL_REPLACE : GL_MODULATE);
	glColor3f(1, 1, 1);
	glBindTexture(GL_TEXTURE_2D, texture[8]);
	glColor3d(1, 1, 1);
	glTranslated(0, h, 0);
	glColor3d(.6, 1, .6);
	points(50, h / 10, 100);

	glDisable(GL_TEXTURE_2D);

}

// Draw the ping pong table net
static void net(double x, double y, double z, double dx, double dy, double dz, double th, double rx, double ry, double rz) {
	//  Set specular color to white
	float white[] = { 1,1,1,1 };
	float black[] = { 0,0,0,1 };
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shiny);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, white);
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, black);

	// Translations
	glTranslated(x, y, z);
	glRotated(th, rx, ry, rz);
	glScaled(dx, dy, dz);

	//Enable textures
	glEnable(GL_TEXTURE_2D);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, mode ? GL_REPLACE : GL_MODULATE);
	glColor3f(1, 1, 1);
	glBindTexture(GL_TEXTURE_2D, texture[7]);

	glBegin(GL_QUADS);

	glColor3f(1.0f, 1.0f, 1.0f);

	int x1 = 100;
	int y1 = 6;
	int y2 = 40;
	int z1 = 10;
	int z2 = 10.5;

	//Back side
	glNormal3f(0.0f, 0.0f, -1.0f);

	glTexCoord2f(0, 0); glVertex3f(-x1, y1, -z2);
	glTexCoord2f(5, 0); glVertex3f(x1, y1, -z2);
	glTexCoord2f(5, 1); glVertex3f(x1, y2, -z2);
	glTexCoord2f(0, 1); glVertex3f(-x1, y2, -z2);

	//Front side
	glNormal3f(0.0f, 0.0f, 1.0f);

	glTexCoord2f(0, 0); glVertex3f(-x1, y1, -z1);
	glTexCoord2f(5, 0); glVertex3f(x1, y1, -z1);
	glTexCoord2f(5, 1); glVertex3f(x1, y2, -z1);
	glTexCoord2f(0, 1); glVertex3f(-x1, y2, -z1);


	//Left side
	glNormal3f(-1.0f, 0.0f, 0.0f);

	glTexCoord2f(0, 0); glVertex3f(-x1, y1, -z2);
	glTexCoord2f(1, 0); glVertex3f(-x1, y2, -z2);
	glTexCoord2f(1, 1); glVertex3f(-x1, y2, -z1);
	glTexCoord2f(0, 1); glVertex3f(-x1, y1, -z1);

	//Right side
	glNormal3f(1.0f, 0.0f, 0.0f);

	glTexCoord2f(0, 0); glVertex3f(x1, y1, -z2);
	glTexCoord2f(1, 0); glVertex3f(x1, y2, -z2);
	glTexCoord2f(1, 1); glVertex3f(x1, y2, -z1);
	glTexCoord2f(0, 1); glVertex3f(x1, y1, -z1);

	//Top
	glNormal3f(0.0f, 1.0f, 0.0f);

	glTexCoord2f(0, 0); glVertex3f(-x1, y2, -z2);
	glTexCoord2f(1, 0); glVertex3f(-x1, y2, -z1);
	glTexCoord2f(1, 1); glVertex3f(x1, y2, -z1);
	glTexCoord2f(0, 1); glVertex3f(x1, y2, -z2);

	glEnd();
	glDisable(GL_TEXTURE_2D);
}

// Draw the bookcase
static void bookcase(double x, double y, double z, double dx, double dy, double dz, double th, double rx, double ry, double rz) {
	//  Set specular color to white
	float white[] = { 1,1,1,1 };
	float black[] = { 0,0,0,1 };
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shiny);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, white);
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, black);

	// Translations
	glTranslated(x, y, z);
	glRotated(th, rx, ry, rz);
	glScaled(dx, dy, dz);

	//Enable textures
	glEnable(GL_TEXTURE_2D);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, mode ? GL_REPLACE : GL_MODULATE);
	glColor3f(1, 1, 1);
	glBindTexture(GL_TEXTURE_2D, texture[9]);

	glBegin(GL_QUADS);

	glColor3f(1.0f, 1.0f, 1.0f);

	int x1 = 100;
	int y1 = 20;
	int y2 = 200;
	int z1 = 50;
	int z2 = 120;
	
	//Bottom
	glNormal3f(0.0f, 0.0f, -1.0f);

	glTexCoord2f(0, 0); glVertex3f(-x1, y1, -z2);
	glTexCoord2f(5, 0); glVertex3f(x1, y1, -z2);
	glTexCoord2f(5, 1); glVertex3f(x1, y2, -z2);
	glTexCoord2f(0, 1); glVertex3f(-x1, y2, -z2);

	glEnd();
	glDisable(GL_TEXTURE_2D);

	glEnable(GL_TEXTURE_2D);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, mode ? GL_REPLACE : GL_MODULATE);
	glColor3f(1, 1, 1);
	glBindTexture(GL_TEXTURE_2D, texture[13]);

	glBegin(GL_QUADS);

	glColor3f(1.0f, 1.0f, 1.0f);
	
	//back side
	glNormal3f(0.0f, 0.0f, 1.0f);

	glTexCoord2f(0, 0); glVertex3f(-x1, y1, -z1);
	glTexCoord2f(5, 0); glVertex3f(x1, y1, -z1);
	glTexCoord2f(5, 1); glVertex3f(x1, y2, -z1);
	glTexCoord2f(0, 1); glVertex3f(-x1, y2, -z1);
	

	//Left side
	glNormal3f(-1.0f, 0.0f, 0.0f);

	glTexCoord2f(0, 0); glVertex3f(-x1, y1, -z2);
	glTexCoord2f(1, 0); glVertex3f(-x1, y2, -z2);
	glTexCoord2f(1, 1); glVertex3f(-x1, y2, -z1);
	glTexCoord2f(0, 1); glVertex3f(-x1, y1, -z1);

	//Right side
	glNormal3f(1.0f, 0.0f, 0.0f);

	glTexCoord2f(0, 0); glVertex3f(x1, y1, -z2);
	glTexCoord2f(1, 0); glVertex3f(x1, y2, -z2);
	glTexCoord2f(1, 1); glVertex3f(x1, y2, -z1);
	glTexCoord2f(0, 1); glVertex3f(x1, y1, -z1);

	//Top
	glNormal3f(0.0f, 1.0f, 0.0f);

	glTexCoord2f(0, 0); glVertex3f(-x1, y2, -z2);
	glTexCoord2f(1, 0); glVertex3f(-x1, y2, -z1);
	glTexCoord2f(1, 1); glVertex3f(x1, y2, -z1);
	glTexCoord2f(0, 1); glVertex3f(x1, y2, -z2);

	glEnd();
	glDisable(GL_TEXTURE_2D);
}

// Draw the small side table
static void smalltable(double x, double y, double z, double dx, double dy, double dz, double th, double rx, double ry, double rz) {

	// Translations
	glTranslated(x, y, z);
	glRotated(th, rx, ry, rz);
	glScaled(dx, dy, dz);

	glEnable(GL_TEXTURE_2D);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, mode ? GL_REPLACE : GL_MODULATE);
	glColor3f(1, 1, 1);
	glBindTexture(GL_TEXTURE_2D, texture[4]);

	glColor3d(1, 1, 1);
	double h = 30;
	glPushMatrix();
	glTranslated(-40, 0, -90);
	p(h);
	glPopMatrix();
	glPushMatrix();
	glTranslated(40, 0, -90);
	p(h);
	glPopMatrix();
	glPushMatrix();
	glTranslated(-40, 0, 90);
	p(h);
	glPopMatrix();
	glPushMatrix();
	glTranslated(40, 0, 90);
	p(h);
	glPopMatrix();

	glTranslated(0, h, 0);
	glColor3d(1, 1, 1);
	points(50, h / 10, 100);

	glDisable(GL_TEXTURE_2D);

}

// Draw the ottoman
static void ottoman(double x, double y, double z, double dx, double dy, double dz, double th, double rx, double ry, double rz) {
	//  Set specular color to white
	float white[] = { 1,1,1,1 };
	float black[] = { 0,0,0,1 };
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shiny);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, white);
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, black);

	// Translations
	glTranslated(x, y, z);
	glRotated(th, rx, ry, rz);
	glScaled(dx, dy, dz);

	//Enable textures
	glEnable(GL_TEXTURE_2D);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, mode ? GL_REPLACE : GL_MODULATE);
	glColor3f(1, 1, 1);
	glBindTexture(GL_TEXTURE_2D, texture[16]);

	glBegin(GL_QUADS);

	glColor3f(1.0f, 1.0f, 1.0f);

	int x1 = 23;
	int y1 = 20;
	int y2 = 30;
	int z1 = 50;
	int z2 = 70;

	//Bottom
	glNormal3f(0.0f, 0.0f, -1.0f);

	glTexCoord2f(0, 0); glVertex3f(-x1, y1, -z2);
	glTexCoord2f(5, 0); glVertex3f(x1, y1, -z2);
	glTexCoord2f(5, 1); glVertex3f(x1, y2, -z2);
	glTexCoord2f(0, 1); glVertex3f(-x1, y2, -z2);

	//back side
	glNormal3f(0.0f, 0.0f, 1.0f);

	glTexCoord2f(0, 0); glVertex3f(-x1, y1, -z1);
	glTexCoord2f(5, 0); glVertex3f(x1, y1, -z1);
	glTexCoord2f(5, 1); glVertex3f(x1, y2, -z1);
	glTexCoord2f(0, 1); glVertex3f(-x1, y2, -z1);


	//Left side
	glNormal3f(-1.0f, 0.0f, 0.0f);

	glTexCoord2f(0, 0); glVertex3f(-x1, y1, -z2);
	glTexCoord2f(1, 0); glVertex3f(-x1, y2, -z2);
	glTexCoord2f(1, 1); glVertex3f(-x1, y2, -z1);
	glTexCoord2f(0, 1); glVertex3f(-x1, y1, -z1);

	//Right side
	glNormal3f(1.0f, 0.0f, 0.0f);

	glTexCoord2f(0, 0); glVertex3f(x1, y1, -z2);
	glTexCoord2f(1, 0); glVertex3f(x1, y2, -z2);
	glTexCoord2f(1, 1); glVertex3f(x1, y2, -z1);
	glTexCoord2f(0, 1); glVertex3f(x1, y1, -z1);

	//Top
	glNormal3f(0.0f, 1.0f, 0.0f);

	glTexCoord2f(0, 0); glVertex3f(-x1, y2, -z2);
	glTexCoord2f(1, 0); glVertex3f(-x1, y2, -z1);
	glTexCoord2f(1, 1); glVertex3f(x1, y2, -z1);
	glTexCoord2f(0, 1); glVertex3f(x1, y2, -z2);

	glEnd();
	glDisable(GL_TEXTURE_2D);
}


/*
 *  Draw vertex in polar coordinates with normal
 */
static void Vertex(double th, double ph)
{
	double x = Sin(th)*Cos(ph);
	double y = Cos(th)*Cos(ph);
	double z = Sin(ph);
	//  For a sphere at the origin, the position
	//  and normal vectors are the same
	glNormal3d(x, y, z);
	glVertex3d(x, y, z);
}

// Draw the light ball
static void ball(double x, double y, double z, double r)
{
	int th, ph;
	float yellow[] = { 1.0,1.0,0.0,1.0 };
	float Emission[] = { 0.0,0.0,0.01*emission,1.0 };
	//  Save transformation
	glPushMatrix();
	//  Offset, scale and rotate
	glTranslated(x, y, z);
	glScaled(r, r, r);
	//  White ball
	glColor3f(1, 1, 1);
	glMaterialf(GL_FRONT, GL_SHININESS, shiny);
	glMaterialfv(GL_FRONT, GL_SPECULAR, yellow);
	glMaterialfv(GL_FRONT, GL_EMISSION, Emission);
	//  Bands of latitude
	for (ph = -90; ph < 90; ph += inc)
	{
		glBegin(GL_QUAD_STRIP);
		for (th = 0; th <= 360; th += 2 * inc)
		{
			Vertex(th, ph);
			Vertex(th, ph + inc);
		}
		glEnd();
	}
	//  Undo transofrmations
	glPopMatrix();
}

// Draw the ping pong ball
static void pingball(double x, double y, double z, double dx, double dy, double dz, double th1, double rx, double ry, double rz) {
	int th, ph;
	float yellow[] = { 1.0,1.0,0.0,1.0 };
	float Emission[] = { 0.0,0.0,0.01*emission,1.0 };

	// Translations
	glTranslated(x, y, z);
	glRotated(th1, rx, ry, rz);
	glScaled(dx, dy, dz);

	//  Save transformation
	glPushMatrix();

	//  White ball
	glColor3f(1, 1, 1);
	glMaterialf(GL_FRONT, GL_SHININESS, shiny);
	glMaterialfv(GL_FRONT, GL_SPECULAR, yellow);
	glMaterialfv(GL_FRONT, GL_EMISSION, Emission);
	//  Bands of latitude
	for (ph = -90; ph < 90; ph += inc)
	{
		glBegin(GL_QUAD_STRIP);
		for (th = 0; th <= 360; th += 2 * inc)
		{
			Vertex(th, ph);
			Vertex(th, ph + inc);
		}
		glEnd();
	}
	//  Undo transofrmations
	glPopMatrix();
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
		if (m) {
			double Ex = -2 * dim*Sin(th)*Cos(ph);
			double Ey = +2 * dim        *Sin(ph);
			double Ez = +2 * dim*Cos(th)*Cos(ph);
			gluLookAt(Ex, Ey, Ez, 0, 0, 0, 0, Cos(ph), 0);
		}
		//Orthogonal - set view angle (like normal)
		else {
			glRotatef(ph, 1, 0, 0);
			glRotatef(th, 0, 1, 0);
		}
	}

	//  Flat or smooth shading
	glShadeModel(smooth ? GL_SMOOTH : GL_FLAT);

	//  Light switch
	if (light)
	{
		//  Translate intensity to color vectors
		float Ambient[] = { 0.01*ambient ,0.01*ambient ,0.01*ambient ,1.0 };
		float Diffuse[] = { 0.01*diffuse ,0.01*diffuse ,0.01*diffuse ,1.0 };
		float Specular[] = { 0.01*specular,0.01*specular,0.01*specular,1.0 };
		//  Light position
		float Position[] = { distance*Cos(zh),ylight,distance*Sin(zh),1.0 };
		//  Draw light position as ball (still no lighting here)
		glColor3f(1, 1, 1);
		ball(Position[0], Position[1], Position[2], 10);
		//  OpenGL should normalize normal vectors
		glEnable(GL_NORMALIZE);
		//  Enable lighting
		glEnable(GL_LIGHTING);
		//      //  Location of viewer for specular calculations
		//      glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER,local);
			   //  glColor sets ambient and diffuse color materials
		glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
		glEnable(GL_COLOR_MATERIAL);
		//  Enable light 0
		glEnable(GL_LIGHT0);
		//  Set ambient, diffuse, specular components and position of light 0
		glLightfv(GL_LIGHT0, GL_AMBIENT, Ambient);
		glLightfv(GL_LIGHT0, GL_DIFFUSE, Diffuse);
		glLightfv(GL_LIGHT0, GL_SPECULAR, Specular);
		glLightfv(GL_LIGHT0, GL_POSITION, Position);
	}
	else
		glDisable(GL_LIGHTING);


	//Draw all the objects
	walls();
	if (w) { o_walls(); }
	sky();

	couch(-100, 37.5, 0, 3, 1, 1.5, 0, 0, 0, 0);
	seat(100, -20, -27.5, 0.5, 1, 1, 95, 1, 0, 0);
	tvstand(-100, -300, -35, 2, 1, 0.75, 95, 1, 0, 0);
	tv(0, -3.5, 40, 0.75 , 1, 0.75, 0, 0, 0, 0);
	table(0, -9, -900, 1.5, 1, 1, 0, 0, 0, 0);
	net(10, 0, 0, 1, 1, 1, 90, 0, 1, 0);
	bookcase(285, -110, -25, 1, 1, 1, 90, 0, 1, 0);
	smalltable(85, 50, -625, 0.25, 1, 0.5, 0, 0, 0, 0);
	pingball(-220, 39.5, 520, 5, 5, 10, 0, 0, 0, 0);
	ottoman(0, -40, -30, 1, 1, 1, 0, 0, 0, 0);

	ErrCheck("display");

	//  Render the scene
	glFlush();
	//  Make the rendered scene visible
	glutSwapBuffers();
}

/*
 *  GLUT calls this routine when the window is resized
 */
void idle()
{
	//  Elapsed time in seconds
	double t = glutGet(GLUT_ELAPSED_TIME) / 1000.0;
	zh = fmod(90 * t, 360.0);
	//  Tell GLUT it is necessary to redisplay the scene
	glutPostRedisplay();
}

/*
 *  GLUT calls this routine when an arrow key is pressed
 */
void special(int key, int x, int y)
{
	if (!fp) { //for first person
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
		//  PageUp key - increase dim
		else if (key == GLUT_KEY_PAGE_DOWN)
			dim += 5;
		//  PageDown key - decrease dim
		else if (key == GLUT_KEY_PAGE_UP && dim > 1)
			dim -= 5;
		//  Keep angles to +/-360 degrees
		th %= 360;
		ph %= 360;
	}
	//  Update projection
	Project(45, asp, dim, fp, m);
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
	//  Toggle lighting
	else if (ch == 'l')
		light = 1 - light;
	//  Toggle the tv
	else if (ch == 't')
		tv_on = 1 - tv_on;
	//  Toggle the walls
	else if (ch == 'w')
		w = 1 - w;
	//  Toggle light movement
	else if (ch == 'm')
		move = 1 - move;
	//  Light elevation
	else if (ch == '[')
		ylight -= 10;
	else if (ch == ']')
		ylight += 10;
	if (fp) { //only when in first person
		//Update eye variables based on camera variables
		double dt = 0.05;
		//Move 'forward'
		if (ch == 'y') {
			Ex += Cx * dt;
			Ez += Cz * dt;
		}
		//Rotate view left
		else if (ch == 'g') {
			rotation -= 3;
		}
		//Move 'backward'
		else if (ch == 'h') {
			Ex -= Cx * dt;
			Ez -= Cz * dt;
		}
		//Rotate view right
		else if (ch == 'j') {
			rotation += 3;
		}
		//Keep angles to +/-360 degrees
		rotation %= 360;
	}
	else { //when not in first person mode
		//  Reset view angle
		if (ch == '0')
			th = ph = 45;
		//Switch display mode
		else if (ch == 'p')
			m = 1 - m;
	}
	//  Translate shininess power to value (-1 => 0)
	shiny = shininess < 0 ? 0 : pow(2.0, shininess);
	//  Reproject
	Project(45, asp, dim, fp, m);
	//  Animate if requested
	glutIdleFunc(move ? idle : NULL);
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
	//  Set projection
	Project(45, asp, dim, fp, m);
}

/*
 *  Start up GLUT and tell it what to do
 */
int main(int argc, char* argv[])
{
	//  Initialize GLUT and process user parameters
	glutInit(&argc, argv);
	//  Request double buffered, true color window with Z buffering at 600x600
	glutInitWindowSize(800, 600);
	glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
	//  Create the window
	glutCreateWindow("The Living Room by Colin O'Connell");
	//  Tell GLUT to call "display" when the scene should be drawn
	glutDisplayFunc(display);
	//  Tell GLUT to call "reshape" when the window is resized
	glutReshapeFunc(reshape);
	//  Tell GLUT to call "special" when an arrow key is pressed
	glutSpecialFunc(special);
	//  Tell GLUT to call "key" when a key is pressed
	glutKeyboardFunc(key);
	glutIdleFunc(idle);
	//Load textures
	texture[0] = LoadTexBMP("blue-fabric.bmp");
	texture[1] = LoadTexBMP("brown-fabric.bmp");
	texture[2] = LoadTexBMP("tv.bmp");
	texture[3] = LoadTexBMP("the-office.bmp");
	texture[4] = LoadTexBMP("vector-wood-texture.bmp");
	texture[5] = LoadTexBMP("black_metal.bmp");
	texture[6] = LoadTexBMP("tv_screen.bmp");
	texture[7] = LoadTexBMP("net.bmp");
	texture[8] = LoadTexBMP("pingtable.bmp");
	texture[9] = LoadTexBMP("bookshelf.bmp");
	texture[10] = LoadTexBMP("wall.bmp");
	texture[11] = LoadTexBMP("hardwood-floor.bmp");
	texture[12] = LoadTexBMP("chair-fabric.bmp");
	texture[13] = LoadTexBMP("medium-wood.bmp");
	texture[14] = LoadTexBMP("brick.bmp");
	texture[15] = LoadTexBMP("sky.bmp");
	texture[16] = LoadTexBMP("ottoman.bmp");
	//  Pass control to GLUT so it can interact with the user
	ErrCheck("init");
	glutMainLoop();
	return 0;
}

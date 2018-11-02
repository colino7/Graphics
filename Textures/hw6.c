/*	Colin O'Connell HW6

	*Some code taken directly from professor's example files - especially ex15.c
	*Objects from my HW3, HW4, and HW5
 */
#include "CSCIx229.h"

int th = 45.0;      //  Azimuth of view angle
int ph = 45.0;      //  Elevation of view angle
int move = 1;       //  Move light
int light = 1;      //  Lighting
double asp = 1;     //  Aspect ratio
double dim = 5.0;   //  Size of world

// Light values
int one = 1;		// Unit value
int distance = 5;	// Light distance
int smooth = 1;		// Smooth/Flat shading
int local = 0;		// Local Viewer Model
int ambient = 30;	// Ambient intensity (%)
int diffuse = 100;  // Diffuse intensity (%)
int specular = 0;	// Specular intensity (%)
int zh = 90;		// Light azimuth
float ylight = 0;	// Elevation of light
int emission = 0;	// Emission intensity (%)
int shininess = 0;  // Shininess (power of two)
float shiny = 1;	// Shininess (value)
int inc = 10;		// Ball increment

//Texture values
int mode = 0;    //  Texture mode
unsigned int texture[2];  //  Texture names

//Draw a chair object (with updated Normals)
static void chair(double x, double y, double z, double dx, double dy, double dz, double th) {

	//  Set specular color to white
	float white[] = { 1,1,1,1 };
	float black[] = { 0,0,0,1 };
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shiny);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, white);
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, black);

	// Translations
	glTranslated(x, y, z);
	glRotated(th, 0, 1, 0);
	glScaled(dx, dy, dz);

	//Enable textures
	glEnable(GL_TEXTURE_2D);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, mode ? GL_REPLACE : GL_MODULATE);
	glColor3f(1, 1, 1);
	glBindTexture(GL_TEXTURE_2D, texture[1]);

	glBegin(GL_QUADS);

	glColor3f(0.71f, 0.65f, 0.26f);

	//Front of bench
	glNormal3f(0.0f, 0.0f, 1.0f);

	glTexCoord2f(0, 0); glVertex3f(-0.5f, -0.05f, 0.5f);
	glTexCoord2f(1, 0); glVertex3f(0.5f, -0.05f, 0.5f);
	glTexCoord2f(1, 1); glVertex3f(0.5f, 0.05f, 0.5f);
	glTexCoord2f(0, 1); glVertex3f(-0.5f, 0.05f, 0.5f);


	//Right side of bench
	glNormal3f(1.0f, 0.0f, 0.0f);

	glTexCoord2f(0, 0); glVertex3f(0.5f, -0.05f, -0.5f);
	glTexCoord2f(1, 0); glVertex3f(0.5f, 0.05f, -0.5f);
	glTexCoord2f(1, 1); glVertex3f(0.5f, 0.05f, 0.5f);
	glTexCoord2f(0, 1); glVertex3f(0.5f, -0.05f, 0.5f);


	//Back side of bench
	glNormal3f(0.0f, 0.0f, -1.0f);

	glTexCoord2f(0, 0); glVertex3f(-0.5f, -0.05f, -0.5f);
	glTexCoord2f(1, 0); glVertex3f(-0.5f, 0.05f, -0.5f);
	glTexCoord2f(1, 1); glVertex3f(0.5f, 0.05f, -0.5f);
	glTexCoord2f(0, 1); glVertex3f(0.5f, -0.05f, -0.5f);


	//Left side of bench
	glNormal3f(-1.0f, 0.0f, 0.0f);

	glTexCoord2f(0, 0); glVertex3f(-0.5f, -0.05f, -0.5f);
	glTexCoord2f(1, 0); glVertex3f(-0.5f, -0.05f, 0.5f);
	glTexCoord2f(1, 1); glVertex3f(-0.5f, 0.05f, 0.5f);
	glTexCoord2f(0, 1); glVertex3f(-0.5f, 0.05f, -0.5f);

	//Top of bench
	glNormal3f(0.0f, 1.0f, 0.0f);

	glTexCoord2f(0, 0); glVertex3f(0.5f, 0.05f, 0.5f);
	glTexCoord2f(1, 0); glVertex3f(-0.5f, 0.05f, 0.5f);
	glTexCoord2f(1, 1); glVertex3f(-0.5f, 0.05f, -0.5f);
	glTexCoord2f(0, 1); glVertex3f(0.5f, 0.05f, -0.5f);


	//Bottom of bench
	glNormal3f(0.0f, -1.0f, 0.0f);

	glTexCoord2f(0, 0); glVertex3f(0.5f, -0.05f, 0.5f);
	glTexCoord2f(1, 0); glVertex3f(-0.5f, -0.05f, 0.5f);
	glTexCoord2f(1, 1); glVertex3f(-0.5f, -0.05f, -0.5f);
	glTexCoord2f(0, 1); glVertex3f(0.5f, -0.05f, -0.5f);


	glColor3f(0.9f, 0.91f, 0.98f);

	//Front right leg

	//Front side
	glNormal3f(0.0f, 0.0f, 1.0f);

	glTexCoord2f(0, 0); glVertex3f(0.45f, -0.05f, 0.4f);
	glTexCoord2f(1, 0); glVertex3f(0.35f, -0.05f, 0.4f);
	glTexCoord2f(1, 1); glVertex3f(0.35f, -0.75f, 0.4f);
	glTexCoord2f(0, 1); glVertex3f(0.45f, -0.75f, 0.4f);

	//Back side
	glNormal3f(0.0f, 0.0f, -1.0f);

	glTexCoord2f(0, 0); glVertex3f(0.45f, -0.05f, 0.3f);
	glTexCoord2f(1, 0); glVertex3f(0.35f, -0.05f, 0.3f);
	glTexCoord2f(1, 1); glVertex3f(0.35f, -0.75f, 0.3f);
	glTexCoord2f(0, 1); glVertex3f(0.45f, -0.75f, 0.3f);

	//Right side
	glNormal3f(1.0f, 0.0f, 0.0f);

	glTexCoord2f(0, 0); glVertex3f(0.45f, -0.05f, 0.4f);
	glTexCoord2f(1, 0); glVertex3f(0.45f, -0.05f, 0.3f);
	glTexCoord2f(1, 1); glVertex3f(0.45f, -0.75f, 0.3f);
	glTexCoord2f(0, 1); glVertex3f(0.45f, -0.75f, 0.4f);

	//Left side
	glNormal3f(-1.0f, 0.0f, 0.0f);

	glTexCoord2f(0, 0); glVertex3f(0.35f, -0.05f, 0.4f);
	glTexCoord2f(1, 0); glVertex3f(0.35f, -0.05f, 0.3f);
	glTexCoord2f(1, 1); glVertex3f(0.35f, -0.75f, 0.3f);
	glTexCoord2f(0, 1); glVertex3f(0.35f, -0.75f, 0.4f);

	//Back Right Leg

	//Front side
	glNormal3f(0.0f, 0.0f, 1.0f);

	glTexCoord2f(0, 0); glVertex3f(0.45f, -0.05f, -0.3f);
	glTexCoord2f(1, 0); glVertex3f(0.35f, -0.05f, -0.3f);
	glTexCoord2f(1, 1); glVertex3f(0.35f, -0.75f, -0.3f);
	glTexCoord2f(0, 1); glVertex3f(0.45f, -0.75f, -0.3f);

	//Back side
	glNormal3f(0.0f, 0.0f, -1.0f);

	glTexCoord2f(0, 0); glVertex3f(0.45f, -0.05f, -0.4f);
	glTexCoord2f(1, 0); glVertex3f(0.35f, -0.05f, -0.4f);
	glTexCoord2f(1, 1); glVertex3f(0.35f, -0.75f, -0.4f);
	glTexCoord2f(0, 1); glVertex3f(0.45f, -0.75f, -0.4f);

	//Right side
	glNormal3f(1.0f, 0.0f, 0.0f);

	glTexCoord2f(0, 0); glVertex3f(0.45f, -0.05f, -0.4f);
	glTexCoord2f(1, 0); glVertex3f(0.45f, -0.05f, -0.3f);
	glTexCoord2f(1, 1); glVertex3f(0.45f, -0.75f, -0.3f);
	glTexCoord2f(0, 1); glVertex3f(0.45f, -0.75f, -0.4f);

	//Left side
	glNormal3f(-1.0f, 0.0f, 0.0f);

	glTexCoord2f(0, 0); glVertex3f(0.35f, -0.05f, -0.4f);
	glTexCoord2f(1, 0); glVertex3f(0.35f, -0.05f, -0.3f);
	glTexCoord2f(1, 1); glVertex3f(0.35f, -0.75f, -0.3f);
	glTexCoord2f(0, 1); glVertex3f(0.35f, -0.75f, -0.4f);

	//Front Left Leg

	//Front side
	glNormal3f(0.0f, 0.0f, 1.0f);

	glTexCoord2f(0, 0); glVertex3f(-0.45f, -0.05f, 0.4f);
	glTexCoord2f(1, 0); glVertex3f(-0.35f, -0.05f, 0.4f);
	glTexCoord2f(1, 1); glVertex3f(-0.35f, -0.75f, 0.4f);
	glTexCoord2f(0, 1); glVertex3f(-0.45f, -0.75f, 0.4f);

	//Back side
	glNormal3f(0.0f, 0.0f, -1.0f);

	glTexCoord2f(0, 0); glVertex3f(-0.45f, -0.05f, 0.3f);
	glTexCoord2f(1, 0); glVertex3f(-0.35f, -0.05f, 0.3f);
	glTexCoord2f(1, 1); glVertex3f(-0.35f, -0.75f, 0.3f);
	glTexCoord2f(0, 1); glVertex3f(-0.45f, -0.75f, 0.3f);

	//Right side
	glNormal3f(-1.0f, 0.0f, 0.0f);

	glTexCoord2f(0, 0); glVertex3f(-0.45f, -0.05f, 0.4f);
	glTexCoord2f(1, 0); glVertex3f(-0.45f, -0.05f, 0.3f);
	glTexCoord2f(1, 1); glVertex3f(-0.45f, -0.75f, 0.3f);
	glTexCoord2f(0, 1); glVertex3f(-0.45f, -0.75f, 0.4f);

	//Left side
	glNormal3f(1.0f, 0.0f, 0.0f);

	glTexCoord2f(0, 0); glVertex3f(-0.35f, -0.05f, 0.4f);
	glTexCoord2f(1, 0); glVertex3f(-0.35f, -0.05f, 0.3f);
	glTexCoord2f(1, 1); glVertex3f(-0.35f, -0.75f, 0.3f);
	glTexCoord2f(0, 1); glVertex3f(-0.35f, -0.75f, 0.4f);

	//Back Left Leg

	//Front side
	glNormal3f(0.0f, 0.0f, 1.0f);

	glTexCoord2f(0, 0); glVertex3f(-0.45f, -0.05f, -0.3f);
	glTexCoord2f(1, 0); glVertex3f(-0.35f, -0.05f, -0.3f);
	glTexCoord2f(1, 1); glVertex3f(-0.35f, -0.75f, -0.3f);
	glTexCoord2f(0, 1); glVertex3f(-0.45f, -0.75f, -0.3f);

	//Back side
	glNormal3f(0.0f, 0.0f, -1.0f);

	glTexCoord2f(0, 0); glVertex3f(-0.45f, -0.05f, -0.4f);
	glTexCoord2f(1, 0); glVertex3f(-0.35f, -0.05f, -0.4f);
	glTexCoord2f(1, 1); glVertex3f(-0.35f, -0.75f, -0.4f);
	glTexCoord2f(0, 1); glVertex3f(-0.45f, -0.75f, -0.4f);

	//Right side
	glNormal3f(-1.0f, 0.0f, 0.0f);

	glTexCoord2f(0, 0); glVertex3f(-0.45f, -0.05f, -0.4f);
	glTexCoord2f(1, 0); glVertex3f(-0.45f, -0.05f, -0.3f);
	glTexCoord2f(1, 1); glVertex3f(-0.45f, -0.75f, -0.3f);
	glTexCoord2f(0, 1); glVertex3f(-0.45f, -0.75f, -0.4f);

	//Left side
	glNormal3f(1.0f, 0.0f, 0.0f);

	glTexCoord2f(0, 0); glVertex3f(-0.35f, -0.05f, -0.4f);
	glTexCoord2f(1, 0); glVertex3f(-0.35f, -0.05f, -0.3f);
	glTexCoord2f(1, 1); glVertex3f(-0.35f, -0.75f, -0.3f);
	glTexCoord2f(0, 1); glVertex3f(-0.35f, -0.75f, -0.4f);

	glColor3f(0.65f, 0.50f, 0.39f);

	//Chair Back

	//Front side
	glNormal3f(0.0f, 0.0f, 1.0f);

	glTexCoord2f(0, 0); glVertex3f(-0.45f, 0.05f, -0.45f);
	glTexCoord2f(1, 0); glVertex3f(0.45f, 0.05f, -0.45f);
	glTexCoord2f(1, 1); glVertex3f(0.45f, 0.875f, -0.45f);
	glTexCoord2f(0, 1); glVertex3f(-0.45f, 0.875f, -0.45f);

	//Back side
	glNormal3f(0.0f, 0.0f, -1.0f);

	glTexCoord2f(0, 0); glVertex3f(-0.45f, 0.05f, -0.5f);
	glTexCoord2f(1, 0); glVertex3f(0.45f, 0.05f, -0.5f);
	glTexCoord2f(1, 1); glVertex3f(0.45f, 0.875f, -0.5f);
	glTexCoord2f(0, 1); glVertex3f(-0.45f, 0.875f, -0.5f);

	//Left side
	glNormal3f(-1.0f, 0.0f, 0.0f);

	glTexCoord2f(0, 0); glVertex3f(-0.45f, 0.05f, -0.5f);
	glTexCoord2f(1, 0); glVertex3f(-0.45f, 0.875f, -0.5f);
	glTexCoord2f(1, 1); glVertex3f(-0.45f, 0.875f, -0.45f);
	glTexCoord2f(0, 1); glVertex3f(-0.45f, 0.05f, -0.45f);

	//Right side
	glNormal3f(1.0f, 0.0f, 0.0f);

	glTexCoord2f(0, 0); glVertex3f(0.45f, 0.05f, -0.5f);
	glTexCoord2f(1, 0); glVertex3f(0.45f, 0.875f, -0.5f);
	glTexCoord2f(1, 1); glVertex3f(0.45f, 0.875f, -0.45f);
	glTexCoord2f(0, 1); glVertex3f(0.45f, 0.05f, -0.45f);

	//Top
	glNormal3f(0.0f, 1.0f, 0.0f);

	glTexCoord2f(0, 0); glVertex3f(-0.45f, 0.875f, -0.5f);
	glTexCoord2f(1, 0); glVertex3f(-0.45f, 0.875f, -0.45f);
	glTexCoord2f(1, 1); glVertex3f(0.45f, 0.875f, -0.45f);
	glTexCoord2f(0, 1); glVertex3f(0.45f, 0.875f, -0.5f);

	glEnd();
	glDisable(GL_TEXTURE_2D);
}

//Draw a bench object (with updated Normals)
static void bench(double x, double y, double z, double dx, double dy, double dz, double th) {

	//  Set specular color to white
	float white[] = { 1,1,1,1 };
	float black[] = { 0,0,0,1 };
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shiny);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, white);
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, black);

	// Translations
	glTranslated(x, y, z);
	glRotated(th, 0, 1, 0);
	glScaled(dx, dy, dz);

	//Enable textures
	glEnable(GL_TEXTURE_2D);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, mode ? GL_REPLACE : GL_MODULATE);
	glColor3f(1, 1, 1);
	glBindTexture(GL_TEXTURE_2D, texture[0]);

	glBegin(GL_QUADS);

	glColor3f(0.91f, 0.76f, 0.65f);
	//Front of bench
	glNormal3f(0.0f, 0.0f, 1.0f);

	glTexCoord2f(0, 0); glVertex3f(-0.5f, -0.05f, 0.5f);
	glTexCoord2f(1, 0); glVertex3f(0.5f, -0.05f, 0.5f);
	glTexCoord2f(1, 1); glVertex3f(0.5f, 0.05f, 0.5f);
	glTexCoord2f(0, 1); glVertex3f(-0.5f, 0.05f, 0.5f);


	//Right side of bench
	glNormal3f(1.0f, 0.0f, 0.0f);

	glTexCoord2f(0, 0); glVertex3f(0.5f, -0.05f, -0.5f);
	glTexCoord2f(1, 0); glVertex3f(0.5f, 0.05f, -0.5f);
	glTexCoord2f(1, 1); glVertex3f(0.5f, 0.05f, 0.5f);
	glTexCoord2f(0, 1); glVertex3f(0.5f, -0.05f, 0.5f);


	//Back side of bench
	glNormal3f(0.0f, 0.0f, -1.0f);

	glTexCoord2f(0, 0); glVertex3f(-0.5f, -0.05f, -0.5f);
	glTexCoord2f(1, 0); glVertex3f(-0.5f, 0.05f, -0.5f);
	glTexCoord2f(1, 1); glVertex3f(0.5f, 0.05f, -0.5f);
	glTexCoord2f(0, 1); glVertex3f(0.5f, -0.05f, -0.5f);


	//Left side of bench
	glNormal3f(-1.0f, 0.0f, 0.0f);

	glTexCoord2f(0, 0); glVertex3f(-0.5f, -0.05f, -0.5f);
	glTexCoord2f(1, 0); glVertex3f(-0.5f, -0.05f, 0.5f);
	glTexCoord2f(1, 1); glVertex3f(-0.5f, 0.05f, 0.5f);
	glTexCoord2f(0, 1); glVertex3f(-0.5f, 0.05f, -0.5f);

	//Top of bench
	glNormal3f(0.0f, 1.0f, 0.0f);

	glTexCoord2f(0, 0); glVertex3f(0.5f, 0.05f, 0.5f);
	glTexCoord2f(1, 0); glVertex3f(-0.5f, 0.05f, 0.5f);
	glTexCoord2f(1, 1); glVertex3f(-0.5f, 0.05f, -0.5f);
	glTexCoord2f(0, 1); glVertex3f(0.5f, 0.05f, -0.5f);


	//Bottom of bench
	glNormal3f(0.0f, -1.0f, 0.0f);

	glTexCoord2f(0, 0); glVertex3f(0.5f, -0.05f, 0.5f);
	glTexCoord2f(1, 0); glVertex3f(-0.5f, -0.05f, 0.5f);
	glTexCoord2f(1, 1); glVertex3f(-0.5f, -0.05f, -0.5f);
	glTexCoord2f(0, 1); glVertex3f(0.5f, -0.05f, -0.5f);


	glColor3f(0.52f, 0.37f, 0.26f);

	//Front right leg

	//Front side
	glNormal3f(0.0f, 0.0f, 1.0f);

	glTexCoord2f(0, 0); glVertex3f(0.45f, -0.05f, 0.4f);
	glTexCoord2f(1, 0); glVertex3f(0.35f, -0.05f, 0.4f);
	glTexCoord2f(1, 1); glVertex3f(0.35f, -0.75f, 0.4f);
	glTexCoord2f(0, 1); glVertex3f(0.45f, -0.75f, 0.4f);

	//Back side
	glNormal3f(0.0f, 0.0f, -1.0f);

	glTexCoord2f(0, 0); glVertex3f(0.45f, -0.05f, 0.3f);
	glTexCoord2f(1, 0); glVertex3f(0.35f, -0.05f, 0.3f);
	glTexCoord2f(1, 1); glVertex3f(0.35f, -0.75f, 0.3f);
	glTexCoord2f(0, 1); glVertex3f(0.45f, -0.75f, 0.3f);

	//Right side
	glNormal3f(1.0f, 0.0f, 0.0f);

	glTexCoord2f(0, 0); glVertex3f(0.45f, -0.05f, 0.4f);
	glTexCoord2f(1, 0); glVertex3f(0.45f, -0.05f, 0.3f);
	glTexCoord2f(1, 1); glVertex3f(0.45f, -0.75f, 0.3f);
	glTexCoord2f(0, 1); glVertex3f(0.45f, -0.75f, 0.4f);

	//Left side
	glNormal3f(-1.0f, 0.0f, 0.0f);

	glTexCoord2f(0, 0); glVertex3f(0.35f, -0.05f, 0.4f);
	glTexCoord2f(1, 0); glVertex3f(0.35f, -0.05f, 0.3f);
	glTexCoord2f(1, 1); glVertex3f(0.35f, -0.75f, 0.3f);
	glTexCoord2f(0, 1); glVertex3f(0.35f, -0.75f, 0.4f);

	//Back Right Leg

	//Front side
	glNormal3f(0.0f, 0.0f, 1.0f);

	glTexCoord2f(0, 0); glVertex3f(0.45f, -0.05f, -0.3f);
	glTexCoord2f(1, 0); glVertex3f(0.35f, -0.05f, -0.3f);
	glTexCoord2f(1, 1); glVertex3f(0.35f, -0.75f, -0.3f);
	glTexCoord2f(0, 1); glVertex3f(0.45f, -0.75f, -0.3f);

	//Back side
	glNormal3f(0.0f, 0.0f, -1.0f);

	glTexCoord2f(0, 0); glVertex3f(0.45f, -0.05f, -0.4f);
	glTexCoord2f(1, 0); glVertex3f(0.35f, -0.05f, -0.4f);
	glTexCoord2f(1, 1); glVertex3f(0.35f, -0.75f, -0.4f);
	glTexCoord2f(0, 1); glVertex3f(0.45f, -0.75f, -0.4f);

	//Right side
	glNormal3f(1.0f, 0.0f, 0.0f);

	glTexCoord2f(0, 0); glVertex3f(0.45f, -0.05f, -0.4f);
	glTexCoord2f(1, 0); glVertex3f(0.45f, -0.05f, -0.3f);
	glTexCoord2f(1, 1); glVertex3f(0.45f, -0.75f, -0.3f);
	glTexCoord2f(0, 1); glVertex3f(0.45f, -0.75f, -0.4f);

	//Left side
	glNormal3f(-1.0f, 0.0f, 0.0f);

	glTexCoord2f(0, 0); glVertex3f(0.35f, -0.05f, -0.4f);
	glTexCoord2f(1, 0); glVertex3f(0.35f, -0.05f, -0.3f);
	glTexCoord2f(1, 1); glVertex3f(0.35f, -0.75f, -0.3f);
	glTexCoord2f(0, 1); glVertex3f(0.35f, -0.75f, -0.4f);

	//Front Left Leg

	//Front side
	glNormal3f(0.0f, 0.0f, 1.0f);

	glTexCoord2f(0, 0); glVertex3f(-0.45f, -0.05f, 0.4f);
	glTexCoord2f(1, 0); glVertex3f(-0.35f, -0.05f, 0.4f);
	glTexCoord2f(1, 1); glVertex3f(-0.35f, -0.75f, 0.4f);
	glTexCoord2f(0, 1); glVertex3f(-0.45f, -0.75f, 0.4f);

	//Back side
	glNormal3f(0.0f, 0.0f, -1.0f);

	glTexCoord2f(0, 0); glVertex3f(-0.45f, -0.05f, 0.3f);
	glTexCoord2f(1, 0); glVertex3f(-0.35f, -0.05f, 0.3f);
	glTexCoord2f(1, 1); glVertex3f(-0.35f, -0.75f, 0.3f);
	glTexCoord2f(0, 1); glVertex3f(-0.45f, -0.75f, 0.3f);

	//Right side
	glNormal3f(-1.0f, 0.0f, 0.0f);

	glTexCoord2f(0, 0); glVertex3f(-0.45f, -0.05f, 0.4f);
	glTexCoord2f(1, 0); glVertex3f(-0.45f, -0.05f, 0.3f);
	glTexCoord2f(1, 1); glVertex3f(-0.45f, -0.75f, 0.3f);
	glTexCoord2f(0, 1); glVertex3f(-0.45f, -0.75f, 0.4f);

	//Left side
	glNormal3f(1.0f, 0.0f, 0.0f);

	glTexCoord2f(0, 0); glVertex3f(-0.35f, -0.05f, 0.4f);
	glTexCoord2f(1, 0); glVertex3f(-0.35f, -0.05f, 0.3f);
	glTexCoord2f(1, 1); glVertex3f(-0.35f, -0.75f, 0.3f);
	glTexCoord2f(0, 1); glVertex3f(-0.35f, -0.75f, 0.4f);

	//Back Left Leg

	//Front side
	glNormal3f(0.0f, 0.0f, 1.0f);

	glTexCoord2f(0, 0); glVertex3f(-0.45f, -0.05f, -0.3f);
	glTexCoord2f(1, 0); glVertex3f(-0.35f, -0.05f, -0.3f);
	glTexCoord2f(1, 1); glVertex3f(-0.35f, -0.75f, -0.3f);
	glTexCoord2f(0, 1); glVertex3f(-0.45f, -0.75f, -0.3f);

	//Back side
	glNormal3f(0.0f, 0.0f, -1.0f);

	glTexCoord2f(0, 0); glVertex3f(-0.45f, -0.05f, -0.4f);
	glTexCoord2f(1, 0); glVertex3f(-0.35f, -0.05f, -0.4f);
	glTexCoord2f(1, 1); glVertex3f(-0.35f, -0.75f, -0.4f);
	glTexCoord2f(0, 1); glVertex3f(-0.45f, -0.75f, -0.4f);

	//Right side
	glNormal3f(-1.0f, 0.0f, 0.0f);

	glTexCoord2f(0, 0); glVertex3f(-0.45f, -0.05f, -0.4f);
	glTexCoord2f(1, 0); glVertex3f(-0.45f, -0.05f, -0.3f);
	glTexCoord2f(1, 1); glVertex3f(-0.45f, -0.75f, -0.3f);
	glTexCoord2f(0, 1); glVertex3f(-0.45f, -0.75f, -0.4f);

	//Left side
	glNormal3f(1.0f, 0.0f, 0.0f);

	glTexCoord2f(0, 0); glVertex3f(-0.35f, -0.05f, -0.4f);
	glTexCoord2f(1, 0); glVertex3f(-0.35f, -0.05f, -0.3f);
	glTexCoord2f(1, 1); glVertex3f(-0.35f, -0.75f, -0.3f);
	glTexCoord2f(0, 1); glVertex3f(-0.35f, -0.75f, -0.4f);

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

	//  Perspective - set eye position
	double Ex = -2 * dim*Sin(th)*Cos(ph);
	double Ey = +2 * dim        *Sin(ph);
	double Ez = +2 * dim*Cos(th)*Cos(ph);
	gluLookAt(Ex, Ey, Ez, 0, 0, 0, 0, Cos(ph), 0);

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
		ball(Position[0], Position[1], Position[2], 0.1);
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

	//Draw the first normal chair
	chair(0, 0, 0, 1, 1, 1, 0);
	//Draw the second smaller, offset chair
	chair(1.5, -0.35, 1.5, 0.4, 0.75, 0.5, -30);
	//Draw bench item
	bench(-2, 0, 1.5, 4, 1, 1, 0);

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
		dim += 0.1;
	//  PageDown key - decrease dim
	else if (key == GLUT_KEY_PAGE_UP && dim > 1)
		dim -= 0.1;
	//  Keep angles to +/-360 degrees
	th %= 360;
	ph %= 360;
	//  Update projection
	Project(45, asp, dim);
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
	//  Toggle lighting
	else if (ch == 'l')
		light = 1 - light;
	//  Toggle texture mode
   else if (ch == 't')
      mode = 1-mode;
	//  Toggle light movement
	else if (ch == 'm')
		move = 1 - move;
	//  Light elevation
	else if (ch == '[')
		ylight -= 0.1;
	else if (ch == ']')
		ylight += 0.1;
	//  Ambient level
	else if (ch == 'a' && ambient > 0)
		ambient -= 5;
	else if (ch == 's' && ambient < 100)
		ambient += 5;
	//  Diffuse level
	else if (ch == 'd' && diffuse > 0)
		diffuse -= 5;
	else if (ch == 'f' && diffuse < 100)
		diffuse += 5;
	//  Specular level
	else if (ch == 'g' && specular > 0)
		specular -= 5;
	else if (ch == 'h' && specular < 100)
		specular += 5;
	//  Emission level
	else if (ch == 'j' && emission > 0)
		emission -= 5;
	else if (ch == 'k' && emission < 100)
		emission += 5;
	//  Shininess level
	else if (ch == 'z' && shininess > -1)
		shininess -= 1;
	else if (ch == 'x' && shininess < 7)
		shininess += 1;
	//  Translate shininess power to value (-1 => 0)
	shiny = shininess < 0 ? 0 : pow(2.0, shininess);
	//  Reproject
	Project(45, asp, dim);
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
	Project(45, asp, dim);
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
	glutCreateWindow("Assignment 6: Colin O'Connell");
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
	texture[0] = LoadTexBMP("vector-wood-texture.bmp");
	texture[1] = LoadTexBMP("dark-wood.bmp");
	//  Pass control to GLUT so it can interact with the user
	ErrCheck("init");
	glutMainLoop();
	return 0;
}

/*
 *  Set projection
 */
#include "CSCIx229.h"

void Project(double fov,double asp,double dim,double fp,double m)
{
   //  Tell OpenGL we want to manipulate the projection matrix
   glMatrixMode(GL_PROJECTION);
   //  Undo previous transformations
   glLoadIdentity();
   if (fp) { //First person
		gluPerspective(fov,asp,dim/16,16*dim);
	}
	else {
		if (m)
			gluPerspective(fov,asp,dim/16,16*dim); //same used for first person
		//  Orthogonal projection
		else
			glOrtho(-asp * dim, +asp * dim, -dim, +dim, -dim, +dim);
	}
   //  Switch to manipulating the model matrix
   glMatrixMode(GL_MODELVIEW);
   //  Undo previous transformations
   glLoadIdentity();
}


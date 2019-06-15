#include <cmath>
#include <gl\glew.h>
#include <SDL_opengl.h>
//#include <gl\glu.h> // Deja inclus dans glew.h

#include <SDL.h>

#include "forms.h"

using namespace std;

///////////////////////////////////
///////////		FORM	///////////
///////////////////////////////////
void Form::update(double delta_t)
{
    // Nothing to do here, animation update is done in child class method
	//glColor3f(col.r, col.g, col.b);
}


void Form::render()
{
    // Point of view for rendering
    // Common for all Forms
    Point org = anim.getPos();
    glTranslated(org.x, org.y, org.z);
	glColor3f(col.r, col.g, col.b);

	//glScaled(0.15, 0.15, 0.15);
}

///////////////////////////////////////
///////////		SPHERE		///////////
///////////////////////////////////////
Sphere::Sphere(double r, Color cl)
{
    radius = r;
    col = cl;
}


void Sphere::update(double delta_t)
{
    // Complete this part
}


void Sphere::render()
{
    GLUquadric *quad;
	glColor3f(col.r, col.g, col.b);
	glTranslated(this->getAnim().getPos().x * 0.15, this->getAnim().getPos().y * 0.15, this->getAnim().getPos().z *0.15);
	glScaled(0.15, 0.15, 0.15);

    quad = gluNewQuadric();

	gluSphere(quad, radius, 100, 20);

    // Complete this part

    gluDeleteQuadric(quad);
}


///////////////////////////////////
///////////		GLASS	///////////
///////////////////////////////////
Verre::Verre(double hei, double rayB, double rayT, Color co)
{
	height = hei;
	rayBottom = rayB;
	rayTop = rayT;
	col = RED;
	drawStyle = drawStyle;
	col = co;
}


void Verre::update(double delta_t)
{
	// Complete this part
}


void Verre::render()
{
	/*
	GLUquadric *quad;

	quad = gluNewQuadric();

	// Complete this part

	gluDeleteQuadric(quad);*/
	//////////////

	//glBindTexture(GL_TEXTURE_2D, texture1);
	
	

	// create cilynder
	GLUquadric* params;
	params = gluNewQuadric();

	// set possition 
	glTranslated(this->getAnim().getPos().x, this->getAnim().getPos().y, this->getAnim().getPos().z);
	glRotated(90, -1, 0, 0);
	glScaled(0.15, 0.15, 0.15);
	glColor3f(col.r, col.g, col.b);

	gluQuadricDrawStyle(params, GLU_LINE);

	gluCylinder(params, this->rayBottom, this->rayTop, this->height, 20, 1);
	//gluCylinder(GLUquadric* params,base,top,height,slices,stacks);
	gluDeleteQuadric(params);
}


///////////////////////////////////
///////////		LIQUIDE	///////////
///////////////////////////////////
Liquide::Liquide(double hei, double rayB, double rayT, Color co)
{
	height = hei;
	rayBottom = rayB;
	rayTop = rayT;
	col = RED;
	drawStyle = drawStyle;
	col = co;
}


void Liquide::update(double delta_t)
{
	// Complete this part
}


void Liquide::render()
{
	/*
	GLUquadric *quad;

	quad = gluNewQuadric();

	// Complete this part

	gluDeleteQuadric(quad);*/
	//////////////

	//glBindTexture(GL_TEXTURE_2D, texture1);


	
	// create cilynder
	GLUquadric* params;
	params = gluNewQuadric();

	// set possition 
	glTranslated(this->getAnim().getPos().x, this->getAnim().getPos().y, this->getAnim().getPos().z);
	glRotated(90, -1, 0, 0);
	glScaled(0.15, 0.15, 0.15);
	glColor3f(col.r, col.g, col.b);

	gluQuadricDrawStyle(params, GLU_FILL);
	//gluQuadricTexture(params, GL_TRUE);

	gluCylinder(params, this->rayBottom, this->rayTop, this->height, 20, 1);
	//gluCylinder(GLUquadric* params,base,top,height,slices,stacks);
	gluDeleteQuadric(params);



		//glBindTexture(GL_TEXTURE_2D, texture1);

	/*
	GLUquadric* params = gluNewQuadric();

	gluQuadricDrawStyle(params, GLU_LINE);
	gluCylinder(params, 1, 1, 2, 20, 1);

	gluQuadricDrawStyle(params, GLU_FILL);
	gluQuadricTexture(params, GL_TRUE);
	glTranslated(0, 0, 1);
	gluSphere(params, 0.75, 20, 20);

	gluDeleteQuadric(params);
	*/
}

///////////////////////////////////
///////////		CUBE	///////////
///////////////////////////////////
Cube_face::Cube_face(Vector v1, Vector v2, Point org, double l, double w, Color cl)
{
    vdir1 = 1.0 / v1.norm() * v1;
    vdir2 = 1.0 / v2.norm() * v2;
    anim.setPos(org);
    length = l;
    width = w;
    col = cl;
}


void Cube_face::update(double delta_t)
{
    // Do nothing, no physics associated to a Cube_face
}


void Cube_face::render()
{
    Point p1 = Point();
    Point p2 = p1, p3, p4 = p1;
    p2.translate(length*vdir1);
    p3 = p2;
    p3.translate(width*vdir2);
    p4.translate(width*vdir2);
	//glScaled(0.15, 0.15, 0.15);
	glColor3f(col.r, col.g, col.b);

    Form::render();
	
	// Dessin une seul couleur
	glBegin(GL_QUADS);
	{
		glColor3f(0, 0, 1);
		glVertex3d(p1.x, p1.y, p1.z);
		glColor3f(0, 0, 1);
		glVertex3d(p2.x, p2.y, p2.z);
		glColor3f(0, 0, 1);
		glVertex3d(p3.x, p3.y, p3.z);
		glColor3f(0, 0, 1);
		glVertex3d(p4.x, p4.y, p4.z);
	}
	glEnd();

}


///////////////////////////////////////////
///////////		PARALLELEPIPEDE	///////////
///////////////////////////////////////////
Parallelepipede::Parallelepipede(double len, double wid, double hei, Color co)
{
	length = len;
	width = wid;
	height = hei;
	col = co;
}

void Parallelepipede::update(double delta_t)
{
	// Do nothing, no physics associated toa table
	glColor3f(col.r, col.g, col.b);
}


void Parallelepipede::render()
{
	glScaled(0.15, 0.15, 0.15);

	glEnable(GL_DEPTH_TEST);

	Point p = anim.getPos();


	glBegin(GL_QUADS);
	
	glColor3f(col.r, col.g, col.b); //face fond droit
	glVertex3d(p.x, p.y, p.z);
	glColor3f(col.r, col.g, col.b);
	glVertex3d(p.x + length, p.y, p.z);
	glColor3f(col.r, col.g, col.b);
	glVertex3d(p.x + length, p.y + height, p.z);
	glColor3f(col.r, col.g, col.b);
	glVertex3d(p.x, p.y + height, p.z);

	glColor3f(col.r, col.g, col.b); //face  fond gauche
	glVertex3d(p.x, p.y, p.z);
	glColor3f(col.r, col.g, col.b);
	glVertex3d(p.x, p.y, p.z + width);
	glColor3f(col.r, col.g, col.b);
	glVertex3d(p.x, p.y + height, p.z + width);
	glColor3f(col.r, col.g, col.b);
	glVertex3d(p.x, p.y + height, p.z);

	glColor3f(col.r, col.g, col.b); //face du bas
	glVertex3d(p.x, p.y, p.z);
	glColor3f(col.r, col.g, col.b);
	glVertex3d(p.x, p.y, p.z + width);
	glColor3f(col.r, col.g, col.b);
	glVertex3d(p.x + length, p.y, p.z + width);
	glColor3f(col.r, col.g, col.b);
	glVertex3d(p.x + length, p.y, p.z);


	glColor3f(col.r, col.g, col.b); //face avant droit
	glVertex3d(p.x + length, p.y, p.z);
	glColor3f(col.r, col.g, col.b);
	glVertex3d(p.x + length, p.y + height, p.z);
	glColor3f(col.r, col.g, col.b);
	glVertex3d(p.x + length, p.y + height, p.z + width);
	glColor3f(col.r, col.g, col.b);
	glVertex3d(p.x + length, p.y, p.z + width);

	glColor3f(col.r, col.g, col.b); //face avant gauche
	glVertex3d(p.x, p.y, p.z + width);
	glColor3f(col.r, col.g, col.b);
	glVertex3d(p.x, p.y + height, p.z + width);
	glColor3f(col.r, col.g, col.b);
	glVertex3d(p.x + length, p.y + height, p.z + width);
	glColor3f(col.r, col.g, col.b);
	glVertex3d(p.x + length, p.y, p.z + width);
	
	glColor3f(col.r, col.g, col.b); //face du haut
	glVertex3d(p.x, p.y + height, p.z);
	glColor3f(col.r, col.g, col.b);
	glVertex3d(p.x, p.y + height, p.z + width);
	glColor3f(col.r, col.g, col.b);
	glVertex3d(p.x + length, p.y + height, p.z + width);
	glColor3f(col.r, col.g, col.b);
	glVertex3d(p.x + length, p.y + height, p.z);
	
	glEnd();


	// contours
	// face haut

	glLineWidth(0.5);
	glColor3f(0.0, 0.0, 0.0);

	glBegin(GL_LINES);

	glVertex3d(p.x, p.y + height, p.z);
	glVertex3d(p.x, p.y + height, p.z + width);

	glVertex3d(p.x, p.y + height, p.z + width);
	glVertex3d(p.x + length, p.y + height, p.z + width);
	

	glVertex3d(p.x + length, p.y + height, p.z + width);
	glVertex3d(p.x + length, p.y + height, p.z);

	glVertex3d(p.x + length, p.y + height, p.z);
	glVertex3d(p.x, p.y + height, p.z);

	glVertex3d(p.x, p.y, p.z);
	glVertex3d(p.x, p.y + height, p.z);

	glVertex3d(p.x, p.y, p.z + width);
	glVertex3d(p.x, p.y + height, p.z + width);

	glVertex3d(p.x + length, p.y, p.z + width);
	glVertex3d(p.x + length, p.y + height, p.z + width);

	glVertex3d(p.x + length, p.y, p.z);
	glVertex3d(p.x + length, p.y + height, p.z);

	glVertex3d(p.x, p.y, p.z);
	glVertex3d(p.x, p.y, p.z + width);

	glVertex3d(p.x, p.y, p.z + width);
	glVertex3d(p.x + length, p.y, p.z + width);
	
	glVertex3d(p.x + length, p.y, p.z + width);
	glVertex3d(p.x + length, p.y, p.z);
	
	glVertex3d(p.x + length, p.y, p.z);
	glVertex3d(p.x, p.y, p.z);


	glEnd();


	



	
}
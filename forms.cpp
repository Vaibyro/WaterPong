#include <cmath>
#include <gl\glew.h>
#include <SDL_opengl.h>
//#include <gl\glu.h> // Deja inclus dans glew.h

#include <SDL.h>
#include "forms.h"
#include "Project_App3/physics.h"

using namespace std;


void Form::update(double delta_t)
{
    // Nothing to do here, animation update is done in child class method
}


void Form::render()
{
    // Point of view for rendering
    // Common for all Forms
    Vector3 org = anim->getPosition();
    glTranslated(org.x, org.y, org.z);
    glColor3f(col.r, col.g, col.b);

	Vector3 scale = anim->getScale();
	glScaled(scale.x, scale.y, scale.z);
}


Sphere::Sphere(double r, Color cl)
{
    radius = r;
    col = cl;
}


void Sphere::update(double delta_t)
{
	
}


void Sphere::render()
{
    GLUquadric *quad;
    quad = gluNewQuadric();
	Form::render();
	gluSphere(quad, radius, 30, 20);
    gluDeleteQuadric(quad);
}


Cube_face::Cube_face(Vector3 v1, Vector3 v2, Vector3 org, double l, double w, Color cl)
{
    vdir1 = 1.0 / v1.norm() * v1;
    vdir2 = 1.0 / v2.norm() * v2;
    anim->setPosition(org);
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

    Form::render();
    glBegin(GL_QUADS);
    {
        glColor3f(1,1,0);
        glVertex3d(p1.x, p1.y, p1.z);
        glColor3f(0,1,1);
        glVertex3d(p2.x, p2.y, p2.z);
        glColor3f(1,0,1);
        glVertex3d(p3.x, p3.y, p3.z);
        glColor3f(0,1,0);
        glVertex3d(p4.x, p4.y, p4.z);
    }
    glEnd();
}

void Axis::update(double delta_t)
{
	// Do nothing, no physics associated to a Cube_face
}

Axis::Axis()
{
	arrowY = make_shared<Arrow>(Vector3(0, 1, 0), GREEN);
	arrowX = make_shared<Arrow>(Vector3(1, 0, 0), RED);
	arrowZ = make_shared<Arrow>(Vector3(0, 0, 1), BLUE);
}

void Axis::render()
{
	arrowY->setAnim(anim);
	arrowY->render();
	
	glPopMatrix();
	glPushMatrix();

	arrowX->setAnim(anim);
	arrowX->render();

	glPopMatrix();
	glPushMatrix();

	arrowZ->setAnim(anim);
	arrowZ->render();
}


void Plane::update(double delta_t)
{
	// Do nothing, no physics associated to a Cube_face
}


void Plane::render()
{
	Vector3 org = anim->getPosition();
	glTranslated(org.x - length / 2.0, org.y, org.z - width / 2.0);
	glColor3f(col.r, col.g, col.b);

	Vector3 scale = anim->getScale();
	glScaled(scale.x, scale.y, scale.z);
	
	Point p1(0, 0, 0);
	Point p4(length, 0, 0);
	Point p2(0, 0, width);
	Point p3(length, 0, width);

	glBegin(GL_QUADS);
	{
		glColor3f(1, 1, 0);
		glVertex3d(p1.x, p1.y, p1.z);
		glColor3f(0, 1, 1);
		glVertex3d(p2.x, p2.y, p2.z);
		glColor3f(1, 0, 1);
		glVertex3d(p3.x, p3.y, p3.z);
		glColor3f(0, 1, 0);
		glVertex3d(p4.x, p4.y, p4.z);
	}
	glEnd();
}

Vector3& Plane::getNormal()
{
	Vector3 p1(anim->getPosition().x - length / 2.0, anim->getPosition().y, anim->getPosition().z - width / 2.0);
	Vector3 p3(anim->getPosition().x + length / 2.0, anim->getPosition().y, anim->getPosition().z - width / 2.0);
	Vector3 p2(anim->getPosition().x - length / 2.0, anim->getPosition().y, anim->getPosition().z + width / 2.0);
	Vector3 dir = (p2 - p1) ^ (p3 - p1);
	return dir;
}



void Arrow::update(double delta_t)
{
	// Do nothing, no physics associated to a Cube_face
}

void Arrow::render()
{
	Form::render();
	Vector3 to = dirFromOrigin;
	Vector3 org = anim->getPosition();


	glTranslated(org.x, org.y, org.z);

	// Draw the line
	glBegin(GL_LINES);
	{
		glVertex3d(0, 0, 0);
		glVertex3d(to.x, to.y, to.z);
	}
	glEnd();

	glTranslated(to.x, to.y, to.z);

	// Get the angle of rotation of the cap
	double L = to.norm();
	if ((to.x != 0.0) || (to.y != 0.0)) {
		glRotated(atan2(to.y, to.x) / RADPERDEG, 0.0, 0.0, 1.0);
		glRotated(atan2(sqrt(to.x * to.x + to.y * to.y), to.z) / RADPERDEG, 0.0, 1.0, 0.0);
	}
	else if (to.z < 0) {
		glRotated(180, 1.0, 0.0, 0.0);
	}

	// Draw the cap
	GLUquadric *quad = gluNewQuadric();
	gluCylinder(quad, 0.05, 0, 0.1, 20, 1);
	gluDeleteQuadric(quad);

	//glTranslated(org.x - to.x, org.y - to.y, org.z - to.z);
}


void Ray::update(double delta_t)
{
	
}

void Ray::render()
{

	Form::render();

	// Draw the line
	glBegin(GL_LINES);
	{
		glVertex3d(pos1.x, pos1.y, pos1.z);
		glVertex3d(pos2.x, pos2.y, pos2.z);
	}
	glEnd();
}
#include <cmath>
#include <gl\glew.h>
#include <SDL_opengl.h>
//#include <gl\glu.h> // Deja inclus dans glew.h

#include <SDL.h>
#include "forms.h"

using namespace std;


void Form::update(double delta_t)
{
    // Nothing to do here, animation update is done in child class method
}


void Form::render()
{
    // Point of view for rendering
    // Common for all Forms
    Vector org = anim->getPosition();
    glTranslated(org.x, org.y, org.z);
    glColor3f(col.r, col.g, col.b);

	Vector scale = anim->getScale();
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


Cube_face::Cube_face(Vector v1, Vector v2, Vector org, double l, double w, Color cl)
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


void Axis::render()
{
	Form::render();

	// Render the coordinates system
	glBegin(GL_LINES);
	{
		glColor3f(1.0f, 0.0f, 0.0f);
		glVertex3i(0, 0, 0);
		glVertex3i(1, 0, 0);
		glColor3f(0.0f, 1.0f, 0.0f);
		glVertex3i(0, 0, 0);
		glVertex3i(0, 1, 0);
		glColor3f(0.0f, 0.0f, 1.0f);
		glVertex3i(0, 0, 0);
		glVertex3i(0, 0, 1);
	}
	glEnd();
}

#ifndef FORMS_H_INCLUDED
#define FORMS_H_INCLUDED

#include "geometry.h"
#include "animation.h"

using namespace std;

class Color
{
public:
	float r, g, b;
	Color(float rr = 1.0f, float gg = 1.0f, float bb = 1.0f) { r = rr; g = gg; b = bb; }
};

// Constant Colors
const Color RED(1.0f, 0.0f, 0.0f);
const Color BLUE(0.0f, 0.0f, 1.0f);
const Color GREEN(0.0f, 1.0f, 0.0f);
const Color YELLOW(1.0f, 1.0f, 0.0f);
const Color WHITE(1.0f, 1.0f, 1.0f);


// Generic class to render and animate an object
class Form
{
protected:
	Color col;
	shared_ptr<Animation> anim;
public:
	shared_ptr<Animation> getAnim() { return anim; }
	void setAnim(shared_ptr<Animation> ani) { anim = ani; }

	void setColor(const Color& color) { col = color; };
	const Color& getColor() { return col; };


	// This method should update the anim object with the corresponding physical model
	// It has to be done in each inherited class, otherwise all forms will have the same movements !
	// Virtual method for dynamic function call
	// Pure virtual to ensure all objects have their physics implemented
	virtual void update(double delta_t) = 0;
	// Virtual method : Form is a generic type, only setting color and reference position
	virtual void render();
};


// A particular Form
class Sphere : public Form
{
private:
	// The sphere center is aligned with the coordinate system origin
	// => no center required here, information is stored in the anim object
	double radius;
public:
	Sphere(double r = 1.0, Color cl = Color());
	const double getRadius() { return radius; }
	void setRadius(double r) { radius = r; }
	void update(double delta_t);
	void render();
};


// A face of a cube
class Cube_face : public Form
{
private:
	Vector3 vdir1, vdir2;
	double length, width;
public:
	Cube_face(Vector3 v1 = Vector3(1, 0, 0), Vector3 v2 = Vector3(0, 0, 1),
		Vector3 org = Vector3(), double l = 1.0, double w = 1.0,
		Color cl = Color());
	void update(double delta_t);
	void render();
};

class Axis : public Form
{
public:
	void update(double delta_t);
	void render();
};



// Class plane
class Plane : public Form
{
private:
	double length, width;
public:
	Plane(double l = 1.0, double w = 1.0) { length = l; width = w; };
	Vector3& getNormal();
	void update(double delta_t);
	void render();
};



class Ray : public Form
{
private:
	Vector3 dirFromOrigin;
public:
	Ray(const Vector3& dir) { dirFromOrigin = dir; };
	Ray(const Vector3& dir, const Color& cl) { dirFromOrigin = dir; col = cl; };
	void update(double delta_t);
	void render();
};

#endif // FORMS_H_INCLUDED

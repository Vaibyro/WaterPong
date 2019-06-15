#ifndef FORMS_H_INCLUDED
#define FORMS_H_INCLUDED

#include "geometry.h"
#include "animation.h"

using namespace std;


class Color
{
public:
    float r, g, b;
    Color(float rr = 1.0f, float gg = 1.0f, float bb = 1.0f) {r=rr; g=gg; b=bb;}
};

// Constant Colors
const Color RED(1.0f, 0.0f, 0.0f);
const Color BLUE(0.0f, 0.0f, 1.0f);
const Color GREEN(0.0f, 1.0f, 0.0f);
const Color YELLOW(1.0f, 1.0f, 0.0f);
const Color WHITE(1.0f, 1.0f, 1.0f);
const Color BLACK(0.0f, 0.0f, 0.0f);


// Generic class to render and animate an object
class Form
{
protected:
    Color col;
    Animation anim;
public:
    Animation& getAnim() {return anim;}
    void setAnim(Animation ani) {anim = ani;}
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
    const double getRadius() {return radius;}
    void setRadius(double r) {radius = r;}
    void update(double delta_t);
    void render();
};


class Verre : public Form
{
private:
	// The sphere center is aligned with the coordinate system origin
	// => no center required here, information is stored in the anim object
	double height;
	double rayBottom;
	double rayTop;
	GLenum drawStyle;
public:
	Verre(double height = 1.0, double rayBottom = 0.5, double rayTop = 1, Color co = Color(1, 0, 0));
	const double getHeight() { return height; }
	const double getRayBottom() { return rayBottom; }
	const double getRayTop() { return rayTop; }

	void update(double delta_t);
	void render();
};


class Liquide : public Form
{
private:
	// The sphere center is aligned with the coordinate system origin
	// => no center required here, information is stored in the anim object
	double height;
	double rayBottom;
	double rayTop;
	GLenum drawStyle;
public:
	Liquide(double height = 1.0, double rayBottom = 0.5, double rayTop = 1, Color co = Color(0, 0, 1));
	const double getHeight() { return height; }
	const double getRayBottom() { return rayBottom; }
	const double getRayTop() { return rayTop; }

	void update(double delta_t);
	void render();
};

// A face of a cube
class Cube_face : public Form
{
private:
    Vector vdir1, vdir2;
    double length, width;
public:
    Cube_face(Vector v1 = Vector(1,0,0), Vector v2 = Vector(0,0,1),
          Point org = Point(), double l = 1.0, double w = 1.0,
          Color cl = Color());
    void update(double delta_t);
    void render();
};




// A parallélépipède
class Parallelepipede : public Form
{
private:
	double length;
	double width;
	double height;

public:
	Parallelepipede(double len, double wid, double hei, Color co);

	
	void update(double delta_t);
	void render();
};





#endif // FORMS_H_INCLUDED

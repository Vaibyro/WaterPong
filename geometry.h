#ifndef GEOMETRY_H_INCLUDED
#define GEOMETRY_H_INCLUDED

#include <iostream>


class Coordinates
{
public:
    double x, y, z;
    Coordinates(double xx=0, double yy=0, double zz=0) {x=xx; y=yy; z=zz;}
};


// Declaration in order to use it within Point methods
class Vector3;

class Point : public Coordinates
{
public:
    // Point constructor calls the base class constructor and do nothing more
    Point(double xx=0, double yy=0, double zz=0) : Coordinates(xx, yy, zz) {}
    void translate(const Vector3 &);
};


class Vector3 : public Coordinates
{
public:
    // Instantiates a Vector from its coordinates
    Vector3(double xx=0, double yy=0, double zz=0) : Coordinates(xx, yy, zz) {}
    // Or with two points
    Vector3(Point, Point);
    // Compute the vector norm
    double norm();
	Vector3 integral(double delta_t);
	Vector3 normalize();
	static Vector3 zero() { return Vector3(0, 0, 0); };
	static Vector3 one() { return Vector3(1.0, 1.0, 1.0); };
	static Vector3 up() { return Vector3(0.0, 1.0, 0.0); };
	static Vector3 down() { return Vector3(0.0, -1.0, 0.0); };
    // Overloaded standard operators
    void operator+=(const Vector3 &v);

	double distance(const Vector3& vec);
};


// Compute the distance between two points
double distance(Point p1, Point p2);

// Overloaded standard operators
std::ostream& operator<<(std::ostream& os, const Coordinates& coord);
Vector3 operator+(const Vector3 &v1, const Vector3 &v2);
Vector3 operator-(const Vector3 &v);
Vector3 operator-(const Vector3 &v1, const Vector3 &v2);
Vector3 operator*(const double &k, const Vector3 &v);
bool operator==(const Vector3 &v1, const Vector3 &v2);
bool operator!=(const Vector3 &v1, const Vector3 &v2);
// Scalar product
double operator*(const Vector3 &v1, const Vector3 &v2);
// Vector product
Vector3 operator^(const Vector3 &v1, const Vector3 &v2);
// Operator to string

class Geometry
{
public:
	static void plane(const Vector3& p1, const Vector3& p2, const Vector3& p3);
};


class Vector4 : public Coordinates
{
public:
	double w;
	// Instantiates a Vector from its coordinates
	Vector4(double xx = 0, double yy = 0, double zz = 0, double ww = 0) : Coordinates(xx, yy, zz) { w = ww; }

	static Vector4 zero() { return Vector4(0, 0, 0, 0); };
	static Vector4 one() { return Vector4(1.0, 1.0, 1.0, 1.0); };
};


#endif // GEOMETRY_H_INCLUDED

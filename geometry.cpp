#include <cmath>
#include "geometry.h"


using namespace std;


void Point::translate(const Vector3 &v)
{
    x += v.x;
    y += v.y;
    z += v.z;
}


Vector3::Vector3(Point p1, Point p2)
{
    x = p2.x - p1.x;
    y = p2.y - p1.y;
    z = p2.z - p1.z;
}


double Vector3::norm()
{
    double norm;

    norm = sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2));

    return norm;
}

Vector3 Vector3::normalize()
{
	double n = norm();
	return Vector3(x / n, y / n, z / n);
}

double Vector3::distance(const Vector3& vec)
{
	return sqrt(pow(vec.x - x, 2) + pow(vec.y - y, 2) + pow(vec.z - z, 2));
}

Vector3 Vector3::integral(double delta_t)
{
    Vector3 res;

    res.x = delta_t * x;
    res.y = delta_t * y;
    res.z = delta_t * z;

    return res;
}


void Vector3::operator+=(const Vector3 &v)
{
    x += v.x;
    y += v.y;
    z += v.z;
}


double distance(Point p1, Point p2)
{
    Vector3 vect(p1, p2);

    return vect.norm();
}


// Overloaded standard operators
std::ostream& operator<<(std::ostream& os, const Coordinates& coord)
{
    os << '(' << coord.x << ", " << coord.y << ", " << coord.z << ')';
    return os;
}

Vector3 operator+(const Vector3 &v1, const Vector3 &v2)
{
    Vector3 res = v1;

    res.x += v2.x;
    res.y += v2.y;
    res.z += v2.z;

    return res;
}

Vector3 operator-(const Vector3 &v)
{
    Vector3 res;

    res.x = -v.x;
    res.y = -v.y;
    res.z = -v.z;

    return res;
}

Vector3 operator-(const Vector3 &v1, const Vector3 &v2)
{
    Vector3 res = -v2;

    res = res + v1;

    return res;
}

Vector3 operator*(const double &k, const Vector3 &v)
{
    Vector3 res = v;

    res.x *= k;
    res.y *= k;
    res.z *= k;

    return res;
}

// Scalar product
double operator*(const Vector3 &v1, const Vector3 &v2)
{
    double res;

    res = v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;

    return res;
}

bool operator==(const Vector3 &v1, const Vector3 &v2)
{
	return v1.x == v2.x && v1.y == v2.y && v1.z == v2.z;
}

bool operator!=(const Vector3 &v1, const Vector3 &v2)
{
	return !(v1 == v2);
}

// Vector product
Vector3 operator^(const Vector3 &v1, const Vector3 &v2)
{
    Vector3 res;

    res.x = v1.y * v2.z - v1.z * v2.y;
    res.y = v1.z * v2.x - v1.x * v2.z;
    res.z = v1.x * v2.y - v1.y * v2.x;

    return res;
}


void Geometry::plane(const Vector3& p1, const Vector3& p2, const Vector3& p3)
{

	Vector3 px1 = p2 - p3;
	Vector3 px2 = p3 - p1;
	double a = (px1.y * px2.z) - (px2.y * px1.z);
	double b = (px2.x * px1.z) - (px1.x * px2.z);
	double c = (px1.x * px2.y) - (px1.y * px2.x);
	double d = (-a * p1.x - b * p1.y - c * p1.z);
	cout << "equation of plane is " << a << " x + " << b
		<< " y + " << c << " z + " << d << " = 0.";
}
#ifndef ANIMATION_H_INCLUDED
#define ANIMATION_H_INCLUDED

#include "geometry.h"


using namespace std;

class Animation
{
private:
	double phi, theta; // Azimuthal and polar angles for local coordinate system orientation
	Vector acc, spd; //  Instantaneous acceleration and speed
	Vector pos; // Instantaneous position of the local coordinate system origin
	Vector scale;
public:
	Animation(double ph = 0.0, double th = 0.0,
		Vector accel = Vector::zero(),
		Vector speed = Vector::zero(),
		Vector p = Vector::zero(),
		Vector s = Vector::one()
	);

	Animation(double x, double y, double z) : Animation() { pos.x = x; pos.y = y; pos.z = z; };
	Animation(const Vector& v) : Animation() { pos = v; };

	// Get or set Phi
	void setPhi(double agl) { phi = agl; }
	const double getPhi() { return phi; }

	// Get or set theta
	void setTheta(double agl) { theta = agl; }
	const double getTheta() { return theta; }

	// Get or set the acceleration
	void setAccel(Vector vect) { acc = vect; }
	const Vector& getAccel() { return acc; }

	// Get or set the speed
	void setSpeed(Vector vect) { spd = vect; }
	void setSpeed(double x, double y, double z) { spd.x = x; spd.y = y; spd.z = z; }
	const Vector& getSpeed() { return spd; }

	// Get or set the position of the object
	void setPosition(const Vector& pt) { pos = pt; }
	void setPosition(double x, double y, double z) { pos.x = x; pos.y = y; pos.z = z; };
	const Vector& getPosition() { return pos; }

	// Get or set the scale
	void setScale(double newscale) { scale = Vector(newscale, newscale, newscale); };
	void setScale(double x, double y, double z) { scale = Vector(x, y, z); };
	void setScale(const Vector& newscale) { scale = newscale; };
	const Vector& getScale() { return scale; };

	// Quick method for translation
	void translate(const Vector& vector);
	void translate(double x, double y, double z);
};

std::ostream& operator<<(std::ostream& os, shared_ptr<Animation>& tr);

#endif // ANIMATION_H_INCLUDED

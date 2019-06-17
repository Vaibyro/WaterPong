#ifndef ANIMATION_H_INCLUDED
#define ANIMATION_H_INCLUDED

#include "geometry.h"


using namespace std;

class Animation
{
private:
	double phi, theta; // Azimuthal and polar angles for local coordinate system orientation
	Vector3 acc, spd; //  Instantaneous acceleration and speed
	Vector3 pos; // Instantaneous position of the local coordinate system origin
	Vector3 scale;
public:
	Animation(double ph = 0.0, double th = 0.0,
		Vector3 accel = Vector3::zero(),
		Vector3 speed = Vector3::zero(),
		Vector3 p = Vector3::zero(),
		Vector3 s = Vector3::one()
	);

	Animation(double x, double y, double z) : Animation() { pos.x = x; pos.y = y; pos.z = z; };
	Animation(const Vector3& v) : Animation() { pos = v; };

	// Get or set Phi
	void setPhi(double agl) { phi = agl; }
	const double getPhi() { return phi; }

	// Get or set theta
	void setTheta(double agl) { theta = agl; }
	const double getTheta() { return theta; }

	// Get or set the acceleration
	void setAccel(Vector3 vect) { acc = vect; }
	const Vector3& getAccel() { return acc; }

	// Get or set the speed
	void setSpeed(Vector3 vect) { spd = vect; }
	void setSpeed(double x, double y, double z) { spd.x = x; spd.y = y; spd.z = z; }
	const Vector3& getSpeed() { return spd; }

	// Get or set the position of the object
	void setPosition(const Vector3& pt) { pos = pt; }
	void setPosition(double x, double y, double z) { pos.x = x; pos.y = y; pos.z = z; };
	const Vector3& getPosition() { return pos; }

	// Get or set the scale
	void setScale(double newscale) { scale = Vector3(newscale, newscale, newscale); };
	void setScale(double x, double y, double z) { scale = Vector3(x, y, z); };
	void setScale(const Vector3& newscale) { scale = newscale; };
	const Vector3& getScale() { return scale; };

	// Quick method for translation
	void translate(const Vector3& vector);
	void translate(double x, double y, double z);
};

std::ostream& operator<<(std::ostream& os, shared_ptr<Animation>& tr);

#endif // ANIMATION_H_INCLUDED

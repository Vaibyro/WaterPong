#include "animation.h"

using namespace std;

Animation::Animation(double ph, double th, Vector accel, Vector speed, Vector p, Vector s)
{
    // Constructor
    // Initialization
    phi = ph;
    theta = th;
    acc = accel;
    spd = speed;
    pos = p;
	scale = s;
}

void Animation::translate(const Vector& vector)
{
	pos += vector;
}

void Animation::translate(double x, double y, double z)
{
	pos += Vector(x, y, z);
}

std::ostream& operator<<(std::ostream& os, shared_ptr<Animation>& tr)
{
	os << "Animation(V=" << tr->getPosition() << ')';
	return os;
}

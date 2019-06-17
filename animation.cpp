#include "animation.h"

using namespace std;

Animation::Animation(double ph, double th, Vector3 accel, Vector3 speed, Vector3 p, Vector3 s)
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

void Animation::translate(const Vector3& vector)
{
	pos += vector;
}

void Animation::translate(double x, double y, double z)
{
	pos += Vector3(x, y, z);
}

std::ostream& operator<<(std::ostream& os, shared_ptr<Animation>& tr)
{
	os << "Animation(V=" << tr->getPosition() << ')';
	return os;
}

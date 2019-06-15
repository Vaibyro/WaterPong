#include "collider.h"


bool SphereCollider::collision(const Vector& point)
{
	return collision(point.x, point.y, point.z);
}

bool SphereCollider::collision(double x, double y, double z)
{
	Vector pos = linkedAnimation->getPosition();
	int d2 = (x - pos.x) * (x - pos.x)
		+ (y - pos.y) * (y - pos.y)
		+ (z - pos.z) * (z - pos.z);
	return d2 < radius * radius;
}
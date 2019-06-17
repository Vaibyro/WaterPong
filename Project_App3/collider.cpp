#include "collider.h"


bool SphereCollider::collision(const Vector3& point)
{
	return collision(point.x, point.y, point.z);
}

bool SphereCollider::collision(double x, double y, double z)
{
	Vector3 pos = linkedAnimation->getPosition();
	int d2 = (x - pos.x) * (x - pos.x)
		+ (y - pos.y) * (y - pos.y)
		+ (z - pos.z) * (z - pos.z);
	return d2 < radius * radius;
}

bool SphereCollider::collision(const shared_ptr<SphereCollider>& collider)
{
	Vector3 pos1 = linkedAnimation->getPosition();
	Vector3 pos2 = collider->linkedAnimation->getPosition();
	int d2 = (pos1.x - pos2.x) * (pos1.x - pos2.x) +
		(pos1.y - pos2.y) * (pos1.y - pos2.y) +
		(pos1.z - pos2.z) * (pos1.z - pos2.z);
	return d2 < (radius + collider->radius) * (radius + collider->radius);
}

bool SphereCollider::collision(const shared_ptr<PlaneCollider>& collider)
{
	Vector3 posOrgPlane = collider->getAnimation()->getPosition();
	Vector3 posOrgSphere = linkedAnimation->getPosition();

	// Distance between center of plane and center of sphere
	double d = posOrgPlane.distance(posOrgSphere);

	// Normal vector of plane
	Vector3 normal = collider->getNormal();

	double fdis = normal * (posOrgSphere - posOrgPlane);

	//fdis = (posOrgSphere - posOrgPlane) * normal;


	//cout << normal << " * (" << posOrgSphere << " - " << posOrgPlane << ") = " << fdis << " !!! " << radius << endl;
	return fdis - radius <= 10e-6;
}

Vector3 PlaneCollider::getNormal()
{
	Vector3 pos = linkedAnimation->getPosition();
	Vector3 p1(pos.x - length / 2.0, pos.y, pos.z - width / 2.0);
	Vector3 p3(pos.x + length / 2.0, pos.y, pos.z - width / 2.0);
	Vector3 p2(pos.x - length / 2.0, pos.y, pos.z + width / 2.0);

	Vector3 dir = (p2 - p1) ^ (p3 - p1);
	double n = dir.norm();
	return Vector3(dir.x / n, dir.y / n, dir.z / n);
}

Vector3 Collider::closestPoint(const Vector3& a, const Vector3& b, const Vector3& point)
{
	return (a - b) ^ (a - point);
}

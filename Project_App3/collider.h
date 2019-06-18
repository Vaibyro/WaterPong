#pragma once
#include "..\forms.h"

using namespace std;

class SphereCollider;
class PlaneCollider;
class BoxCollider;

class Collider // ABSTRACT
{
protected:
	shared_ptr<Animation> linkedAnimation;
	Vector3 relativePosition;
public:
	Collider() { relativePosition = Vector3::zero(); };
	Collider(const shared_ptr<Animation>& anim) : Collider() { linkedAnimation = anim; };

	// Get or set the animation linked
	void setAnimation(const shared_ptr<Animation>& anim) { linkedAnimation = anim; };
	const shared_ptr<Animation>& getAnimation() { return linkedAnimation; };

	// Get or set the relative position
	void setRelativePosition(const Vector3& pos) { relativePosition = pos; };
	const Vector3& getRelativePosition() { return relativePosition; };

	virtual bool collision(const Vector3& point) = 0;
	virtual bool collision(double x, double y, double z) = 0;
	virtual bool collision(const shared_ptr<SphereCollider>& collider) = 0;
	virtual bool collision(const shared_ptr<PlaneCollider>& collider) = 0;
	virtual bool collision(const shared_ptr<BoxCollider>& collider) = 0;

	static Vector3 closestPoint(const Vector3& a, const Vector3& b, const Vector3& point);
};

class SphereCollider : public Collider
{
private:
	double radius;
public:
	SphereCollider(double r, const shared_ptr<Animation>& anim) : Collider(anim) { radius = r; };

	bool collision(const Vector3& point);
	bool collision(double x, double y, double z);
	bool collision(const shared_ptr<SphereCollider>& collider);
	bool collision(const shared_ptr<PlaneCollider>& collider);
	bool collision(const shared_ptr<BoxCollider>& collider);
};

class PlaneCollider : public Collider
{
private:
	double length;
	double width;
public:
	PlaneCollider(double l, double w, const shared_ptr<Animation>& anim) : Collider(anim) { length = l; width = w; };

	Vector3 getNormal();

	bool collision(const Vector3& point) { return true; }; // todo
	bool collision(double x, double y, double z) { return true; }; // todo
	bool collision(const shared_ptr<SphereCollider>& collider) { return true; }; // todo
	bool collision(const shared_ptr<PlaneCollider>& collider) { return true; }; // todo
	bool collision(const shared_ptr<BoxCollider>& collider) { return true; }; // todo
};

class BoxCollider : public Collider
{
private:
	double height;
	double length;
	double width;
public:
	BoxCollider(double h, double l, double w, const shared_ptr<Animation>& anim) : Collider(anim) { height = h; length = l; width = w; };

	double getHeight() { return height; };
	double getLength() { return length; };
	double getWidth() { return width; };


	bool collision(const Vector3& point) { return true; }; // todo
	bool collision(double x, double y, double z) { return true; }; // todo
	bool collision(const shared_ptr<SphereCollider>& collider) { return true; }; // todo
	bool collision(const shared_ptr<PlaneCollider>& collider) { return true; }; // todo
	bool collision(const shared_ptr<BoxCollider>& collider) { return true; }; // todo
};
#pragma once
#include "..\forms.h"

using namespace std;

class Collider
{
protected:
	shared_ptr<Animation> linkedAnimation;
	Vector relativePosition;
public:
	Collider() { relativePosition = Vector::zero(); };
	Collider(const shared_ptr<Animation>& anim) : Collider() { linkedAnimation = anim; };

	// Get or set the animation linked
	void setAnimation(const shared_ptr<Animation>& anim) { linkedAnimation = anim; };
	const shared_ptr<Animation>& getAnimation() { return linkedAnimation; };

	// Get or set the relative position
	void setRelativePosition(const Vector& pos) { relativePosition = pos; };
	const Vector& getRelativePosition() { return relativePosition; };

	virtual bool collision(const Vector& point) = 0;
	virtual bool collision(double x, double y, double z) = 0;
};

class SphereCollider : public Collider
{
private:
	double radius;
public:
	SphereCollider(double r, const shared_ptr<Animation>& anim) : Collider(anim) { radius = r; };

	bool collision(const Vector& point);
	bool collision(double x, double y, double z);
	//bool collision(const SphereCollider& collider);
};

class BoxCollider : public Collider
{

};
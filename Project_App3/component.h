#pragma once

#include <vector>
#include "..\forms.h"
#include "collider.h"

using namespace std;

class Transform;

class Component : public enable_shared_from_this<Component>
{
private:
	vector<shared_ptr<Collider>> colliders;
	shared_ptr<Form> form;
	shared_ptr<Animation> animation;
	bool applyPhysics;
	double mass;
public:
	Component() { mass = 1.0; applyPhysics = true; };
	Component(shared_ptr<Form> const& shape);
	Component(shared_ptr<Form> const& shape, double x, double y, double z);
	Component(shared_ptr<Form> const& shape, const Vector& position);

	// Get or set the mass of the object for physics (default = 1)
	void setMass(double newmass) { mass = newmass; };
	double getMass() { return mass; };

	// Bool physics applied on this object
	void setApplyPhysics(bool value) { applyPhysics = value; };
	bool getApplyPhysics() { return applyPhysics; }

	// Get or set the animation
	void setAnimation(shared_ptr<Animation> anim) { animation = anim; };
	shared_ptr<Animation> getAnimation() { return animation; };

	shared_ptr<vector<shared_ptr<Collider>>> getColliders() { return make_shared<vector<shared_ptr<Collider>>>(colliders); };
	void addCollider(const shared_ptr<Collider>& collider) { colliders.push_back(collider); };

	// Get or set the form
	void setForm(shared_ptr<Form> shape) { form = shape; };
	shared_ptr<Form> getForm() { return form; };

	// Modifiers methods
	void update(double delta_t);
	//void fixedUpdate();

	// Factories
	static shared_ptr<Component> create(const shared_ptr<Form>& form, const Vector& pos);

	// Quick methods
	void addSphereCollider(double r, const Vector& pos);
};
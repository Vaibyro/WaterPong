#include <cmath>
#include <gl\glew.h>
#include <SDL_opengl.h>
#include "component.h"
#include "collider.h"

Component::Component(const shared_ptr<Form>& shape) : Component()
{
	form = shape; 
	animation = make_shared<Animation>();
}

Component::Component(const shared_ptr<Form>& shape, double x, double y, double z) {
	form = shape;
	animation = make_shared<Animation>(x, y, z);
}

Component::Component(const shared_ptr<Form>& shape, const Vector& vect) {
	form = shape;
	animation = make_shared<Animation>(vect);
}

void Component::update(double delta_t)
{
	form->setAnim(animation);
	form->update(delta_t);

	form->setColor(BLUE);

	// Colliders
	for (auto& collider : colliders)
	{
		bool coll = collider->collision(0, 0, 1);
		cout << "Position=" << animation->getPosition() << endl;
		if (coll) {
			form->setColor(RED);
			cout << "Collision detected" << endl;
		}
	}
}

shared_ptr<Component> Component::create(const shared_ptr<Form>& form, const Vector& pos)
{
	return make_shared<Component>(form, pos);
}

void Component::addSphereCollider(double r, const Vector& pos)
{
	shared_ptr<Collider> ptr = make_shared<SphereCollider>(r, animation);
	colliders.push_back(ptr);
}
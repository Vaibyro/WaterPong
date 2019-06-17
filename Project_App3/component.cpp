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

Component::Component(const shared_ptr<Form>& shape, const Vector3& vect) {
	form = shape;
	animation = make_shared<Animation>(vect);
}

void Component::update(double delta_t)
{
	form->setAnim(animation);
	form->update(delta_t);
}

shared_ptr<Component> Component::create(const shared_ptr<Form>& form, const Vector3& pos)
{
	return make_shared<Component>(form, pos);
}

shared_ptr<SphereCollider> Component::addSphereCollider(double r, const Vector3& pos)
{
	auto ptr = make_shared<SphereCollider>(r, animation);
	//todo do relative pos
	colliders.push_back(ptr);
	return ptr;
}

shared_ptr<PlaneCollider> Component::addPlaneCollider(double l, double w, const Vector3& pos)
{
	auto ptr = make_shared<PlaneCollider>(l, w, animation);
	colliders.push_back(ptr);
	return ptr;
}
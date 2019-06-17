#include "scene.h"

Scene::Scene() 
{

}

void Scene::update(double delta_t)
{
	// Nothing to do here, animation update is done in child class method
}

void Scene::fixedUpdate()
{
	// Nothing to do here, animation update is done in child class method
}

void Scene::setup()
{
	// Nothing to do here, animation update is done in child class method
}

shared_ptr<Component> Scene::createComponent(const shared_ptr<Form>& form, const Vector3& pos)
{
	auto component = make_shared<Component>(form, pos);
	components.push_back(component);
	return component;
}

shared_ptr<Component> Scene::createComponent(const shared_ptr<Form>& form)
{
	return createComponent(form, Vector3(0, 0, 0));
}
#include <algorithm>
#include "scene.h"

Scene::Scene() 
{

}

void Scene::update(double delta_t)
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

void Scene::removeComponent(const shared_ptr<Component>& pointerToComponent)
{
	auto iter = std::find_if(components.begin(), components.end(),
		[pointerToComponent](const shared_ptr<Component> m) { return (m == pointerToComponent); });
	if (iter != components.end())
	{
		components.erase(iter);
	}
}
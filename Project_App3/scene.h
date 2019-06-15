 #pragma once

#include <iostream>
#include <vector>
#include "component.h"

class Scene
{
public:

	int screenx;
	int screeny;
	int mouseposx;
	int mouseposy;

	Scene();
	virtual void setup();
	virtual void fixedUpdate();
	virtual void update(double delta_t);

	const vector<shared_ptr<Component>>& getComponents() { return components; };

	shared_ptr<Component> createComponent(const shared_ptr<Form>& form, const Vector& pos);

	size_t componentsCount() { return components.size(); };

protected:
	vector<shared_ptr<Component>> components;
};
 #pragma once

#include <iostream>
#include <vector>
#include "component.h"
#include "matrix.h"

class Mouse
{
public:
	int posX;
	int posY;
	bool rightButtonPressed;
	bool leftButtonPressed;
	bool rightButtonReleased;
	bool leftButtonReleased;

	Mouse() { posX = 0; posY = 0; rightButtonPressed = false; leftButtonPressed = false; rightButtonReleased = false; leftButtonReleased = false; };
	Mouse(int x, int y) : Mouse() { posX = x; posY = y; };
};

class Screen
{
public:
	int width;
	int height;
};

class Camera
{
public:
	Matrix4 viewMatrix;
	Matrix4 projectionMatrix;
	Vector3 raycastStart;
	Vector3 raycastEnd;
};

class Scene
{
public:
	Mouse mouse;
	Screen screen;
	Camera camera;

	Scene();
	virtual void setup();
	virtual void fixedUpdate();
	virtual void update(double delta_t);

	const vector<shared_ptr<Component>>& getComponents() { return components; };

	shared_ptr<Component> createComponent(const shared_ptr<Form>& form, const Vector3& pos);

	size_t componentsCount() { return components.size(); };



protected:
	vector<shared_ptr<Component>> components;
};
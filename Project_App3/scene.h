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
	bool middleButtonPressed;
	bool rightButtonReleased;
	bool leftButtonReleased;
	bool middleButtonReleased;
	int wheel;
	int motionX;
	int motionY;

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
	Vector3 position;
	Vector3 lookAt;
	double rho;
	double phi;
	double theta;
};

class Scene
{
public:
	Mouse mouse;
	Screen screen;
	Camera camera;

	Scene();
	virtual void setup();
	virtual void update(double delta_t);

	const vector<shared_ptr<Component>>& getComponents() { return components; };

	shared_ptr<Component> createComponent(const shared_ptr<Form>& form, const Vector3& pos);
	shared_ptr<Component> createComponent(const shared_ptr<Form>& form);

	size_t componentsCount() { return components.size(); };



protected:
	vector<shared_ptr<Component>> components;
};
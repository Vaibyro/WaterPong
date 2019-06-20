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
	Vector3 target;
	Vector3 position;
	double rho;
	double phi;
	double theta;
};


class Keyboard
{
public:
	bool oneNumericButtonPressed;
	bool twoNumericButtonPressed;
	bool threeNumericButtonPressed;
	bool fourNumericButtonPressed;
	bool fiveNumericButtonPressed;
	bool sixNumericButtonPressed;
	bool cameraBalleView;
	bool wind;
};


class Scene
{
public:
	Mouse mouse;
	Screen screen;
	Camera camera;
	Keyboard keyboard;

	Scene();
	virtual void setup();
	virtual void update(double delta_t);

	const vector<shared_ptr<Component>>& getComponents() { return components; };

	shared_ptr<Component> createComponent(const shared_ptr<Form>& form, const Vector3& pos);
	shared_ptr<Component> createComponent(const shared_ptr<Form>& form);

	void removeComponent(const shared_ptr<Component>& pointerToComponent);

	size_t componentsCount() { return components.size(); };



protected:
	vector<shared_ptr<Component>> components;
};
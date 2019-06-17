#pragma once

#include "scene.h"

class MainScene : public Scene
{
public:
	void setup();
	void fixedUpdate();
	void update(double delta_t);
private:
	shared_ptr<Component> balleSouris;
	shared_ptr<PlaneCollider> coll;
	shared_ptr<Component> ray;
	shared_ptr<Component> rayThrow;
	//shared_ptr<Component> point;
	shared_ptr<Component> balleTest;
	double radius;
	double rB;

	double d;

	bool lastCollision;
	bool mousePressedLastState;

	int previous_time;
	int current_time;

	Vector3 mouseDeparture;
	Vector3 mouseArrival;
};
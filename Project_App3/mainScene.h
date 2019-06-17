#pragma once

#include "scene.h"

class MainScene : public Scene
{
public:
	void setup();
	void fixedUpdate();
	void update(double delta_t);
private:
	shared_ptr<Component> toto;
	shared_ptr<PlaneCollider> coll;
	shared_ptr<Component> axisU;
	shared_ptr<Component> point;
};
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
};
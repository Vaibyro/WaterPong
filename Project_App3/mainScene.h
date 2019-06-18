#pragma once

#include "scene.h"

class MainScene : public Scene
{
public:
	void setup();
	void update(double delta_t);
	void physiqueBalle(double delta_t);
	void gestionCamera();
private:

	// ===================================================================================================
	// FORMS
	// ---------------------------------------------------------------------------------------------------
	// Objets de l'action
	shared_ptr<Component> balleSouris;
	shared_ptr<PlaneCollider> collPlane;
	shared_ptr<BoxCollider> collTable;
	shared_ptr<Component> ray;
	shared_ptr<Component> rayThrow;
	//shared_ptr<Component> point;
	shared_ptr<Component> balle;

	// Decor
	shared_ptr<Component> table;
	shared_ptr<Component> verre1;
	shared_ptr<Component> verre2;
	shared_ptr<Component> verre3;
	shared_ptr<Component> verre4;
	shared_ptr<Component> verre5;
	shared_ptr<Component> verre6;
	shared_ptr<Component> verre7;
	shared_ptr<Component> verre8;
	shared_ptr<Component> verre9;
	shared_ptr<Component> verre10;
	shared_ptr<Component> personnage1;
	shared_ptr<Component> personnage2;
	// ---------------------------------------------------------------------------------------------------

	double radius;
	double rB;

	double d;

	double radSphere = 0.03;
	double niveauSol = -10.0 * 0.15;
	bool lastCollision;
	bool mousePressedLastState;

	// ===================================================================================================
	// CAMERA
	// ---------------------------------------------------------------------------------------------------
	bool previousMouseMiddleButtonDownState;
	double middleClickX;
	double middleClickY;
	double oldMouseMiddleFactorX;
	double oldMouseMiddleFactorY;

	bool previousMouseRightButtonDownState;
	double rightClickX;
	double rightClickY;
	double oldMouseRightFactorX;
	double oldMouseRightFactorY;

	double camTranslationSpeed;
	// ---------------------------------------------------------------------------------------------------


	int previous_time;
	int current_time;

	Vector3 mouseDeparture;
	Vector3 mouseArrival;

	
};

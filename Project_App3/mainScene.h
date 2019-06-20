#pragma once

#include "scene.h"

class MainScene : public Scene
{
public:
	void setup();
	void update(double delta_t);
	void physiqueBalle(double delta_t);
	void gestionCamera();
	void genererVent();

	void successThrowNoBounce(double delta_t);
	void successThrowBounce(double delta_t);
	void failThrow(double delta_t);
	void tableThrow(double delta_t);
	void hardThrow(double delta_t);
	void inhumanThrow(double delta_t);


private:

	// ===================================================================================================
	// FORMS
	// ---------------------------------------------------------------------------------------------------
	// Objets de l'action
	shared_ptr<PlaneCollider> collPlane;
	shared_ptr<BoxCollider> collTable;
	vector<shared_ptr<BoxCollider>> collVerres;
	vector<shared_ptr<BoxCollider>> collVerresFonds;
	vector<Vector3> lastPointCollisionsVerres;
	vector<bool> lastCollisionVerres;

	// Colliders personnages
	shared_ptr<BoxCollider> collPersonnage1;
	shared_ptr<BoxCollider> collPersonnage2;

	shared_ptr<Component> ray;
	shared_ptr<Component> rayThrow;
	shared_ptr<Component> balle;

	// Decor
	shared_ptr<Component> table;
	vector<shared_ptr<Component>> verres;

	shared_ptr<Component> personnage1;
	shared_ptr<Component> personnage2;
	shared_ptr<Component> mancheAAir;
	shared_ptr<MancheAAir> mancheAAirForm;

	// ---------------------------------------------------------------------------------------------------

	double rayonBalle = 0.02;
	double niveauSol = -0.7;
	double niveauTable = 0.0;
	bool lastCollisionSol;
	bool lastCollisionTable;
	
	bool mousePressedLastState;

	double masse;

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

	Vector3 lastPointCollisionTable;
	
	// vent
	Vector3 vent;
};

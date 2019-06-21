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

	void simulationThrow(double delta_t, Vector3 position, Vector3 speed);

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

	bool displayWindVector;

	// ---------------------------------------------------------------------------------------------------

	double rayonBalle = 0.02;
	double niveauSol = -0.7;
	double niveauTable = 0.0;
	bool lastCollisionSol;
	bool lastCollisionTable;
	bool lastCollisionPerso1;
	bool lastCollisionPerso2;
	
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
	Vector3 lastPointCollisionPerso1;
	Vector3 lastPointCollisionPerso2;
	
	// vent
	Vector3 vent;
};

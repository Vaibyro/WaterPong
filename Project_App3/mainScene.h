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
	int generateRandom();

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
	shared_ptr<Component> balleSouris;
	shared_ptr<PlaneCollider> collPlane;
	shared_ptr<BoxCollider> collTable;
	shared_ptr<BoxCollider> collVerre1;
	shared_ptr<BoxCollider> collVerre1_fond;

	vector<shared_ptr<BoxCollider>> collVerres;
	vector<shared_ptr<BoxCollider>> collVerresFonds;
	vector<Vector3> lastPointCollisionsVerres;
	vector<bool> lastCollisionVerres;

	Vector3 lastPointCollisionVerre1; // a virer
	bool lastCollisionVerre1;



	shared_ptr<BoxCollider> collVerre2;
	shared_ptr<BoxCollider> collVerre3;
	shared_ptr<BoxCollider> collVerre4;
	shared_ptr<BoxCollider> collVerre5;
	shared_ptr<BoxCollider> collVerre6;
	shared_ptr<BoxCollider> collVerre7;
	shared_ptr<BoxCollider> collVerre8;
	shared_ptr<BoxCollider> collVerre9;
	shared_ptr<BoxCollider> collVerre10;
	shared_ptr<BoxCollider> collPersonnage1;
	shared_ptr<BoxCollider> collPersonnage2;
	shared_ptr<Component> ray;
	shared_ptr<Component> rayThrow;
	//shared_ptr<Component> point;
	shared_ptr<Component> balle;

	// Decor
	shared_ptr<Component> table;

	vector<shared_ptr<Component>> verres;

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
	shared_ptr<Component> mancheAAir;
	shared_ptr<MancheAAir> mancheAAirForm;

	// ---------------------------------------------------------------------------------------------------

	double radius;
	double rB;

	double d;

	double radSphere = 0.02;
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

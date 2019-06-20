#include <cmath>
#include <windows.h>
#include "mainScene.h"
#include "component.h"
#include "..\forms.h"
#include "..\geometry.h"
#include "physics.h"
#include <gl\glew.h>
#include <SDL_opengl.h>
//#include <gl\glu.h> // Deja inclus dans glew.h

#include <SDL.h>
/*
 * Une fois au debut de la creation de la scene.
 */
void MainScene::setup()
{

	// Initialize cam
	camera.target = Vector3(0, 0, 0);
	camera.phi = 90.0;
	camera.theta = 45.0;
	camera.rho = 4.0;

	// For debugging
	auto axis = createComponent(shared_ptr<Form>(new Axis()), Vector3(0, 0, 0));


	auto skyBox = createComponent(shared_ptr<Form>(new Sphere(50, SKY)), Vector3(0, 0, 0));


	// ============= Balle
	radius = 0.5;
	balleSouris = createComponent(shared_ptr<Form>(new Sphere(radius, RED)), Vector3(1, 10, 0));
	balleSouris->addSphereCollider(radius, Vector3(0, 0, 0));

	auto planeform = shared_ptr<Plane>(new Plane(15.0, 15.0, GRASS));
	auto plane = createComponent(planeform, Vector3(0, niveauSol, 0));
	collPlane = plane->addPlaneCollider(3.0, 3.0, Vector3(0, 0, 0));

	ray = createComponent(shared_ptr<Form>(new Arrow(Vector3(0, 0, 0), RED)));
	rayThrow = createComponent(shared_ptr<Form>(new Ray(Vector3(0, 0, 0), Vector3(0, 0, 0), RED)));

	balle = createComponent(shared_ptr<Form>(new Sphere(radSphere, WHITE)), Vector3(0, 3, 0));
	balle->addSphereCollider(radSphere, Vector3(0, 0, 0));
	balle->getAnimation()->setSpeed(-2, 0, -1);

	d = 5.0;

	// ============= Décor

	// Table
	table = createComponent(shared_ptr<Form>(new Table(0.7, 0.1, 2.4, 0.6, 0.1)), Vector3(-2.4, -0.7, -0.3));
	// Table(double heiTotal, double heiTray, double len, double wi, double wiFoot)
	collTable = table->addBoxCollider(0.7, 2.4, 0.6, Vector3(0, 0, 0));

	
	// Verres
	double heightGlass = 0.2;
	double rayBottomGlass = 0.03;
	double rayTopGlass = 0.05;
	double decalageTable = 0.1;
	// Verre(double hei, double rayB, double rayT, Color coGob, Color coLiq)

	double hauteurFondVerre = 0.1;

	verre1 = createComponent(shared_ptr<Form>(new Verre(heightGlass, rayBottomGlass, rayTopGlass, RED, BLUE)), Vector3(-2.4 + decalageTable, -0.05, -0.3 + decalageTable + rayTopGlass));
	collVerre1 = verre1->addBoxCollider(0.2, 0.1, 0.1, Vector3(0, 0, 0));
	collVerre1_fond = verre1->addBoxCollider(hauteurFondVerre, 0.05, 0.05, Vector3(0, 0, 0));
	verres.push_back(verre1);
	lastCollisionVerres.push_back(false);
	collVerres.push_back(collVerre1);
	collVerresFonds.push_back(collVerre1_fond);
	lastPointCollisionsVerres.push_back(Vector3(0, 0, 0));

	verre2 = createComponent(shared_ptr<Form>(new Verre(heightGlass, rayBottomGlass, rayTopGlass, RED, BLUE)), Vector3(-2.4 + decalageTable, -0.05, -0.2 + decalageTable + rayTopGlass));
	collVerre2 = verre2->addBoxCollider(0.2, 0.1, 0.1, Vector3(0, 0, 0));
	auto collVerre2_fond = verre2->addBoxCollider(hauteurFondVerre, 0.05, 0.05, Vector3(0, 0, 0));
	verres.push_back(verre2);
	lastCollisionVerres.push_back(false);
	collVerres.push_back(collVerre2);
	collVerresFonds.push_back(collVerre2_fond);
	lastPointCollisionsVerres.push_back(Vector3(0, 0, 0));
	
	verre3 = createComponent(shared_ptr<Form>(new Verre(heightGlass, rayBottomGlass, rayTopGlass, RED, BLUE)), Vector3(-2.4 + decalageTable, -0.05, -0.1 + decalageTable + rayTopGlass));
	collVerre3 = verre3->addBoxCollider(0.2, 0.1, 0.1, Vector3(0, 0, 0));
	auto collVerre3_fond = verre3->addBoxCollider(hauteurFondVerre, 0.05, 0.05, Vector3(0, 0, 0));
	verres.push_back(verre3);
	lastCollisionVerres.push_back(false);
	collVerres.push_back(collVerre3);
	collVerresFonds.push_back(collVerre3_fond);
	lastPointCollisionsVerres.push_back(Vector3(0, 0, 0));

	verre4 = createComponent(shared_ptr<Form>(new Verre(heightGlass, rayBottomGlass, rayTopGlass, RED, BLUE)), Vector3(-2.4 + decalageTable, -0.05, 0 + decalageTable + rayTopGlass));
	collVerre4 = verre4->addBoxCollider(0.2, 0.1, 0.1, Vector3(0, 0, 0));
	auto collVerre4_fond = verre4->addBoxCollider(hauteurFondVerre, 0.05, 0.05, Vector3(0, 0, 0));
	verres.push_back(verre4);
	lastCollisionVerres.push_back(false);
	collVerres.push_back(collVerre4);
	collVerresFonds.push_back(collVerre4_fond);
	lastPointCollisionsVerres.push_back(Vector3(0, 0, 0));

	verre5 = createComponent(shared_ptr<Form>(new Verre(heightGlass, rayBottomGlass, rayTopGlass, RED, BLUE)), Vector3(-2.3 + decalageTable, -0.05, -0.25 + decalageTable + rayTopGlass));
	collVerre5 = verre5->addBoxCollider(0.2, 0.1, 0.1, Vector3(0, 0, 0));
	auto collVerre5_fond = verre5->addBoxCollider(hauteurFondVerre, 0.05, 0.05, Vector3(0, 0, 0));
	verres.push_back(verre5);
	lastCollisionVerres.push_back(false);
	collVerres.push_back(collVerre5);
	collVerresFonds.push_back(collVerre5_fond);
	lastPointCollisionsVerres.push_back(Vector3(0, 0, 0));
	
	verre6 = createComponent(shared_ptr<Form>(new Verre(heightGlass, rayBottomGlass, rayTopGlass, RED, BLUE)), Vector3(-2.3 + decalageTable, -0.05, -0.15 + decalageTable + rayTopGlass));
	collVerre6 = verre6->addBoxCollider(0.2, 0.1, 0.1, Vector3(0, 0, 0));
	auto collVerre6_fond = verre6->addBoxCollider(hauteurFondVerre, 0.05, 0.05, Vector3(0, 0, 0));
	verres.push_back(verre6);
	lastCollisionVerres.push_back(false);
	collVerres.push_back(collVerre6);
	collVerresFonds.push_back(collVerre6_fond);
	lastPointCollisionsVerres.push_back(Vector3(0, 0, 0));

	verre7 = createComponent(shared_ptr<Form>(new Verre(heightGlass, rayBottomGlass, rayTopGlass, RED, BLUE)), Vector3(-2.3 + decalageTable, -0.05, -0.05 + decalageTable + rayTopGlass));
	collVerre7 = verre7->addBoxCollider(0.2, 0.1, 0.1, Vector3(0, 0, 0));
	auto collVerre7_fond = verre7->addBoxCollider(hauteurFondVerre, 0.05, 0.05, Vector3(0, 0, 0));
	verres.push_back(verre7);
	lastCollisionVerres.push_back(false);
	collVerres.push_back(collVerre7);
	collVerresFonds.push_back(collVerre7_fond);
	lastPointCollisionsVerres.push_back(Vector3(0, 0, 0));

	verre8 = createComponent(shared_ptr<Form>(new Verre(heightGlass, rayBottomGlass, rayTopGlass, RED, BLUE)), Vector3(-2.2 + decalageTable, -0.05, -0.2 + decalageTable + rayTopGlass));
	collVerre8 = verre8->addBoxCollider(0.2, 0.1, 0.1, Vector3(0, 0, 0));
	auto collVerre8_fond = verre8->addBoxCollider(hauteurFondVerre, 0.05, 0.05, Vector3(0, 0, 0));
	verres.push_back(verre8);
	lastCollisionVerres.push_back(false);
	collVerres.push_back(collVerre8);
	collVerresFonds.push_back(collVerre8_fond);
	lastPointCollisionsVerres.push_back(Vector3(0, 0, 0));

	verre9 = createComponent(shared_ptr<Form>(new Verre(heightGlass, rayBottomGlass, rayTopGlass, RED, BLUE)), Vector3(-2.2 + decalageTable, -0.05, -0.1 + decalageTable + rayTopGlass));
	collVerre9 = verre9->addBoxCollider(0.2, 0.1, 0.1, Vector3(0, 0, 0));
	auto collVerre9_fond = verre9->addBoxCollider(hauteurFondVerre, 0.05, 0.05, Vector3(0, 0, 0));
	verres.push_back(verre9);
	lastCollisionVerres.push_back(false);
	collVerres.push_back(collVerre9);
	collVerresFonds.push_back(collVerre9_fond);
	lastPointCollisionsVerres.push_back(Vector3(0, 0, 0));

	verre10 = createComponent(shared_ptr<Form>(new Verre(heightGlass, rayBottomGlass, rayTopGlass, RED, BLUE)), Vector3(-2.1 + decalageTable, -0.05, -0.15 + decalageTable + rayTopGlass));
	collVerre10 = verre10->addBoxCollider(0.2, 0.1, 0.1, Vector3(0, 0, 0));
	auto collVerre10_fond = verre10->addBoxCollider(hauteurFondVerre, 0.05, 0.05, Vector3(0, 0, 0));
	verres.push_back(verre10);
	lastCollisionVerres.push_back(false);
	collVerres.push_back(collVerre10);
	collVerresFonds.push_back(collVerre10_fond);
	lastPointCollisionsVerres.push_back(Vector3(0, 0, 0));


	// personnages
	personnage1 = createComponent(shared_ptr<Form>(new Personnage()), Vector3(-3, -0.7, 0.3));
	personnage2 = createComponent(shared_ptr<Form>(new Personnage()), Vector3(-3, -0.7, -0.8));

	lastCollisionSol = false;
	lastCollisionTable = false;

	//lastCollisionVerre1 = false;
	previous_time = 0;
	current_time = 0;

	// Middle click
	oldMouseMiddleFactorX = 0.0;
	oldMouseMiddleFactorY = 0.0;
	middleClickX = 0.0;
	middleClickY = 0.0;

	// Right click
	oldMouseRightFactorX = 0.0;
	oldMouseRightFactorY = 0.0;
	rightClickX = 0.0;
	rightClickY = 0.0;

	camTranslationSpeed = 5.0;

	masse = 0.027;
	vent = Vector3(-1, 0, -1);

	// L'initialisation de la scène est terminé.
	cout << "Main scene setup finished" << endl;
}


void MainScene::physiqueBalle(double delta_t)
{
	// TODO: variables a déplacer !
	double coeff = 0.70;


	Vector3 axisCollisionTable;

	Vector3 axisCollisionVerre1; // a virer
	vector<Vector3> axisCollisionVerres;

	// --------------------------------------------------------------------------------------------------------------------
	// On effectue une vérification des collisions entre la balle et ses colliders.
	// Deux colliders sont à vérifier : le sol pour que la balle ne retombe pas plus bas que ce dernier et
	// la table pour que la balle rebomdisse dessus.
	// TODO: colliders verres.
	bool collisionSol = false;
	bool collisionTable = false;

	// Verres
	//bool collisionVerre1 = false;

	// Tableau des collision des verres
	vector<bool> collisionVerres;
	vector<bool> collisionVerresFonds;
	for (int i = 0; i < lastCollisionVerres.size(); i++) {
		collisionVerres.push_back(false);
		collisionVerresFonds.push_back(false);
		axisCollisionVerres.push_back(Vector3(0, 0, 0));
	}

	//bool collisionVerre1_2 = false; // a virer

	for (auto& collider : balle->getColliders())
	{
		collisionSol = collider->collision(collPlane);
		collisionTable = collider->collision(collTable, axisCollisionTable);

		// Collision verres
		for (int i = 0; i < lastCollisionVerres.size(); i++) {
			collisionVerres[i] = collider->collision(collVerres[i], axisCollisionVerres[i]);
			collisionVerresFonds[i] = collider->collision(collVerresFonds[i], Vector3(0, 0, 0));
		}

		//collisionVerre1 = collider->collision(collVerre1, axisCollisionVerre1); // a virer
		//collisionVerre1_2 = collider->collision(collVerre1_fond, Vector3(0, 0, 0)); //a virer
	}
	// --------------------------------------------------------------------------------------------------------------------

	// On retient le dernier axe de collision entre la balle et la table (X, Y ou Z).
	if ((axisCollisionTable != Vector3::zero())) {
		lastPointCollisionTable = axisCollisionTable;
	}

	for (int i = 0; i < lastCollisionVerres.size(); i++) {
		
		if (axisCollisionVerres[i] != Vector3::zero())
		{
			lastPointCollisionsVerres[i] = axisCollisionVerres[i];
		}
	}
	

	// --------------------------------------------------------------------------------------------------------------------
	// On cherche à calculer maintenant les nouvelles composantes vitesses de la balle à l'instant T présent
	double speed_x = balle->getAnimation()->getSpeed().x;
	double speed_y = balle->getAnimation()->getSpeed().y;
	double speed_z = balle->getAnimation()->getSpeed().z;

	if (!lastCollisionSol && collisionSol) // Si une collision vient d'être detectée avec le sol
	{
		// On applique le coefficient de rebond
		speed_x *= coeff;
		speed_y *= coeff * -1.0; // Cette collision inverse uniquement la composante vitesse Y pour un rebondi vertical.
		speed_z *= coeff;
		lastCollisionSol = true;

		// Sécurité pour pas que la balle parte dans le sol...
		balle->setY(niveauSol + radSphere);
	}
	else if (!lastCollisionTable && collisionTable) // Si une collision vient d'être detectée avec la table (sur n'importe quel côté)
	{
		// On applique le coefficient de rebond
		speed_x *= coeff;
		speed_y *= coeff;
		speed_z *= coeff;

		// Lorsqu'il y a un rebond sur un des côtés de la table, on inverse la composante vitesse adéquate :
		if (abs(lastPointCollisionTable.x) == 1.0) // Rebond sur une face de l'axe X
		{
			speed_x = -speed_x;
		}
		
		if (abs(lastPointCollisionTable.y) == 1.0) // Rebond sur une face de l'axe Y (haut ou bas)
		{
			speed_y = -speed_y;
		}
		
		if (abs(lastPointCollisionTable.z) == 1.0) // Rebond sur une face de l'axe Z
		{
			speed_z = -speed_z;
		}

		lastCollisionTable = true;

		// Sécurité pour pas que la balle ne parte dans la table...
		if (lastPointCollisionTable.y == 1.0)
		{
			balle->setY(niveauTable + radSphere);
		}

		// TODO: vérifier s'il faut d'autres sécurités pour les côtés de la table
	}
	else
	{
		bool noCollision = true;
		for (int i = 0; i < lastCollisionVerres.size(); i++) {
			if (!lastCollisionVerres[i] && collisionVerres[i]) // Si une collision vient d'être detectée avec la table (sur n'importe quel côté)
			{
				
				// On applique le coefficient de rebond
				speed_x *= coeff;
				speed_y *= coeff;
				speed_z *= coeff;

				// Lorsqu'il y a un rebond sur un des côtés de la table, on inverse la composante vitesse adéquate :
				if (abs(lastPointCollisionsVerres[i].x) == 1.0) // Rebond sur une face de l'axe X
				{
					speed_x = -speed_x;
				}

				if (abs(lastPointCollisionsVerres[i].z) == 1.0) // Rebond sur une face de l'axe Z
				{
					speed_z = -speed_z;
				}

				noCollision = false;
				lastCollisionVerres[i] = true;
			}
		}
		

		if (noCollision)
		{
			// Si pas de collisions, on applique la force de gravité.
			//speed_y -= (GRAVITY * delta_t);

			speed_x += + (0.5 * 1.2 * M_PI * (radSphere * radSphere) * 0.7 * (balle->getAnimation()->getSpeed().x * balle->getAnimation()->getSpeed().x) * delta_t) / masse + vent.x * 0.01 / 3.6;
			speed_y += (0.5 * 1.2 * M_PI * (radSphere * radSphere) * 0.7 * (balle->getAnimation()->getSpeed().y * balle->getAnimation()->getSpeed().y) * delta_t) / masse - (GRAVITY * delta_t) + vent.y / 3.6;
			speed_z += (0.5 * 1.2 * M_PI * (radSphere * radSphere) * 0.7 * (balle->getAnimation()->getSpeed().z * balle->getAnimation()->getSpeed().z) * delta_t) / masse + vent.z * 0.01 / 3.6;

			// On indique qu'il n'y a pas eu de collision sur cette frame.
			lastCollisionSol = false;
			lastCollisionTable = false;
			for (int i = 0; i < lastCollisionVerres.size(); i++) {
				lastCollisionVerres[i] = false;
			}
		}
		
	}

	for (int i = 0; i < lastCollisionVerres.size(); i++) {
		if (collisionVerresFonds[i])
		{
			balle->getAnimation()->setSpeed(0, 0, 0);
			Vector3 posVerre = Vector3(verres[i]->getX(), verres[i]->getY() + 0.05, verres[i]->getZ());
			balle->getAnimation()->setPosition(posVerre);
			cout << verres[i]->getAnimation()->getPosition() << endl;

		}
	}

	// On applique la vitesse calculées à l'instant T à la balle.
	balle->getAnimation()->setSpeed(speed_x, speed_y, speed_z);

	// Trois variables qui vont contenir les positions futures de la balle.
	double x, y, z;

	// --------------------------------------------------------------------------------------------------------------------
	// Si le click gauche de la souris est enfoncé, on passe en mode lancer.
	if (mouse.leftButtonPressed) {
		// On arrete la balle car la souris la gere en lui appliquant une vitesse nulle (reset vitesse).
		balle->getAnimation()->setSpeed(0, 0, 0);

		// Coordonnees souris normalisees
		double mousePosNormalX = (2.0 * mouse.posX) / screen.width - 1.0;
		double mousePosNormalY = (2.0 * mouse.posY) / screen.height - 1.0;

		// Position de la balle au centre de la camera
		Vector3 init = camera.position - 2 * (camera.position - camera.target).normalize();

		// On peut bouger la balle avec la souris verticalement
		x = init.x + (0 * sin(camera.theta * RADPERDEG) // Enlever les variables * 0
			+ mousePosNormalY * cos(camera.theta * RADPERDEG)) * 2;
		y = init.y - mousePosNormalY * 0.8;
		z = init.z + (0 * cos(camera.theta * RADPERDEG + M_PI)
			+ mousePosNormalY * sin(camera.theta * RADPERDEG)) * 2;
	}
	else
	{
		// Si le click gauche n'est pas enfoncé, on n'est pas en mode lancer et on laisse la physique se débrouiller pour positionner la balle
		//x = balle->getAnimation()->getPosition().x + balle->getAnimation()->getSpeed().x * delta_t;
		//y = balle->getAnimation()->getPosition().y + balle->getAnimation()->getSpeed().y * delta_t - GRAVITY * (delta_t * delta_t) / 2.0; // Gravité
		//z = balle->getAnimation()->getPosition().z + balle->getAnimation()->getSpeed().z * delta_t;

		double Ftx = (0.5 * 1.2 * M_PI * (radSphere * radSphere) * 0.7 * (balle->getAnimation()->getSpeed().x * balle->getAnimation()->getSpeed().x) * delta_t * delta_t) / 2.0 * masse;
		double Fty = (0.5 * 1.2 * M_PI * (radSphere * radSphere) * 0.7 * (balle->getAnimation()->getSpeed().y * balle->getAnimation()->getSpeed().y) * delta_t * delta_t) / 2.0 * masse;
		double Ftz = (0.5 * 1.2 * M_PI * (radSphere * radSphere) * 0.7 * (balle->getAnimation()->getSpeed().z * balle->getAnimation()->getSpeed().z) * delta_t * delta_t) / 2.0 * masse;

		x = balle->getAnimation()->getPosition().x + balle->getAnimation()->getSpeed().x * delta_t + (Ftx * (delta_t * delta_t)) / 2 * masse;
		y = balle->getAnimation()->getPosition().y + balle->getAnimation()->getSpeed().y * delta_t - GRAVITY * (delta_t * delta_t) / 2.0 + (Fty * (delta_t * delta_t)) / 2 * masse;
		z = balle->getAnimation()->getPosition().z + balle->getAnimation()->getSpeed().z * delta_t + (Ftz * (delta_t * delta_t));

	}

	// Front montant souris : se produit lors du changement d'état du click gauche.
	if (!mousePressedLastState && mouse.leftButtonPressed)
	{
		// On enregistre le point de départ du tir
		mouseDeparture = Vector3(x, y, z);
		mousePressedLastState = true;
	}
	
	// --------------------------------------------------------------------------------------------------------------------
	// Toutes les forces et déplacements ont été calculés : on les applique à la balle.
	balle->getAnimation()->setPosition(x, y, z);
	// --------------------------------------------------------------------------------------------------------------------

	// --------------------------------------------------------------------------------------------------------------------
	// Pour la frame d'après, on calcule le lancer eventuel lorsque le bouton de la souris est relevé.
	if (mouse.leftButtonReleased)
	{
		mousePressedLastState = false;

		// Point d'arrivée du lancer.
		mouseArrival = balle->getAnimation()->getPosition();

		//ray->setForm(shared_ptr<Form>(new Ray(mouseDeparture, mouseArrival)));
		//ray->setForm(shared_ptr<Form>(new Arrow((mouseArrival - mouseDeparture).normalize())));
		
		// On enregistre la vitesse en fonction du lancer
		Vector3 throwingSpeed = (mouseArrival - mouseDeparture);
		balle->getAnimation()->setSpeed(throwingSpeed);
	}
	// --------------------------------------------------------------------------------------------------------------------
}



/*
 * Gestion de la rotation camera.
 */
void MainScene::gestionCamera()
{
	// ================================================================================================================
	// VARIABLES FOR CAMERA
	// ----------------------------------------------------------------------------------------------------------------
	double mousePosNormalX = (2.0 * mouse.posX) / screen.width - 1.0;
	double mousePosNormalY = (2.0 * mouse.posY) / screen.height - 1.0;


	// ================================================================================================================
	// ZOOM
	// ----------------------------------------------------------------------------------------------------------------
	if (mouse.wheel == 1 && camera.rho > 0.5f)
	{
		camera.rho -= 0.5f;
	}

	if (mouse.wheel == -1 && camera.rho < 40.0f)
	{
		camera.rho += 0.5f;
	}
	// ----------------------------------------------------------------------------------------------------------------


	// ================================================================================================================
	// Rotation around
	// ----------------------------------------------------------------------------------------------------------------
	if (mouse.middleButtonPressed && !previousMouseMiddleButtonDownState)
	{
		middleClickX = mousePosNormalX;
		middleClickY = mousePosNormalY;
	}

	double mouseMiddlePointXfactor = (middleClickX - mousePosNormalX + oldMouseMiddleFactorX);
	double mouseMiddlePointYfactor = (middleClickY - mousePosNormalY + oldMouseMiddleFactorY);

	// Rotation for the camera
	if (mouse.middleButtonPressed)
	{
		previousMouseMiddleButtonDownState = true;

		// X Axis
		if (camera.theta > 360 || camera.theta < -360)
		{
			camera.theta = 0;
		}
		else
		{
			camera.theta = mouseMiddlePointXfactor * 180;
		}


		// Y Axis
		if (camera.phi < 180)
		{
			camera.phi = mouseMiddlePointYfactor * 90;
		}
		else
		{
			camera.phi = 180;
		}

		if (camera.phi > 0)
		{
			camera.phi = mouseMiddlePointYfactor * 90;
		}
		else
		{
			camera.phi = 1;
		}
	}

	// When middle click released
	if (mouse.middleButtonReleased)
	{
		oldMouseMiddleFactorX = mouseMiddlePointXfactor;
		oldMouseMiddleFactorY = mouseMiddlePointYfactor;
		previousMouseMiddleButtonDownState = false;
	}
	// ----------------------------------------------------------------------------------------------------------------


	// ================================================================================================================
	// Translation
	// ----------------------------------------------------------------------------------------------------------------
	if (mouse.rightButtonPressed && !previousMouseRightButtonDownState)
	{
		rightClickX = mousePosNormalX;
		rightClickY = mousePosNormalY;
	}

	double mouseRightPointXFactor = (rightClickX - mousePosNormalX + oldMouseRightFactorX);
	double mouseRightPointYFactor = (rightClickY - mousePosNormalY + oldMouseRightFactorY);

	if (mouse.rightButtonPressed)
	{
		previousMouseRightButtonDownState = true;

		camera.target.x = (mouseRightPointXFactor * sin(camera.theta * RADPERDEG) 
					      + mouseRightPointYFactor * cos(camera.theta * RADPERDEG)) * camTranslationSpeed;

		camera.target.z = (mouseRightPointXFactor * cos(camera.theta * RADPERDEG + M_PI)
						  + mouseRightPointYFactor * sin(camera.theta * RADPERDEG)) * camTranslationSpeed;
	}

	if (mouse.rightButtonReleased)
	{
		oldMouseRightFactorX = mouseRightPointXFactor;
		oldMouseRightFactorY = mouseRightPointYFactor;
		previousMouseRightButtonDownState = false;
	}
}


/*
 * Une fois par frame graphique (depend donc de la vitesse du PC et de l'affichage).
 */
void MainScene::update(double delta_t)
{
	// Gestion de la physique de la balle
	physiqueBalle(delta_t);

	// Gestion de la caméra
	gestionCamera();
}
#include <cmath>
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
	camera.position = Vector3(0, 0, 0);
	camera.phi = 90.0;
	camera.theta = 45.0;
	camera.rho = 4.0;

	// For debugging
	auto axis = createComponent(shared_ptr<Form>(new Axis()), Vector3(0, 0, 0));

	// ============= Balle
	radius = 0.5;
	balleSouris = createComponent(shared_ptr<Form>(new Sphere(radius, RED)), Vector3(1, 10, 0));
	balleSouris->addSphereCollider(radius, Vector3(0, 0, 0));

	auto planeform = shared_ptr<Plane>(new Plane(15.0, 15.0, FLOOR));
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
	verre1 = createComponent(shared_ptr<Form>(new Verre(heightGlass, rayBottomGlass, rayTopGlass, RED, BLUE)), Vector3(-2.4 + decalageTable, 0, -0.3 + decalageTable + rayTopGlass));
	collVerre1 = verre1->addBoxCollider(0.2, 0.1, 0.1, Vector3(0, 0, 0));
	verre2 = createComponent(shared_ptr<Form>(new Verre(heightGlass, rayBottomGlass, rayTopGlass, RED, BLUE)), Vector3(-2.4 + decalageTable, 0, -0.2 + decalageTable + rayTopGlass));
	collVerre2 = verre2->addBoxCollider(0.2, 0.1, 0.1, Vector3(0, 0, 0));
	verre3 = createComponent(shared_ptr<Form>(new Verre(heightGlass, rayBottomGlass, rayTopGlass, RED, BLUE)), Vector3(-2.4 + decalageTable, 0, -0.1 + decalageTable + rayTopGlass));
	collVerre3 = verre3->addBoxCollider(0.2, 0.1, 0.1, Vector3(0, 0, 0));
	verre4 = createComponent(shared_ptr<Form>(new Verre(heightGlass, rayBottomGlass, rayTopGlass, RED, BLUE)), Vector3(-2.4 + decalageTable, 0, 0 + decalageTable + rayTopGlass));
	collVerre4 = verre4->addBoxCollider(0.2, 0.1, 0.1, Vector3(0, 0, 0));

	verre5 = createComponent(shared_ptr<Form>(new Verre(heightGlass, rayBottomGlass, rayTopGlass, RED, BLUE)), Vector3(-2.3 + decalageTable, 0, -0.25 + decalageTable + rayTopGlass));
	collVerre5 = verre5->addBoxCollider(0.2, 0.1, 0.1, Vector3(0, 0, 0));
	verre6 = createComponent(shared_ptr<Form>(new Verre(heightGlass, rayBottomGlass, rayTopGlass, RED, BLUE)), Vector3(-2.3 + decalageTable, 0, -0.15 + decalageTable + rayTopGlass));
	collVerre6 = verre6->addBoxCollider(0.2, 0.1, 0.1, Vector3(0, 0, 0));
	verre7 = createComponent(shared_ptr<Form>(new Verre(heightGlass, rayBottomGlass, rayTopGlass, RED, BLUE)), Vector3(-2.3 + decalageTable, 0, -0.05 + decalageTable + rayTopGlass));
	collVerre7 = verre7->addBoxCollider(0.2, 0.1, 0.1, Vector3(0, 0, 0));

	verre8 = createComponent(shared_ptr<Form>(new Verre(heightGlass, rayBottomGlass, rayTopGlass, RED, BLUE)), Vector3(-2.2 + decalageTable, 0, -0.2 + decalageTable + rayTopGlass));
	collVerre8 = verre8->addBoxCollider(0.2, 0.1, 0.1, Vector3(0, 0, 0));
	verre9 = createComponent(shared_ptr<Form>(new Verre(heightGlass, rayBottomGlass, rayTopGlass, RED, BLUE)), Vector3(-2.2 + decalageTable, 0, -0.1 + decalageTable + rayTopGlass));
	collVerre9 = verre9->addBoxCollider(0.2, 0.1, 0.1, Vector3(0, 0, 0));

	verre10 = createComponent(shared_ptr<Form>(new Verre(heightGlass, rayBottomGlass, rayTopGlass, RED, BLUE)), Vector3(-2.1 + decalageTable, 0, -0.15 + decalageTable + rayTopGlass));
	collVerre10 = verre10->addBoxCollider(0.2, 0.1, 0.1, Vector3(0, 0, 0));

	// personnages
	personnage1 = createComponent(shared_ptr<Form>(new Personnage()), Vector3(-3, -0.7, 0.3));
	personnage2 = createComponent(shared_ptr<Form>(new Personnage()), Vector3(-3, -0.7, -0.8));
	
	//auto spherex = createComponent(shared_ptr<Form>(new Sphere(0.5, BLUE)), Vector3(-1, 0, 0));

	lastCollisionSol = false;
	lastCollisionTable = false;

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

	cout << "Main scene setup finished" << endl;
}


void MainScene::physiqueBalle(double delta_t)
{
	// Detect collision ball / plane
	bool collisionSol = false;
	bool collisionTable = false;
	for (auto& collider : balle->getColliders())
	{
		collisionSol = collider->collision(collPlane);
		collisionTable = collider->collision(collTable, lastPointCollisionTable);
	}


	// ray casting

	double coeff = 0.70;

	// Calculate speeds
	double speed_x, speed_y, speed_z;


	if (!lastCollisionSol && collisionSol)
	{
		speed_x = balle->getAnimation()->getSpeed().x * coeff;
		speed_y = balle->getAnimation()->getSpeed().y * -coeff;
		speed_z = balle->getAnimation()->getSpeed().z * coeff;
		lastCollisionSol = true;

		// Sécurité
		balle->setY(niveauSol + radSphere);
	}
	else if (!lastCollisionTable && collisionTable)
	{
		Vector3 axis = (balle->getAnimation()->getPosition() - lastPointCollisionTable).normalize();

		// Rebonds cotes
		if (abs(axis.x) == 1.0)
		{
			speed_x = balle->getAnimation()->getSpeed().x * coeff * -1.0;
		}
		else
		{
			speed_x = balle->getAnimation()->getSpeed().x * coeff;
		}

		if (abs(axis.y) == 1.0)
		{
			speed_y = balle->getAnimation()->getSpeed().y * coeff * -1.0;
		}
		else
		{
			speed_y = balle->getAnimation()->getSpeed().y * coeff;
		}

		if (abs(axis.z) == 1.0)
		{
			speed_z = balle->getAnimation()->getSpeed().z * coeff * -1.0;
		}
		else
		{
			speed_z = balle->getAnimation()->getSpeed().z * coeff;
		}

		lastCollisionTable = true;

		// Sécurité
		if (axis.y == 1.0)
		{
			balle->setY(niveauTable + radSphere);
		}
	}
	else
	{
		speed_x = balle->getAnimation()->getSpeed().x;
		speed_y = balle->getAnimation()->getSpeed().y - (GRAVITY * delta_t); // TODO delta_t^2 bizarre
		speed_z = balle->getAnimation()->getSpeed().z;

		//cout << abs(speed_y) << endl;
		lastCollisionSol = false;
		lastCollisionTable = false;
	}

	balle->getAnimation()->setSpeed(speed_x, speed_y, speed_z);

	// Assign pos
	double x, y, z;

	if (mouse.leftButtonPressed) {

		x = (2.0 * mouse.posX) / screen.width * 2.0 - 2.0;
		y = 1.5 - (2.0 * mouse.posY) / screen.width * 1.5;
		z = 0.0f;
		balle->getAnimation()->setSpeed(0, 0, 0);

		if (!mousePressedLastState) {
			previous_time = SDL_GetTicks();
			mouseDeparture = Vector3(x, y, z);
		}

		mousePressedLastState = true;
	}
	else
	{
		x = balle->getAnimation()->getPosition().x + balle->getAnimation()->getSpeed().x * delta_t;
		y = balle->getAnimation()->getPosition().y + balle->getAnimation()->getSpeed().y * delta_t - GRAVITY * (delta_t * delta_t) / 2.0;
		z = balle->getAnimation()->getPosition().z + balle->getAnimation()->getSpeed().z * delta_t;
	}

	balle->getAnimation()->setPosition(x, y, z);


	if (mouse.leftButtonReleased)
	{
		mousePressedLastState = false;
		current_time = SDL_GetTicks();
		double time = current_time - previous_time;
		double secs = time / 1000.0;
		double distance = mouseArrival.distance(mouseDeparture);
		double spd = distance / secs;

		//cout << distance << "from " << mouseDeparture << " to " << mouseArrival << endl;


		// Throw ball by mouse


		mouseArrival = balle->getAnimation()->getPosition();


		//ray->setForm(shared_ptr<Form>(new Ray(mouseDeparture, mouseArrival)));
		ray->setForm(shared_ptr<Form>(new Arrow((mouseArrival - mouseDeparture).normalize())));
		rayThrow->setForm(shared_ptr<Form>(new Ray(mouseArrival, mouseDeparture)));

		Vector3 throwingSpeed = distance * 5.0 * (mouseArrival - mouseDeparture).normalize();
		balle->getAnimation()->setSpeed(throwingSpeed);
	}

	// Garde fou
	if (balle->getY() - radSphere <= niveauSol)
	{
		//balle->setY(niveauSol + radSphere);
	}

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

		camera.position.x = (mouseRightPointXFactor * sin(camera.theta * RADPERDEG) 
					      + mouseRightPointYFactor * cos(camera.theta * RADPERDEG)) * camTranslationSpeed;

		camera.position.z = (mouseRightPointXFactor * cos(camera.theta * RADPERDEG + M_PI)
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
	/*
	// Raycast
	auto b = camera.raycastEnd;
	auto a = camera.raycastStart;
	auto c = balleSouris->getAnimation()->getPosition();

	Vector3 a1 = b - a;
	Vector3 a2 = c - a;
	Vector3 bv = c - b;

	if (!mouse.leftButtonPressed) {
		if (a2 * a1 <= 0.0)           // Point is lagging behind start of the segment, so perpendicular distance is not viable.
			d = a2.norm();         // Use distance to start of segment instead.
		else if (bv * a1 >= 0.0)           // Point is advanced past the end of the segment, so perpendicular distance is not viable.
			d = bv.norm();         // Use distance to end of the segment instead.
		else
			d = (a1 ^ a2).norm() / a1.norm();       // Perpendicular distance of point to segment.
	}

	cout << "new d =" << d << endl;

	Vector3 newPos((b.x - a.x) / 3.0, (b.y - a.y) / 3.0, (b.z - a.z) / 3.0);

	Vector3 Q = a + d * a1;
	ray->setForm(shared_ptr<Form>(new Ray(Q, c)));
	//balleTest->getAnimation()->setPosition(a1);

	//cout << (a + d * a1) << endl;
	if (d < radius) {
		cout << "la souris est sur la balle" << endl;
		if (mouse.leftButtonPressed)
		{
			cout << "la souris est cliquee sur la balle" << endl;
			balleSouris->getAnimation()->setPosition(Q);
		}
	}
	*/

	// Gestion de la physique de la balle
	physiqueBalle(delta_t);

	// Gestion de la caméra
	gestionCamera();
}
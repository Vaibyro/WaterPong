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
	double coefficientReduc = 1;

	// Table
	table = createComponent(shared_ptr<Form>(new Table(0.7, 0.1, 2.4, 0.6, 0.1)), Vector3(-2.4, -0.7, -0.3));
	// Table(double heiTotal, double heiTray, double len, double wi, double wiFoot)
	collTable = table->addBoxCollider(10.0 * coefficientReduc, 30.0 * coefficientReduc, 15.0 * coefficientReduc, Vector3(0, 0, 0));

	
	// Verres
	double heightGlass = 0.2;
	double rayBottomGlass = 0.03;
	double rayTopGlass = 0.05;
	double decalageTable = 0.1;
	// Verre(double hei, double rayB, double rayT, Color coGob, Color coLiq)
	verre1 = createComponent(shared_ptr<Form>(new Verre(heightGlass, rayBottomGlass, rayTopGlass, RED, BLUE)), Vector3(-2.4 + decalageTable, 0, -0.3 + decalageTable + rayTopGlass));
	verre2 = createComponent(shared_ptr<Form>(new Verre(heightGlass, rayBottomGlass, rayTopGlass, RED, BLUE)), Vector3(-2.4 + decalageTable, 0, -0.2 + decalageTable + rayTopGlass));
	verre3 = createComponent(shared_ptr<Form>(new Verre(heightGlass, rayBottomGlass, rayTopGlass, RED, BLUE)), Vector3(-2.4 + decalageTable, 0, -0.1 + decalageTable + rayTopGlass));
	verre4 = createComponent(shared_ptr<Form>(new Verre(heightGlass, rayBottomGlass, rayTopGlass, RED, BLUE)), Vector3(-2.4 + decalageTable, 0, 0 + decalageTable + rayTopGlass));
	
	verre5 = createComponent(shared_ptr<Form>(new Verre(heightGlass, rayBottomGlass, rayTopGlass, RED, BLUE)), Vector3(-2.3 + decalageTable, 0, -0.25 + decalageTable + rayTopGlass));
	verre6 = createComponent(shared_ptr<Form>(new Verre(heightGlass, rayBottomGlass, rayTopGlass, RED, BLUE)), Vector3(-2.3 + decalageTable, 0, -0.15 + decalageTable + rayTopGlass));
	verre7 = createComponent(shared_ptr<Form>(new Verre(heightGlass, rayBottomGlass, rayTopGlass, RED, BLUE)), Vector3(-2.3 + decalageTable, 0, -0.05 + decalageTable + rayTopGlass));

	verre8 = createComponent(shared_ptr<Form>(new Verre(heightGlass, rayBottomGlass, rayTopGlass, RED, BLUE)), Vector3(-2.2 + decalageTable, 0, -0.2 + decalageTable + rayTopGlass));
	verre9 = createComponent(shared_ptr<Form>(new Verre(heightGlass, rayBottomGlass, rayTopGlass, RED, BLUE)), Vector3(-2.2 + decalageTable, 0, -0.1 + decalageTable + rayTopGlass));

	verre10 = createComponent(shared_ptr<Form>(new Verre(heightGlass, rayBottomGlass, rayTopGlass, RED, BLUE)), Vector3(-2.1 + decalageTable, 0, -0.15 + decalageTable + rayTopGlass));
	
	
	// personnages
	personnage1 = createComponent(shared_ptr<Form>(new Personnage()), Vector3(-3, -0.7, 0.3));
	personnage2 = createComponent(shared_ptr<Form>(new Personnage()), Vector3(-3, -0.7, -0.8));
	
	//auto spherex = createComponent(shared_ptr<Form>(new Sphere(0.5, BLUE)), Vector3(-1, 0, 0));
	cout << "Scene setup finished !" << endl;


	lastCollision = false;

	previous_time = 0;
	current_time = 0;
}

/*
 * Une fois par frame graphique (depend donc de la vitesse du PC et de l'affichage).
 */
void MainScene::update(double delta_t)
{
	// Detect collision ball / plane
	bool collisionSol = false;
	bool collisionTable = false;
	for (auto& collider : balle->getColliders())
	{
		collisionSol = collider->collision(collPlane);
		collisionTable = collider->collision(collTable);
	}

	cout << collisionTable << endl;

	// ray casting

	double coeff = 0.40;

	// Calculate speeds
	double speed_x, speed_y, speed_z;


	if (!lastCollision && collisionSol)
	{
		speed_x = balle->getAnimation()->getSpeed().x * coeff;
		speed_y = balle->getAnimation()->getSpeed().y * -coeff;
		speed_z = balle->getAnimation()->getSpeed().z * coeff;
		lastCollision = true;
	}
	else
	{
		speed_x = balle->getAnimation()->getSpeed().x;
		speed_y = balle->getAnimation()->getSpeed().y - (GRAVITY * delta_t); // TODO delta_t^2 bizarre
		speed_z = balle->getAnimation()->getSpeed().z;

		//cout << abs(speed_y) << endl;
		lastCollision = false;
	}

	balle->getAnimation()->setSpeed(speed_x, speed_y, speed_z);

	// Assign pos
	double x, y, z;

	if (mouse.leftButtonPressed) {

		x = (2.0f * mouse.posX) / screen.width * 2.0 - 2.0f;
		y = 1.5f - (2.0f * mouse.posY) / screen.width * 1.5;
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
		balle->setY(niveauSol + radSphere);
	}

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
}

/*
 * Une fois toutes les t millisecondes. Ne depend pas de la vitesse du PC.
 */
void MainScene::fixedUpdate()
{

}

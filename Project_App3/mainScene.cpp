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

	radius = 0.5;
	balleSouris = createComponent(shared_ptr<Form>(new Sphere(radius, RED)), Vector3(1, 10, 0));
	balleSouris->addSphereCollider(radius, Vector3(0, 0, 0));



	auto planeform = shared_ptr<Plane>(new Plane(3.0, 3.0));
	auto plane = createComponent(planeform, Vector3(0, -1, 0));
	coll = plane->addPlaneCollider(3.0, 3.0, Vector3(0, 0, 0));

	ray = createComponent(shared_ptr<Form>(new Arrow(Vector3(0, 0, 0), RED)));
	rayThrow = createComponent(shared_ptr<Form>(new Ray(Vector3(0, 0, 0), Vector3(0, 0, 0), RED)));

	double radSphere = 0.2;
	balleTest = createComponent(shared_ptr<Form>(new Sphere(radSphere, GREEN)), Vector3(0, 3, 0));
	balleTest->addSphereCollider(radSphere, Vector3(0, 0, 0));
	balleTest->getAnimation()->setSpeed(-2, 0, -1);

	d = 5.0;
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
	/*
	//toto->getAnimation()->translate(delta_t * Vector(0, -1, 0));
	//toto->getAnimation()->setScale(0.992 * toto->getAnimation()->getScale());

	double grav = 9.81;//9.81;
	double alpha = 90.0;

	Vector3 pt;
	//pt.x = toto->getAnimation()->getPosition().x; //(V0x * cos(alpha) * delta_t + x0);
	//pt.y = (-(grav * (delta_t * delta_t)) / 2.0 - 0.1 * sin(alpha) + toto->getAnimation()->getPosition().y);
	//pt.z = toto->getAnimation()->getPosition().z;//(V0z * cos(alpha) * delta_t + z0);

	double newspeed = toto->getAnimation()->getSpeed().y + (-grav * delta_t * delta_t) / 2.0;
	toto->getAnimation()->setSpeed(0, newspeed, 0);

	// Colliders
	for (auto& collider : toto->getColliders())
	{
		bool iscoll = collider->collision(coll);
		if (iscoll) {
			toto->getAnimation()->setSpeed(0, 0, 0);
			toto->getAnimation()->setPosition(toto->getAnimation()->getPosition().x, 0.5 - 1, toto->getAnimation()->getPosition().z);
		}
	}


	float x, y, z;
	x = toto->getAnimation()->getPosition().x;
	y = toto->getAnimation()->getPosition().y + toto->getAnimation()->getSpeed().y;
	z = toto->getAnimation()->getPosition().z;


	if (mouse.leftButtonPressed) {
		x = (2.0f * mouse.posX) / screen.width * 2.0 - 2.0f;
		y = 1.5f - (2.0f * mouse.posY) / screen.width * 1.5;
		z = 0.0f;
		toto->getAnimation()->setSpeed(0, 0, 0);
	}


	toto->getAnimation()->setPosition(x, y, z);

	*/

	// Detect collision ball / plane
	bool collision = false;
	for (auto& collider : balleTest->getColliders())
	{
		collision = collider->collision(coll);
	}

	// ray casting

	double coeff = 0.92;

	// Calculate speeds
	double speed_x, speed_y, speed_z;


	if (!lastCollision && collision)
	{
		speed_x = balleTest->getAnimation()->getSpeed().x * coeff;
		speed_y = balleTest->getAnimation()->getSpeed().y * -coeff;
		speed_z = balleTest->getAnimation()->getSpeed().z * coeff;
		lastCollision = true;
	}
	else
	{
		speed_x = balleTest->getAnimation()->getSpeed().x;
		speed_y = balleTest->getAnimation()->getSpeed().y - (GRAVITY * delta_t); // TODO delta_t^2 bizarre
		speed_z = balleTest->getAnimation()->getSpeed().z;

		//cout << abs(speed_y) << endl;
		lastCollision = false;
	}

	balleTest->getAnimation()->setSpeed(speed_x, speed_y, speed_z);

	// Assign pos
	double x, y, z;

	if (mouse.leftButtonPressed) {
		
		x = (2.0f * mouse.posX) / screen.width * 2.0 - 2.0f;
		y = 1.5f - (2.0f * mouse.posY) / screen.width * 1.5;
		z = 0.0f;
		balleTest->getAnimation()->setSpeed(0, 0, 0);

		if (!mousePressedLastState) {
			previous_time = SDL_GetTicks();
			mouseDeparture = Vector3(x, y, z);
		}

		mousePressedLastState = true;
	}
	else
	{
		x = balleTest->getAnimation()->getPosition().x + balleTest->getAnimation()->getSpeed().x * delta_t;
		y = balleTest->getAnimation()->getPosition().y + balleTest->getAnimation()->getSpeed().y * delta_t;// - GRAVITY * (delta_t * delta_t) / 2.0;
		z = balleTest->getAnimation()->getPosition().z + balleTest->getAnimation()->getSpeed().z * delta_t;
	}


	balleTest->getAnimation()->setPosition(x, y, z);

	if (mouse.leftButtonReleased) 
	{
		mousePressedLastState = false;
		current_time = SDL_GetTicks();
		double time = current_time - previous_time;
		double secs = time / 1000.0;
		double distance = mouseArrival.distance(mouseDeparture);
		double spd = distance / secs;

		cout << distance << "from " << mouseDeparture << " to " << mouseArrival << endl;


		// Throw ball by mouse
		

		mouseArrival = balleTest->getAnimation()->getPosition();


		//ray->setForm(shared_ptr<Form>(new Ray(mouseDeparture, mouseArrival)));
		ray->setForm(shared_ptr<Form>(new Arrow((mouseArrival - mouseDeparture).normalize())));
		rayThrow->setForm(shared_ptr<Form>(new Ray(mouseArrival, mouseDeparture)));

		Vector3 throwingSpeed = spd * (mouseArrival - mouseDeparture).normalize();
		balleTest->getAnimation()->setSpeed(throwingSpeed);
	}


	// Garde fou
	if (balleTest->getY() - 0.2 <= -1)
	{
		balleTest->setY(-1 + 0.2);
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


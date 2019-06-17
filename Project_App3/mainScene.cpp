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
	/*
	auto axis2 = createComponent(shared_ptr<Form>(new Axis()), Vector3(0, -0.1, 0));
	auto axis3 = createComponent(shared_ptr<Form>(new Axis()), Vector3(0, -0.2, 0));
	auto axis4 = createComponent(shared_ptr<Form>(new Axis()), Vector3(0, -0.4, 0));
	*/
	toto = createComponent(shared_ptr<Form>(new Sphere(0.5, RED)), Vector3(1, 0, 0));

	toto->addSphereCollider(0.3, Vector3(0, 0, 0));

	auto planeform = shared_ptr<Plane>(new Plane(3.0, 10.0));
	auto plane = createComponent(planeform, Vector3(0, -0.5, 0));
	coll = plane->addPlaneCollider(3.0, 10.0, Vector3(0, 0, 0));


	auto sp = createComponent(shared_ptr<Form>(new Sphere(0.02, GREEN)), Vector3(0, 0, 0));
	auto sp1 = createComponent(shared_ptr<Form>(new Sphere(0.03, GREEN)), Vector3(0, -0.2, 0));



	//auto ray = createComponent(shared_ptr<Form>(new Ray(Vector3(1, 0, 0), RED)), Vector3(-0.2, 0.2, 0));
	//auto ray2 = createComponent(shared_ptr<Form>(new Ray(Vector3(0, 1, 0), GREEN)), Vector3(-0.2, 0.2, 0));

	axisU = createComponent(shared_ptr<Form>(new Axis()), Vector3(camera.raycastStart.x, camera.raycastStart.y, camera.raycastStart.z));


	auto spherex = createComponent(shared_ptr<Form>(new Sphere(0.5, BLUE)), Vector3(-1, 0, 0));
	point = createComponent(shared_ptr<Form>(new Sphere(0.1, WHITE)), Vector3(0, 0, 0));
	cout << "Scene setup finished !" << endl;
}

Vector3 ClosestPoint(const Vector3 A, const Vector3 B, const Vector3 P, double *t)
{
	Vector3 AB = B - A;
	double ab_square = AB * AB;
	Vector3 AP = P - A;
	double ap_dot_ab = AP * AB;
	// t is a projection param when we project vector AP onto AB 
	*t = ap_dot_ab / ab_square;
	// calculate the closest point 
	Vector3 Q = A + AB * (*t);
	return Q;
}

float shortDistance(Vector3 line_point1, Vector3 line_point2, Vector3 point)
{
	Vector3 AB = line_point2 - line_point1;
	Vector3 AC = point - line_point1;
	float area = Vector3(AB * AC).norm();
	float CD = area / AB.norm();
	return CD;
}

/*
 * Une fois par frame graphique (depend donc de la vitesse du PC et de l'affichage).
 */
void MainScene::update(double delta_t)
{
	//toto->getAnimation()->translate(delta_t * Vector(0, -1, 0));
	//toto->getAnimation()->setScale(0.992 * toto->getAnimation()->getScale());

	double grav = 0.25;//9.81;
	double alpha = 90.0;

	Vector3 pt;
	//pt.x = toto->getAnimation()->getPosition().x; //(V0x * cos(alpha) * delta_t + x0);
	//pt.y = (-(grav * (delta_t * delta_t)) / 2.0 - 0.1 * sin(alpha) + toto->getAnimation()->getPosition().y);
	//pt.z = toto->getAnimation()->getPosition().z;//(V0z * cos(alpha) * delta_t + z0);

	double newspeed = toto->getAnimation()->getSpeed().y + (-grav * delta_t) / 2.0;
	toto->getAnimation()->setSpeed(0, newspeed, 0);

	// Colliders
	for (auto& collider : toto->getColliders())
	{
		bool iscoll = collider->collision(coll);
		if (iscoll) {
			toto->getAnimation()->setSpeed(0, 0, 0);
			//cout << "Collision detected" << endl;
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

	// ray casting

	// Get normalized coordd
	double nmousex = (2.0 * mouse.posX) / screen.width - 1.0;
	double nmousey = (2.0 * mouse.posY) / screen.height - 1.0;
	
	Vector4 mm = Vector4(nmousex, nmousey, -1.0, 1.0);


	


	axisU->getAnimation()->setPosition(camera.raycastEnd.normalize());
	
	double t;
	Vector3 v = ClosestPoint(camera.raycastStart, camera.raycastEnd, Vector3(-1, 0, 0), &t);
	cout << v << " d=" << shortDistance(camera.raycastStart, camera.raycastEnd, Vector3(-1, 0, 0)) << endl;

	point->getAnimation()->setPosition(v);

	//cout << "Scene update ! d=" << toto->getAnimation()->getSpeed().y << endl;
}





/*
 * Une fois toutes les t millisecondes. Ne depend pas de la vitesse du PC.
 */
void MainScene::fixedUpdate()
{

}


#include "mainScene.h"
#include "component.h"
#include "..\forms.h"
#include "..\geometry.h"

/*
 * Une fois au debut de la creation de la scene.
 */
void MainScene::setup()
{
	auto axis = createComponent(shared_ptr<Form>(new Axis()), Vector(0, -1, 0));
	toto = createComponent(shared_ptr<Form>(new Sphere(0.2, RED)), Vector(0, 5, 0));
	createComponent(shared_ptr<Form>(new Sphere(1, YELLOW)), Vector(0, 0, 0));
	toto->addSphereCollider(0.05, Vector(0, 0, 1));

	cout << "Scene setup finished !" << endl;
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

	Vector pt;
	//pt.x = toto->getAnimation()->getPosition().x; //(V0x * cos(alpha) * delta_t + x0);
	//pt.y = (-(grav * (delta_t * delta_t)) / 2.0 - 0.1 * sin(alpha) + toto->getAnimation()->getPosition().y);
	//pt.z = toto->getAnimation()->getPosition().z;//(V0z * cos(alpha) * delta_t + z0);

	double newspeed = toto->getAnimation()->getSpeed().y + (-grav * delta_t) / 2.0;

	//cout << newspeed << endl;

	toto->getAnimation()->setSpeed(0, newspeed, 0);
	pt.y = toto->getAnimation()->getPosition().y + toto->getAnimation()->getSpeed().y;

	float x = (2.0f * mouseposx) / screenx * 2.0 - 2.0f;
	float y = 1.5f - (2.0f * mouseposy) / screeny * 1.5;
	float z = 1.0f;

	toto->getAnimation()->setPosition(x, y, z);


	//cout << "Scene update ! d=" << toto->getAnimation()->getSpeed().y << endl;
}


/*
 * Une fois toutes les t millisecondes. Ne depend pas de la vitesse du PC.
 */
void MainScene::fixedUpdate()
{

}


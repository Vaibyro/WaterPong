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

	// Table
	table = createComponent(shared_ptr<Form>(new Table(2, 30, 15)), Vector3(-30, -2, -7.5));
	//Table(double hei, double len, double wi);



	// Verres
	double heightGlass = 3;
	double rayBottomGlass = 1;
	double rayTopGlass = 1.5;
	double decalageTable = 3;
	// Verre(double hei, double rayB, double rayT, Color coGob, Color coLiq)
	verre1 = createComponent(shared_ptr<Form>(new Verre(heightGlass, rayBottomGlass, rayTopGlass, RED, BLUE)), Vector3(-30+decalageTable, 0, -7.5+ decalageTable));
	verre2 = createComponent(shared_ptr<Form>(new Verre(heightGlass, rayBottomGlass, rayTopGlass, RED, BLUE)), Vector3(-30 + decalageTable, 0, -4.5 + decalageTable));
	verre3 = createComponent(shared_ptr<Form>(new Verre(heightGlass, rayBottomGlass, rayTopGlass, RED, BLUE)), Vector3(-30 + decalageTable, 0, -1.5 + decalageTable));
	verre4 = createComponent(shared_ptr<Form>(new Verre(heightGlass, rayBottomGlass, rayTopGlass, RED, BLUE)), Vector3(-30 + decalageTable, 0, 1.5 + decalageTable));
	
	verre5 = createComponent(shared_ptr<Form>(new Verre(heightGlass, rayBottomGlass, rayTopGlass, RED, BLUE)), Vector3(-27.5 + decalageTable, 0, -6 + decalageTable));
	verre6 = createComponent(shared_ptr<Form>(new Verre(heightGlass, rayBottomGlass, rayTopGlass, RED, BLUE)), Vector3(-27.5 + decalageTable, 0, -3 + decalageTable));
	verre7 = createComponent(shared_ptr<Form>(new Verre(heightGlass, rayBottomGlass, rayTopGlass, RED, BLUE)), Vector3(-27.5 + decalageTable, 0, 0 + decalageTable));

	verre8 = createComponent(shared_ptr<Form>(new Verre(heightGlass, rayBottomGlass, rayTopGlass, RED, BLUE)), Vector3(-25 + decalageTable, 0, -4.5 + decalageTable));
	verre9 = createComponent(shared_ptr<Form>(new Verre(heightGlass, rayBottomGlass, rayTopGlass, RED, BLUE)), Vector3(-25 + decalageTable, 0, -1.5 + decalageTable));

	verre10 = createComponent(shared_ptr<Form>(new Verre(heightGlass, rayBottomGlass, rayTopGlass, RED, BLUE)), Vector3(-22.5 + decalageTable, 0, -3 + decalageTable));
	
	// personnages
	personnage1 = createComponent(shared_ptr<Form>(new Personnage()), Vector3(-40, -10, 5));
	personnage2 = createComponent(shared_ptr<Form>(new Personnage()), Vector3(-40, -10, -15));

	
	//auto spherex = createComponent(shared_ptr<Form>(new Sphere(0.5, BLUE)), Vector3(-1, 0, 0));
	cout << "Scene setup finished !" << endl;
}


/*
 * Une fois par frame graphique (depend donc de la vitesse du PC et de l'affichage).
 */
void MainScene::update(double delta_t)
{
	
}


/*
 * Une fois toutes les t millisecondes. Ne depend pas de la vitesse du PC.
 */
void MainScene::fixedUpdate()
{

}


#include <iostream>
#include <cmath>

//Using SDL, SDL OpenGL, GLEW
#include <SDL.h>
#include <gl\glew.h>  // glu.h included
#include <SDL_opengl.h>

// Module for space geometry
#include "geometry.h"
// Module for generating and rendering forms
#include "forms.h"

using namespace std;


/***************************************************************************/
/* Constants and functions declarations                                    */
/***************************************************************************/
// Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

// Max number of forms : static allocation
const int MAX_FORMS_NUMBER = 50;

// Animation actualization delay (in ms) => 100 updates per second
const Uint32 ANIM_DELAY = 10;
const float RALENTI = 1; // 1 = pas de ralenti

// Starts up SDL, creates window, and initializes OpenGL
bool init(SDL_Window** window, SDL_GLContext* context);

// Initializes matrices and clear color
bool initGL();

// Updating forms for animation
void update(Form* formlist[MAX_FORMS_NUMBER], double delta_t);

// Renders scene to the screen
const void render(Form* formlist[MAX_FORMS_NUMBER], const Point& cam_pos);

// Frees media and shuts down SDL
void close(SDL_Window** window);

// Generate all form for the Scene
void generateScene();


// GLOBAL PARAMETERS
// List of form
Form* forms_list[MAX_FORMS_NUMBER];
// Forms
const double heightGlass = 3;
const double rayBottomGlass = 1;
const double rayTopGlass = 1.5;
const double heightSubGlass = 2.8;
const double rayBottomSubGlass = 0.95;
const double rayTopSubGlass = 1.45;
// graphics
const double coeffReduc = 0.15;
const double decalageTable = 1.5;


/***************************************************************************/
/* Functions implementations                                               */
/***************************************************************************/
bool init(SDL_Window** window, SDL_GLContext* context)
{
	// Initialization flag
	bool success = true;

	// Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		cout << "SDL could not initialize! SDL Error: " << SDL_GetError() << endl;
		success = false;
	}
	else
	{
		// Use OpenGL 2.1
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);

		// Create window
		*window = SDL_CreateWindow("TP intro OpenGL / SDL 2", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
		if (*window == NULL)
		{
			cout << "Window could not be created! SDL Error: " << SDL_GetError() << endl;
			success = false;
		}
		else
		{
			// Create context
			*context = SDL_GL_CreateContext(*window);
			if (*context == NULL)
			{
				cout << "OpenGL context could not be created! SDL Error: " << SDL_GetError() << endl;
				success = false;
			}
			else
			{
				// Use Vsync
				if (SDL_GL_SetSwapInterval(1) < 0)
				{
					cout << "Warning: Unable to set VSync! SDL Error: " << SDL_GetError() << endl;
				}

				// Initialize OpenGL
				if (!initGL())
				{
					cout << "Unable to initialize OpenGL!" << endl;
					success = false;
				}
			}
		}
	}

	return success;
}


bool initGL()
{
	bool success = true;
	GLenum error = GL_NO_ERROR;

	// Initialize Projection Matrix
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	// Set the viewport : use all the window to display the rendered scene
	glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);

	// Fix aspect ratio and depth clipping planes
	gluPerspective(40.0, (GLdouble)SCREEN_WIDTH / SCREEN_HEIGHT, 1.0, 100.0);


	// Initialize Modelview Matrix
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// Initialize clear color : black with no transparency
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	// Activate Z-Buffer


	// Check for error
	error = glGetError();
	if (error != GL_NO_ERROR)
	{
		cout << "Error initializing OpenGL!  " << gluErrorString(error) << endl;
		success = false;
	}

	glEnable(GL_DEPTH_TEST);

	return success;
}

void update(Form* formlist[MAX_FORMS_NUMBER], double delta_t)
{
	// Update the list of forms
	unsigned short i = 0;
	while (formlist[i] != NULL)
	{
		formlist[i]->update(delta_t);
		i++;
	}
}

const void render(Form* formlist[MAX_FORMS_NUMBER], const Point& cam_pos)
{
	// Clear color buffer and Z-Bufferq
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Initialize Modelview Matrix
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// Set the camera position and parameters
	gluLookAt(cam_pos.x, cam_pos.y, cam_pos.z, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
	// Isometric view
	glRotated(-45, 0, 1, 0);
	glRotated(30, 1, 0, -1);

	// X, Y and Z axis
	glPushMatrix(); // Preserve the camera viewing point for further forms
	// Render the coordinates system
	glBegin(GL_LINES);
	{
		glColor3f(1.0f, 0.0f, 0.0f);
		glVertex3i(0, 0, 0);
		glVertex3i(1, 0, 0);
		glColor3f(0.0f, 1.0f, 0.0f);
		glVertex3i(0, 0, 0);
		glVertex3i(0, 1, 0);
		glColor3f(0.0f, 0.0f, 1.0f);
		glVertex3i(0, 0, 0);
		glVertex3i(0, 0, 1);
	}
	glEnd();
	glPopMatrix(); // Restore the camera viewing point for next object

	// Render the list of forms
	unsigned short i = 0;
	while (formlist[i] != NULL)
	{
		glPushMatrix(); // Preserve the camera viewing point for further forms
		formlist[i]->render();
		glPopMatrix(); // Restore the camera viewing point for next object
		i++;
	}
}

void close(SDL_Window** window)
{
	//Destroy window
	SDL_DestroyWindow(*window);
	*window = NULL;

	//Quit SDL subsystems
	SDL_Quit();
}


void generateScene()
{
	// The forms to render
	unsigned short number_of_forms = 0, i;
	for (i = 0; i < MAX_FORMS_NUMBER; i++)
	{
		forms_list[i] = NULL;
	}
	
	
	// TABLE
	// pieds
	Animation *animationPied1 = new Animation(0.5, 0.5, Vector(0, 0, 0), Vector(0.1, 0.1, 0.1), Point(0, -10, 0));
	Parallelepipede *pied1 = new Parallelepipede(3, 3, 8, RED);
	//Parallelepipede(double len, double wid, double hei, Color co)
	forms_list[number_of_forms] = pied1;
	number_of_forms++;
	pied1->setAnim(*animationPied1);

	Animation *animationPied2 = new Animation(0.5, 0.5, Vector(0, 0, 0), Vector(0.1, 0.1, 0.1), Point(0, -10, 12));
	Parallelepipede *pied2 = new Parallelepipede(3, 3, 8, RED);
	//Parallelepipede(double len, double wid, double hei, Color co)
	forms_list[number_of_forms] = pied2;
	number_of_forms++;
	pied2->setAnim(*animationPied2);

	Animation *animationPied3 = new Animation(0.5, 0.5, Vector(0, 0, 0), Vector(0.1, 0.1, 0.1), Point(27, -10, 0));
	Parallelepipede *pied3 = new Parallelepipede(3, 3, 8, RED);
	//Parallelepipede(double len, double wid, double hei, Color co)
	forms_list[number_of_forms] = pied3;
	number_of_forms++;
	pied3->setAnim(*animationPied3);

	Animation *animationPied4 = new Animation(0.5, 0.5, Vector(0, 0, 0), Vector(0.1, 0.1, 0.1), Point(27, -10, 12));
	Parallelepipede *pied4 = new Parallelepipede(3, 3, 8, RED);
	//Parallelepipede(double len, double wid, double hei, Color co)
	forms_list[number_of_forms] = pied4;
	number_of_forms++;
	pied4->setAnim(*animationPied4);


	// plateau
	Animation *animationPlateau = new Animation(0.5, 0.5, Vector(0, 0, 0), Vector(0.1, 0.1, 0.1), Point(0, -2, 0));
	Parallelepipede *plateau = new Parallelepipede(30, 15, 2, GREEN);
	//Parallelepipede(double len, double wid, double hei, Color co)
	forms_list[number_of_forms] = plateau;
	number_of_forms++;
	plateau->setAnim(*animationPlateau);
	

	// GLASS

	// animation
	// creer animations
	Animation *animation1 = NULL;
	Animation *animation2 = NULL;
	Animation *animation3 = NULL;
	Animation *animation4 = NULL;
	Animation *animation5 = NULL;
	Animation *animation6 = NULL;
	Animation *animation7 = NULL;
	Animation *animation8 = NULL;
	Animation *animation9 = NULL;
	Animation *animation10 = NULL;
	animation1 = new Animation(0.5, 0.5, Vector(0, 0, 0), Vector(0.1, 0.1, 0.1), Point(1.5*coeffReduc, 0 * coeffReduc, (1.5 + decalageTable)*coeffReduc));
	animation2 = new Animation(0.5, 0.5, Vector(1, 1, 1), Vector(0.1, 0.1, 0.1), Point(1.5*coeffReduc, 0 * coeffReduc, (4.5 + decalageTable)*coeffReduc));
	animation3 = new Animation(0.5, 0.5, Vector(1, 1, 1), Vector(0.1, 0.1, 0.1), Point(1.5*coeffReduc, 0 * coeffReduc, (7.5 + decalageTable)*coeffReduc));
	animation4 = new Animation(0.5, 0.5, Vector(1, 1, 1), Vector(0.1, 0.1, 0.1), Point(1.5*coeffReduc, 0 * coeffReduc, (10.5 + decalageTable)*coeffReduc));

	animation5 = new Animation(0.5, 0.5, Vector(1, 1, 1), Vector(0.1, 0.1, 0.1), Point(4.0*coeffReduc, 0 * coeffReduc, (3.0 + decalageTable)*coeffReduc));
	animation6 = new Animation(0.5, 0.5, Vector(1, 1, 1), Vector(0.1, 0.1, 0.1), Point(4.0*coeffReduc, 0 * coeffReduc, (6.0 + decalageTable)*coeffReduc));
	animation7 = new Animation(0.5, 0.5, Vector(1, 1, 1), Vector(0.1, 0.1, 0.1), Point(4.0*coeffReduc, 0 * coeffReduc, (9.0 + decalageTable)*coeffReduc));

	animation8 = new Animation(0.5, 0.5, Vector(1, 1, 1), Vector(0.1, 0.1, 0.1), Point(6.5*coeffReduc, 0 * coeffReduc, (4.5 + decalageTable)*coeffReduc));
	animation9 = new Animation(0.5, 0.5, Vector(1, 1, 1), Vector(0.1, 0.1, 0.1), Point(6.5*coeffReduc, 0 * coeffReduc, (7.5 + decalageTable)*coeffReduc));

	animation10 = new Animation(0.5, 0.5, Vector(1, 1, 1), Vector(0.1, 0.1, 0.1), Point(9 * coeffReduc, 0 * coeffReduc, (6.0 + decalageTable)*coeffReduc));
	// Animation (phi, theta, vector accel, vector speed, point);


	// creer verres
	Verre *verre1 = new Verre(heightGlass, rayBottomGlass, rayTopGlass, RED);
	//Verre(double height = 1.0, double rayBottom = 0.5, double rayTop = 1, Color co);
	Liquide *liquide1 = new Liquide(heightSubGlass, rayBottomSubGlass, rayTopSubGlass, BLUE);
	//Liquide(double height = 1.0, double rayBottom = 0.5, double rayTop = 1, Color co);
	forms_list[number_of_forms] = verre1;
	number_of_forms++;
	forms_list[number_of_forms] = liquide1;
	number_of_forms++;
	verre1->setAnim(*animation1);
	liquide1->setAnim(*animation1);
	
	Verre *verre2 = new Verre(heightGlass, rayBottomGlass, rayTopGlass);
	//Verre(double hei, double rayB, double rayT)
	Liquide *liquide2 = new Liquide(heightSubGlass, rayBottomSubGlass, rayTopSubGlass, BLUE);
	//Liquide(double height = 1.0, double rayBottom = 0.5, double rayTop = 1, Color co);
	forms_list[number_of_forms] = verre2;
	number_of_forms++;
	forms_list[number_of_forms] = liquide2;
	number_of_forms++;
	verre2->setAnim(*animation2);
	liquide2->setAnim(*animation2);

	Verre *verre3 = new Verre(heightGlass, rayBottomGlass, rayTopGlass);
	//Verre(double hei, double rayB, double rayT)
	Liquide *liquide3 = new Liquide(heightSubGlass, rayBottomSubGlass, rayTopSubGlass, BLUE);
	//Liquide(double height = 1.0, double rayBottom = 0.5, double rayTop = 1, Color co);
	forms_list[number_of_forms] = verre3;
	number_of_forms++;
	forms_list[number_of_forms] = liquide3;
	number_of_forms++;
	verre3->setAnim(*animation3);
	liquide3->setAnim(*animation3);

	Verre *verre4 = new Verre(heightGlass, rayBottomGlass, rayTopGlass);
	//Verre(double hei, double rayB, double rayT)
	Liquide *liquide4 = new Liquide(heightSubGlass, rayBottomSubGlass, rayTopSubGlass, BLUE);
	//Liquide(double height = 1.0, double rayBottom = 0.5, double rayTop = 1, Color co);
	forms_list[number_of_forms] = verre4;
	number_of_forms++;
	forms_list[number_of_forms] = liquide4;
	number_of_forms++;
	verre4->setAnim(*animation4);
	liquide4->setAnim(*animation4);


	Verre *verre5 = new Verre(heightGlass, rayBottomGlass, rayTopGlass);
	//Verre(double hei, double rayB, double rayT)
	Liquide *liquide5 = new Liquide(heightSubGlass, rayBottomSubGlass, rayTopSubGlass, BLUE);
	//Liquide(double height = 1.0, double rayBottom = 0.5, double rayTop = 1, Color co);
	forms_list[number_of_forms] = verre5;
	number_of_forms++;
	forms_list[number_of_forms] = liquide5;
	number_of_forms++;
	verre5->setAnim(*animation5);
	liquide5->setAnim(*animation5);

	Verre *verre6 = new Verre(heightGlass, rayBottomGlass, rayTopGlass);
	//Verre(double hei, double rayB, double rayT)
	Liquide *liquide6 = new Liquide(heightSubGlass, rayBottomSubGlass, rayTopSubGlass, BLUE);
	//Liquide(double height = 1.0, double rayBottom = 0.5, double rayTop = 1, Color co);
	forms_list[number_of_forms] = verre6;
	number_of_forms++;
	forms_list[number_of_forms] = liquide6;
	number_of_forms++;
	verre6->setAnim(*animation6);
	liquide6->setAnim(*animation6);

	Verre *verre7 = new Verre(heightGlass, rayBottomGlass, rayTopGlass);
	//Verre(double hei, double rayB, double rayT)
	Liquide *liquide7 = new Liquide(heightSubGlass, rayBottomSubGlass, rayTopSubGlass, BLUE);
	//Liquide(double height = 1.0, double rayBottom = 0.5, double rayTop = 1, Color co);
	forms_list[number_of_forms] = verre7;
	number_of_forms++;
	forms_list[number_of_forms] = liquide7;
	number_of_forms++;
	verre7->setAnim(*animation7);
	liquide7->setAnim(*animation7);


	Verre *verre8 = new Verre(heightGlass, rayBottomGlass, rayTopGlass);
	//Verre(double hei, double rayB, double rayT)
	Liquide *liquide8 = new Liquide(heightSubGlass, rayBottomSubGlass, rayTopSubGlass, BLUE);
	//Liquide(double height = 1.0, double rayBottom = 0.5, double rayTop = 1, Color co);
	forms_list[number_of_forms] = verre8;
	number_of_forms++;
	forms_list[number_of_forms] = liquide8;
	number_of_forms++;
	verre8->setAnim(*animation8);
	liquide8->setAnim(*animation8);

	Verre *verre9 = new Verre(heightGlass, rayBottomGlass, rayTopGlass);
	//Verre(double hei, double rayB, double rayT)
	Liquide *liquide9 = new Liquide(heightSubGlass, rayBottomSubGlass, rayTopSubGlass, BLUE);
	//Liquide(double height = 1.0, double rayBottom = 0.5, double rayTop = 1, Color co);
	forms_list[number_of_forms] = verre9;
	number_of_forms++;
	forms_list[number_of_forms] = liquide9;
	number_of_forms++;
	verre9->setAnim(*animation9);
	liquide9->setAnim(*animation9);


	Verre *verre10 = new Verre(heightGlass, rayBottomGlass, rayTopGlass);
	//Verre(double hei, double rayB, double rayT)
	Liquide *liquide10 = new Liquide(heightSubGlass, rayBottomSubGlass, rayTopSubGlass, BLUE);
	//Liquide(double height = 1.0, double rayBottom = 0.5, double rayTop = 1, Color co);
	forms_list[number_of_forms] = verre10;
	number_of_forms++;
	forms_list[number_of_forms] = liquide10;
	number_of_forms++;
	verre10->setAnim(*animation10);
	liquide10->setAnim(*animation10);
	

	
	// PERSON 1
	
	// jambe droite
	Animation *animationJambeGauchePer1 = new Animation(0.5, 0.5, Vector(0, 0, 0), Vector(0.1, 0.1, 0.1), Point(-20, -10, 20));
	Parallelepipede *jambeDroitePer1 = new Parallelepipede(3, 3, 9, BLUE);
	//Parallelepipede(double len, double wid, double hei, Color co)
	forms_list[number_of_forms] = jambeDroitePer1;
	number_of_forms++;
	jambeDroitePer1->setAnim(*animationJambeGauchePer1);

	// jambe gauche
	Animation *animationJambeDroitePer1 = new Animation(0.5, 0.5, Vector(0, 0, 0), Vector(0.1, 0.1, 0.1), Point(-20, -10, 15));
	Parallelepipede *jambeGauchePer1 = new Parallelepipede(3, 3, 9, BLUE);
	//Parallelepipede(double len, double wid, double hei, Color co)
	forms_list[number_of_forms] = jambeGauchePer1;
	number_of_forms++;
	jambeGauchePer1->setAnim(*animationJambeDroitePer1);

	// bassin
	Animation *animationBassinPer1 = new Animation(0.5, 0.5, Vector(0, 0, 0), Vector(0.1, 0.1, 0.1), Point(-20, -1, 15));
	Parallelepipede *bassinPer1 = new Parallelepipede(3, 8, 3, Color(0.3, 0, 0));
	//Parallelepipede(double len, double wid, double hei, Color co)
	forms_list[number_of_forms] = bassinPer1;
	number_of_forms++;
	bassinPer1->setAnim(*animationBassinPer1);

	// tronc
	Animation *animationTroncPer1 = new Animation(0.5, 0.5, Vector(0, 0, 0), Vector(0.1, 0.1, 0.1), Point(-20, 2, 15));
	Parallelepipede *troncPer1 = new Parallelepipede(3, 8, 10, WHITE);
	//Parallelepipede(double len, double wid, double hei, Color co)
	forms_list[number_of_forms] = troncPer1;
	number_of_forms++;
	troncPer1->setAnim(*animationTroncPer1);

	// bras gauche
	Animation *animationBrasGauchePer1 = new Animation(0.5, 0.5, Vector(0, 0, 0), Vector(0.1, 0.1, 0.1), Point(-20, 3, 13));
	Parallelepipede *brasGauchePer1 = new Parallelepipede(3, 2, 9, Color(0.9, 0.8, 0));
	//Parallelepipede(double len, double wid, double hei, Color co)
	forms_list[number_of_forms] = brasGauchePer1;
	number_of_forms++;
	brasGauchePer1->setAnim(*animationBrasGauchePer1);

	// bras droit
	Animation *animationBrasDroitPer1 = new Animation(0.5, 0.5, Vector(0, 0, 0), Vector(0.1, 0.1, 0.1), Point(-20, 3, 23));
	Parallelepipede *brasDroitPer1 = new Parallelepipede(3, 2, 9, Color(0.9, 0.8, 0));
	//Parallelepipede(double len, double wid, double hei, Color co)
	forms_list[number_of_forms] = brasDroitPer1;
	number_of_forms++;
	brasDroitPer1->setAnim(*animationBrasDroitPer1);
	
	// tete
	Animation *animationTetePer1 = new Animation(0, 0, Vector(0, 0, 0), Vector(0, 0, 0), Point(-18, 14.5, 19.5));
	Sphere *tetePer1 = new Sphere(2.5, Color(0.9, 0.8, 0));
	//Sphere(double r = 1.0, Color cl = Color());
	forms_list[number_of_forms] = tetePer1;
	number_of_forms++;
	tetePer1->setAnim(*animationTetePer1);
	


	// PERSON 2
	
	// jambe droite
	Animation *animationJambeGauchePer2 = new Animation(0.5, 0.5, Vector(0, 0, 0), Vector(0.1, 0.1, 0.1), Point(-20, -10, 0));
	Parallelepipede *jambeGauchePer2 = new Parallelepipede(3, 3, 9, BLUE);
	//Parallelepipede(double len, double wid, double hei, Color co)
	forms_list[number_of_forms] = jambeGauchePer2;
	number_of_forms++;
	jambeGauchePer2->setAnim(*animationJambeGauchePer2);
	
	// jambe gauche
	Animation *animationJambeDroitePer2 = new Animation(0.5, 0.5, Vector(0, 0, 0), Vector(0.1, 0.1, 0.1), Point(-20, -10, -5));
	Parallelepipede *jambeDroitePer2 = new Parallelepipede(3, 3, 9, BLUE);
	//Parallelepipede(double len, double wid, double hei, Color co)
	forms_list[number_of_forms] = jambeDroitePer2;
	number_of_forms++;
	jambeDroitePer2->setAnim(*animationJambeDroitePer2);

	
	// bassin
	Animation *animationBassinPer2 = new Animation(0.5, 0.5, Vector(0, 0, 0), Vector(0.1, 0.1, 0.1), Point(-20, -1, -5));
	Parallelepipede *bassinPer2 = new Parallelepipede(3, 8, 3, Color(0.3, 0, 0));
	//Parallelepipede(double len, double wid, double hei, Color co)
	forms_list[number_of_forms] = bassinPer2;
	number_of_forms++;
	bassinPer2->setAnim(*animationBassinPer2);

	// tronc
	Animation *animationTroncPer2 = new Animation(0.5, 0.5, Vector(0, 0, 0), Vector(0.1, 0.1, 0.1), Point(-20, 2, -5));
	Parallelepipede *troncPer2 = new Parallelepipede(3, 8, 10, WHITE);
	//Parallelepipede(double len, double wid, double hei, Color co)
	forms_list[number_of_forms] = troncPer2;
	number_of_forms++;
	troncPer2->setAnim(*animationTroncPer2);

	// bras gauche
	Animation *animationBrasGauchePer2 = new Animation(0.5, 0.5, Vector(0, 0, 0), Vector(0.1, 0.1, 0.1), Point(-20, 3, -7));
	Parallelepipede *brasGauchePer2 = new Parallelepipede(3, 2, 9, Color(0.9, 0.8, 0));
	//Parallelepipede(double len, double wid, double hei, Color co)
	forms_list[number_of_forms] = brasGauchePer2;
	number_of_forms++;
	brasGauchePer2->setAnim(*animationBrasGauchePer2);

	// bras droit
	Animation *animationBrasDroitPer2 = new Animation(0.5, 0.5, Vector(0, 0, 0), Vector(0.1, 0.1, 0.1), Point(-20, 3, 3));
	Parallelepipede *brasDroitPer2 = new Parallelepipede(3, 2, 9, Color(0.9, 0.8, 0));
	//Parallelepipede(double len, double wid, double hei, Color co)
	forms_list[number_of_forms] = brasDroitPer2;
	number_of_forms++;
	brasDroitPer2->setAnim(*animationBrasDroitPer2);

	// tete
	Animation *animationTetePer2 = new Animation(0, 0, Vector(0, 0, 0), Vector(0, 0, 0), Point(-18, 14.5, -0.5));
	Sphere *tetePer2 = new Sphere(2.5, Color(0.9, 0.8, 0));
	//Sphere(double r = 1.0, Color cl = Color());
	forms_list[number_of_forms] = tetePer2;
	number_of_forms++;
	tetePer2->setAnim(*animationTetePer2);

	cout << "Le jeu du WaterPong est installe ! " << endl;
	
}


/***************************************************************************/
/* MAIN Function                                                           */
/***************************************************************************/
int main(int argc, char* args[])
{
	// The window we'll be rendering to
	SDL_Window* gWindow = NULL;

	// OpenGL context
	SDL_GLContext gContext;

	// Start up SDL and create window
	if (!init(&gWindow, &gContext))
	{
		cout << "Failed to initialize!" << endl;
	}
	else
	{
		// Main loop flag
		bool quit = false;
		Uint32 current_time, previous_time, elapsed_time;

		// Event handler
		SDL_Event event;
		
		// Camera position
		Point camera_position(0, 0.0, 3.0);

		
		// Create here specific forms and add them to the list...
		// Don't forget to update the actual number_of_forms !
		
		/////////////////////////////////////////////
		///////////////	FORMS	/////////////////////
		/////////////////////////////////////////////
		generateScene();
		

		// Get first "current time"
		previous_time = SDL_GetTicks();
		// While application is running
		while (!quit)
		{
			// Handle events on queue
			while (SDL_PollEvent(&event) != 0)
			{
				int x = 0, y = 0;
				SDL_Keycode key_pressed = event.key.keysym.sym;

				switch (event.type)
				{
					// User requests quit
				case SDL_QUIT:
					quit = true;
					break;
				case SDL_KEYDOWN:
					// Handle key pressed with current mouse position
					SDL_GetMouseState(&x, &y);

					switch (key_pressed)
					{
						// Quit the program when 'q' or Escape keys are pressed
					case SDLK_q:
					case SDLK_ESCAPE:
						quit = true;
						break;

					default:
						break;
					}
					break;
				default:
					break;
				}
			}

			// Update the scene
			current_time = SDL_GetTicks(); // get the elapsed time from SDL initialization (ms)
			elapsed_time = current_time - previous_time;
			if (elapsed_time > ANIM_DELAY)
			{
				previous_time = current_time;
				update(forms_list, 1e-3 * elapsed_time); // International system units : seconds
			}

			// Render the scene
			render(forms_list, camera_position);

			// Update window screen
			SDL_GL_SwapWindow(gWindow);
		}
	}

	// Free resources and close SDL
	close(&gWindow);

	return 0;
}

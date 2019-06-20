#include <iostream>
#include <cmath>

//Using SDL, SDL OpenGL, GLEW
#include <SDL.h>
#include <gl\glew.h>  // glu.h included
#include <SDL_opengl.h>
#include <vector>

// Module for space geometry
#include "geometry.h"
// Module for generating and rendering forms
#include "forms.h"
#include "Project_App3\component.h"
#include "Project_App3\scene.h"
#include "Project_App3\mainScene.h"
#include "Project_App3\matrix.h"

using namespace std;


/***************************************************************************/
/* Constants and functions declarations                                    */
/***************************************************************************/
// Screen dimension constants
const int SCREEN_WIDTH = 1200;
const int SCREEN_HEIGHT = 800;

// Animation actualization delay (in ms) => 100 updates per second
const Uint32 ANIM_DELAY = 10;
const float RALENTI = 1; // 1 = pas de ralenti

// Starts up SDL, creates window, and initializes OpenGL
bool init(SDL_Window** window, SDL_GLContext* context);

// Initializes matrices and clear color
bool initGL();

// Updating forms for animation
void update(shared_ptr<Scene> scene, double delta_t);

// Renders scene to the screen
const void render(shared_ptr<Scene> scene);

// Camera rotation
void cameraRotation(const Vector3 &cam_pos, double phi, double theta, double rho, Vector3& outAbsPos);

// Frees media and shuts down SDL
void close(SDL_Window** window);

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

void update(shared_ptr<Scene> scene, double delta_t)
{
	// Update the list of forms
	for (const auto& component : scene->getComponents())
	{
		component->update(delta_t);
	}
}

const void render(shared_ptr<Scene> scene)
{
	// Clear color buffer and Z-Buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Initialize Modelview Matrix
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// Set the camera position and parameters
	Vector3 absPos;
	cameraRotation(scene->camera.target, scene->camera.phi * M_PI / 180.0, scene->camera.theta * M_PI / 180.0, scene->camera.rho, absPos);
	scene->camera.position = absPos;

	// View matrix
	double vm[16], pm[16];
	glGetDoublev(GL_MODELVIEW_MATRIX, vm);
	glGetDoublev(GL_PROJECTION_MATRIX, pm);
	Matrix4 viewMatrix = Matrix4(vm);
	Matrix4 projectionMatrix = Matrix4(pm);
	scene->camera.viewMatrix = viewMatrix;
	scene->camera.projectionMatrix = projectionMatrix;


	// Isometric view
	//glRotated(-45, 0, 1, 0);
	//glRotated(30, 1, 0, -1);

	//glScaled(0.9, 0.9, 0.9);

	// Render the list of forms
	for (const auto& component : scene->getComponents())
	{
		glPushMatrix(); // Preserve the camera viewing point for further forms
		component->getForm()->render();
		glPopMatrix(); // Restore the camera viewing point for next object
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

void cameraRotation(const Vector3 &cam_pos, double phi, double theta, double rho, Vector3& outAbsPos)
{

	outAbsPos = Vector3(rho * sin(phi) * cos(theta) + cam_pos.x, rho * cos(phi), rho * sin(phi) * sin(theta) + cam_pos.z);
	
	gluLookAt(outAbsPos.x, outAbsPos.y, outAbsPos.z,
		cam_pos.x, cam_pos.y, cam_pos.z, //Position where to look at
		0.0, 1.0, 0.0); // Position of vectors
		
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

		// Initialize the scene
		shared_ptr<Scene> scene = make_shared<MainScene>();
		scene->screen.width = SCREEN_WIDTH;
		scene->screen.height = SCREEN_HEIGHT;
		scene->setup();

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

				case SDL_MOUSEWHEEL:
					if (event.wheel.y > 0) // scroll up
					{
						scene->mouse.wheel = 1;
					}
					else if (event.wheel.y < 0) // scroll down
					{
						scene->mouse.wheel = -1;
					}
					break;

				case SDL_MOUSEMOTION:
					if (event.motion.xrel > 0)
					{
						scene->mouse.motionX = 1;
					}
					if (event.motion.xrel < 0)
					{
						scene->mouse.motionX = -1;
					}
					if (event.motion.yrel > 0)
					{
						scene->mouse.motionY = 1;
					}
					if (event.motion.yrel < 0)
					{
						scene->mouse.motionY = -1;
					}
					break;

				case SDL_MOUSEBUTTONDOWN:
					//do whatever you want to do after a mouse button was pressed,
					// e.g.:
					if (event.button.button == SDL_BUTTON_LEFT) {
						scene->mouse.leftButtonPressed = true;
					}
					else if (event.button.button == SDL_BUTTON_RIGHT) {
						scene->mouse.rightButtonPressed = true;
					}
					else if (event.button.button == SDL_BUTTON_MIDDLE) {
						scene->mouse.middleButtonPressed = true;
					}
					break;

				case SDL_MOUSEBUTTONUP:
					//do whatever you want to do after a mouse button was pressed,
					// e.g.:
					if (event.button.button == SDL_BUTTON_LEFT) {
						scene->mouse.leftButtonPressed = false;
						scene->mouse.leftButtonReleased = true;
					}
					else if (event.button.button == SDL_BUTTON_RIGHT) {
						scene->mouse.rightButtonPressed = false;
						scene->mouse.rightButtonReleased = true;
					}
					else if (event.button.button == SDL_BUTTON_MIDDLE) {
						scene->mouse.middleButtonPressed = false;
						scene->mouse.middleButtonReleased = true;
					}
					break;


				case SDL_QUIT:
					quit = true;
					break;
				case SDL_KEYDOWN:
					// Handle key pressed with current mouse position
					SDL_GetMouseState(&x, &y);

					switch (key_pressed)
					{

						// Reset the view when 'r' is pressed
						case SDLK_r:
							scene->camera.position = Vector3(0, 0, 0);
							scene->camera.phi = 90.0;
							scene->camera.theta = 45.0;
							scene->camera.rho = 4.0;
							break;

							// Modes
						case SDLK_1:
							scene->keyboard.oneNumericButtonPressed = true;
							break;

						case SDLK_2:
							scene->keyboard.twoNumericButtonPressed = true;
							break;

						case SDLK_3:
							scene->keyboard.threeNumericButtonPressed = true;
							break;

						case SDLK_4:
							scene->keyboard.fourNumericButtonPressed = true;
							break;

						case SDLK_5:
							scene->keyboard.fiveNumericButtonPressed = true;
							break;

						case SDLK_6:
							scene->keyboard.sixNumericButtonPressed = true;
							break;

						case SDLK_c:
							if (!scene->keyboard.cameraBalleView)
							{
								scene->keyboard.cameraBalleView = true;
							}
							else
							{
								scene->keyboard.cameraBalleView = false;
							}
							break;



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

			// Mouse position to scene
			SDL_GetMouseState(&scene->mouse.posX, &scene->mouse.posY);

			// Raycast
			double x1, y1, z1, x2, y2, z2;
			double matModelView[16], matProjection[16];
			int viewport[4];
			glGetDoublev(GL_MODELVIEW_MATRIX, matModelView);
			glGetDoublev(GL_PROJECTION_MATRIX, matProjection);
			glGetIntegerv(GL_VIEWPORT, viewport);
			double winX = (double) scene->mouse.posX;
			double winY = viewport[3] - (double) scene->mouse.posY;
			gluUnProject(winX, winY, 0.0, matModelView, matProjection,
				viewport, &x1, &y1, &z1);
			gluUnProject(winX, winY, 1.0, matModelView, matProjection,
				viewport, &x2, &y2, &z2);
			scene->camera.raycastStart = Vector3(x1, y1, z1);
			scene->camera.raycastEnd = Vector3(x2, y2, z2);

			// Update the scene
			current_time = SDL_GetTicks(); // get the elapsed time from SDL initialization (ms)
			elapsed_time = current_time - previous_time;
			if (elapsed_time > ANIM_DELAY)
			{
				previous_time = current_time;

				double delta_t = 1e-3 * elapsed_time;

				// Raise update event in scene
				scene->update(delta_t);

				// Update the scene objects
				update(scene, delta_t); // International system units : seconds


			}

			// Reset scene events
			scene->mouse.rightButtonReleased = false;
			scene->mouse.leftButtonReleased = false;
			scene->mouse.middleButtonReleased = false;
			scene->mouse.wheel = 0;


			// Render the scene
			render(scene);

			// Update window screen
			SDL_GL_SwapWindow(gWindow);
		}
	}

	// Free resources and close SDL
	close(&gWindow);

	return 0;
}

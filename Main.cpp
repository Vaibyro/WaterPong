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
const void render(shared_ptr<Scene> scene, const Point& cam_pos);

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

const void render(shared_ptr<Scene> scene, const Point& cam_pos)
{
	// Clear color buffer and Z-Buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Initialize Modelview Matrix
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// Set the camera position and parameters
	gluLookAt(cam_pos.x, cam_pos.y, cam_pos.z, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

	// Isometric view
	//glRotated(-45, 0, 1, 0);
	//glRotated(30, 1, 0, -1);

	//glScaled(0.05, 0.05, 0.05);

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
		Point camera_position(0, 0.0, 5.0);

		// Initialize the scene
		shared_ptr<Scene> scene = make_shared<MainScene>();
		scene->screenx = SCREEN_WIDTH;
		scene->screeny = SCREEN_HEIGHT;
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

			// Mouse position
			int x = 0, y = 0;
			SDL_GetMouseState(&scene->mouseposx, &scene->mouseposy);

			// Update the scene
			current_time = SDL_GetTicks(); // get the elapsed time from SDL initialization (ms)
			elapsed_time = current_time - previous_time;
			if (elapsed_time > ANIM_DELAY)
			{
				previous_time = current_time;

				double delta_t = 1e-3 * elapsed_time;

				// Update the scene objects
				update(scene, delta_t); // International system units : seconds

				// Raise update event in scene
				scene->update(delta_t);
			}

			// Render the scene
			render(scene, camera_position);

			// Update window screen
			SDL_GL_SwapWindow(gWindow);
		}
	}

	// Free resources and close SDL
	close(&gWindow);

	return 0;
}

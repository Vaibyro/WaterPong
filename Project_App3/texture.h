#pragma once
#include <iostream> 
#include <string> 
#include <gl\glew.h>
#include <SDL_opengl.h>
#include <SDL.h>

using namespace std;

class Texture2D
{
private:
	string path;
	unsigned char * data;
	int width;
	int height;
	GLuint tex;
	bool loaded;
public:


	Texture2D() { loaded = false; };
	Texture2D(string filename) : Texture2D() { load(filename); };
	void load(string filename);
	unsigned char * getData() { return data; };
	int getWidth() { return width; };
	int getHeight() { return height; };
	bool isLoaded() { return loaded; };
};

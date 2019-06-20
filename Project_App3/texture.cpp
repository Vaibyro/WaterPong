#include "texture.h"



void Texture2D::load(string filename) 
{
#pragma warning(disable:4996)
	int i;
	const char* constCharFilename = &filename[0];

	FILE* f = fopen(constCharFilename, "rb");
	unsigned char info[54];
	fread(info, sizeof(unsigned char), 54, f); // read the 54-byte header

	// extract image height and width from header
	width = *(int*)&info[18];
	height = *(int*)&info[22];

	int size = 3 * width * height;
	unsigned char* bmp = new unsigned char[size]; // allocate 3 bytes per pixel
	fread(bmp, sizeof(unsigned char), size, f); // read the rest of the data at once
	fclose(f);

	for (i = 0; i < size; i += 3)
	{
		unsigned char tmp = bmp[i];
		bmp[i] = bmp[i + 2];
		bmp[i + 2] = tmp;
	}

	data = bmp;
	path = filename;
	loaded = true;

	cout << "[INFO] Texture [" << filename << "] chargee." << endl;
}
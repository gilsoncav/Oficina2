#pragma once

#include "SDL.h"
#include "SDL_image.h"

class Cursor {
private:
	int x, y;
	SDL_Surface *primaria;
	SDL_Surface *cursor;
	SDL_Rect src, dst;
public:
	Cursor(int xMouse, int yMouse, SDL_Surface *surface);
	void atual(int xMouse, int yMouse);
	void draw();
};
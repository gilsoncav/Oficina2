#include "Cursor.h"

Cursor::Cursor(int xMouse, int yMouse, SDL_Surface *surface)
{
	SDL_ShowCursor(SDL_DISABLE);
	primaria = surface;
	this->atual(xMouse, yMouse);

	SDL_Surface *aux = IMG_Load("imagens/cursor.png");
	cursor = SDL_DisplayFormatAlpha(aux);
	SDL_FreeSurface(aux);

	src.x = src.y = 0;
	src.w = src.h = 48;
}

void Cursor::atual(int xMouse, int yMouse)
{
	x = xMouse;
	y = yMouse;
	dst.x = x; dst.y = y;
	dst.h = dst.w = 48;
}

void Cursor::draw()
{
	SDL_BlitSurface(cursor, &src, primaria, &dst);
}
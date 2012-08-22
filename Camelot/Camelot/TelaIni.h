#pragma once

#include "assets.h"

#include "SDL.h"
#include "SDL_ttf.h"
#include "SDL_image.h"

class TelaIni
{
private:
	SDL_Surface* primary;
	SDL_Surface* fundo;
	SDL_Rect retOri, retDest;
	SDL_Event evento;
	void texto(SDL_Surface *screen, char *texto, char *nome_fonte, int tamanho, int x, int y, Uint8 r, Uint8 g, Uint8 b);
public:
	TelaIni(SDL_Surface* Primary);
	bool abrir();
};
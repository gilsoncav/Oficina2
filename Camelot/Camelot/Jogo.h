#pragma once

#include "SDL.h"
#include "SDL_ttf.h"
#include "SDL_image.h"
#include "SDL_mixer.h"

#include "assets.h"
#include "Fase.h"
#include "TelaIni.h"

class Jogo
{
private:
	Fase *fase;
	TelaIni *telaIni;
public:
	SDL_Surface* primary;
public:
	Jogo();
	void run();
	void initSDL();
};
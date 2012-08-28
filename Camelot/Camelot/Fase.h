#pragma once

#include "assets.h"
#include "Cursor.h"

#include "SDL.h"
#include "SDL_ttf.h"
#include "SDL_image.h"
#include "SDL_mixer.h"

class Fase
{
private:
	SDL_Surface *primaria;
	SDL_Surface *fundo;
	SDL_Surface *deckPerso;
	SDL_Surface *deckPersogran;
	SDL_Event evento;
	SDL_Rect src, dst;
	SDL_Rect clickDeck, clickCards;

	Cursor *cursor;

	int status;
	int fps;
	int atualTime;
	int tempo;
	int posDeckPerso;
	int posCardTer;
	int posCamelot[6];
	int posCornwall[6];
	int posPerilousForest[6];
	bool exibirgran;
	bool escolhacard;
	bool mudarPosCard;
public:
	Fase(SDL_Surface *Primaria);
	bool run();
	int getStatus();
private:
	void draw();
	void atual();
	void texto(SDL_Surface *screen, char *texto, char *nome_fonte, int tamanho, int x, int y, Uint8 r, Uint8 g, Uint8 b);
};
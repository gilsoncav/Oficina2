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
	// Referência ao Deck de personagens em tamanho pequeno. No arquivo de imagem original, elas estão 
	// tiled na horizontal.
	SDL_Surface *deckPerso;
	// Referência ao Deck de personagens em tamanho grande. No arquivo de imagem original, elas estão 
	// tiled na horizontal.
	SDL_Surface *deckPersoGde;
	SDL_Event evento;
	SDL_Rect src, dst;
	SDL_Rect clickDeck, clickCards;

	Cursor *cursor;

	int status;
	int fps;
	int atualTime;
	int tempo;
	// GILSON: ? pelo que entendi, marca a posicao do deck do jogador
	int posDeckPerso;
	// GILSON: flag para indicar se a carta que está no topo do baralho deve ser exibida em tamanho ampliado
	bool exibirGde;
public:
	Fase(SDL_Surface *Primaria);
	bool run();
	int getStatus();
private:
	void draw();
	void atual();
	void texto(SDL_Surface *screen, char *texto, char *nome_fonte, int tamanho, int x, int y, Uint8 r, Uint8 g, Uint8 b);
};
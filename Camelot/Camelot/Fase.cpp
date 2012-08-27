#include <windows.h>
#include <conio.h>
#include <time.h>

#include "Fase.h"

Fase::Fase(SDL_Surface *Primaria)
{
	primaria = Primaria;

	SDL_Surface *aux;

	clickDeck.x = 400; clickDeck.y = 400;
	clickDeck.w = clickCards.w = 84;
	clickDeck.h = clickCards.h = 120;
	clickCards.x = 500; clickCards.y = 400;

	aux = IMG_Load("imagens/mesadejogo.png");
	fundo = SDL_DisplayFormatAlpha(aux);
	SDL_FreeSurface(aux);

	aux = IMG_Load("imagens/persobasicasmin.png");
	deckPerso = SDL_DisplayFormatAlpha(aux);
	SDL_FreeSurface(aux);

	aux = IMG_Load("imagens/persobasicas.png");
	deckPersoGde = SDL_DisplayFormatAlpha(aux);
	SDL_FreeSurface(aux);

	cursor = new Cursor(512, 384, primaria);

	status = 0;
	fps = 10;
	tempo = fps;
	atualTime = 0;
	posDeckPerso = 0;
	exibirGde = false;
}

bool Fase::run()
{
	int i, x, y;

	do
	{
		if (SDL_PollEvent (&evento))
		{
			switch(evento.type)
			{
			case SDL_QUIT:
				return true;
				break;

			case SDL_MOUSEBUTTONDOWN:
				x = evento.button.x;
				y = evento.button.y;
				switch(evento.button.button)
				{
				case SDL_BUTTON_LEFT:
					if ((x >= clickDeck.x) && (x <= (clickDeck.x + clickDeck.w)) &&
						(y >= clickDeck.y) && (y <= (clickDeck.y + clickDeck.h))) {
						posDeckPerso++;
						if (posDeckPerso > 35) posDeckPerso = 35;
					}
					if ((x >= clickCards.x) && (x <= (clickCards.x + clickCards.w)) &&
						(y >= clickCards.y) && (y <= (clickCards.y + clickCards.h))) {
						posDeckPerso = 0;
						exibirGde = false;
					}
					break;
				}

			case SDL_MOUSEMOTION:
				x = evento.motion.x;
				y = evento.motion.y;
				cursor->atual(evento.motion.x, evento.motion.y);
				// GILSON: se o cursor está dentro da área do Deck, altera-se a flag de exibição da imagem grande da carta
				if ((x >= clickCards.x) && (x <= (clickCards.x + clickCards.w)) &&
					(y >= clickCards.y) && (y <= (clickCards.y + clickCards.h))) {
					// Só exibe se o Deck já foi aberto
					if (posDeckPerso > 0)
						exibirGde = true;
				} else {
					exibirGde = false;
				}
				break;

			case SDL_KEYDOWN:
				switch(evento.key.keysym.sym)
				{
				case SDLK_ESCAPE:
					status = 1;
					return true;
					break;
				}
				break;
			}
		}

		if (SDL_GetTicks() >= tempo)
		{
			//this->atual();
			this->draw();

			tempo = SDL_GetTicks() + fps;
		}
	} while (1);

}

int Fase::getStatus()
{
	return status;
}

void Fase::draw()
{
	//char faseatual[3], vidas[2], pontos[6], vasos[3];

	//sprintf(faseatual, "%d", m_numFase);
	//sprintf(vidas, "%d", m_Perso->life());
	//sprintf(pontos, "%d", m_Perso->score());
	//sprintf(vasos, "%d", m_Perso->vasos());
	SDL_BlitSurface(fundo, NULL, primaria, NULL);
	//texto(m_Primary, faseatual, "augie.ttf", 15, 750, 55, 0, 0, 0);
	//texto(m_Primary, vidas, "augie.ttf", 15, 750, 105, 0, 0, 0);
	//texto(m_Primary, pontos, "augie.ttf", 10, 740, 165, 0, 0, 0);
	//texto(m_Primary, vasos, "augie.ttf", 15, 750, 215, 0, 0, 0);
	//SDL_BlitSurface(m_OSPerso, &m_retOriPerso, m_Primary, &m_retDestPerso);

	src.x = src.y = 0;
	src.w = 84; src.h = 120;
	dst.x = 400; dst.y = 400;

	SDL_BlitSurface(deckPerso, &src, primaria, &dst);

	if (posDeckPerso > 0) {
		src.x = posDeckPerso * 84; src.y = 0;
		src.w = 84; src.h = 120;
		dst.x = 500; dst.y = 400;

		SDL_BlitSurface(deckPerso, &src, primaria, &dst);
	}

	// Se for para exibir a imagem da carta do Topo do Deck
	if (exibirGde) {
		src.x = posDeckPerso * 280; src.y = 0;
		src.w = 280; src.h = 400;
		dst.x = 0; dst.y = 0;

		SDL_BlitSurface(deckPersoGde, &src, primaria, &dst);
	}

	cursor->draw();

	if ((SCREEN_FLAGS & SDL_FULLSCREEN) != 0)
		SDL_Flip(primaria);
	else
		SDL_UpdateRect (primaria, 0, 0, 0, 0);
}

void Fase::atual()
{

}

void Fase::texto(SDL_Surface *screen, char *texto, char *nome_fonte, int tamanho, int x, int y, Uint8 r, Uint8 g, Uint8 b)
{
	SDL_Surface *surf;

	TTF_Font *fonte = TTF_OpenFont(nome_fonte, tamanho);
	
	SDL_Color cor;
	cor.r = r;
	cor.g = g;
	cor.b = b;
	
	surf = TTF_RenderText_Solid(fonte, texto, cor);

	SDL_Rect ret_font_dest;
	ret_font_dest.x = x;
	ret_font_dest.y = y;	
	ret_font_dest.h = screen->h;
	ret_font_dest.w = screen->w;
	
	SDL_BlitSurface(surf, NULL, SDL_GetVideoSurface(), &ret_font_dest);

	SDL_FreeSurface(surf);
	
   	TTF_CloseFont(fonte);	
}

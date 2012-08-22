#include <windows.h>
#include <conio.h>

#include "TelaIni.h"

TelaIni::TelaIni(SDL_Surface *Primary)
{
	primary = Primary;
}

bool TelaIni::abrir()
{
	//fundo = IMG_Load("images/telaini.jpg");

	retOri.x = retDest.x = 0;
	retOri.y = retDest.y = 0;
	retOri.w = retDest.w = 1024;
	retOri.h = retDest.h = 768;

	do
	{
		if (SDL_PollEvent (&evento))
		{
			switch(evento.type)
			{
				case SDL_QUIT:
					return false;
					break;

				case SDL_KEYDOWN:
					switch(evento.key.keysym.sym)
					{
						case SDLK_ESCAPE:
							return false;
							break;
					}
					return true;
					break;
			}
		}

		//SDL_BlitSurface(fundo, &retOri, primary, &retDest);
		SDL_FillRect(primary, 0, 0);
		texto(primary, "Áquila Produções", "augie.ttf", 13, 250, 550, 255, 0, 0);
		texto(primary, "Camelot Legends - versão 0.1", "augie.ttf", 12, 200, 565, 255, 0, 0);
		texto(primary, "- 2012 -", "augie.ttf", 10, 280, 580, 255, 0, 0);

		if ((SCREEN_FLAGS & SDL_FULLSCREEN) != 0)
			SDL_Flip(primary);
		else
			SDL_UpdateRect (primary, 0, 0, 0, 0);

	} while (1);

}

void TelaIni::texto(SDL_Surface *screen, char *texto, char *nome_fonte, int tamanho, int x, int y, Uint8 r, Uint8 g, Uint8 b)
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
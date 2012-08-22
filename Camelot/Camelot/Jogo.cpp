#include <windows.h>
#include <conio.h>

#include "Jogo.h"

Jogo::Jogo()
{
	this->initSDL();
}

void Jogo::run()
{
	bool fim;

	fim = false;

	telaIni = new TelaIni(primary);
	while(telaIni->abrir())
	{
		do
		{
			
			fase = new Fase(primary);
			fase->run();
			
			if(fase->getStatus() == 1)
				fim = true;
			
			delete fase;
			fase = NULL;

		} while (!fim);
	}
	
	delete telaIni;
}

void Jogo::initSDL()
{
	SDL_Init (SDL_INIT_VIDEO | SDL_INIT_TIMER);
	atexit (SDL_Quit);
	primary = SDL_SetVideoMode (SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SCREEN_FLAGS);
	ShowCursor(SDL_DISABLE);
	TTF_Init();
	//Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 1, 1024);
}

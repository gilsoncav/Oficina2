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

	aux = IMG_Load("imagens/persobasicas.png");
	deckPersogran = SDL_DisplayFormatAlpha(aux);


	SDL_FreeSurface(aux);

	cursor = new Cursor(512, 384, primaria);

	status = 0;
	fps = 10;
	tempo = fps;
	atualTime = 0;
	posDeckPerso = 0;
	posCardTer = 0;
	exibirgran = false;
	escolhacard = false;
	mudarPosCard = false;

	for(int i=0; i<6; i++){
		posCamelot[i]=-1;
		posCornwall[i]=-1;
		posPerilousForest[i]=-1;
	}
}

bool Fase::run()
{
	int i, x, y;

	do
	{
		if (SDL_PollEvent (&evento))
		{
			for(int i=0; i<5; i++){
				if(posCamelot[i]==-1){
					posCamelot[i] = posCamelot[i+1];
					posCamelot[i+1] = -1;
				}
				if(posCornwall[i]==-1){
					posCornwall[i] = posCornwall[i+1];
					posCornwall[i+1] = -1;
				}
				if(posPerilousForest[i]==-1){
					posPerilousForest[i] = posPerilousForest[i+1];
					posPerilousForest[i+1] = -1;
				}
			}

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
						if(!mudarPosCard)
							posDeckPerso++;
						escolhacard = false;
						if (posDeckPerso > 35) posDeckPerso = 35;
					}
					if ((x >= clickCards.x) && (x <= (clickCards.x + clickCards.w)) &&
						(y >= clickCards.y) && (y <= (clickCards.y + clickCards.h))) {
						//posDeckPerso = 0;
						if(!mudarPosCard)
							escolhacard = true;
						exibirgran = false;
					}
					if ((x >= 371) && (x <=653) &&
						(y >= 86) && (y <= 286) && (escolhacard || mudarPosCard)){
							for(int i=0; i<6; i++){
								if(posCamelot[i]==-1){
									if(escolhacard){
										posCamelot[i]=posDeckPerso;
										escolhacard = false;
										posDeckPerso++;
										break;
									}
									if(mudarPosCard){
										posCamelot[i]=posCardTer;
										mudarPosCard = false;
										break;
									}
								}
							}
							escolhacard = false;
					}else
					if ((x >= 654) && (x <=935) &&
						(y >= 481) && (y <= 681) && (escolhacard || mudarPosCard)){
							for(int i=0; i<6; i++){
								if(posCornwall[i]==-1){
									if(escolhacard){
										posCornwall[i]=posDeckPerso;
										escolhacard = false;
										posDeckPerso++;
										break;
									}
									if(mudarPosCard){
										posCornwall[i]=posCardTer;
										mudarPosCard = false;
										break;
									}
								}
							}
							escolhacard = false;
					}else
					if ((x >= 89) && (x <=371) &&
						(y >= 481) && (y <= 681) && (escolhacard || mudarPosCard)){
							for(int i=0; i<6; i++){
								if(posPerilousForest[i]==-1){
									if(escolhacard){
										posPerilousForest[i]=posDeckPerso;
										escolhacard = false;
										posDeckPerso++;
										break;
									}
									if(mudarPosCard){
										posPerilousForest[i]=posCardTer;
										mudarPosCard = false;
										break;
									}
								}
							}
							escolhacard = false;
					}
					if(!mudarPosCard && !escolhacard)
						for(int i=0; i<6; i++){
							if((x >= 262 + i * src.w) && (x <= 346 + i * src.w) &&
								(y >= 286) && (y <= 406) && posCamelot[i]!=-1){
								mudarPosCard = true;
								posCardTer = posCamelot[i];
								posCamelot[i] = -1;
							}
							if((x >= 545 + i * src.w) && (x <= 629 + i * src.w) &&
								(y >= 681) && (y <= 801) && posCornwall[i]!=-1){
								mudarPosCard = true;
								posCardTer = posCornwall[i];
								posCornwall[i] = -1;
							}
							if((x >= -20 + (i * src.w)) && (x <= 64 + i * src.w) &&
								(y >= 681) && (y <= 801) && posPerilousForest[i]!=-1){
								mudarPosCard = true;
								posCardTer = posPerilousForest[i];
								posPerilousForest[i] = -1;
							}
						}

					break;
				}

			case SDL_MOUSEMOTION:
				cursor->atual(evento.motion.x, evento.motion.y);
				x = evento.motion.x;
				y = evento.motion.y;
				if (x >= clickCards.x && x <= (clickCards.x + clickCards.w) && y >= clickCards.y && y <= (clickCards.y + clickCards.h)){
					if(posDeckPerso > 0)
						exibirgran = true;
				}else{
					exibirgran = false;
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
	for(int i=0; i<6; i++) {
		if (posCamelot[i] > 0){
			src.x = posCamelot[i] * 84; src.y = 0;
			src.w = 84; src.h = 120;
			dst.x = 262 + (i * src.w); dst.y = 286;

			SDL_BlitSurface(deckPerso, &src, primaria, &dst);
		}
		if (posCornwall[i] > 0){
			src.x = posCornwall[i] * 84; src.y = 0;
			src.w = 84; src.h = 120;
			dst.x = 545 + (i * src.w); dst.y = 681;

			SDL_BlitSurface(deckPerso, &src, primaria, &dst);
		}
		if (posPerilousForest[i] > 0){
			src.x = posPerilousForest[i] * 84; src.y = 0;
			src.w = 84; src.h = 120;
			dst.x = -20 + (i * src.w); dst.y = 681;

			SDL_BlitSurface(deckPerso, &src, primaria, &dst);
		}
	}


	if (exibirgran){
		src.x = posDeckPerso * 280; src.y = 0;
		src.w = 280; src.h = 400;
		dst.x = 700; dst.y = 50;
		SDL_BlitSurface(deckPersogran, &src, primaria, &dst);
	}
	if(escolhacard || mudarPosCard){
		texto(primaria, "Posicione a carta em um campo de batalha. ", "augie.ttf", 24, 50, 25, 255, 0, 0);
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

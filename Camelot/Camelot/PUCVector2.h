#pragma once
#include <iostream>
#include <SDL_video.h>

namespace pucjogos {

/************************************************************************
 * Classe para modelar um vetor.  
 * Os angulos sao implementados em graus
 *
 * Gilson Cavalcanti - gilsoncav@blackmuppet.com 
 ************************************************************************/
class PUCVector2
{
public:
	// O modo de funcionamento do vetor. Se é retangular ou Polar.
	enum Modo {RECT, POLAR};

private:
	double _x;
	double _y;
	// Magnitude do vetor
	double _mag;
	// Angulo do vetor
	double _ang;
	// Modo de funcionamento do vetor
	Modo _modo;
	// O sprite associado ao vetor. Alguns metodos fazem acoes com este vetor caso ele nao seja nulo
	SDL_Surface* _surface;
	// Métodos privados para setar valores
	void calcX();
	void calcY();
	void calcMag();
	void calcAng();
public:
	PUCVector2(void);
	// Construtores cujo modo ja seta o valor padrao como RECT
	PUCVector2(double n1, double n2, SDL_Surface* surface = NULL, Modo modo = RECT);
	void Reset(double n1, double n2, Modo modo = RECT);
	~PUCVector2(void);
	double X() const {return _x;}
	double Y() const {return _y;}
	double Mag() const {return _mag;}
	double Ang() const {return _ang;}
	SDL_Surface* Surface() {return _surface;}
	void Surface(SDL_Surface* surface) {_surface = surface;}
	// Seta o modo do vetor para o modo de operação polar
	void PolarMode();
	// Seta o modo do vetor para o modo de operação de retangulo
	void RectMode();
// Sobrescrevendo operadores
	PUCVector2 operator+(const PUCVector2 b) const;
	PUCVector2 operator-(const PUCVector2 b) const;
	// inverte as coordenadas do vetor
	PUCVector2 operator-() const;
	PUCVector2 operator*(double n) const;
// Sobrescrições "amigas"
	friend PUCVector2 operator*(double n, const PUCVector2 a);
	friend std::ostream & operator<<(std::ostream& os, const PUCVector2 a);
};

} // fim do namespace pucjogos

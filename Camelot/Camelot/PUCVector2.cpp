#include "PUCVector2.h"
#include <cmath>
using std::cout;

namespace pucjogos {
	// constante de conversão de radianos para graus
	const double RAD_TO_DEGREE = 45.0 / atan(1.0);

	// Seta o valor da magnitude baseado no x e y
	void PUCVector2::calcMag() {
		_mag = sqrt(_x*_x + _y*_y);
	}
	// Seta o valor do Angulo baseado no x e y
	void PUCVector2::calcAng() {
		if (_x == 0.0 && _y == 0.0) {
			_ang = 0.0;
		} else {
			_ang = atan2(_y, _x);
		}
	}
	// seta o valor do X baseado na magnitude
	void PUCVector2::calcX() {
		_x = _mag * cos(_ang);
	}
	void PUCVector2::calcY() {
		_y = _mag * sin(_ang);
	}

	// Construtor padrao
	PUCVector2::PUCVector2(void) {
		_x = _y = _mag = _ang = 0.0;
		_modo = RECT;
	}

	PUCVector2::PUCVector2( double n1, double n2, SDL_Surface* surface, Modo modo) {
		Reset(n1, n2, modo);
		Surface(surface);
	}
	void PUCVector2::Reset( double n1, double n2, Modo modo ) {
		if (modo == RECT) {
			_x = n1;
			_y = n2;
			calcMag();
			calcAng();
		} else if (modo == POLAR) {
			_mag = n1;
			_ang = n2 / RAD_TO_DEGREE;
			calcX();
			calcY();
		} else {
			cout << "Parametro de modo do vetor incorreto - setando o valor do vetor para zero";
			_x = _y = _mag = _ang = 0.0;
			modo = RECT;
		}
	}

	// Destrutor da classe
	PUCVector2::~PUCVector2(void) {
	}

	void PUCVector2::PolarMode() {
		_modo = POLAR;
	}

	void PUCVector2::RectMode() {
		_modo = RECT;
	}

	PUCVector2 PUCVector2::operator+( const PUCVector2 b ) const {
		return PUCVector2(_x + b._x, _y + b._x);
	}

	PUCVector2 PUCVector2::operator-( const PUCVector2 b ) const {
		return PUCVector2(_x - b._x, _y - b._y);
	}

	PUCVector2 PUCVector2::operator-() const {
		return PUCVector2(-_x, -_y);
	}

	PUCVector2 PUCVector2::operator*( double n ) const {
		return PUCVector2(n * _x, n * _y);
	}

	PUCVector2 operator*(double n, const PUCVector2 a) {
		return a * n;
	}
	std::ostream& operator<<(std::ostream& os, const PUCVector2 a) {
		if (a._modo == PUCVector2::RECT) {
			os << "[x,y] = " << "[" << a._x << "," << a._y << "]";
		} else if (a._modo == PUCVector2::POLAR) {
			os << "[m,a] = " << "[" << a._mag << "," << a._ang << "]";
		} else {
			os << "ERRO: PUCVector2: Modo do vetor invalido.";
		}
		return os;
	}







} // fim do namespace pucjogos
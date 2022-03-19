#include "Przeszkoda.h"
Przeszkoda::Przeszkoda(int x, int y, int wysokosc, int szerokosc)
{
	this->x = x;
	this->y = y;
	this->wysokosc = szerokosc;
	this->szerokosc = wysokosc;

	co = 1; //1 - przeszkoda
}

Przeszkoda::~Przeszkoda()
{
}

Przeszkoda::Przeszkoda()
{
	x = 0;
	y = 0;
	wysokosc = 0;
	szerokosc = 0;
}

#pragma once
#include "Platforma.h"
Platforma::Platforma(int x, int y, int wysokosc, int szerokosc)
{
	this->x = x;
	this->y = y;
	this->wysokosc = szerokosc;
	this->szerokosc = wysokosc;
	co = 0; //0 = platforma
}

Platforma::~Platforma()
{
}

Platforma::Platforma()
{
	x = 0;
	y = 0;
	wysokosc = 0;
	szerokosc = 0;
}
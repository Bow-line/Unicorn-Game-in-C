#pragma once
#include "Platforma.h"
#include "Przeszkoda.h"

#define MAX_OBJ 100

class Gracz;
union SDL_Event;

class Plansza
{
public:
	Plansza();
	Plansza(int x, int y);
	~Plansza();
	Platforma* platformy;
	Przeszkoda* przeszkody;
	Obiekt obiekty[MAX_OBJ];
	Gracz* gracz;
	int ilosc_platform = 0;
	int ilosc_przeszkod = 0;
	int ilosc_obiektow = 0;
	int licznik = 1;
	float szybkosc;
	int szerokosc, wysokosc;
	Plansza(Platforma *platformy, int ilosc_platform, int szerokosc,int wysokosc);
	void DodajPlatforme(Platforma platforma);

	void DodajPrzeszkode(Przeszkoda przeszkoda);
	void sortPlatformyByY();
	void sortPrzeszkodyByY();
	void sortByY();

	void addPlayer(Gracz *gracz);

	void UpdatePlayer(double delta, SDL_Event& e, int* exit);
	bool KolizjaGracz(Obiekt& o, int x, int y);

	double CalcSpeed(double pixelsPerSecond, double tickCount)
	{
		
		return tickCount * pixelsPerSecond;
	}

private:

};


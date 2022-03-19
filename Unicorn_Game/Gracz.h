#pragma once
#include"SDL2-2.0.10/include/SDL.h"
#include"SDL2-2.0.10/include/SDL_main.h"
inline double scale_v = 60; //skala przyspieszenia

class Gracz
{
public:
	SDL_Surface* wyglad;
	SDL_Surface* wyglad_skok;
	SDL_Surface* wyglad_dash;
	Gracz();
	~Gracz();
	double x, y;
	double v_x = 0; //prêdkoœæ x
	double v_y = 0; //prêdkosc y
	double a_x = 0.2 * scale_v; //przyspieszenie x
	double da_x = 0.3 * scale_v; //opóŸnienie x
	int sizeX = 0;
	int sizeY = 0;
	Gracz(int x, int y, SDL_Surface* wyglad, SDL_Surface* wyglad2, SDL_Surface* wyglad3);
	bool Ruch(SDL_Event &event, double delta);
	int szanse = 3;
	bool zab = false;
	bool przelicznik = false;
	int ilosc_skokow = 0;
	int punkty = 0;
	int punkty_zmienna = 0;
	bool podwojny_skok = false;
	double punkty_kolizji_x[8];
	double punkty_kolizji_y[8];

	double offset_x = 4; //offset na jakim gracz mo¿e byæ kolizyja
	double offset_y = 8;
	double max_v_x = 5 * scale_v; //maksymalna prêdkoœæ x
	double max_v_y = 20 * scale_v; //maksymalna prêdkoœæ y
	double a_g = 0.5 * scale_v; //przepieszenie grawitacyjne
	double jumpStart = 10 * scale_v; //prêdkoœæ y podczas skoku
	bool jumping = false; //czy w powietrzu
	bool jumpKeyDown = false; //czy guzik skoku wciœniêty

	bool ruch_prawo = false;
	bool ruch_prawo_auto = false;
	bool ruch_lewo = false;
	bool ruch_skok = false;
	bool ruch_podwojny = false;
	bool zmiana_trybu = false;
	bool zryw = false;
	bool pauza = false;

	double CalcSpeed(double pixelsPerSecond, double tickCount)
	{

		return tickCount * pixelsPerSecond;
	}
private:

};






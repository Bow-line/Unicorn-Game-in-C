#include "Gracz.h"
#include"SDL2-2.0.10/include/SDL.h"
#include"SDL2-2.0.10/include/SDL_main.h"
bool Gracz::Ruch(SDL_Event& event, double delta)
{
	x += CalcSpeed(v_x, delta);
	y += CalcSpeed(v_y, delta);

	bool czy_ruch = false;
	
	if (ruch_lewo )
	{
		v_x -= a_x;
		czy_ruch = true;
	}
	if (ruch_prawo )
	{
		v_x += a_x;
		czy_ruch = true;
		punkty++;
	}
	if (ruch_prawo_auto )
	{
		v_x += a_x*(5*delta);
		czy_ruch = true;
		punkty ++;
		
	}
	if (zryw )
	{
		v_x += 3 * a_x;
		czy_ruch = true;
	}
	


	


	if (event.type == SDL_KEYDOWN && pauza==false)
	{
		if (event.key.keysym.sym == SDLK_LEFT && zmiana_trybu == false)
		{
			ruch_lewo = true;
			
		}
		if (event.key.keysym.sym == SDLK_RIGHT && zmiana_trybu == false)
		{
			ruch_prawo = true;
		}
		if (event.key.keysym.sym == SDLK_UP && podwojny_skok && !jumping && !jumpKeyDown && ilosc_skokow < 2 && zmiana_trybu == false)
		{
			ilosc_skokow++;
			jumping = true;
			jumpKeyDown = true;
			v_y = -jumpStart;
		}
		if (event.key.keysym.sym == SDLK_UP && podwojny_skok && jumping && !jumpKeyDown && ilosc_skokow < 2 && zmiana_trybu == false)
		{
			ilosc_skokow++;
			jumping = true;
			jumpKeyDown = true;
			v_y = -jumpStart;
		}
	

	}


	if (event.type == SDL_KEYUP && pauza == false)
	{
		if (event.key.keysym.sym == SDLK_LEFT && zmiana_trybu == false)
		{
			ruch_lewo = false;

		}
		if (event.key.keysym.sym == SDLK_RIGHT && zmiana_trybu == false)
		{
			ruch_prawo = false;
		}
		if (event.key.keysym.sym == SDLK_UP && zmiana_trybu == false)
		{
			jumpKeyDown = false;
			podwojny_skok = false;
		}
		if (event.key.keysym.sym == SDLK_UP && !podwojny_skok && zmiana_trybu == false)
		{
			jumpKeyDown = false;
			podwojny_skok = true;
		}
		if (event.key.keysym.sym == SDLK_z && zmiana_trybu == true)
		{
			jumpKeyDown = false;
			podwojny_skok = false;
		}
		if (event.key.keysym.sym == SDLK_z && !podwojny_skok && zmiana_trybu == true)
		{
			jumpKeyDown = false;
			podwojny_skok = true;
		}
	}

	if (v_x > max_v_x) v_x = max_v_x;
	if (v_x < -max_v_x) v_x = -max_v_x; // Limit prêdkoœci
	if (v_y < -max_v_y) v_y = -max_v_y;

	v_y += a_g;

	if (!czy_ruch)
	{
		if (v_x < 0) v_x += da_x;
		if (v_x > 0) v_x -= da_x;
		if (v_x > 0 && v_x < da_x) v_x = 0;
		if (v_x < 0 && v_x > -da_x) v_x = 0;
	}
	

	return czy_ruch;
}

Gracz::Gracz()
{
	this->x = 0;
	y = 0;
}
Gracz::Gracz(int x, int y, SDL_Surface* wyglad, SDL_Surface* wyglad2, SDL_Surface* wyglad3)
{
	this->wyglad = wyglad;
	this->wyglad_skok = wyglad2;
	this->wyglad_dash = wyglad3;

	this->wyglad->format->Amask = 0xFF000000;
	this->wyglad->format->Ashift = 24;

	this->x = x;
	this->y = y;
	this->sizeX = wyglad->w;
	this->sizeY = wyglad->h;
	this->v_y = 2;

	punkty_kolizji_x[0] = 0;
	punkty_kolizji_x[1] = sizeX;
	punkty_kolizji_x[2] = 0;
	punkty_kolizji_x[3] = sizeX;

	punkty_kolizji_x[4] = 0;
	punkty_kolizji_x[5] = 0;
	punkty_kolizji_x[6] = sizeX;
	punkty_kolizji_x[7] = sizeX;

	punkty_kolizji_y[0] = 0;
	punkty_kolizji_y[1] = 0;
	punkty_kolizji_y[2] = sizeY;
	punkty_kolizji_y[3] = sizeY;

	punkty_kolizji_y[4] = 0;
	punkty_kolizji_y[5] = sizeY;
	punkty_kolizji_y[6] = 0;
	punkty_kolizji_y[7] = sizeY;
}

Gracz::~Gracz()
{
}
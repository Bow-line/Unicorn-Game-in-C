#include "Grafika.h"
#include "Gracz.h"
#include "Plansza.h"
#include"SDL2-2.0.10/include/SDL.h"
#include"SDL2-2.0.10/include/SDL_main.h"

void Grafika::UpdateSurface(SDL_Surface* surf)
{
	screen = surf;
}

void Grafika::DrawString(int x, int y, const char* text
) {
	int px, py, c;
	SDL_Rect s, d;
	s.w = 8;
	s.h = 8;
	d.w = 8;
	d.h = 8;
	while (*text) {
		c = *text & 255;
		px = (c % 16) * 8;
		py = (c / 16) * 8;
		s.x = px;
		s.y = py;
		d.x = x;
		d.y = y;
		SDL_BlitSurface(charset, &s, screen, &d);
		x += 8;
		text++;
	};
};


// narysowanie na ekranie screen powierzchni sprite w punkcie (x, y)
// (x, y) to punkt úrodka obrazka sprite na ekranie
// draw a surface sprite on a surface screen in point (x, y)
// (x, y) is the center of sprite on screen
void Grafika::DrawSurface(SDL_Surface * sprite, int x, int y) {
	SDL_Rect dest;
	dest.x = x - sprite->w / 2;
	dest.y = y - sprite->h / 2;
	dest.w = sprite->w;
	dest.h = sprite->h;
	SDL_BlitSurface(sprite, NULL, screen, &dest);
};


// rysowanie pojedynczego pixela
// draw a single pixel
void Grafika::DrawPixel(SDL_Surface * surface, int x, int y, Uint32 color) {
	int bpp = surface->format->BytesPerPixel;
	if (y < SCREEN_HEIGHT && y > 0 && x > 0 && x < SCREEN_WIDTH)
	{
		Uint8* p = (Uint8*)surface->pixels + y * surface->pitch + x * bpp;
		*(Uint32*)p = color;
	}

};


// rysowanie linii o d≥ugoúci l w pionie (gdy dx = 0, dy = 1) 
// bπdü poziomie (gdy dx = 1, dy = 0)
// draw a vertical (when dx = 0, dy = 1) or horizontal (when dx = 1, dy = 0) line
void Grafika::DrawLine(int x, int y, int l, int dx, int dy, Uint32 color) {
	for (int i = 0; i < l; i++) {
		DrawPixel(screen, x, y, color);
		x += dx;
		y += dy;
	};
};


// rysowanie prostokπta o d≥ugoúci bokÛw l i k
// draw a rectangle of size l by k
void Grafika::DrawRectangle(int x, int y, int l, int k,
	Uint32 outlineColor, Uint32 fillColor) {
	int i;
	DrawLine(x, y, k, 0, 1, outlineColor);
	DrawLine(x + l - 1, y, k, 0, 1, outlineColor);
	DrawLine(x, y, l, 1, 0, outlineColor);
	DrawLine(x, y + k - 1, l, 1, 0, outlineColor);
	for (i = y + 1; i < y + k - 1; i++)
		DrawLine(x + 1, i, l - 2, 1, 0, fillColor);
};
void Grafika::RysujGracza(Gracz & gracz)
{

	if (gracz.jumping)
	{
		DrawSurface(gracz.wyglad_skok, (gracz.x + gracz.sizeX / 2 - camera.x), (gracz.y + gracz.sizeY / 2 - camera.y));
	}else
	DrawSurface(gracz.wyglad, (gracz.x + gracz.sizeX/2 - camera.x), (gracz.y + gracz.sizeY/2 - camera.y));
}
void Grafika::RysujPlansze(Plansza & plansza)
{
	if (plansza.gracz->x > plansza.szerokosc - SCREEN_WIDTH)
	{
		plansza.gracz->x = -1000;
	}
	for (int i = 0; i < plansza.ilosc_przeszkod; i++)
	{
		DrawRectangle((plansza.przeszkody[i].x - camera.x), (plansza.przeszkody[i].y - camera.y), plansza.przeszkody[i].szerokosc, plansza.przeszkody[i].wysokosc, czerwony, czarny);
	}
	for (int i = 0; i < plansza.ilosc_platform; i++)
	{
		DrawRectangle((plansza.platformy[i].x - camera.x), (plansza.platformy[i].y - camera.y), plansza.platformy[i].szerokosc, plansza.platformy[i].wysokosc, niebieski, zielony);
	}

	RysujGracza(*plansza.gracz);
}

Grafika::Grafika(SDL_Surface* screen, SDL_Surface* charset)
{
	this->screen = screen;
	this->charset = charset;
}

Grafika::~Grafika()
{
}
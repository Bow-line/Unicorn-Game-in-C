#include "Plansza.h"
#include "Gracz.h"


void Plansza::DodajPlatforme(Platforma platforma)
{
	Platforma* temp = new Platforma[ilosc_platform + 1];
	for (int i = 0; i < ilosc_platform; i++)
	{
		temp[i] = platformy[i];
	}
	temp[ilosc_platform] = platforma;
	ilosc_platform++;
	delete[] platformy;
	platformy = new Platforma[ilosc_platform];
	for (int i = 0; i < ilosc_platform; i++)
	{
		platformy[i] = temp[i];
	}
	obiekty[ilosc_obiektow] = platformy[ilosc_platform - 1];
	if(ilosc_obiektow < MAX_OBJ)
		ilosc_obiektow++;
	sortByY();
	sortPlatformyByY();

}
void Plansza::DodajPrzeszkode(Przeszkoda przeszkoda)
{
	Przeszkoda* temp = new Przeszkoda[ilosc_przeszkod + 1];
	for (int i = 0; i < ilosc_przeszkod; i++)
	{
		temp[i] = przeszkody[i];
	}
	temp[ilosc_przeszkod] = przeszkoda;
	ilosc_przeszkod++;
	delete[] przeszkody;
	przeszkody = new Przeszkoda[ilosc_przeszkod];
	for (int i = 0; i < ilosc_przeszkod; i++)
	{
		przeszkody[i] = temp[i];
	}
	obiekty[ilosc_obiektow] = przeszkody[ilosc_przeszkod - 1];
	if (ilosc_obiektow < MAX_OBJ)
		ilosc_obiektow++;

	sortByY();
	sortPrzeszkodyByY();
}

void Plansza::addPlayer(Gracz *gracz)
{
	this->gracz = gracz;
}

void Plansza::sortPlatformyByY()
{
	for (int i = 0; i < ilosc_platform; i++)
		for (int j = 1; j < ilosc_platform - i; j++)
			if (platformy[j - 1].y > platformy[j].y)
			{
				Platforma temp = platformy[j - 1];
				platformy[j - 1] = platformy[j];
				platformy[j] = temp;
			}
}

void Plansza::sortPrzeszkodyByY()
{
	for (int i = 0; i < ilosc_przeszkod; i++)
		for (int j = 1; j < ilosc_przeszkod - i; j++)
			if (przeszkody[j - 1].y > przeszkody[j].y)
			{
				Przeszkoda temp = przeszkody[j - 1];
				przeszkody[j - 1] = przeszkody[j];
				przeszkody[j] = temp;
			}
}

void Plansza::sortByY()
{
	for (int i = 0; i < ilosc_obiektow; i++)
		for (int j = 1; j < ilosc_obiektow - i; j++)
			if (obiekty[j - 1].y > obiekty[j].y)
			{
				Obiekt temp = obiekty[j - 1];
				obiekty[j - 1] = obiekty[j];
				obiekty[j] = temp;
			}
}

Plansza::Plansza(Platforma* platformy, int ilosc_platform, int szerokosc, int wysokosc)
{

	this->platformy = platformy;
	this->ilosc_platform = ilosc_platform;
	this->szerokosc = szerokosc;
	this->wysokosc = wysokosc;
	szybkosc = 1.0;
	gracz = nullptr;
	this->platformy = new Platforma[ilosc_platform];
	for (int i = 0; i < ilosc_platform; i++)
	{
		this->platformy[i] = platformy[i];
	}
	this->przeszkody = new Przeszkoda[ilosc_platform];
	for (int i = 0; i < ilosc_platform; i++)
	{
		this->platformy[i] = platformy[i];
	}
	sortPlatformyByY();
	sortPrzeszkodyByY();
}

Plansza::~Plansza()
{
}

Plansza::Plansza()
{
	platformy = nullptr;
	przeszkody = nullptr;
	ilosc_platform = 0;
	ilosc_przeszkod = 0;
	wysokosc = 0;
	szerokosc = 0;
	szybkosc = 1.0;
	gracz = nullptr;

}

Plansza::Plansza(int x, int y)
{
	platformy = nullptr;
	przeszkody = nullptr;
	ilosc_platform = 0;
	ilosc_przeszkod = 0;
	wysokosc = y;
	szerokosc = x;
	szybkosc = 1.0;
	gracz = nullptr;

}

bool Plansza::KolizjaGracz(Obiekt& o, int x, int y) {
	int l1 = o.x; //left
	int r1 = o.x + o.szerokosc; //right
	int t1 = o.y; //top
	int b1 = o.y + o.wysokosc; //bottom


	if (x < l1 || x > r1 || y > b1 || y < t1)
		return false;
	else
		return true;
}

void Plansza::UpdatePlayer(double delta, SDL_Event& e, int* exit)
{
	ilosc_obiektow = ilosc_platform + ilosc_przeszkod;


	int iteracje = 3; //iloœæ sprawdzeñ na tick
	bool kolizja_x = true, kolizja_dol = true, kolizja_gora = true;
	bool stop = false;

	for (int i = 0; i < iteracje && (kolizja_x || kolizja_dol || kolizja_gora); i++)
	{
		float nextMoveX = CalcSpeed(gracz->v_x, delta);
		float nextMoveY = CalcSpeed(gracz->v_y, delta);

		kolizja_x = kolizja_dol = kolizja_gora = false;
		float mozliweX, mozliweY, stareX, stareY;

		stareX = nextMoveX;
		stareY = nextMoveY;

		for (int o = 0; o < ilosc_obiektow && !kolizja_x && !kolizja_dol && !kolizja_gora; o++)
		{
			for (int dir = 0; dir < 4; dir++)
			{
				if (dir == 0 && nextMoveY > 0) continue;
				if (dir == 1 && nextMoveY < 0) continue;
				if (dir == 2 && nextMoveX > 0) continue;
				if (dir == 3 && nextMoveX < 0) continue;

				mozliweX = (dir >= 2 ? nextMoveX : 0); // if dir >= 2 - > mozliweX = nexMoveX else -> 0
				mozliweY = (dir < 2 ? nextMoveY : 0);

				while (KolizjaGracz(obiekty[o], gracz->punkty_kolizji_x[dir*2] + gracz->x + mozliweX
						,gracz->punkty_kolizji_y[dir*2] + gracz->y + mozliweY)
						|| KolizjaGracz(obiekty[o], gracz->punkty_kolizji_x[dir * 2+1] + gracz->x + mozliweX
							, gracz->punkty_kolizji_y[dir * 2+1] + gracz->y + mozliweY))
				{
					
					if (dir == 0) mozliweY++;
					if (dir == 1) mozliweY--;
					if (dir == 2) mozliweX++;
					if (dir == 3) mozliweX--;

				}

				if (dir >= 2 && dir <= 3) nextMoveX = mozliweX;
				if (dir >= 0 && dir <= 1) nextMoveY = mozliweY;
			}
			
			if (nextMoveY > stareY && stareY < 0)
			{
				kolizja_gora = true;
			}

			if (nextMoveY < stareY && stareY > 0)
			{
				kolizja_dol = true;
			}


			if (fabsf(nextMoveX - stareX) > 0.01f)
			{

				
					kolizja_x = true;
					gracz->szanse--;
					gracz->punkty = 0;
					*exit = 1;
				
					
					
				
			}


			if (kolizja_x && gracz->v_y < 0)
				gracz->v_y = nextMoveY = 0;

			if ((kolizja_dol || kolizja_gora || kolizja_x) && obiekty[o].co == 1)
			{

					kolizja_x = true;
					if (kolizja_gora || kolizja_dol) {
						gracz->szanse--;
					}
					*exit = 1;

					gracz->punkty = 0;
					return;

				
			}
		}
		

		if (kolizja_gora || kolizja_dol)
		{
			gracz->y += nextMoveY;
			gracz->v_y = 0;

			if (kolizja_dol)
			{
				gracz->jumping = false;
				gracz->ilosc_skokow = 0;
			}
				
		}

		if (kolizja_x)
		{
			gracz->x += nextMoveX;
			gracz->v_x = 0;
		}
	}



	gracz->Ruch(e, delta);



	
		


	
}
#include "Linker.h"

// main
#ifdef __cplusplus
extern "C"
#endif
int main(int argc, char** argv) {
	int t1, t2, quit, frames, rc, nowa_gra;
	double delta, worldTime, fpsTimer, fps, distance, etiSpeed;
	SDL_Event event;
	SDL_Surface* screen, * charset;
	SDL_Surface* eti, * kuc1, * kuc2, * kuc3, * zycie, * delfin;
	SDL_Texture* scrtex;
	SDL_Window* window;
	SDL_Renderer* renderer;




	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		printf("SDL_Init error: %s\n", SDL_GetError());
		return 1;
	}

	// tryb pe?noekranowy / fullscreen mode
//	rc = SDL_CreateWindowAndRenderer(0, 0, SDL_WINDOW_FULLSCREEN_DESKTOP,
//	                                 &window, &renderer);
	rc = SDL_CreateWindowAndRenderer(SCREEN_WIDTH, SCREEN_HEIGHT, 0,
		&window, &renderer);
	if (rc != 0) {
		SDL_Quit();
		printf("SDL_CreateWindowAndRenderer error: %s\n", SDL_GetError());
		return 1;
	};

	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
	SDL_RenderSetLogicalSize(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

	SDL_SetWindowTitle(window, "Projekt 2 - 184622");


	screen = SDL_CreateRGBSurface(0, SCREEN_WIDTH, SCREEN_HEIGHT, 32,
		0x00FF0000, 0x0000FF00, 0x000000FF, 0xFF000000);

	scrtex = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888,
		SDL_TEXTUREACCESS_STREAMING,
		SCREEN_WIDTH, SCREEN_HEIGHT);


	// wy??czenie widoczno?ci kursora myszy
	SDL_ShowCursor(SDL_DISABLE);

	// wczytanie obrazka cs8x8.bmp
	charset = SDL_LoadBMP("./cs8x8.bmp");
	if (charset == NULL) {
		printf("SDL_LoadBMP(cs8x8.bmp) error: %s\n", SDL_GetError());
		SDL_FreeSurface(screen);
		SDL_DestroyTexture(scrtex);
		SDL_DestroyWindow(window);
		SDL_DestroyRenderer(renderer);
		SDL_Quit();
		return 1;
	};
	//SDL_SetColorKey(charset, true, 0x000000);

	eti = SDL_LoadBMP("./eti.bmp");
	if (eti == NULL) {
		printf("SDL_LoadBMP(eti.bmp) error: %s\n", SDL_GetError());
		SDL_FreeSurface(charset);
		SDL_FreeSurface(screen);
		SDL_DestroyTexture(scrtex);
		SDL_DestroyWindow(window);
		SDL_DestroyRenderer(renderer);
		SDL_Quit();
		return 1;
	};



	kuc1 = SDL_LoadBMP("./kuc1.bmp");
	if (kuc1 == NULL) {
		printf("SDL_LoadBMP(kuc1.bmp) error: %s\n", SDL_GetError());
		SDL_FreeSurface(charset);
		SDL_FreeSurface(screen);
		SDL_DestroyTexture(scrtex);
		SDL_DestroyWindow(window);
		SDL_DestroyRenderer(renderer);
		SDL_Quit();
		return 1;
	};

	kuc2 = SDL_LoadBMP("./kuc2.bmp");
	if (kuc2 == NULL) {
		printf("SDL_LoadBMP(kuc2.bmp) error: %s\n", SDL_GetError());
		SDL_FreeSurface(charset);
		SDL_FreeSurface(screen);
		SDL_DestroyTexture(scrtex);
		SDL_DestroyWindow(window);
		SDL_DestroyRenderer(renderer);
		SDL_Quit();
		return 1;
	};
	kuc3 = SDL_LoadBMP("./kuc3.bmp");
	if (kuc3 == NULL) {
		printf("SDL_LoadBMP(kuc3.bmp) error: %s\n", SDL_GetError());
		SDL_FreeSurface(charset);
		SDL_FreeSurface(screen);
		SDL_DestroyTexture(scrtex);
		SDL_DestroyWindow(window);
		SDL_DestroyRenderer(renderer);
		SDL_Quit();
		return 1;
	};
	zycie = SDL_LoadBMP("./zycie.bmp");
	if (zycie == NULL) {
		printf("SDL_LoadBMP(zycie.bmp) error: %s\n", SDL_GetError());
		SDL_FreeSurface(charset);
		SDL_FreeSurface(screen);
		SDL_DestroyTexture(scrtex);
		SDL_DestroyWindow(window);
		SDL_DestroyRenderer(renderer);
		SDL_Quit();
		return 1;
	};

	delfin = SDL_LoadBMP("./delfin.bmp");
	if (delfin == NULL) {
		printf("SDL_LoadBMP(delfin.bmp) error: %s\n", SDL_GetError());
		SDL_FreeSurface(charset);
		SDL_FreeSurface(screen);
		SDL_DestroyTexture(scrtex);
		SDL_DestroyWindow(window);
		SDL_DestroyRenderer(renderer);
		SDL_Quit();
		return 1;
	};

	char text[128];
	czarny = SDL_MapRGB(screen->format, 0x00, 0x00, 0x00);
	zielony = SDL_MapRGB(screen->format, 0x00, 0xFF, 0x00);
	int tlo_kolor = SDL_MapRGB(screen->format, 0x00, 0xBB, 0xFF);
	czerwony = SDL_MapRGB(screen->format, 0xFF, 0x00, 0x00);
	niebieski = SDL_MapRGB(screen->format, 0x11, 0x11, 0xCC);

	t1 = SDL_GetTicks();

	quit = 0;

	Grafika grafika(screen, charset);
	Gracz gracz(100, 100, kuc1, kuc3, kuc2);
	Plansza plansza(5000, SCREEN_HEIGHT + 50);
	plansza.addPlayer(&gracz);



	//Przeszkoda prz1(650, plansza.wysokosc -40, 50, 50);
	Przeszkoda prz2(650, plansza.wysokosc - 300, 50, 50);
	Przeszkoda prz3(1800, plansza.wysokosc - 400, 25, 50);
	Przeszkoda prz4(2050, plansza.wysokosc - 400, 25, 50);
	Przeszkoda prz5(2010, plansza.wysokosc - 400, 25, 50);
	Przeszkoda prz6(500, plansza.wysokosc - 2000, 50, 1500); // poczatek stalaktytow
	Przeszkoda prz7(900, plansza.wysokosc - 2000, 50, 1500);
	Przeszkoda prz8(1100, plansza.wysokosc - 2000, 50, 1500);
	Przeszkoda prz9(1700, plansza.wysokosc - 2000, 50, 1200);
	//Platforma pl_d(-1500, plansza.wysokosc-10, plansza.szerokosc + 1500, 50);
	Platforma pl_d2(0, plansza.wysokosc - 100, 300, 25);
	Platforma pl_d3(-1400, plansza.wysokosc - 500, 300, 30);
	Platforma pl_d4(0, plansza.wysokosc - 500, 200, 25); //spawn
	Platforma pl_d5(250, plansza.wysokosc - 250, 200, 25);
	Platforma pl_d6(550, plansza.wysokosc - 250, 150, 25);
	Platforma pl_d7(750, plansza.wysokosc - 325, 200, 25);
	Platforma pl_d8(1000, plansza.wysokosc - 250, 200, 25);
	Platforma pl_d9(1100, plansza.wysokosc - 275, 100, 25);
	Platforma pl_d10(1250, plansza.wysokosc - 370, 125, 25);
	Platforma pl_d11(1400, plansza.wysokosc - 410, 200, 25);
	Platforma pl_d12(1600, plansza.wysokosc - 470, 100, 25);
	Platforma pl_d13(1675, plansza.wysokosc - 350, 400, 25);
	Platforma pl_d14(2175, plansza.wysokosc - 375, 200, 25);
	Platforma pl_d15(2325, plansza.wysokosc - 450, 200, 25);
	Platforma pl_d16(2450, plansza.wysokosc - 375, 200, 25);
	Platforma pl_d17(2700, plansza.wysokosc - 450, 150, 25);
	Platforma pl_d18(2900, plansza.wysokosc - 500, 200, 25);
	Platforma pl_d19(3100, plansza.wysokosc - 375, 200, 25);
	Platforma pl_d20(3300, plansza.wysokosc - 500, 700, 25);
	Platforma pl_d21(3500, plansza.wysokosc - 370, 500, 25);
	Platforma pl_d22(3820, plansza.wysokosc - 410, 200, 25);
	Platforma pl_d23(-1000, plansza.wysokosc - 375, 200, 25);
	Platforma pl_d24(-900, plansza.wysokosc - 320, 200, 25);
	Platforma pl_d25(-650, plansza.wysokosc - 300, 200, 25);
	Platforma pl_d26(-200, plansza.wysokosc - 350, 200, 25);


	//plansza.DodajPrzeszkode(prz1);
	plansza.DodajPrzeszkode(prz2);
	plansza.DodajPrzeszkode(prz3);
	plansza.DodajPrzeszkode(prz4);
	plansza.DodajPrzeszkode(prz5);
	plansza.DodajPrzeszkode(prz6);
	plansza.DodajPrzeszkode(prz7);
	plansza.DodajPrzeszkode(prz8);
	plansza.DodajPrzeszkode(prz9);
	//plansza.DodajPlatforme(pl_d);
	plansza.DodajPlatforme(pl_d2);
	plansza.DodajPlatforme(pl_d3);
	plansza.DodajPlatforme(pl_d4);
	plansza.DodajPlatforme(pl_d5);
	plansza.DodajPlatforme(pl_d6);
	plansza.DodajPlatforme(pl_d7);
	plansza.DodajPlatforme(pl_d8);
	plansza.DodajPlatforme(pl_d9);
	plansza.DodajPlatforme(pl_d10);
	plansza.DodajPlatforme(pl_d11);
	plansza.DodajPlatforme(pl_d12);
	plansza.DodajPlatforme(pl_d13);
	plansza.DodajPlatforme(pl_d14);
	plansza.DodajPlatforme(pl_d15);
	plansza.DodajPlatforme(pl_d16);
	plansza.DodajPlatforme(pl_d17);
	plansza.DodajPlatforme(pl_d18);
	plansza.DodajPlatforme(pl_d19);
	plansza.DodajPlatforme(pl_d20);
	plansza.DodajPlatforme(pl_d21);
	plansza.DodajPlatforme(pl_d22);
	plansza.DodajPlatforme(pl_d23);
	plansza.DodajPlatforme(pl_d24);
	plansza.DodajPlatforme(pl_d25);
	plansza.DodajPlatforme(pl_d26);


	bool zdane1 = false;
	bool zdane2 = false;

	int def = 2;


	while (!quit) {

		frames = 0;
		fpsTimer = 0;
		fps = 0;
		nowa_gra = 0;

		worldTime = 0;
		distance = 0;
		etiSpeed = 1;
		gracz.x = 100;
		gracz.y = 10;
		while (!nowa_gra) {

			if (quit != 0) break;
			t2 = SDL_GetTicks();

			delta = (t2 - t1) * 0.001;
			t1 = t2;

			worldTime += delta;

			distance += etiSpeed * delta;
			SDL_FillRect(screen, NULL, tlo_kolor);

			fpsTimer += delta;
			if (fpsTimer > 0.5) {
				fps = frames * 2;
				frames = 0;
				fpsTimer -= 0.5;
			};


			grafika.camera.x = (plansza.gracz->x + plansza.gracz->sizeY / 2) - SCREEN_WIDTH / 4;
			grafika.camera.y = (plansza.gracz->y + plansza.gracz->sizeX / 2) - SCREEN_HEIGHT / 3 * 2;

			grafika.RysujPlansze(plansza);
			grafika.DrawRectangle(0, 0, SCREEN_WIDTH, 40, czerwony, niebieski);
			//            "template for the second project, elapsed time = %.1lf s  %.0lf frames / s"
			sprintf(text, "Czas trwania = %.1lf s  %.0lf klatek / s  punkty = %d", worldTime, fps, plansza.gracz->punkty);
			grafika.DrawString(screen->w / 2 - strlen(text) * 8 / 2, 10, text);

			sprintf(text, "Gracz.X = %.1lf  Gracz.Y = %.1lf", plansza.gracz->x, plansza.gracz->y);
			grafika.DrawString(screen->w / 2 - strlen(text) * 8 / 2, 40, text);



			int g = 50;
			int t = 0;
			for (int i = 0; i < plansza.gracz->szanse; i++)
			{
				grafika.DrawSurface(zycie, (screen->w - SCREEN_WIDTH + 70) + t, 50);      //zycia
				t += 50;
			}
			if (plansza.gracz->punkty % 200 > 50 && plansza.gracz->punkty % 300 > 50 && plansza.gracz->punkty != 0) {
				for (int i = 0; i < def; i++)
				{
					grafika.DrawSurface(delfin, (sin(distance) * SCREEN_HEIGHT / 3) + g, SCREEN_HEIGHT / 3 * sin(distance));
					g += 50;

				}

			}


			sprintf(text, "Esc - wyjscie, n - nowa gra, d - zmiana trybu");
			grafika.DrawString(screen->w / 2 - strlen(text) * 8 / 2, 26, text);

			if ((plansza.gracz->szanse == 2 && zdane1 == false) || (plansza.gracz->szanse == 1 && zdane2 == false)) {
				plansza.gracz->pauza = true;
				grafika.DrawRectangle(0, 100, SCREEN_WIDTH, 100, czerwony, niebieski);
				sprintf(text, "Kontynuowac?");
				grafika.DrawString(screen->w / 2 - strlen(text) * 8 / 2, 150, text);
				sprintf(text, "Tak(t) --------- Nie(g)");
				grafika.DrawString(screen->w / 2 - strlen(text) * 8 / 2, 170, text);
				worldTime = 0;
				plansza.gracz->v_x = 0;
				plansza.gracz->v_y = 0;
				gracz.x = 0;
				plansza.gracz->punkty = 0;
				plansza.gracz->ruch_prawo_auto = false;
				while (SDL_PollEvent(&event)) {

					switch (event.type) {
					case SDL_KEYDOWN:
						if (event.key.keysym.sym == SDLK_t) {
							if (plansza.gracz->szanse == 2) zdane1 = true;
							if (plansza.gracz->szanse == 1) zdane2 = true;
							plansza.gracz->pauza = false;
							gracz.x = 0;
							plansza.gracz->v_x = 0;
							plansza.gracz->v_y = 0;
							plansza.gracz->punkty = 0;
						}
						if (event.key.keysym.sym == SDLK_g) {
							quit = 1;
						}
					}
				}
			}

			if (plansza.gracz->szanse <= 0) {
				plansza.gracz->pauza = true;
				grafika.DrawRectangle(0, 100, SCREEN_WIDTH, 100, czerwony, niebieski);
				sprintf(text, "Koniec gry!");
				grafika.DrawString(screen->w / 2 - strlen(text) * 8 / 2, 150, text);
				sprintf(text, "Koniec(t) -------- Nowa gra(n)");
				grafika.DrawString(screen->w / 2 - strlen(text) * 8 / 2, 170, text);
				worldTime = 0;
				plansza.gracz->v_x = 0;
				plansza.gracz->v_y = 0;
				gracz.x = 0;
				plansza.gracz->punkty = 0;
				plansza.gracz->ruch_prawo_auto = false;
				while (SDL_PollEvent(&event)) {

					switch (event.type) {
					case SDL_KEYDOWN:
						if (event.key.keysym.sym == SDLK_t) {
							quit = 1;
						}
						if (event.key.keysym.sym == SDLK_n) {
							plansza.gracz->ruch_prawo_auto = false;
							plansza.gracz->v_x = 0;
							plansza.gracz->v_y = 0;
							gracz.x = 0;
							nowa_gra = 1;
							plansza.gracz->szanse = 3;
							plansza.gracz->pauza = false;
							plansza.gracz->punkty = 0;
						}
					}
				}
			}


			if (plansza.gracz->y > 1500) {
				plansza.gracz->szanse--;
				nowa_gra = 1;
			}

			SDL_UpdateTexture(scrtex, NULL, screen->pixels, screen->pitch);

			//	SDL_RenderClear(renderer);
			SDL_RenderCopy(renderer, scrtex, NULL, NULL);
			SDL_RenderPresent(renderer);


			plansza.UpdatePlayer(delta, event, &nowa_gra);

			// obs?uga zdarze? (o ile jakie? zasz?y) / handling of events (if there were any)
			while (SDL_PollEvent(&event)) {

				switch (event.type) {
				case SDL_KEYDOWN:
					if (event.key.keysym.sym == SDLK_ESCAPE && plansza.gracz->pauza == false)
					{
						quit = 1;
						break;
					}
					else if (event.key.keysym.sym == SDLK_n) {
						nowa_gra = 1;
						plansza.gracz->szanse = 3;
						plansza.gracz->zmiana_trybu = false;
						plansza.gracz->ruch_prawo_auto = false;
						plansza.gracz->punkty = 0;
					}

					else if (event.key.keysym.sym == SDLK_d && plansza.gracz->pauza == false)
					{
						plansza.gracz->zmiana_trybu = true;
						plansza.gracz->ruch_prawo_auto = true;

					}
					else if (event.key.keysym.sym == SDLK_f && plansza.gracz->pauza == false)
					{
						plansza.gracz->zmiana_trybu = false;
						plansza.gracz->ruch_prawo_auto = false;

					}
					else if (plansza.gracz->zmiana_trybu == true && event.key.keysym.sym == SDLK_z && plansza.gracz->podwojny_skok && !plansza.gracz->jumping && !plansza.gracz->jumpKeyDown && plansza.gracz->ilosc_skokow < 2)
					{
						plansza.gracz->ilosc_skokow++;
						plansza.gracz->jumping = true;
						plansza.gracz->jumpKeyDown = true;
						plansza.gracz->v_y = -plansza.gracz->jumpStart;
					}
					else if (event.key.keysym.sym == SDLK_z && plansza.gracz->zmiana_trybu == true && plansza.gracz->podwojny_skok && plansza.gracz->jumping && !plansza.gracz->jumpKeyDown && plansza.gracz->ilosc_skokow < 2)
					{
						plansza.gracz->ilosc_skokow++;
						plansza.gracz->jumping = true;
						plansza.gracz->jumpKeyDown = true;
						plansza.gracz->v_y = -plansza.gracz->jumpStart;
					}
					else if (event.key.keysym.sym == SDLK_x && plansza.gracz->zmiana_trybu == true)
					{
						plansza.gracz->zryw = true;

					}
					break;
				case SDL_KEYUP:
					if (event.key.keysym.sym == SDLK_x && plansza.gracz->zmiana_trybu == true)
					{
						plansza.gracz->zryw = false;
						plansza.gracz->zab = false;
						plansza.gracz->przelicznik = false;
					}
					etiSpeed = 1.0;
					break;
				case SDL_QUIT:
					quit = 1;
					break;

				};

			};
			frames++;

		};
	};
	// zwolnienie powierzchni / freeing all surfaces
	SDL_FreeSurface(charset);
	SDL_FreeSurface(screen);
	SDL_DestroyTexture(scrtex);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);

	SDL_Quit();
	return 0;
};

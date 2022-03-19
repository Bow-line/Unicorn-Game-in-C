#define _USE_MATH_DEFINES
#include<math.h>
#include<stdio.h>
#include<string.h>

extern "C" {
#include"./SDL2-2.0.10/include/SDL.h"
#include"./SDL2-2.0.10/include/SDL_main.h"
}

#define SCREEN_WIDTH	640
#define SCREEN_HEIGHT	480


// narysowanie napisu txt na powierzchni screen, zaczynajπc od punktu (x, y)
// charset to bitmapa 128x128 zawierajπca znaki
// draw a text txt on surface screen, starting from the point (x, y)
// charset is a 128x128 bitmap containing character images
void DrawString(SDL_Surface *screen, int x, int y, const char *text,
                SDL_Surface *charset) {
	int px, py, c;
	SDL_Rect s, d;
	s.w = 8;
	s.h = 8;
	d.w = 8;
	d.h = 8;
	while(*text) {
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
void DrawSurface(SDL_Surface *screen, SDL_Surface *sprite, int x, int y) {
	SDL_Rect dest;
	dest.x = x - sprite->w / 2;
	dest.y = y - sprite->h / 2;
	dest.w = sprite->w;
	dest.h = sprite->h;
	SDL_BlitSurface(sprite, NULL, screen, &dest);
	};


// rysowanie pojedynczego pixela
// draw a single pixel
void DrawPixel(SDL_Surface *surface, int x, int y, Uint32 color) {
	int bpp = surface->format->BytesPerPixel;
	Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * bpp;
	*(Uint32 *)p = color;
	};


// rysowanie linii o d≥ugoúci l w pionie (gdy dx = 0, dy = 1) 
// bπdü poziomie (gdy dx = 1, dy = 0)
// draw a vertical (when dx = 0, dy = 1) or horizontal (when dx = 1, dy = 0) line
void DrawLine(SDL_Surface *screen, int x, int y, int l, int dx, int dy, Uint32 color) {
	for(int i = 0; i < l; i++) {
		DrawPixel(screen, x, y, color);
		x += dx;
		y += dy;
		};
	};


// rysowanie prostokπta o d≥ugoúci bokÛw l i k
// draw a rectangle of size l by k
void DrawRectangle(SDL_Surface *screen, int x, int y, int l, int k,
                   Uint32 outlineColor, Uint32 fillColor) {
	int i;
	DrawLine(screen, x, y, k, 0, 1, outlineColor);
	DrawLine(screen, x + l - 1, y, k, 0, 1, outlineColor);
	DrawLine(screen, x, y, l, 1, 0, outlineColor);
	DrawLine(screen, x, y + k - 1, l, 1, 0, outlineColor);
	for(i = y + 1; i < y + k - 1; i++)
		DrawLine(screen, x + 1, i, l - 2, 1, 0, fillColor);
	};

void DrawBackground(SDL_Surface* background, SDL_Rect camera, SDL_Surface* screen, SDL_Renderer* renderer) {
	SDL_BlitSurface(background, &camera, screen, NULL);
	//SDL_RenderPresent(renderer);
}
bool Collision(SDL_Rect* rec1, SDL_Rect* rec2) {
	if (rec1->y >= rec2->y + rec2->h)
		return 0;
	if (rec1->x >= rec2->x + rec2->w)
		return 0;
	if (rec1->y + rec1->h <= rec2->y)
		return 0;
	if (rec1->x + rec1->w <= rec2->x)
		return 0;
	return 1;

}
void Jump(int v_y) {
	v_y = -5;
}


// main
#ifdef __cplusplus
extern "C"
#endif
int main(int argc, char **argv) {
#define _USE_MATH_DEFINES
	int t1, t2, quit, frames, rc, nowa_gra, x=0, y=0 ;
	double delta, worldTime, fpsTimer, fps, distance, etiSpeed;
	const int speed = 20;
	SDL_Event event;
	SDL_Surface *screen, *charset, *background, *image;
	SDL_Surface *unicorn;
	SDL_Texture *scrtex;
	SDL_Window *window;
	SDL_Renderer *renderer;

	// okno konsoli nie jest widoczne, jeøeli chcemy zobaczyÊ
	// komunikaty wypisywane printf-em trzeba w opcjach:
	// project -> szablon2 properties -> Linker -> System -> Subsystem
	// zmieniÊ na "Console"
	// console window is not visible, to see the printf output
	// the option:
	// project -> szablon2 properties -> Linker -> System -> Subsystem
	// must be changed to "Console"
	printf("wyjscie printfa trafia do tego okienka\n");
	printf("printf output goes here\n");

	if(SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		printf("SDL_Init error: %s\n", SDL_GetError());
		return 1;
		}

	// tryb pe≥noekranowy / fullscreen mode
//	rc = SDL_CreateWindowAndRenderer(0, 0, SDL_WINDOW_FULLSCREEN_DESKTOP,
//	                                 &window, &renderer);
	rc = SDL_CreateWindowAndRenderer(SCREEN_WIDTH, SCREEN_HEIGHT, 0,
	                                 &window, &renderer);
	if(rc != 0) {
		SDL_Quit();
		printf("SDL_CreateWindowAndRenderer error: %s\n", SDL_GetError());
		return 1;
		};
	
	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
	SDL_RenderSetLogicalSize(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

	SDL_SetWindowTitle(window, "Szablon do zdania drugiego 2017");


	screen = SDL_CreateRGBSurface(0, SCREEN_WIDTH, SCREEN_HEIGHT, 32,
	                              0x00FF0000, 0x0000FF00, 0x000000FF, 0xFF000000);

	scrtex = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888,
	                           SDL_TEXTUREACCESS_STREAMING,
	                           SCREEN_WIDTH, SCREEN_HEIGHT);


	// wy≥πczenie widocznoúci kursora myszy
	SDL_ShowCursor(SDL_DISABLE);

	// wczytanie obrazka cs8x8.bmp
	charset = SDL_LoadBMP("./cs8x8.bmp");
	if(charset == NULL) {
		printf("SDL_LoadBMP(cs8x8.bmp) error: %s\n", SDL_GetError());
		SDL_FreeSurface(screen);
		SDL_DestroyTexture(scrtex);
		SDL_DestroyWindow(window);
		SDL_DestroyRenderer(renderer);
		SDL_Quit();
		return 1;
		};
	SDL_SetColorKey(charset, true, 0x000000);

	unicorn = SDL_LoadBMP("unicorn.bmp");
	SDL_Rect unicorn_location = { 2000,0,50,100 };
	if(unicorn == NULL) {
		printf("SDL_LoadBMP(eti.bmp) error: %s\n", SDL_GetError());
		SDL_FreeSurface(charset);
		SDL_FreeSurface(screen);
		SDL_DestroyTexture(scrtex);
		SDL_DestroyWindow(window);
		SDL_DestroyRenderer(renderer);
		SDL_Quit();
		return 1;
		};

	char text[128];
	int czarny = SDL_MapRGB(screen->format, 0x00, 0x00, 0x00);
	int zielony = SDL_MapRGB(screen->format, 0x00, 0xFF, 0x00);
	int czerwony = SDL_MapRGB(screen->format, 0xFF, 0x00, 0x00);
	int niebieski = SDL_MapRGB(screen->format, 0x11, 0x11, 0xCC);
	int tlo_kolor = SDL_MapRGB(screen->format, 0x00, 0xBB, 0xFF);

	t1 = SDL_GetTicks();

	quit = 0;
	





	int v_x = 0;
	int v_y = 0;
	int a=40, d=309;
	float gravity = 7;
	background = SDL_LoadBMP("background.bmp");
	SDL_Rect camera;
	camera.x = 0;
	camera.y = 0;
	camera.w = 640;
	camera.h = 480;
	bool b[2] = { 0,0 };
	while (!quit) {
		frames = 0;
		fpsTimer = 0;
		fps = 0;
		nowa_gra = 0;
		worldTime = 0;
		distance = 0;
		etiSpeed = 1;

		while (!nowa_gra) {
			if (quit != 0) break;
			t2 = SDL_GetTicks();

			// w tym momencie t2-t1 to czas w milisekundach,
			// jaki uplyna≥ od ostatniego narysowania ekranu
			// delta to ten sam czas w sekundach
			// here t2-t1 is the time in milliseconds since
			// the last screen was drawn
			// delta is the same time in seconds
			delta = (t2 - t1) * 0.001;
			t1 = t2;

			worldTime += delta;

			distance += etiSpeed * delta;

			//SDL_FillRect(screen, NULL, tlo_kolor);

			
			SDL_Surface* sprite;


			
			
			


			//DrawSurface(screen, unicorn, 0, SCREEN_HEIGHT / 2);
			DrawBackground(background, camera, screen, renderer);
			DrawSurface(screen, unicorn, a, d);

			fpsTimer += delta;
			if (fpsTimer > 0.5) {
				fps = frames * 2;
				frames = 0;
				fpsTimer -= 0.5;
			};

			// tekst informacyjny / info text
			DrawRectangle(screen, 0, 0, SCREEN_WIDTH, 40, czerwony, niebieski);
			DrawRectangle(screen, 0, 330, 100, 150, czerwony, niebieski);
			//            "template for the second project, elapsed time = %.1lf s  %.0lf frames / s"
			sprintf(text, "Szablon drugiego zadania, czas trwania = %.1lf s  %.0lf klatek / s", worldTime, fps);
			DrawString(screen, screen->w / 2 - strlen(text) * 8 / 2, 10, text, charset);
			//	      "Esc - exit, \030 - faster, \031 - slower"
			sprintf(text, "Esc - wyjscie, n - nowa gra, \030 - przyspieszenie, \031 - zwolnienie");
			DrawString(screen, screen->w / 2 - strlen(text) * 8 / 2, 26, text, charset);

			SDL_UpdateTexture(scrtex, NULL, screen->pixels, screen->pitch);
			//		SDL_RenderClear(renderer);
			SDL_RenderCopy(renderer, scrtex, NULL, NULL);
			SDL_RenderPresent(renderer);

		a += v_x;


			if ((a < 0) || (a + 20 > 640))
			{
				a-= v_x;
			}
			d += v_y;

			if ((d < 80) || (d >= 310))
			{
				d -= v_y;
			}

			
			// obs≥uga zdarzeÒ (o ile jakieú zasz≥y) / handling of events (if there were any)
			while (SDL_PollEvent(&event)) {
				switch (event.type ) {
				case SDL_KEYDOWN:
					switch (event.key.keysym.sym) {
					case SDLK_ESCAPE:
						quit = 1;
						break;
					case SDLK_UP:
						v_y = -3;
						d += v_y;
						break;
					case SDLK_DOWN:
						break;
					case SDLK_RIGHT:
						b[0] = 1;
						break;
					case SDLK_LEFT:
						b[1] = 1;
						break;
					case SDLK_n:
						nowa_gra = 1;
						d = 309;
						break;
					}
					/*if (event.key.keysym.sym == SDLK_ESCAPE)
					{
						quit = 1;
						break;
					}
					else if (event.key.keysym.sym == SDLK_UP) {
						 //v_y -= 2;
						/*d -= 50;
						
						break;
					//	etiSpeed = 2.0;
					}
					else if (event.key.keysym.sym == SDLK_DOWN) {
						//v_y += 4;
						etiSpeed = 0.3;
					} 
					else if (event.key.keysym.sym == SDLK_RIGHT) {
						//v_x += 2;
						b[0] = 1;
					}
					else if (event.key.keysym.sym == SDLK_LEFT) {
						//v_x -= 2;
						b[1] = 1;
					}
					else if (event.key.keysym.sym == SDLK_n) nowa_gra = 1;
					*/
					if (b[0] == 1) {
						x += speed;
						camera.x += speed;
						if (camera.x >= 2000 - 640) {
							camera.x = 0;
						}
					}
					else if (b[1] == 1) {
						x -= speed;
						camera.x -= speed;
						if (camera.x <= 0) {
							camera.x = 2000 - 640;
						}
					}
					break;
				case SDL_KEYUP:
					switch (event.key.keysym.sym) {
					case SDLK_UP:

						v_y += gravity;
						/*d += 50;

						break;*/
					case SDLK_RIGHT:
						b[0] = 0;
						break;
					case SDLK_LEFT:
						b[1] = 0;
						break;
					}

					/*if (event.key.keysym.sym == SDLK_UP) {
						/*d += 50;
						
						break;
					}
					if (event.key.keysym.sym == SDLK_RIGHT) {
						//v_x -= 2;
						b[0] = 0;
					}
					else if (event.key.keysym.sym == SDLK_LEFT) {
						//v_x += 2;
						b[1] = 0;
					}*/
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

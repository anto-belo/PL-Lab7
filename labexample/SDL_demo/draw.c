#include "draw.h"
#include "stdafx.h"
#include "math.h"

#define RGB32(r, g, b) (uint32_t)(((((uint32_t)(b) << 8) | g) << 8) | r)

void draw_circumference(SDL_Renderer* ren, double a, double b, double r) {
	int d = 35;
	for (double x = a - r; x <= a + r + d; x++) {
		for (double y = b - r - d; y <= b + r; y++) {
			double dx = x - a;
			double dy = y - b;
			double exp = dx * dx + dy * dy;
			if ((r * r - d) <= exp && exp <= (r * r + d)) {
				SDL_RenderDrawPoint(ren, x, y);
			}
		}
	}
}

void draw(SDL_Surface *s)
{
	if (SDL_Init(SDL_INIT_VIDEO) == 0) {
		SDL_Window* win = NULL;
		SDL_Renderer* ren = NULL;

		double cycle_speed = 1;
		double cycle_spoke_off = 0;

		if (SDL_CreateWindowAndRenderer(640, 480, 0, &win, &ren) == 0) {
			SDL_bool done = SDL_FALSE;

			while (!done) {
				SDL_Event event;

				SDL_SetRenderDrawColor(ren, 0, 0, 0, 0);
				SDL_RenderClear(ren);
				SDL_SetRenderDrawColor(ren, 255, 255, 255, 255);

				// Каркас
				SDL_RenderDrawLine(ren, 50 + cycle_speed, 400, 100 + cycle_speed, 330);
				SDL_RenderDrawLine(ren, 50 + cycle_speed, 400, 115 + cycle_speed, 400);
				SDL_RenderDrawLine(ren, 100 + cycle_speed, 330, 120 + cycle_speed, 390);
				SDL_RenderDrawLine(ren, 220 + cycle_speed, 400, 200 + cycle_speed, 290);
				SDL_RenderDrawLine(ren, 133 + cycle_speed, 395, 205 + cycle_speed, 325);
				SDL_RenderDrawLine(ren, 100 + cycle_speed, 330, 205 + cycle_speed, 325);
				SDL_RenderDrawLine(ren, 175 + cycle_speed, 290, 200 + cycle_speed, 290);

				// Педали
				draw_circumference(ren, 125 + cycle_speed, 400, 10);
				SDL_RenderDrawLine(ren, 105 + cycle_speed + 0.4 * cycle_spoke_off, -sqrt(pow(20, 2) - pow(0.4 * cycle_spoke_off - 20, 2)) + 400,
										145 + cycle_speed - 0.4 * cycle_spoke_off, sqrt(pow(20, 2) - pow(20 - 0.4 * cycle_spoke_off, 2)) + 400);
				SDL_RenderDrawLine(ren, 105 + cycle_speed + 0.4 * cycle_spoke_off, -sqrt(pow(20, 2) - pow(0.4 * cycle_spoke_off - 20, 2)) + 400,
										110 + cycle_speed + 0.4 * cycle_spoke_off, -sqrt(pow(20, 2) - pow(0.4 * cycle_spoke_off - 20, 2)) + 400);
				SDL_RenderDrawLine(ren, 145 + cycle_speed - 0.4 * cycle_spoke_off, sqrt(pow(20, 2) - pow(20 - 0.4 * cycle_spoke_off, 2)) + 400,
										150 + cycle_speed - 0.4 * cycle_spoke_off, sqrt(pow(20, 2) - pow(20 - 0.4 * cycle_spoke_off, 2)) + 400);

				// Заднее колесо
				draw_circumference(ren, 50 + cycle_speed, 400, 50);
				SDL_RenderDrawLine(ren, cycle_speed + cycle_spoke_off, -sqrt(pow(50, 2) - pow(cycle_spoke_off - 50, 2)) + 400, 
										100 + cycle_speed - cycle_spoke_off, sqrt(pow(50, 2) - pow(50 - cycle_spoke_off, 2)) + 400);
				SDL_RenderDrawLine(ren, sqrt(pow(50, 2) - pow(cycle_spoke_off - 50, 2)) + 50 + cycle_speed, 350 + cycle_spoke_off,
										-sqrt(pow(50, 2) - pow(50 - cycle_spoke_off, 2)) + 50 + cycle_speed, 450 - cycle_spoke_off);

				// Переднее колесо
				draw_circumference(ren, 220 + cycle_speed, 400, 50);
				SDL_RenderDrawLine(ren, 170 + cycle_speed + cycle_spoke_off, -sqrt(pow(50, 2) - pow(cycle_spoke_off - 50, 2)) + 400,
										270 + cycle_speed - cycle_spoke_off, sqrt(pow(50, 2) - pow(50 - cycle_spoke_off, 2)) + 400);
				SDL_RenderDrawLine(ren, sqrt(pow(50, 2) - pow(cycle_spoke_off - 50, 2)) + 220 + cycle_speed, 350 + cycle_spoke_off,
										-sqrt(pow(50, 2) - pow(50 - cycle_spoke_off, 2)) + 220 + cycle_speed, 450 - cycle_spoke_off);

				// Человек...
				draw_circumference(ren, 110 + cycle_speed, 210, 20);
				SDL_RenderDrawLine(ren, 107 + cycle_speed, 229, 105 + cycle_speed, 310);
				SDL_RenderDrawLine(ren, 106 + cycle_speed, 258, 146 + cycle_speed, 285);
				SDL_RenderDrawLine(ren, 146 + cycle_speed, 285, 185 + cycle_speed, 290);
				draw_circumference(ren, 103 + cycle_speed, 320, 10);

				// ...и его ноги
				SDL_RenderDrawLine(ren, 105 + cycle_speed, 320, 135 + cycle_speed, 340);
				SDL_RenderDrawLine(ren, 135 + cycle_speed, 340, 
										107 + cycle_speed + 0.4 * cycle_spoke_off, -sqrt(pow(20, 2) - pow(0.4 * cycle_spoke_off - 20, 2)) + 400);
				SDL_RenderDrawLine(ren, 105 + cycle_speed, 320, 132 + cycle_speed, 344);
				SDL_RenderDrawLine(ren, 132 + cycle_speed, 344,
										147 + cycle_speed - 0.4 * cycle_spoke_off, sqrt(pow(20, 2) - pow(20 - 0.4 * cycle_spoke_off, 2)) + 400);

				cycle_speed += 0.05;
				cycle_spoke_off += 0.08;
				if (cycle_spoke_off > 100)
					cycle_spoke_off = 0;

				SDL_RenderPresent(ren);

				while (SDL_PollEvent(&event)) {
					if (event.type == SDL_QUIT) {
						done = SDL_TRUE;
					}
				}
			}
		}

		if (ren) {
			SDL_DestroyRenderer(ren);
		}
		if (win) {
			SDL_DestroyWindow(win);
		}
	}
	SDL_Quit();
	return 0;
}
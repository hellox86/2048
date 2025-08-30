#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include "game.h"
#include <math.h>

#define CELL_SIZE 100
#define SCR_W 410
#define SCR_H 410

SDL_Window* window = NULL;
SDL_Renderer* rend  = NULL;

typedef struct
{
    int32_t w;
    int32_t h;
} Field;

uint32_t game_field[4][4] = {0};

SDL_Surface* scr;

void secc(int32_t code)
{
    if (code < 0)
    {
	fprintf(stderr, "SDL error: %s\n", SDL_GetError());
	exit(1);
    }
}
void secc_ttf(int32_t code)
{
    if (code < 0)
    {
	fprintf(stderr, "TTF error: %s\n", TTF_GetError());
	exit(2);
    }
}
void secp(void* ptr)
{
    if (!ptr)
    {
	fprintf(stderr, "SDL error: %s\n", SDL_GetError());
	exit(1);
    }
}
void secp_ttf(void* ptr)
{
    if (!ptr)
    {
	fprintf(stderr, "TTF error: %s\n", TTF_GetError());
	exit(2);
    }
}
void sdl_init(void)
{
    secc(SDL_Init(SDL_INIT_VIDEO));
    window = SDL_CreateWindow("2048 game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCR_W, SCR_H, 0);
    secp(window);
 
    rend = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    secp(rend);    
}

// Bresenham's algorithm constructing a circle

// void draw_circle(int32_t center_x, int32_t center_y, int radius)
// {
//     int32_t x = 0;
//     int32_t y = radius;
//     int32_t delta = 1-2*radius; 
//     int32_t error = 0;
//     while (y >= x)
//     {
// 	SDL_RenderDrawPoint(rend, center_x+x, center_y+y);
// 	SDL_RenderDrawPoint(rend, center_x+x, center_y-y);
// 	SDL_RenderDrawPoint(rend, center_x-x, center_y+y);
// 	SDL_RenderDrawPoint(rend, center_x-x, center_y-y);
// 	SDL_RenderDrawPoint(rend, center_x+y, center_y+x);
// 	SDL_RenderDrawPoint(rend, center_x+y, center_y-x);
// 	SDL_RenderDrawPoint(rend, center_x-y, center_y+x);
// 	SDL_RenderDrawPoint(rend, center_x-y, center_y-x);
// 	error = 2*(delta+y)-1;
// 	if((delta < 0) && (error <= 0))
// 	{
// 	    ++x;
// 	    delta+=2 * x + 1;
// 	    continue;
// 	}
// 	if ((delta > 0) && (error > 0))
// 	{
// 	    --y;
// 	    delta-= 2 * y +1;
// 	    continue;
// 	} 
// 	++x;
// 	--y;
// 	delta+=2*(x-y);
//     }
// }
// // TODO: field 

int main(int argc, char* argv[])
{
    sdl_init();
    SDL_Event e;
    //Field field = {100, 100};
    
    bool run = true;
    
    while (run)
    {
	SDL_SetRenderDrawColor(rend, 189, 172, 151, 255);

	while (SDL_PollEvent(&e))
	{
	    switch(e.type)
	    {
		case SDL_QUIT:
		    run = false;
		    break;
		}
	    }
	    SDL_RenderClear(rend);
	    SDL_SetRenderDrawColor(rend, 0, 0, 0, 0);
	    //draw_circle(200, 200, 50);
	    //draw_field(field);

	    SDL_RenderPresent(rend);
	}
	
	SDL_Quit();
	return 0;
    }

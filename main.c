#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include "game.h"

SDL_Window* window = NULL;
SDL_Renderer* rend  = NULL;

#define CELL_SIZE 100
#define SCR_W 410
#define SCR_H 410

SDL_Surface* scr;

void secc(int code)
{
    if (code < 0)
    {
	fprintf(stderr, "SDL error: %s\n", SDL_GetError());
	exit(1);
    }
}
void secc_ttf(int code)
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
TTF_Font* f_base = NULL;

void sdl_init(void)
{
    secc(SDL_Init(SDL_INIT_VIDEO));
    window = SDL_CreateWindow("2048 game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCR_W, SCR_H, 0);
    secp(window);

    rend = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    secp(rend);
    
}

void draw_border(void)
{
    
}

int main(int argc, char* argv[])
{
    sdl_init();
    SDL_Event e;
    
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
	    draw_border();
	    SDL_RenderPresent(rend);
	}

	TTF_CloseFont(f_base);
	TTF_Quit();
	SDL_Quit();
	return 0;
}

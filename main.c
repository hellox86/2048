#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
//#include "game.h"
#include <math.h>
#include <pthread.h>

#define SCR_W 600
#define SCR_H 600
#define CELL_SIZE 100

int x, y, f_size;

SDL_Window* window = NULL;
SDL_Renderer* rend  = NULL;


SDL_Rect cells[16];

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
void sdl_init(void)
{
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "best");
    f_size = 400;
    x = SCR_W/2-(f_size/2);
    y = SCR_H/2-(f_size/2);

    secc(SDL_Init(SDL_INIT_VIDEO));
    window = SDL_CreateWindow("2048 game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCR_W, SCR_H, 0);
    secp(window);
    
    rend = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    secp(rend);    
}
int sgn(float num)
{
	if (num > 0) return 1;
	else if (num < 0) return -1;
	else return 0;
}
void draw_super_ellipse(float a, float b, float n, float xoffset, float yoffset)
{
    int val = 63;
    SDL_FPoint points[val];
   
    int counter = 0;
    for (float angle = 0.0f; angle < M_PI*2 && counter < val; angle+=0.1)
    {
	
	float na = 2.0f/n;
	float x = powf(fabs(cosf(angle)), na)*a*sgn(cosf(angle)) + xoffset;
	float y = powf(fabs(sinf(angle)), na)*b*sgn(sinf(angle)) + yoffset; 
	
	SDL_FPoint pt = {x, y};
	points[counter] = pt;
	
	counter++;
	
	SDL_FRect tmp = {x, y, 1.0f, 1.0f};
	SDL_SetRenderDrawColor(rend, 212, 184, 124, 255);
	SDL_SetRenderDrawColor(rend, 0, 0, 0, 0);
	SDL_RenderFillRectF(rend, &tmp);
	SDL_RenderDrawRectF(rend, &tmp);
	
    } 
    SDL_RenderDrawPointsF(rend, points, 63);
    
}
float sgn2(float x)
{
    return ((x>0)-(x<0))*1;
}

static void fill_field_matrix()
{
    int all_iter = 16;
    // int j = y+50;
    int j = y;
    int i = x-100;
    
    for (int d = 0; d < 4; d++)
    {
	while(i <= f_size && all_iter >= all_iter-4)
	{
	    cells[all_iter].x = i;
	    cells[all_iter].y = j;
	    cells[all_iter].w = 100;
	    cells[all_iter].h = 100;

	    i+=100;
	    all_iter--;	    
	}
	i = x;
	j+=100;
    }
   
}

// void dr_se()
// {
//     for (int i = 0; i < 16; i++)
//     {
//         draw_super_ellipse(50, 50, 10, cells[i].x+50, cells[i].y);
//     }

// }

void init_field()
{
    fill_field_matrix();
    SDL_Rect rect_field = {x, y, f_size, f_size};
    SDL_SetRenderDrawColor(rend, 221, 193, 113, 255);
    SDL_RenderFillRect(rend, &rect_field);
    SDL_SetRenderDrawColor(rend, 212, 184, 103, 255);
    

    SDL_RenderDrawRect(rend, &rect_field);

    for (int i = 0; i < 16; i++)
    {
	SDL_SetRenderDrawColor(rend, 212, 184, 103, 255);

	SDL_RenderDrawRect(rend, &cells[i]);
    }
    
//    dr_se();

}

int main(int argc, char* argv[])
{
    sdl_init();
    SDL_Event e;
    
    bool run = true;
    while (run)
    {
	SDL_SetRenderDrawColor(rend, 250, 248, 239, 255);

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
	    init_field();
	    SDL_RenderPresent(rend);
	   
	}
	
	SDL_Quit();
	return 0;
 }

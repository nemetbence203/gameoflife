#ifndef GRAFIKA_H_INCLUDED
#define GRAFIKA_H_INCLUDED
#include <SDL.h>
#include <SDL2_gfxPrimitives.h>
#include "matrixmuveletek.h"

extern int ablakmeretX;
extern int ablakmeretY;
extern SDL_Window *window;
extern SDL_Renderer *renderer;


void sdl_init(char const *felirat, int szeles, int magas, SDL_Window **pwindow, SDL_Renderer **prenderer);
void kirajzol(SDL_Renderer *renderer, eletter matrix, int ablakmeretX, int ablakmeretY, int cellameretX, int cellameretY);
Uint32 idozit(Uint32 ms, void *param);
void poziciokalkulator(int *cellaX, int *cellaY, int katthelyeX, int katthelyeY, int cellameretX, int cellameretY);

#endif // GRAFIKA_H_INCLUDED

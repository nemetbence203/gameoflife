#include "grafika.h"

int ablakmeretX;
int ablakmeretY;
SDL_Window *window;
SDL_Renderer *renderer;

void sdl_init(char const *felirat, int szeles, int magas, SDL_Window **pwindow, SDL_Renderer **prenderer) {
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        SDL_Log("Nem indithato az SDL: %s", SDL_GetError());
        exit(1);
    }
    SDL_Window *window = SDL_CreateWindow(felirat, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, szeles, magas, 0);
    if (window == NULL) {
        SDL_Log("Nem hozhato letre az ablak: %s", SDL_GetError());
        exit(1);
    }
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);
    if (renderer == NULL) {
        SDL_Log("Nem hozhato letre a megjelenito: %s", SDL_GetError());
        exit(1);
    }
    SDL_RenderClear(renderer);
    *pwindow = window;
    *prenderer = renderer;
}

void kirajzol(SDL_Renderer *renderer, eletter matrix, int ablakmeretX, int ablakmeretY, int cellameretX, int cellameretY){
    boxRGBA(renderer,0,0,ablakmeretX,ablakmeretY,0,0,0,255);
     for(int x = 0; x<matrix.meretX; x++){
        lineRGBA(renderer, x*cellameretX, 0, x*cellameretX, ablakmeretY, 255,255,255,70);
        for(int y = 0; y<matrix.meretY;y++){
            if(matrix.cellak[x][y]){
                boxRGBA(renderer,x*cellameretX, y*cellameretY, (x*cellameretX)+cellameretX, (y*cellameretY)+cellameretY, 0,0,255,255);
            }
        }
    }
    for(int y = 0; y<matrix.meretY;y++){
        lineRGBA(renderer, 0, y*cellameretY, ablakmeretX, y*cellameretY, 255,255,255,70);
    }
}

Uint32 idozit(Uint32 ms, void *param) {
    SDL_Event ev;
    ev.type = SDL_USEREVENT;
    SDL_PushEvent(&ev);
    return ms;
}

void poziciokalkulator(int *cellaX, int *cellaY, int katthelyeX, int katthelyeY, int cellameretX, int cellameretY){
    *cellaX= (katthelyeX-(katthelyeX%cellameretX))/cellameretX;
    *cellaY= (katthelyeY-(katthelyeY%cellameretY))/cellameretY;
}

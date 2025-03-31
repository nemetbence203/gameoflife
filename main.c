#include<windows.h>
#include "grafika.h"


int main(int argc, char *argv[]) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
    GetConsoleScreenBufferInfo(hConsole, &consoleInfo);
    SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
    /* zold konzol mert kurva meno */

    eletter matrix;
    printf("Conway-fele eletjatek\n");
    printf("Szimulacio inditasanak kivalasztasa. Irjon be egyest(1) ha fajlbol olvasna be a kezdeti allapotot, kettest(2) ha kezzel adna meg azt.\n");
    int inditasi_mod;
    int fajlolvasas_returnkodja;
    bool ervenyesvalasz = false;
    while(!ervenyesvalasz){
        inditasi_mod = 0;
        scanf("%d", &inditasi_mod);
        switch(inditasi_mod){
            case 1:
                fajlolvasas_returnkodja = fajlbolbeolvas(&matrix);
                if(fajlolvasas_returnkodja!=0){
                    printf("Adja meg ujra az inditasi mod kodjat, 1 vagy 2:\n");
                    fflush (stdin);
                }else{
                ervenyesvalasz = true;
                }
                break;
            case 2:
                kezzelmegad(&matrix);
                ervenyesvalasz = true;
                break;
            default:
                printf("Csak egyest vagy kettest adjon meg!\n");
                fflush(stdin);
                break;
        }
    }
    /* grafikusan megjelenitett ablak meretenek kiszamitasa, hogy biztosan oszthato legyen a cellak szamaval */
    ablakmeretX = 800-(800%matrix.meretX);
    ablakmeretY = 800-(800%matrix.meretY);
    int cellameretX = ablakmeretX/matrix.meretX;
    int cellameretY = ablakmeretY/matrix.meretY;

    sdl_init("Conway-fele eletjatek, Nemet Bence", ablakmeretX, ablakmeretY, &window, &renderer);
    kirajzol(renderer, matrix, ablakmeretX, ablakmeretY, cellameretX, cellameretY);
    SDL_RenderPresent(renderer);

    bool quit = false;
    bool leptetomod = true;
    SDL_TimerID id = SDL_AddTimer(150, idozit, NULL);
    bool click = false;
    int rajzoltcellaX, rajzoltcellaY;
    bool rajzolt = false;
    /* fo esemenyhurok */
    while (!quit) {
        SDL_Event event;
        SDL_WaitEvent(&event);
        switch (event.type){
            /* egerrel rajzolas a matrixba */
            case SDL_MOUSEBUTTONDOWN:
                if (event.button.button == SDL_BUTTON_LEFT) {
                    click = true;
                    rajzolt = !rajzolt;
                }else if(event.button.button == SDL_BUTTON_RIGHT){
                    reset(&matrix);
                    kirajzol(renderer, matrix, ablakmeretX, ablakmeretY, cellameretX, cellameretY);
                    SDL_RenderPresent(renderer);
                }
                break;
            /* egergomb elengedese */
            case SDL_MOUSEBUTTONUP:
                if (event.button.button == SDL_BUTTON_LEFT) {
                    click = false;
                }
                break;
            /* eger mozdulat */
            case SDL_MOUSEMOTION:
                if (click) {
                    int cellaX, cellaY;
                    poziciokalkulator(&cellaX, &cellaY, event.motion.x, event.motion.y, cellameretX, cellameretY);
                    if(!(cellaX == rajzoltcellaX && cellaY == rajzoltcellaY)){
                        adotthelyenValtoztat(cellaX, cellaY, &matrix, rajzolt);
                        rajzoltcellaX = cellaX;
                        rajzoltcellaY = cellaY;
                        kirajzol(renderer, matrix, ablakmeretX, ablakmeretY, cellameretX, cellameretY);
                        SDL_RenderPresent(renderer);
                    }
                }
                break;
            case SDL_KEYDOWN:
                if(event.key.keysym.sym == SDLK_SPACE){
                    leptetomod = !leptetomod;
                }
                else if(event.key.keysym.sym == SDLK_b && leptetomod){
                        kovetkezoAllapot(&matrix);
                        kirajzol(renderer, matrix, ablakmeretX, ablakmeretY, cellameretX, cellameretY);
                        SDL_RenderPresent(renderer);
                }
                break;
            case SDL_USEREVENT:
                if(!leptetomod){
                    kovetkezoAllapot(&matrix);
                    kirajzol(renderer, matrix, ablakmeretX, ablakmeretY, cellameretX, cellameretY);
                    SDL_RenderPresent(renderer);
                }
                break;
            case SDL_QUIT:
                quit = true;
                break;
        }
    }
    SDL_RemoveTimer(id);
    SDL_Quit();
    felszabadit(matrix);
    return 0;
}

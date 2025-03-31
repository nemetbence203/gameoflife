#include "matrixmuveletek.h"
#include "debugmalloc.h"

void kovetkezoAllapot(eletter *regimatrix){
    eletter ujmatrix;
    ujmatrix.meretX = regimatrix->meretX;
    ujmatrix.meretY = regimatrix->meretY;
    lefoglal(&ujmatrix);
    for(int x = 1; x<regimatrix->meretX-1; x++){
        for(int y = 1; y<regimatrix->meretY-1;y++){
            int szomszedok = szomszedokSzama(regimatrix->cellak, x, y);
            if(regimatrix->cellak[x][y]){
                if(szomszedok==2 || szomszedok==3)ujmatrix.cellak[x][y] = true;
                else ujmatrix.cellak[x][y] = false;
            }else{
                if(szomszedok==3)ujmatrix.cellak[x][y] = true;
            }
        }
    }
    /* uj allapot atmasolasa a regi helyere*/
    for(int x = 0; x<regimatrix->meretX; x++){
        for(int y = 0; y<regimatrix->meretY;y++){
            if(y == regimatrix->meretY-1 || x == regimatrix->meretX-1){
                regimatrix->cellak[x][y] = false;
            }else{
                regimatrix->cellak[x][y] = ujmatrix.cellak[x][y];
            }
        }
    }
    felszabadit(ujmatrix);
    return;
}

void kezdoallapotBeker(eletter *matrix){
        printf("Adja meg a kitolteni kivant cellakat 'x,y' formatumban, CTRL+Z ha vegzett\n");
        int beX;
        int beY;
        while(scanf("%d,%d", &beX, &beY)!=EOF){
                if(beX<0 || beX>=matrix->meretX || beY<0 || beY>=matrix->meretY){
                    printf("Csak ervenyes koordinatat adjon meg!\n");
                }else{
                    matrix->cellak[beX][beY] = !matrix->cellak[beX][beY];
                }
        }
        return;
}

int szomszedokSzama(bool **cellak, int pozX, int pozY){
        int szomszedok = 0;
        /* az egyszeruseg kedveert a vizsgalt cella allapotat is beleszamoljuk, de -1rol indul a szamlalas ha a cella el */
        if(cellak[pozX][pozY]){
            szomszedok = -1;
        }

        for(int x = pozX-1; x <= pozX+1; x++){
            for(int y = pozY-1; y <= pozY+1; y++){
                if(cellak[x][y]){
                    szomszedok++;
                }
            }
        }
        return szomszedok;
}

void lefoglal(eletter *matrix){
        matrix->cellak = (bool**)malloc(matrix->meretX * sizeof(bool*));
        for(int i = 0; i < matrix->meretX; i++){
            matrix->cellak[i] = (bool*)malloc(matrix->meretY * sizeof(bool));
        }
        for(int x = 0; x < matrix->meretX; x++){
            for(int y = 0; y < matrix->meretY; y++){
                matrix->cellak[x][y] = false;
            }
        }
}

void felszabadit(eletter matrix){
        for(int i = 0; i < matrix.meretX; i++){
            free(matrix.cellak[i]);
        }
        free(matrix.cellak);
}

int fajlbolbeolvas(eletter *matrix){
    printf("Adja meg a fajl nevet .txt-vel egyutt(max. 50 karakter):\n");
    char fajlnev[51];
    scanf("%s", fajlnev);
    FILE *fajl = fopen(fajlnev, "r");
    if (fajl == NULL) {
        perror("Hiba tortent a fajl megnyitasakor.\n");
        return 1;
    }
    if(fscanf(fajl,"%d %d", &(matrix->meretX), &(matrix->meretY))!=2){
        printf("Hiba a fajl elso soranak beolvasasakor. Ellenorizze a formatumot a dokumentacio alapjan.\n");
        fclose(fajl);
        return 2;
    }
    if(matrix->meretX < 1 || matrix->meretX>800 || matrix->meretY < 1 || matrix->meretY>800){
        printf("A fajl elso soraban ervenytelen meret szerepel!!\n");
        fclose(fajl);
        return 2;
    }
    lefoglal(matrix);
    for (int x = 0; x < matrix->meretX; x++) {
        for (int y = 0; y < matrix->meretY; y++) {
            int cella;
            if (fscanf(fajl, "%1d", &cella) != 1) {
                fprintf(stderr, "Hiba a fajlban. Ellenorizze a formatumot a dokumentacio alapjan.\n");
                fclose(fajl);
                felszabadit(*matrix);
                return 3;
            }
            if(cella==1){
                matrix->cellak[y][x] = true;
            }else if(cella==0){
                matrix->cellak[y][x] = false;
            }else{
                printf("Hiba az alabbi helyen a fajlban: (%d, %d). Ellenorizze a formatumot a dokumentacio alapjan.\n", x, y);
                felszabadit(*matrix);
                return 3;
            }
        }
    }
    fclose(fajl);
    return 0;
}

void kezzelmegad(eletter *matrix){
    printf("Adja meg az eletter meretet 'X,Y' formatumban! (maximum 800x800-at)\n");
    bool ervenyesmeret = false;
    while(!ervenyesmeret){
        scanf("%d,%d", &matrix->meretX, &matrix->meretY);
        if(matrix->meretX < 1 || matrix->meretX > 800 || matrix->meretY < 1 || matrix->meretY > 800){
            printf("Csak ervenyes meretet adjon meg!\n");
            fflush (stdin);
        }else{
            ervenyesmeret = true;
        }
    }
    lefoglal(matrix);
    kezdoallapotBeker(matrix);
    return;
}

void adotthelyenValtoztat(int X, int Y, eletter *matrix, bool muvelet){
    matrix->cellak[X][Y] = muvelet;
}

void reset(eletter *matrix){
    for(int x = 0; x < matrix->meretX; x++){
        for(int y = 0; y < matrix->meretY; y++){
            matrix->cellak[x][y] = false;
        }
    }
}

#ifndef MATRIXMUVELETEK_H_INCLUDED
#define MATRIXMUVELETEK_H_INCLUDED
#include <stdbool.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct eletter{
    int meretX, meretY;
    bool **cellak;
}eletter;

void kovetkezoAllapot(eletter *regimatrix);
void kezdoallapotBeker(eletter *matrix);
int szomszedokSzama(bool **cellak, int pozX, int pozY);
void lefoglal(eletter *matrix);
void felszabadit(eletter matrix);
int fajlbolbeolvas(eletter *matrix);
void kezzelmegad(eletter *matrix);
void adotthelyenValtoztat(int X, int Y, eletter *matrix, bool muvelet);
void reset(eletter *matrix);


#endif // MATRIXMUVELETEK_H_INCLUDED

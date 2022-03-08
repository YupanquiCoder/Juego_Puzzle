//
//  Tablero.h
//  Juego_Puzzle
//
//  Created by Miguel Ruiz on 27/2/22.
//

#ifndef Tablero_h
#define Tablero_h

#include <stdio.h>
#include "main.h"

extern int Tablero[FILTABLERO][COLTABLERO];

/* Prototipos */
int InicializaTablero(void);
int LimpiaTablero(int pTablero[][7]);
int PintaTablero(void);
int RevisaTablero(int pTablero[][7]);
int BuscaHuecoEnTablero(int pTablero[][7],int* pFila, int* pColumna);
int ResuelveTablero(void);
int PintaTestResumen(long NumTest);


#endif /* Tablero_h */

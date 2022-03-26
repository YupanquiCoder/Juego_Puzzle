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
#include "piezas.h" 

#define NUMMAXLISTANEGRA NUMMAXPRUEBAS

extern int Tablero[FILTABLERO][COLTABLERO];
extern int TableroSoluciones[FILTABLERO][COLTABLERO];

struct ListaNegraPunteros_ {
    int NumPiezasCombi;
    struct CasillaPieza_ CombinacionNegra[9];
};

extern struct ListaNegraPunteros_ ListaNegraPunteros [NUMMAXLISTANEGRA];
extern long int ContCombNegra; /* Contador de Combinaciones en la Lista Negra*/


/* Prototipos */
int InicializaTablero(int pTablero[][7]);
int LimpiaTablero(int pTablero[][7]);
int PintaTablero(int pTablero[][7]);
int RevisaTablero(int pTablero[][7]);
int BuscaHuecoEnTablero(int pTablero[][7],int* pFila, int* pColumna);
int ResuelveTablero(void);
int PintaTestResumen(long NumTest);
int PintaUnaSolucion(int pNumSolucion, int DebugCompleto);

#endif /* Tablero_h */

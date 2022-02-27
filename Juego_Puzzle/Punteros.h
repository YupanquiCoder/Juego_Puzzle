//
//  Punteros.h
//  Juego_Puzzle
//
//  Created by Miguel Ruiz on 26/2/22.
//

#ifndef Punteros_h
#define Punteros_h

#include <stdio.h>
#include "main.h"
#include "piezas.h" 

#define NUMMAXLISTANEGRA 999999



struct ListaNegraPunteros_ {
    int NumPiezasCombi;
    struct CasillaPieza_ CombinacionNegra[9];
};

extern struct CasillaPieza_ BufferPuntero[9];

extern int Punteros[9];


void InicializaPunteros(void);
int IncrementaPunteros(void);
void PintaPunteros(void);

void RellenaOpcionesPuntero(void);
void PintaOpcionesPuntero(void);
void RellenaBufferPuntero(void);
void PintaBufferPuntero(void);
int PunteroEsPosible(struct CasillaPieza_ BuffCheck[CANTIDADPIEZAS]);
int MeteEnListaNegra(struct ListaNegraPunteros_ BuffCheck,int NumPiezas);

#endif /* Punteros_h */

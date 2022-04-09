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
#include "Tablero.h"
#include "piezas.h"
#include "Soluciones.h"

extern struct CasillaPieza_ BufferPuntero[9];

extern int Punteros[9];
extern int SeHaFinalizadoLaCuenta; /* Si 1 -> Ya No se incrementa mas*/


void InicializaPunteros(void);
int IncrementaPunteros(void);
void PintaPunteros(void);

void RellenaBufferPuntero(void);
void PintaBufferPuntero(void);
int PunteroEsPosible(struct CasillaPieza_ BuffCheck[CANTIDADPIEZAS]);

void SaltaCeldasListaNegra(long int NumCeldaListaNegra);
int DameSiguientePunteroValido(void);
int IncrementaBufferPuntero(void);


#endif /* Punteros_h */

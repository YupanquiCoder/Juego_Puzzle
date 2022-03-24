//
//  piezas.h
//  Juego_Puzzle
//
//  Definición de Piezas del Puzzle
//
//  Created by Miguel Ruiz on 11/1/22.
//
#ifndef piezas_h
#define piezas_h

#include "main.h"

extern int Piezas [CANTIDADPIEZAS][CANTIDADORIENTACIONES][FilPiezas][ColPiezas];

struct CasillaPieza_{
    int BuffPieza;
    int BuffOri;
};

int PintaPieza(int NumPieza,int NumOrienta);
void PintaTodasPiezas(void);
int ColocaPieza(int tFil, int tCol, int pNum, int pOri, int pTablero[][COLTABLERO],int DebugCompleto);
int PiezaEsMayor(int NumPieza1,int NumOrienta1,int NumPieza2, int NumOrienta2);
void IncrementaPieza(int* pPieza, int* pOrienta);
void IncrementaOrienta(int* pPieza, int* pOrienta);
void DecrementaOrienta(int* pPieza, int* pOrienta);

#endif /* piezas_h */

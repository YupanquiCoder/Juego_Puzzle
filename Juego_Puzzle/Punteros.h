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
#define NUMMAXSOLUCIONES 50

// Valores de Opciones Punteros
// <0>: [0-0] <1>: [0-1] <2>: [0-2] <3>: [0-3]
// <4>: [1-0] <5>: [1-1] <6>: [1-2] <7>: [1-3]
// <8>: [2-0] <9>: [2-1] <10>:[2-2] <11>:[2-3]
// <12>:[3-0] <13>:[3-1] <14>:[3-2] <15>:[3-3]
// <16>:[4-0] <17>:[4-1] <18>:[4-2] <19>:[4-3]
// <20>:[5-0] <21>:[5-1] <22>:[5-2] <23>:[5-3]
// <24>:[6-0] <25>:[6-1] <26>:[6-2] <27>:[6-3]
// <28>:[7-0] <29>:[7-1] <30>:[7-2] <31>:[7-3]
// <32>:[8-0] <33>:[8-1] <34>:[8-2] <35>:[8-3]


struct ListaNegraPunteros_ {
    int NumPiezasCombi;
    struct CasillaPieza_ CombinacionNegra[9];
};
extern int ContCombNegra; /* Contador de Combinaciones en la Lista Negra*/

struct ListaSoluciones_ {
    double NumPruebaSolucion;
    int PunteroSolucion[9];
    struct CasillaPieza_ CombinacionSolucion[9];
    
};
extern int ContadorSoluciones; /* Indica el número de soluciones encontradas*/

extern struct CasillaPieza_ BufferPuntero[9];

extern int Punteros[9];
extern int SeHaFinalizadoLaCuenta; /* Si 1 -> Ya No se incrementa mas*/


void InicializaPunteros(void);
int IncrementaPunteros(void);
void PintaPunteros(void);

void RellenaOpcionesPuntero(void);
void PintaOpcionesPuntero(void);
void RellenaBufferPuntero(void);
void PintaBufferPuntero(void);
int PunteroEsPosible(struct CasillaPieza_ BuffCheck[CANTIDADPIEZAS]);
int MeteEnListaNegra(struct ListaNegraPunteros_ BuffCheck,int NumPiezas);
void PintaListaNegra(void);
int MeteEnListaSoluciones(struct ListaSoluciones_ BuffCheck,int NumPrueba);
void PintaListaSoluciones(void);
void SaltaCeldasListaNegra(int NumCeldaListaNegra);
int DameSiguientePunteroValido(void);

#endif /* Punteros_h */

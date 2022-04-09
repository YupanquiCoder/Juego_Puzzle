//
//  Soluciones.h
//  Juego_Puzzle
//
//  Created by Miguel Ruiz on 3/4/22.
//

#ifndef Soluciones_h
#define Soluciones_h

#include <stdio.h>
#include "main.h"
#include "piezas.h"
#include "Punteros.h"
#include "Tablero.h"


struct ListaSoluciones_ {
    long int NumPruebaSolucion;
    struct CasillaPieza_ CombinacionSolucion[9];
};

struct PosicionesChincheta_ {
    int FilaChin;
    int ColumnChin;
};

struct BloquesSoluciones_{
    int ContadorSoluciones;
    long int NumeroPruebasRealizadas;
    struct PosicionesChincheta_ PosicionesChincheta;
    struct ListaSoluciones_ ListaSoluciones[NUMMAXSOLUCIONES];
};
extern struct BloquesSoluciones_ BloquesSoluciones[NUMMAXPOSCHINCHETA];

/* Prototipos */
void InicializaBloque(void);
int MeteEnListaSoluciones(struct ListaSoluciones_ BuffCheck,long int NumPrueba);
void PintaListaSoluciones(void);
int PintaUnaSolucion(int pNumSolucion, int DebugCompleto);
void PintaArrayUnaSolucion(int NumSolucion);
void InicializaSoluciones(void);
void PintaSituacionBloquesSoluciones(void);

#endif /* Soluciones_h */

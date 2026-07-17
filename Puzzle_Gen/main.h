//
//  main.h
//  Juego_Puzzle
//
//  Created by Miguel Ruiz on 26/2/22.
//

#ifndef main_h
#define main_h

struct CasillaPieza_ {
    int BuffPieza;
    int BuffOri;
};

struct PosicionesChincheta_ {
    int FilaChin;
    int ColumnChin;
};

/* VARIABLES GLOBALES USADAS*/
#define FILTABLERO 7
#define COLTABLERO 7


#define FilPiezas 5
#define ColPiezas 5
#define CANTIDADPIEZAS 9
#define CANTIDADORIENTACIONES 4


#define NUMMAXSOLUCIONES 5000
#define NUMMAXPOSCHINCHETA 49

/* DEMO */
#define DEBUGPINTAFICHAS 0
#define TESTDEDEMO 2
extern int contTestDemo;
#define NUMMUESTRAPRUEBAS 10000 /* Cada cuántas combinaciones probadas se muestra el progreso */
extern int ContMuestraPruebas;

extern long int PuntPruebas; /* Número de combinaciones pieza/orientación probadas en la búsqueda actual */

/* Prototipos de funciones*/
void MuestraTitulosCredito(void);

#endif /* main_h */

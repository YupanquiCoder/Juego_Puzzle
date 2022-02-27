//
//  main.h
//  Juego_Puzzle
//
//  Created by Miguel Ruiz on 26/2/22.
//

#ifndef main_h
#define main_h

/* VARIABLES GLOBALES USADAS*/
#define FILTABLERO 7
#define COLTABLERO 7


#define NUMMAXPRUEBAS 9000
#define NUMMAXPIEZASPROBADAS 400
#define NUMMAXPRUEBACOMBINACION 2 /* El número de veces que se probará la misma combinación tras una PIEZA COLOCADA*/

#define FilPiezas 5
#define ColPiezas 5
#define CANTIDADPIEZAS 9
#define CANTIDADORIENTACIONES 4

/* DEMO */
#define DEBUGPINTAFICHAS 1
#define TESTDEDEMO 2
extern int contTestDemo;


extern int PuntPruebas; /* Indica en qué prueba estamos ejecutando*/
extern int PuntPieza; /* Indica el puntero a la pieza que se va a colocar*/
extern int PuntOri; /* Indica el puntero a la orientación de la pieza que se va a colocar*/
extern int PuntPiezas; /*Es el número de piezas que se ha probado */
extern int PuntOrdenPieza; /* Es el Orden la pieza que se quiere colocar*/
extern int PuntContColocadas; /*cuenta el número de piezas colocadas en la prueba en curso */
extern int FaseProceso;
extern int ProfundidadFunc;
extern int PrepararNuevaPrueba;

/* Prototipos de funciones*/
int PintaTablero(void);
void PintaTodasPiezas(void);
void LimpiaBuffPiezasAColocar(void);
int ResuelveTableroAvance(void);
int InicializaTablero(void);

int BuscaPrueba55(void);
int BuscaPruebasRepetidas(void);
int BuscaPruebaNoRevisada(void);
void IniciaBuffActual(void);
void PintaBuffActual(void);
void MuestraTitulosCredito(void);
void MuestraPanelPruebasClave(void);
int ResuelveTablero(void);

int MuestraListaResultPruebas(void);
int MuestraListado (int NumPrueba);

#endif /* main_h */

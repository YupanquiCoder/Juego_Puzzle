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


#define NUMMAXPRUEBAS 7250000
#define NUMMAXPIEZASPROBADAS 10
#define NUMMAXPRUEBACOMBINACION 2 /* El número de veces que se probará la misma combinación tras una PIEZA COLOCADA*/

#define FilPiezas 5
#define ColPiezas 5
#define CANTIDADPIEZAS 9
#define CANTIDADORIENTACIONES 4

/* DEMO */
#define DEBUGPINTAFICHAS 0
#define TESTDEDEMO 2
extern int contTestDemo;
extern int MostrarCadaIncrementoDePuntero;
extern int MostrarCadaPunteroValido;
#define NUMMUESTRAPRUEBAS 10000 /* Cuando esté probando se mostrará la prueba cada esas pruebas*/
extern int ContMuestraPruebas; 

struct ListaPruebas_ {
    double NumPrueba;
    struct {
        int PiezaPrueba;
        int OrientaPrueba;
    } CombinacionPrueba[9];
    int Piezascolocadas[9];
    int NumPiezasColocadas;
    struct {
        int PiezaColocada;
        int OrientaColocada;
    } CombinacionColocadas[9];
    struct {
        int OrdenPieza;
        int numPieza;
        int OrientaPieza;
        int ResultadoPieza;
    }PiezaProbada[NUMMAXPIEZASPROBADAS];
    int ResultadoPrueba;
};

extern struct ListaPruebas_ ListaPruebas[NUMMAXPRUEBAS];

extern long int PuntPruebas; /* Indica en qué prueba estamos ejecutando*/
extern int PuntPieza; /* Indica el puntero a la pieza que se va a colocar*/
extern int PuntOri; /* Indica el puntero a la orientación de la pieza que se va a colocar*/
extern int PuntPiezasProbadas; /*Es el número de piezas que se ha probado */
extern int PuntOrdenPieza; /* Es el Orden la pieza que se quiere colocar*/
extern int PuntContColocadas; /*cuenta el número de piezas colocadas en la prueba en curso */
extern int FaseProceso;
extern int ProfundidadFunc;
extern int PrepararNuevaPrueba;

/* Prototipos de funciones*/
void LimpiaBuffPiezasAColocar(void);

void IniciaBuffActual(void);
void PintaBuffActual(void);
void MuestraTitulosCredito(void);
void MuestraPanelPruebasClave(void);
int ResuelveTablero(void);

int MuestraListaResultPruebas(void);
int MuestraListado (long int NumPrueba);

#endif /* main_h */

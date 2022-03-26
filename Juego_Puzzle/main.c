//
//  main.c
//  Juego_Puzzle
//
//  Created by Miguel Ruiz on 11/1/22.
//

#include <stdio.h>
#include <wchar.h>
#include <locale.h>

#include "main.h"
#include "piezas.h" // Definición de las Piezas
#include "Punteros.h"
#include "Tablero.h"


int MuestraListaResultPruebas(void);
int MuestraListado (long int NumPrueba);

/* Variables que controlan el DEBUG*/
int MostrarCadaIncrementoDePuntero=0;
int MostrarCadaPunteroValido=0;
int contTestDemo=TESTDEDEMO;
int ContMuestraPruebas=1; /* Si es 0 NO se muestra ninguna prueba*/

struct ListaPruebas_ ListaPruebas[NUMMAXPRUEBAS];

long int PuntPruebas; /* Indica en qué prueba estamos ejecutando*/
int PuntPieza; /* Indica el puntero a la pieza que se va a colocar*/
int PuntOri; /* Indica el puntero a la orientación de la pieza que se va a colocar*/
int PuntPiezasProbadas; /*Es el número de piezas que se ha probado */
int PuntOrdenPieza; /* Es el Orden la pieza que se quiere colocar*/
int PuntContColocadas; /*cuenta el número de piezas colocadas en la prueba en curso */
int FaseProceso=0;
int ProfundidadFunc=0;
int PrepararNuevaPrueba=0;


struct CasillaPieza_ BufferPiezasAColocar[9];
int PuntBuf=0xffff;


/***************/
int main(int argc, const char * argv[]) {
    
    int MostrarResumen=0;
    char opcion;
    char caracter;
    
    InicializaPunteros();
    InicializaTablero(Tablero);
    MuestraTitulosCredito();
    do
    {
        printf( "\n   1. Pinta los Títulos de Crédito");
        printf( "\n   2. Muestra Lista de Soluciones Encontradas");
        printf( "\n   3. Comenzar a encontrar soluciones");
        printf( "\n   4. Opción 4");
        printf( "\n   9. Salir");
        
        do
        {
            printf( "\n   ¿Qué hacemos? (1-4,9) ");
            fflush( stdin );
            scanf( "%c", &opcion );
            
        } while ( opcion != '1' && opcion != '2' && opcion != '3' && opcion != '4' && opcion != '9' );
        
        
        /* Inicio del anidamiento */
        
        switch ( opcion )
        {
            case '1':
                MuestraTitulosCredito();
                break;
            case '2':
                if(ContadorSoluciones==0)
                    printf("No hay Soluciones todavía en listado\r");
                else
                    PintaListaSoluciones();
                break;
            case '3':
                ContMuestraPruebas=NUMMUESTRAPRUEBAS;
                printf( "OJO este proceso va a llevar varias horas hasta que termine de encontrar\r" );
                printf( "todas las soluciones." );
                printf( "Se mostrará la solución por la que va cada %u Pruebas. ¿Comenzamos? S/N ",ContMuestraPruebas );
                
                fflush( stdin );
                scanf( "%c", &caracter );
                if(caracter == 'S' || caracter == 's'){
                    do
                    {
                        ResuelveTablero();
                        
                        if(MostrarResumen)
                        {
                            MostrarResumen=0;
                            PintaListaSoluciones();
                        }
                        
                    }while (!SeHaFinalizadoLaCuenta);
                }
                
                break;
            case '4': printf( "elegida Opción 4" );
                break;
            case '9': printf( "¿Realmente quieres salir? (S/N)" );
                fflush( stdin );
                scanf( "%c", &caracter );
                if(caracter == 'S' || caracter == 's') opcion=99;
                break;
            default:
                break;
        }
        
        /* Fin del anidamiento */
        
    } while ( opcion != 99 );
    
    
    
    
    return 0;
}


void PintaCombinacionColocadas(int NumTest){
    int i;
    int ContPiezas=0;
    
    ContPiezas=ListaPruebas[NumTest].NumPiezasColocadas;
    printf("   %u Piezas colocadas: ",ContPiezas);
    for (i=0;i<ContPiezas;i++)
    {
        printf("[%u-%u] ",ListaPruebas[NumTest].CombinacionColocadas[i].PiezaColocada,ListaPruebas[NumTest].CombinacionColocadas[i].OrientaColocada);
    }
    printf( "\r");
}

int MuestraListaResultPruebas()
{
    /* Muestra el listado de los resultados de todas las pruebas realizadas*/
    long int TmpContPrueba;
    int i,ContPiezas=0;
    
    
    for(TmpContPrueba=0;TmpContPrueba<=PuntPruebas;TmpContPrueba++){
        
        printf(" PRUEBA: %ld Result: %u  ", TmpContPrueba,ListaPruebas[TmpContPrueba].ResultadoPrueba);
        for (i=0,ContPiezas=0;i<9;i++)
        {
            if(ListaPruebas[TmpContPrueba].Piezascolocadas[i]==0xffff)
                ContPiezas=ContPiezas+1;
        }
        printf("-%u Piezas colocadas: ",ContPiezas);
        for (i=0;i<ContPiezas;i++)
        {
            printf("[%u-%u] ",ListaPruebas[TmpContPrueba].CombinacionColocadas[i].PiezaColocada,ListaPruebas[TmpContPrueba].CombinacionColocadas[i].OrientaColocada);
        }
        printf( "\r");
        
    }
    return 0;
    
}
int MuestraListado (long int NumPrueba){
    /* lista el resultado de una prueba*/
    int i,tmp;
    int ContPiezas=0;
    /* #define NUMMAXPRUEBAS 30
     struct ListaPruebas {
     int NumPrueba;
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
     }ListaPruebas[NUMMAXPRUEBAS];*/
    
    if(NumPrueba<NUMMAXPRUEBAS)
    {
        printf("Mostramos los registros de la prueba [%ld] \n",NumPrueba);
        printf(" Se han Usado las piezas: \n");
        for (i=0;i<9;i++)
        {
            printf("   Pieza %u: ",i);
            if(ListaPruebas[NumPrueba].Piezascolocadas[i]==0xffff) {
                ContPiezas=ContPiezas+1;
                printf("Sí");
            }
            
            else printf("No");
            printf("\n");
        }
        printf(" La combinación de piezas colocadas ha sido: \n");
        printf("   Piezas colocadas: ");
        for (i=0;i<ContPiezas;i++)
        {
            printf("[%u-%u] ",ListaPruebas[NumPrueba].CombinacionColocadas[i].PiezaColocada,ListaPruebas[NumPrueba].CombinacionColocadas[i].OrientaColocada);
        }
        printf("\n");
        printf(" El resultado de la prueba ha sido: \n");
        switch (ListaPruebas[NumPrueba].ResultadoPrueba) {
            case 0:
                printf ("    [0] La Prueba No ha finalizado");
                break;
            case 55:
                printf ("    [55] El Tablero quedó bloqueado");
                break;
            case 99:
                printf ("    [99] El Tablero finalizó!!!! CONSEGUIDO");
                break;
            case 200:
                printf ("    [200] Se paró la prueba por haber probado ya %u Piezas",NUMMAXPIEZASPROBADAS);
                break;
            case 400:
                printf("    [400] Se para porque ya se ha probado la misma combinación %u veces \r\n",NUMMAXPRUEBACOMBINACION);
                break;
            case 500:
                printf("    [500] Se han probado el resto de piezas y no caben \r\n");
                break;
            default:
                printf ("    Resultado Extraño - Revisar");
                break;
        }
        printf("\n");
        printf(" Las Pruebas que se han hecho han sido: \n");
        for (i=0;i<NUMMAXPIEZASPROBADAS;i++)
        {
            if(ListaPruebas[NumPrueba].PiezaProbada[i].OrdenPieza!=0){
                printf("    La Pieza: [%u-%u] Orden: %u  ",ListaPruebas[NumPrueba].PiezaProbada[i].numPieza,ListaPruebas[NumPrueba].PiezaProbada[i].OrientaPieza,ListaPruebas[NumPrueba].PiezaProbada[i].OrdenPieza);
                printf("Result: ");
                tmp=ListaPruebas[NumPrueba].PiezaProbada[i].ResultadoPieza;
                switch (tmp) {
                    case 0:
                        printf("Pieza COLOCADA\n");
                        break;
                    default:
                        printf("Pieza No se coloco porque ");
                        if(tmp<100) printf("Había %u casillas que no cabían\n",tmp);
                        else printf("La pieza se salia del tablero\n");
                        
                        break;
                }
            }
        }
    }
    else{
        printf("No hay tantas pruebas solo hay %u programadas\n\r",NUMMAXPRUEBAS);
    }
    
    return 0;
    
}


void MuestraTitulosCredito()
{
    printf("PROGRAMA para 'decodificar' un puzzle ***********\n\r");
    printf("(c) Miguel Ruiz - 2022 -\n\r");
    
    printf("Consiste en un tablero de %ux%u\n",FILTABLERO,COLTABLERO);
    printf("en el que hay que colocar %u Piezas, las cuales se pueden colocar en %u Orientaciones\n\r",CANTIDADPIEZAS,CANTIDADORIENTACIONES);
    printf("El Tablero tiene una pieza que se puede colocar en distintas coordenadas (Se marca con '9')\r");
    printf("El tablero es:\n\r");
    PintaTablero(Tablero);
    printf("y las piezas son: \n\r");
    PintaTodasPiezas();
    printf("Estan preparadas %u pruebas\n\r",NUMMAXPRUEBAS);
    printf("\nComenzamos con el puntero de pruebas en: \n");
    PintaBufferPuntero();
    
    printf("\n");
    
    if(ContadorSoluciones!=0)
    {
        printf("\nSe Inicializa el Array de soluciones con las ya conocidas: \n");
        PintaListaSoluciones();
    }
    
    printf("\r\n");
    
}


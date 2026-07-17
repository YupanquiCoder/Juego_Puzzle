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
#include "Soluciones.h"
#include "Tablero.h"
#include "piezas.h"
#include "Archivo.h"

/* Variables que controlan el DEBUG*/
int contTestDemo=TESTDEDEMO;
int ContMuestraPruebas=1; /* Si es 0 NO se muestra ninguna prueba*/

long int PuntPruebas; /* Número de combinaciones pieza/orientación probadas en la búsqueda actual*/


/***************/
int main(int argc, const char * argv[]) {

    char opcion;
    char caracter;
    int NumEntrada;
    int s, NumSolucion;
    int SalirBucle;
    int piezasSim[CANTIDADPIEZAS];
    int numSim, esdup;

    InicializaChinchetas();
    AnalizaSimetrias();
    InicializaSoluciones();
    InicializaRutaArchivo();
    CargaSoluciones();
    InicializaTablero(Tablero);
    MuestraTitulosCredito();
    do
    {
        printf( "\n   1. Pinta los Títulos de Crédito");
        printf( "\n   2. Muestra Lista de Soluciones Encontradas");
        printf( "\n   3. Cuadro de Soluciones Probadas");
        printf( "\n   4. Comenzar a encontrar soluciones");
        printf( "\n   5. Pinta una solución ya encontrada");
        printf( "\n   6. Borrar soluciones de un bloque (para volver a buscar)");
        printf( "\n   7. Borrar el archivo completo de soluciones");
        printf( "\n   8. Salir");

        do
        {
            printf( "\n   ¿Qué hacemos? (1-8) ");
            scanf( " %c", &opcion );

        } while ( opcion != '1' && opcion != '2' && opcion != '3' && opcion != '4' && opcion != '5' && opcion != '6' && opcion != '7' && opcion != '8' );
        
        
        /* Inicio del anidamiento */
        
        switch ( opcion )
        {
            case '1':
                MuestraTitulosCredito();
                break;
            case '2':
                {
                    int _hayAlguna = 0, _b;
                    for (_b = 0; _b < NUMMAXPOSCHINCHETA; _b++)
                        if (BloquesSoluciones[_b].ContadorSoluciones > 0) { _hayAlguna = 1; break; }
                    if (!_hayAlguna)
                        printf("No hay Soluciones todavía en ningún bloque.\n");
                    else
                        PintaListaSoluciones();
                }
                break;
            case '3':
                PintaSituacionBloquesSoluciones();
                break;
            case '4':
                ContMuestraPruebas=NUMMUESTRAPRUEBAS;
                printf( "OJO este proceso continua hasta finalizar todas las pruebas, sin detenerse\n" );
                printf( "Se mostrará el progreso cada %u combinaciones probadas.\n",NUMMUESTRAPRUEBAS );
                printf( "¿Qué bloque de soluciones hacemos? (0-%u) ",NUMMAXPOSCHINCHETA-1 );
                fflush( stdin );
                scanf( "%u", &NumEntrada );
                if(NumEntrada>=0 && NumEntrada<NUMMAXPOSCHINCHETA)
                {

                    if(BloquesSoluciones[NumEntrada].NumeroPruebasRealizadas==0){

                        PosChinchetaActual=NumEntrada;

                        InicializaBloque();

                        ResuelveTableroBacktracking();

                        BloquesSoluciones[PosChinchetaActual].NumeroPruebasRealizadas=PuntPruebas;

                        printf("FIN. Se acaban de buscar las soluciones del Bloque: <%u> Posición [%u-%u] \n",PosChinchetaActual,BloquesSoluciones[PosChinchetaActual].PosicionesChincheta.FilaChin,BloquesSoluciones[PosChinchetaActual].PosicionesChincheta.ColumnChin);
                        printf(" Se han probado %ld combinaciones. Se han encontrado %u Soluciones \n",BloquesSoluciones[PosChinchetaActual].NumeroPruebasRealizadas, BloquesSoluciones[PosChinchetaActual].ContadorSoluciones);
                        GuardaSoluciones();
                    }
                    else
                        printf("La Posición <%u> ya se ha probado (%ld pruebas) y se encontraron %u soluciones\n",NumEntrada,BloquesSoluciones[NumEntrada].NumeroPruebasRealizadas,BloquesSoluciones[NumEntrada].ContadorSoluciones);
                }

                break;
            case '5':
                {
                    int _b, _hayAlguna5 = 0;
                    for (_b = 0; _b < NUMMAXPOSCHINCHETA; _b++)
                        if (BloquesSoluciones[_b].ContadorSoluciones > 0) { _hayAlguna5 = 1; break; }

                    if (!_hayAlguna5) {
                        printf("No hay soluciones encontradas en ningún bloque.\n");
                    } else {
                        /* Mostrar bloques disponibles y pedir elección */
                        printf("Bloques con soluciones:\n");
                        for (_b = 0; _b < NUMMAXPOSCHINCHETA; _b++)
                            if (BloquesSoluciones[_b].ContadorSoluciones > 0)
                                printf("  [%d] Posicion [%d-%d] — %u soluciones (%u unicas)\n",
                                       _b,
                                       BloquesSoluciones[_b].PosicionesChincheta.FilaChin,
                                       BloquesSoluciones[_b].PosicionesChincheta.ColumnChin,
                                       BloquesSoluciones[_b].ContadorSoluciones,
                                       BloquesSoluciones[_b].ContadorSoluciones / DivisorSimetrias());
                        printf("¿Qué bloque quieres ver? (0-%u) ", NUMMAXPOSCHINCHETA-1);
                        scanf("%u", &NumEntrada);

                        if (NumEntrada < NUMMAXPOSCHINCHETA && BloquesSoluciones[NumEntrada].ContadorSoluciones > 0) {
                            PosChinchetaActual = NumEntrada;
                            NumSolucion = 0;
                            SalirBucle = 0;
                            do {
                                /* Saltar duplicados simétricos */
                                esdup = 0;
                                for(s = 0; s < NumSolucion && !esdup; s++) {
                                    numSim = 0;
                                    if(EsDuplicadoSimetrico(NumSolucion, s, piezasSim, &numSim))
                                        esdup = 1;
                                }
                                if(!esdup) {
                                    PintaUnaSolucion(NumSolucion, 1);
                                    PintaArrayUnaSolucion(NumSolucion);
                                    printf("Esta es la Solución %u ¿Seguimos con la siguiente? S/N ", NumSolucion);
                                    scanf(" %c", &caracter);
                                    if(caracter == 'N' || caracter == 'n') SalirBucle = 1;
                                }
                                NumSolucion++;
                            } while(NumSolucion < BloquesSoluciones[PosChinchetaActual].ContadorSoluciones && SalirBucle == 0);
                        } else {
                            printf("Bloque no válido o sin soluciones.\n");
                        }
                    }
                }
                break;
                
            case '6':
                PintaSituacionBloquesSoluciones();
                printf( "\n   ¿Qué bloque quieres borrar? (0-%u) ", NUMMAXPOSCHINCHETA-1 );
                fflush( stdin );
                scanf( "%u", &NumEntrada );
                if(NumEntrada >= 0 && NumEntrada < NUMMAXPOSCHINCHETA) {
                    if(BloquesSoluciones[NumEntrada].ContadorSoluciones == 0)
                        printf("El bloque <%u> ya estaba vacío.\n", NumEntrada);
                    else {
                        printf("¿Seguro que quieres borrar el bloque <%u> con %u soluciones? (S/N) ",
                               NumEntrada, BloquesSoluciones[NumEntrada].ContadorSoluciones);
                        scanf( " %c", &caracter );
                        if(caracter == 'S' || caracter == 's')
                            BorraBloqueSoluciones(NumEntrada);
                    }
                }
                break;

            case '7':
                printf("¿Seguro que quieres borrar TODAS las soluciones? (S/N) ");
                scanf( " %c", &caracter );
                if(caracter == 'S' || caracter == 's')
                    BorraArchivoSoluciones();
                break;

            case '8': printf( "¿Realmente quieres salir? (S/N) ");
                scanf( " %c", &caracter );
                if(caracter == 'S' || caracter == 's') opcion=99;
                break;
            default:
                break;
        }
        
        /* Fin del anidamiento */
        
    } while ( opcion != 99 );
    
    return 0;
}


void MuestraTitulosCredito()
{
    printf("PROGRAMA para 'decodificar' un puzzle ***********\n");
    printf("(c) Miguel Ruiz - 2022 -\n");
    
    printf("Consiste en un tablero de %ux%u\n",FILTABLERO,COLTABLERO);
    printf("en el que hay que colocar %u Piezas, las cuales se pueden colocar en %u Orientaciones\n",CANTIDADPIEZAS,CANTIDADORIENTACIONES);
    printf("El Tablero tiene una pieza que se puede colocar en distintas coordenadas (Se marca con '9')\n");
    printf("El tablero es:\n");
    PintaTablero(Tablero);
    printf("y las piezas son: \n");
    PintaTodasPiezas();
    PintaInfoSimetrias();

    printf("\n");
    
    {
        int _i, _posAnalizadas = 0, _totalSoluciones = 0, _divisor = DivisorSimetrias();
        for (_i = 0; _i < NUMMAXPOSCHINCHETA; _i++) {
            if (BloquesSoluciones[_i].NumeroPruebasRealizadas > 0) _posAnalizadas++;
            _totalSoluciones += BloquesSoluciones[_i].ContadorSoluciones;
        }
        if (_totalSoluciones > 0)
            printf("\nEstado actual: analizadas %d posiciones de %d posibles — %d soluciones unicas encontradas.\n",
                   _posAnalizadas, NUMMAXPOSCHINCHETA, _totalSoluciones / _divisor);
    }
    printf("\n");

}

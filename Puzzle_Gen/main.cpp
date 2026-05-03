//
//  main.cpp
//  Puzzle_Gen
//
//  Created by Miguel Ruiz on 24/8/23.
//

#include <stdio.h>
#include <wchar.h>
#include <locale.h>
#include <iostream>
#include "main.h"

int main(int argc, const char * argv[]) {
    char opcion;
    char caracter;
    
    do
    {
        printf( "\n   MENÚ PRINCIPAL:");
        printf( "\n   1. Pinta los Títulos de Crédito");
        printf( "\n   2. Muestra Lista de Soluciones Encontradas");
        printf( "\n   3. Cuadro de Soluciones Probadas");
        printf( "\n   4. Comenzar a encontrar soluciones");
        printf( "\n   5. Pinta una solución ya encontrada");
        printf( "\n   6. Demo 1.000 incrementos de puntero");
        printf( "\n   9. Salir");
        
        do
        {
            printf( "\n   ¿Qué hacemos? (1-6,9) ");
            fflush( stdin );
            scanf( "%c", &opcion );
            
        } while ( opcion != '1' && opcion != '2' && opcion != '3' && opcion != '4' && opcion != '5' && opcion != '6'&& opcion != '9' );
        
        /* Inicio del anidamiento */
        
        switch ( opcion )
        {
            case '1':
                break;
            case '2':
               
                break;
            case '3':
                break;
            case '4':
             
                break;
            case '5':
                break;
                
            case '6':
                printf( "Demostración de como se incrementa el puntero 1.000 veces:\n" );
                 
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

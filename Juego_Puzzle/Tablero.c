//
//  Tablero.c
//  Juego_Puzzle
//
//  Created by Miguel Ruiz on 27/2/22.
//

#include "Tablero.h"

int Tablero[FILTABLERO][COLTABLERO];

int InicializaTablero()
{
    LimpiaTablero(Tablero);
    /*Definimos el reto*/
    Tablero[3][2]=9; /*Donde está el 9 es la Chincheta*/
    return 0;
}

int LimpiaTablero(int pTablero[][7]){
    int i,j;
    
    for(i=0;i<7;i++)
        for(j=0;j<7;j++)
            pTablero[i][j]=0x0;
    return 0;
}

int PintaTablero(){
    int fila=0;
    int col=0;
    int tmp;
    
    printf(" TABLERO\r");
    printf(" ┌─────────────────────┐\r");
    for(fila=0;fila<7;fila++){
        printf(" │");
        for(col=0;col<7;col++){
            tmp=Tablero[fila][col];
            if(tmp<10) printf(" ");
            if(!tmp) printf("° ");
            else printf("%u ",tmp);
        }
        printf("│\r\n");
    }
    printf(" └─────────────────────┘\n\r");
    return 0;
    
}

int RevisaTablero(int pTablero[][7]){
    /* Revisa la situación del tablero
     Devuelve:
     0=ERROR;
     1-50=Número de casillas en 0
     >50 número de casillas en 0 y HAY ALGUNA AISLADA-Solución imposible
     99=Tablero Terminado EXITO*/
    int resultado=0;
    int imposible=0;
    int i,j,tmp,contImposible;
    
    for(i=0;i<7;i++)
        for(j=0;j<7;j++){
            tmp=pTablero[i][j];
            if(tmp==0) {
                resultado++;
                contImposible=0;
                /*la casilla Tablero[i][j] está a 0 ¿Está aislada?*/
                if(i!=0) if(Tablero[i-1][j]==0)contImposible++;
                if(i<6) if(Tablero[i+1][j]==0)contImposible++;
                if(j!=0) if(Tablero[i][j-1]==0)contImposible++;
                if(j<6) if(Tablero[i][j+1]==0)contImposible++;
                if(contImposible==0) imposible=1;
            }
        }
    
    if(resultado==0) {
        resultado=99; /* Tablero completado EXITO*/
        printf("!!! Solución !!!!!\n");
        MuestraListado(PuntPruebas);
        PintaTablero();
    }
    else if(imposible==1)resultado+=50;
    
    return resultado;
}

int BuscaHuecoEnTablero(int pTablero[][7],int* pFila, int* pColumna){
    /* Busca en el tablero, desde la casilla 0,0 hasta la 7,7 el primer hueco (que hay aun 0)
     Devuelve:
     0=NO hay ningúna casilla en 0
     1=Encontrada casilla
     */
    int i=0,j=0,tmp=0;
    
    tmp=1;
    for(i=0;i<7 && tmp!=0;i++)
        for(j=0;j<7 && tmp!=0;j++){
            tmp=pTablero[i][j];
            if(!tmp) {
                *pFila=i;
                *pColumna=j;
                break;
            }
        }
    if(tmp!=0)return 0;
    
    return 1;
}

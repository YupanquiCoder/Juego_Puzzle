//
//  main.c
//  Juego_Puzzle
//
//  Created by Miguel Ruiz on 11/1/22.
//

#include <stdio.h>
#include "piezas.h" // Definición de las Piezas

int Tablero[7][7];

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
    printf("|-------------| TABLERO\r");
    for(fila=0;fila<7;fila++){
        printf(" ");
        for(col=0;col<7;col++){
            printf("%u,",Tablero[fila][col]);
        }
        printf("\r\n");
    }
    printf("|-------------|\n\r");
            return 0;

}
int PintaPieza(int NumPieza,int NumOrienta){
    int fila=0;
    int col=0;
    int caracter;
    if(NumPieza>8 || NumOrienta>3){
        printf("PintaPieza:ERROR Parametros\r\n");
        return 1;
    }
    printf("|---------| Pieza %u; Orientación %u\r", NumPieza, NumOrienta);
    for(fila=0;fila<FilPiezas;fila++){
        printf(" ");
        for(col=0;col<ColPiezas;col++){
            caracter=Piezas[NumPieza][NumOrienta][fila][col];
//            if(caracter==0) caracter=0x20;
            printf("%u,",caracter);
        }
        printf("\r\n");
    }
    printf("|---------|\r");
            return 0;
}

int ColocaPieza(int tFil, int tCol, int pNum, int pOri){
    /*
     Coloca una pieza en el Tablero:
        Parámetros:
            Posición del Tablero (Fila y columna) tFil, tCol
            Número de Pieza (Numero y Orientación) pNum, pOri
        Return.
            0 - Pieza colocada
            <>0- No cabe
            Resultado <100 = Número de casillas que no caben
            Resultado >100 = La casilla queda fuera del tablero y hay x-100 casillas que no caben
     */
//    Punteros
    int ptFil,ptCol;
    int i,j,tmp1,tmp2;
    int Entra=0;
    
    ptFil=tFil;
    ptCol=tCol;

    
    printf("Tablero Antes:\n");
    PintaTablero();
    
    printf("Pieza a Colocar\n");
    PintaPieza(pNum,pOri);
        /* Comprueba si se va a poder colocar (todos los valores !=0 de Pieza están libres en tablero
         Si una casilla <>0 de la pieza está fuera del tablero=> NO Cabe*/
    for(i=0;i<FilPiezas;i++)
        for(j=0;j<ColPiezas;j++){
            tmp1=Piezas[pNum][pOri][i][j];
            if(tmp1!=0){
                if(tFil+i>6||tCol+j>6) Entra+=100;
            }
            tmp2=Tablero[tFil+i][tCol+j];
            if(tmp1!=0 && tmp2!=0) Entra++; /* Entra dirá el número de piezas que NO entran */
//            printf("Tablero [%u][%u]=%u\r",tFil+i,tCol+j,tmp2 );
//            printf("Pieza[%u][%u][%u][%u]=%u\r",pNum,pOri,i,j,tmp1);
        }
    if(Entra!=0) printf("Hay %u Casillas que no entran\n\r",Entra);
    else printf("Sí entra\n\r");
    
    if(Entra==0){
        /* Cabe, entonces la colocamos*/
    for(i=0;i<FilPiezas;i++)
        for(j=0;j<ColPiezas;j++){
            tmp1=Piezas[pNum][pOri][i][j];
            if(tmp1!=0) Tablero[tFil+i][tCol+j]=tmp1;
        }
    }
    printf("Tablero Después:\n");
    PintaTablero();
    return Entra;
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
         
    if(resultado==0) resultado=99; /* Tablero completado EXITO*/
    else if(imposible==1)resultado+=50;
        
    return resultado;
}

int main(int argc, const char * argv[]) {
    
    int tmp;
    
    LimpiaTablero(Tablero);
    /*Definimos el reto*/
    Tablero[3][2]=9; /*Donde está el 9 es la Chincheta*/
//    Tablero[0][2]=9; /*Donde está el 9 es la Chincheta*/
    /* Para forzar Bloqueo tablero*/
    Tablero[1][4]=99;
    Tablero[3][4]=99;
    Tablero[2][5]=99;
    Tablero[2][3]=99;
//    PintaTablero();
//    PintaPieza(0,3);
   
    tmp=ColocaPieza(6,6,8,0);
    printf("Coloca devuelve %u\r\n",tmp);
    printf("Situación:%u\r\n",RevisaTablero(Tablero));
    /* Solución POSIBLE
    ColocaPieza(0,0,0,0);
    printf("Situación:%u",RevisaTablero(Tablero));
    ColocaPieza(0,4,1,0);
    printf("Situación:%u\r\n",RevisaTablero(Tablero));
    ColocaPieza(1,0,2,0);
    ColocaPieza(0,2,3,0);
    ColocaPieza(4,0,4,0);
    ColocaPieza(2,3,5,0);
    ColocaPieza(5,2,6,0);
    ColocaPieza(3,5,7,0);
    printf("Situación:%u",RevisaTablero(Tablero));
    ColocaPieza(6,1,8,0);
    printf("Situación:%u",RevisaTablero(Tablero));
    */
    
    return 0;
}

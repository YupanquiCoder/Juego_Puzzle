//
//  main.c
//  Juego_Puzzle
//
//  Created by Miguel Ruiz on 11/1/22.
//

#include <stdio.h>

int Tablero[7][7];
int Piezas [9][4][4][4]={
    {//    Pieza 1
    /*N*/  {{1,1,1,0},
            {0,1,0,0},
            {0,0,0,0},
            {0,0,0,0},},
    /*S*/  {{1,0,0,0},
            {1,1,0,0},
            {1,0,0,0},
            {0,0,0,0},},
    /*E*/  {{0,1,0,0},
            {1,1,1,0},
            {0,0,0,0},
            {0,0,0,0},},
    /*O*/  {{0,1,0,0},
            {1,1,0,0},
            {0,1,0,0},
            {0,0,0,0},},
    } /*Fin Pieza 1*/
}; // 9 piezas de 4*4 (4 orientaciones)

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
    printf("|------| Pieza %u; Orientación %u\r", NumPieza, NumOrienta);
    for(fila=0;fila<4;fila++){
        printf(" ");
        for(col=0;col<4;col++){
            caracter=Piezas[NumPieza][NumOrienta][fila][col];
//            if(caracter==0) caracter=0x20;
            printf("%u,",caracter);
        }
        printf("\r\n");
    }
    printf("|------|\r");
            return 0;
}

int main(int argc, const char * argv[]) {
    
    // insert code here...
    
    LimpiaTablero(Tablero);
    /*Definimos el reto*/
    Tablero[2][3]=9; /*Donde está el 9 es la Chincheta*/
    PintaTablero();
    PintaPieza(0,3);
        
    return 0;
}

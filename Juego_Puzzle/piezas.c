//
//  piezas.c
//  Juego_Puzzle
//
//  Created by Miguel Ruiz on 27/2/22.
//

#include <stdio.h>
#include "piezas.h" // Definición de las Piezas
#include "Tablero.h"


int Piezas [CANTIDADPIEZAS][CANTIDADORIENTACIONES][FilPiezas][ColPiezas]={
    {//    Pieza 0
    /*N*/  {{01,01,01,00,00},
            {00,01,00,00,00},
            {00,00,00,00,00},
            {00,00,00,00,00},
            {00,00,00,00,00},},
    /*S*/  {{02,00,00,00,00},
            {02,02,00,00,00},
            {02,00,00,00,00},
            {00,00,00,00,00},
            {00,00,00,00,00},},
    /*E*/  {{00,03,00,00,00},
            {03,03,03,00,00},
            {00,00,00,00,00},
            {00,00,00,00,00},
            {00,00,00,00,00},},
    /*O*/  {{00,04,00,00,00},
            {04,04,00,00,00},
            {00,04,00,00,00},
            {00,00,00,00,00},
            {00,00,00,00,00},},
    }, /*Fin Pieza 0*/
    {//    Pieza 1
    /*N*/  {{10,10,10,00,00},
            {00,10,10,00,00},
            {00,00,10,00,00},
            {00,00,00,00,00},
            {00,00,00,00,00},},
    /*S*/  {{00,00,11,00,00},
            {00,11,11,00,00},
            {11,11,11,00,00},
            {00,00,00,00,00},
            {00,00,00,00,00},},
    /*E*/  {{12,00,00,00,00},
            {12,12,00,00,00},
            {12,12,12,00,00},
            {00,00,00,00,00},
            {00,00,00,00,00},},
    /*O*/  {{13,13,13,00,00},
            {13,13,00,00,00},
            {13,00,00,00,00},
            {00,00,00,00,00},
            {00,00,00,00,00},},
    }, /*Fin Pieza 1*/
    {//    Pieza 2
    /*N*/  {{20,00,00,00,00},
            {20,20,00,00,00},
            {20,20,00,00,00},
            {20,00,00,00,00},
            {00,00,00,00,00},},
    /*S*/  {{21,21,21,21,00},
            {00,21,21,00,00},
            {00,00,00,00,00},
            {00,00,00,00,00},
            {00,00,00,00,00},},
    /*E*/  {{00,22,00,00,00},
            {22,22,00,00,00},
            {22,22,00,00,00},
            {00,22,00,00,00},
            {00,00,00,00,00},},
    /*O*/  {{00,23,23,00,00},
            {23,23,23,23,00},
            {00,00,00,00,00},
            {00,00,00,00,00},
            {00,00,00,00,00},},
    }, /*Fin Pieza 2*/
    {//    Pieza 3
    /*N*/  {{00,30,00,00,00},
            {30,30,30,00,00},
            {30,30,30,00,00},
            {00,00,00,00,00},
            {00,00,00,00,00},},
    /*S*/  {{31,31,00,00,00},
            {31,31,31,00,00},
            {31,31,00,00,00},
            {00,00,00,00,00},
            {00,00,00,00,00},},
    /*E*/  {{32,32,32,00,00},
            {32,32,32,00,00},
            {00,32,00,00,00},
            {00,00,00,00,00},
            {00,00,00,00,00},},
    /*O*/  {{00,33,33,00,00},
            {33,33,33,00,00},
            {00,33,33,00,00},
            {00,00,00,00,00},
            {00,00,00,00,00},},
    }, /*Fin Pieza 3*/
    {//    Pieza 4
        /*N*/  {{00,40,40,00,00},
                {40,40,00,00,00},
                {40,00,00,00,00},
                {00,00,00,00,00},
                {00,00,00,00,00},},
        /*S*/  {{41,41,00,00,00},
                {00,41,41,00,00},
                {00,00,41,00,00},
                {00,00,00,00,00},
                {00,00,00,00,00},},
        /*E*/  {{00,00,42,00,00},
                {00,42,42,00,00},
                {42,42,00,00,00},
                {00,00,00,00,00},
                {00,00,00,00,00},},
        /*O*/  {{43,00,00,00,00},
                {43,43,00,00,00},
                {00,43,43,00,00},
                {00,00,00,00,00},
                {00,00,00,00,00},},
    }, /*Fin Pieza 4*/
    {//    Pieza 5
        /*N*/  {{00,00,50,00,00},
                {50,50,50,00,00},
                {50,50,50,00,00},
                {00,50,00,00,00},
                {00,00,00,00,00},},
        /*S*/  {{00,51,51,00,00},
                {51,51,51,00,00},
                {00,51,51,51,00},
                {00,00,00,00,00},
                {00,00,00,00,00},},
        /*E*/  {{00,52,00,00,00},
                {52,52,52,00,00},
                {52,52,52,00,00},
                {52,00,00,00,00},
                {00,00,00,00,00},},
        /*O*/  {{53,53,53,00,00},
                {00,53,53,53,00},
                {00,53,53,0,00},
                {00,00,00,00,00},
                {00,00,00,00,00},},
    }, /*Fin Pieza 5*/
    {//    Pieza 6
        /*N*/  {{60,60,00,00,00},
                {00,00,00,00,00},
                {00,00,00,00,00},
                {00,00,00,00,00},
                {00,00,00,00,00},},
        /*S*/  {{61,00,00,00,00},
                {61,00,00,00,00},
                {00,00,00,00,00},
                {00,00,00,00,00},
                {00,00,00,00,00},},
        /*E*/  {{62,62,00,00,00},
                {00,00,00,00,00},
                {00,00,00,00,00},
                {00,00,00,00,00},
                {00,00,00,00,00},},
        /*O*/  {{63,00,00,00,00},
                {63,00,00,00,00},
                {00,00,00,00,00},
                {00,00,00,00,00},
                {00,00,00,00,00},},
    }, /*Fin Pieza 6*/
    {//    Pieza 7
        /*N*/  {{00,70,00,00,00},
                {00,70,00,00,00},
                {70,70,00,00,00},
                {00,70,00,00,00},
                {00,00,00,00,00},},
        /*S*/  {{00,71,00,00,00},
                {71,71,71,71,00},
                {00,00,00,00,00},
                {00,00,00,00,00},
                {00,00,00,00,00},},
        /*E*/  {{72,00,00,00,00},
                {72,72,00,00,00},
                {72,00,00,00,00},
                {72,00,00,00,00},
                {00,00,00,00,00},},
        /*O*/  {{73,73,73,73,00},
                {00,00,73,00,00},
                {00,00,00,00,00},
                {00,00,00,00,00},
                {00,00,00,00,00},},
    }, /*Fin Pieza 7*/
    {//    Pieza 8
        /*N*/  {{80,80,80,80,80},
                {00,00,00,00,00},
                {00,00,00,00,00},
                {00,00,00,00,00},
                {00,00,00,00,00},},
        /*S*/  {{81,00,00,00,00},
                {81,00,00,00,00},
                {81,00,00,00,00},
                {81,00,00,00,00},
                {81,00,00,00,00},},
        /*E*/  {{82,82,82,82,82},
                {00,00,00,00,00},
                {00,00,00,00,00},
                {00,00,00,00,00},
                {00,00,00,00,00},},
        /*O*/  {{83,00,00,00,00},
                {83,00,00,00,00},
                {83,00,00,00,00},
                {83,00,00,00,00},
                {83,00,00,00,00},},
    }, /*Fin Pieza 8*/
}; // 9 piezas de 5*5 (4 orientaciones)


int PintaPieza(int NumPieza,int NumOrienta){
    int fila=0;
    int col=0;
    int caracter;
    if(NumPieza>8 || NumOrienta>3){
        printf("PintaPieza:ERROR Parametros\r\n");
        return 1;
    }
    printf("Pieza: [%u-%u]\r", NumPieza, NumOrienta);
    printf("┌─────────────────┐\r");
    for(fila=0;fila<FilPiezas;fila++){
        printf("│ ");
        for(col=0;col<ColPiezas;col++){
            caracter=Piezas[NumPieza][NumOrienta][fila][col];
            if(caracter<10) printf(" ");
            if(!caracter) printf("° ");
            else printf("%u ",caracter);
        }
        printf(" │\r\n");
    }
    printf("└─────────────────┘\r");
    
    return 0;
}

void PintaTodasPiezas()
{
    int fila=0;
    int col=0;
    int caracter;
    int tmpNumPieza=0,tmpNumOrienta=0;
    
    for(tmpNumPieza=0;tmpNumPieza<9;tmpNumPieza++)
    {
        printf("Pieza: [%u]\r", tmpNumPieza);
        printf("Orienta [%u-0]        [%u-1]                [%u-2]                [%u-3] \r",tmpNumPieza,tmpNumPieza,tmpNumPieza,tmpNumPieza);
        printf("┌─────────────────┐  ┌─────────────────┐  ┌─────────────────┐  ┌─────────────────┐ \r");
        
        for(fila=0;fila<FilPiezas;fila++)
        {
            printf("│ ");
            for(col=0;col<ColPiezas;col++){
                caracter=Piezas[tmpNumPieza][tmpNumOrienta][fila][col];
                if(caracter<10) printf(" ");
                if(!caracter) printf("° ");
                else printf("%u ",caracter);
            }
            printf(" │  │ ");
            for(col=0;col<ColPiezas;col++){
                caracter=Piezas[tmpNumPieza][tmpNumOrienta+1][fila][col];
                if(caracter<10) printf(" ");
                if(!caracter) printf("° ");
                else printf("%u ",caracter);
            }
            printf(" │  │ ");
            for(col=0;col<ColPiezas;col++){
                caracter=Piezas[tmpNumPieza][tmpNumOrienta+2][fila][col];
                if(caracter<10) printf(" ");
                if(!caracter) printf("° ");
                else printf("%u ",caracter);
            }
            printf(" │  │ ");
            for(col=0;col<ColPiezas;col++){
                caracter=Piezas[tmpNumPieza][tmpNumOrienta+3][fila][col];
                if(caracter<10) printf(" ");
                if(!caracter) printf("° ");
                else printf("%u ",caracter);
            }
            printf(" │\r\n");
        }
        
        printf("└─────────────────┘  └─────────────────┘  └─────────────────┘  └─────────────────┘\r");
    }
    
}

int ColocaPieza(int tFil, int tCol, int pNum, int pOri, int pTablero[][COLTABLERO],int DebugCompleto){
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
    /* DebugCompleto =1: Se muestra todo el proceso de colocación
       DebugCompleto =0: Sólo se muestra el Tablero completo*/
    //    Punteros
    int ptFil,ptCol;
    int i,j,tmp1,tmp2;
    int Entra=0;
    int DesplaIzq=0;
    
    ptFil=tFil;
    ptCol=tCol;
    
    
    if( contTestDemo<TESTDEDEMO || DEBUGPINTAFICHAS || DebugCompleto)
    {
        //            printf("Tablero Antes:\n");
        //            PintaTablero(pTablero);
        
        printf("Pieza a Colocar\n");
        PintaPieza(pNum,pOri);
    }
    
    /* Se calcula el desplazamiento de la pieza a la izquierda para que la primera pieza ocupada coincida con el hueco*/
    for(j=0;j<ColPiezas;j++){
        
        if(Piezas[pNum][pOri][0][j]==0)DesplaIzq++; /*solo se comprueba la primera fila*/
        else break;
    }
    /* Comprueba si se va a poder colocar (todos los valores !=0 de Pieza están libres en tablero
     Si una casilla <>0 de la pieza está fuera del tablero=> NO Cabe*/
    for(i=0;i<FilPiezas;i++)
        for(j=0;j<ColPiezas;j++){
            tmp1=Piezas[pNum][pOri][i][j];
            if(tmp1!=0){
                if(tFil+i>6||tCol-DesplaIzq+j>6||tCol-DesplaIzq+j<0) Entra+=100;/*si se sale por la derecha*/
            }
            tmp2=pTablero[tFil+i][tCol+j-DesplaIzq];
            if(tmp1!=0 && tmp2!=0) Entra++; /* Entra dirá el número de piezas que NO entran */
            //            printf("Tablero [%u][%u]=%u\r",tFil+i,tCol+j,tmp2 );
            //            printf("Pieza[%u][%u][%u][%u]=%u\r",pNum,pOri,i,j,tmp1);
        }
    if(contTestDemo<TESTDEDEMO || DEBUGPINTAFICHAS || DebugCompleto)
    {
        if(Entra!=0) printf("Hay %u Casillas que no entran\n\r",Entra);
        else printf("Sí entra\n\r");
    }
    if(Entra==0){
        /* Cabe, entonces la colocamos*/
        for(i=0;i<FilPiezas;i++)
            for(j=0;j<ColPiezas;j++){
                tmp1=Piezas[pNum][pOri][i][j];
                if(tmp1!=0) pTablero[tFil+i][tCol+j-DesplaIzq]=tmp1;
            }
    }
    if( contTestDemo<TESTDEDEMO || DEBUGPINTAFICHAS ||DebugCompleto){
        printf("Tablero Después:\n");
        PintaTablero(pTablero);
    }
    return Entra;
}

int PiezaEsMayor(int NumPieza1,int NumOrienta1,int NumPieza2, int NumOrienta2){
    /* Se le pasan dos piezas y devuelve:
     0 - La pieza 1 NO es mayor que la Pieza 2
     1 - La Pieza 1 Sí es mayor que la pieza 2
     55 - Las dos piezas son iguales
     22 - Resultado Erróneo*/
    if(NumPieza1>CANTIDADPIEZAS-1 || NumOrienta1>CANTIDADORIENTACIONES-1 ||NumPieza2>CANTIDADPIEZAS-1 || NumOrienta2>CANTIDADORIENTACIONES-1 ) return 22; /* Parámetros erróneos*/
    
    if(NumPieza1==NumPieza2 && NumOrienta1==NumOrienta2) return 55;
    if(NumPieza1>NumPieza2) return 1;
    if(NumPieza1<NumPieza2) return 0;
    /*Piezas son iguales*/
    if(NumOrienta1>NumOrienta2) return 1;
    if(NumOrienta1<NumOrienta2) return 0;
    return 0x22; /*Esto no debería pasar*/
}

void IncrementaPieza(int* pPieza, int* pOrienta)
{ /* Incrementa la Pieza OJO solo incrementa la Pieza y la deja en la orientación 0 y si llega a la Pieza [8-?] pasa a la [0-0]*/
    if(*pPieza==8){
        *pPieza=0;
    }
    else
    {
        *pPieza=*pPieza+1;
        *pOrienta=0;
    }
}

void IncrementaOrienta(int* pPieza, int* pOrienta)
{ /* Incrementa la Pieza a la siguiente orientación y si llega a la Pieza [8-3] paas a la [0-0]*/
    if(*pPieza==8){
        if(*pOrienta==3)
        {
            *pPieza=0;
            *pOrienta=0;
        }
        else *pOrienta=*pOrienta+1;
    }
    else
    {
        if(*pOrienta==3)
        {
            *pPieza=*pPieza+1;
            *pOrienta=0;
        }
        else *pOrienta=*pOrienta+1;
    }
}

void DecrementaOrienta(int* pPieza, int* pOrienta)
{ /* Decrementa la Pieza a la siguiente orientación y si llega a la Pieza [0-0] paas a la [8-3]*/
    if(*pPieza==0){
        if(*pOrienta==0)
        {
            *pPieza=8;
            *pOrienta=3;
        }
        else *pOrienta=*pOrienta-1;
    }
    else
    {
        if(*pOrienta==0)
        {
            *pPieza=*pPieza-1;
            *pOrienta=3;
        }
        else *pOrienta=*pOrienta-1;
    }
}

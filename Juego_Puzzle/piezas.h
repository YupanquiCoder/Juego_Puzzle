//
//  piezas.h
//  Juego_Puzzle
//
//  Definición de Piezas del Puzzle
//
//  Created by Miguel Ruiz on 11/1/22.
//
#define FilPiezas 5
#define ColPiezas 5
#define CANTIDADPIEZAS 9
#define CANTIDADORIENTACIONES 4


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


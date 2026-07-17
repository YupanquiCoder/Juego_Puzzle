//
//  Tablero.c
//  Juego_Puzzle
//
//  Created by Miguel Ruiz on 27/2/22.
//

#include "Tablero.h"
#include "Soluciones.h"

int Tablero[FILTABLERO][COLTABLERO];
int TableroSoluciones[FILTABLERO][COLTABLERO];

/* Posiciones Chincheta */
int NumPosChincheta;
int PosChinchetaActual;



void InicializaChinchetas(void)
{
    int i;
    int tmpFila,tmpCol;
    
    tmpFila=0;
    tmpCol=0;
    
    for(i=0;i<NUMMAXPOSCHINCHETA;i++){
        BloquesSoluciones[i].PosicionesChincheta.FilaChin=tmpFila;
        BloquesSoluciones[i].PosicionesChincheta.ColumnChin =tmpCol;
        
        /* Incremento las pieza*/
        if(tmpCol<6) tmpCol=tmpCol+1;
        else{ /* tmpCol=6*/
            if(tmpFila<6){
                tmpFila=tmpFila+1;
                tmpCol=0;
            }
            
        }
            
    }
    
    NumPosChincheta=49;
    PosChinchetaActual=0;
}

int InicializaTablero(int pTablero[][7])
{
    int tmpFila,tmpCol;
    LimpiaTablero(pTablero);
    /*Definimos el reto*/
    
    /*Donde está el 9 es la Chincheta*/
    tmpFila=BloquesSoluciones[PosChinchetaActual].PosicionesChincheta.FilaChin;
    tmpCol=BloquesSoluciones[PosChinchetaActual].PosicionesChincheta.ColumnChin;
    
    pTablero[BloquesSoluciones[PosChinchetaActual].PosicionesChincheta.FilaChin][BloquesSoluciones[PosChinchetaActual].PosicionesChincheta.ColumnChin]=9;
    return 0;
}

int LimpiaTablero(int pTablero[][7]){
    int i,j;
    
    for(i=0;i<7;i++)
        for(j=0;j<7;j++)
            pTablero[i][j]=0x0;
    return 0;
}

int PintaTablero(int pTablero[][COLTABLERO])
{
    int fila=0;
    int col=0;
    int tmp;
    
    printf(" TABLERO\n");
    printf(" ┌─────────────────────┐\n");
    for(fila=0;fila<7;fila++){
        printf(" │");
        for(col=0;col<7;col++){
            tmp=pTablero[fila][col];
            if(tmp<10) printf(" ");
            if(!tmp) printf("° ");
            else printf("%u ",tmp);
        }
        printf("│\n");
    }
    printf(" └─────────────────────┘\n");
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
        resultado=99;
    }
    else
        if(imposible==1)resultado+=50;
    
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

long int PruebasBacktracking; /* Cuenta las combinaciones pieza/orientación probadas en la búsqueda actual */

static int ResuelveBacktrackRec(int piezasUsadas[CANTIDADPIEZAS], struct CasillaPieza_ combinacion[CANTIDADPIEZAS], int numColocadas)
{
    /* Backtracking recursivo clásico:
     Busca el primer hueco, prueba cada pieza/orientación no usada aún.
     Si encaja: sigue colocando piezas; si el tablero termina, se guarda como solución.
     Al volver de la recursión siempre se deshace la colocación (QuitaPieza) para probar la siguiente combinación. */
    int fila,col,p,o,tmp,tmpTab,i;
    struct ListaSoluciones_ CeldaSoluciones;

    if(!BuscaHuecoEnTablero(Tablero,&fila,&col))
        return 0; /* Tablero ya lleno: no debería llegar aquí, RevisaTablero ya habría dado 99 antes */

    for(p=0;p<CANTIDADPIEZAS;p++){
        if(piezasUsadas[p]) continue;
        for(o=0;o<CANTIDADORIENTACIONES;o++){

            PruebasBacktracking=PruebasBacktracking+1;
            tmp=ColocaPieza(fila,col,p,o,Tablero,0);

            if(tmp==0){
                piezasUsadas[p]=1;
                combinacion[numColocadas].BuffPieza=p;
                combinacion[numColocadas].BuffOri=o;

                tmpTab=RevisaTablero(Tablero);
                if(tmpTab==99){
                    for(i=0;i<CANTIDADPIEZAS;i++)
                        CeldaSoluciones.CombinacionSolucion[i]=combinacion[i];
                    PuntPruebas=PruebasBacktracking;
                    MeteEnListaSoluciones(CeldaSoluciones,PruebasBacktracking);
                } else if(tmpTab<=50){
                    /* No está bloqueado: seguimos colocando piezas */
                    ResuelveBacktrackRec(piezasUsadas,combinacion,numColocadas+1);
                }
                /* Si tmpTab>50 el tablero ha quedado bloqueado: no seguimos, deshacemos abajo */

                QuitaPieza(fila,col,p,o,Tablero);
                piezasUsadas[p]=0;
            }

            if(ContMuestraPruebas!=0)
            {
                ContMuestraPruebas=ContMuestraPruebas+1;
                if(ContMuestraPruebas>NUMMUESTRAPRUEBAS)
                {
                    printf(" ... %ld combinaciones probadas\n",PruebasBacktracking);
                    ContMuestraPruebas=1;
                }
            }
        }
    }
    return 0;
}

int ResuelveTableroBacktracking(void)
{
    int piezasUsadas[CANTIDADPIEZAS]={0};
    struct CasillaPieza_ combinacion[CANTIDADPIEZAS];

    PruebasBacktracking=0;
    ResuelveBacktrackRec(piezasUsadas,combinacion,0);
    PuntPruebas=PruebasBacktracking;
    return 0;
}



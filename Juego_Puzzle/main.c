//
//  main.c
//  Juego_Puzzle
//
//  Created by Miguel Ruiz on 11/1/22.
//

#include <stdio.h>
#include <wchar.h>
#include <locale.h>

#include "piezas.h" // Definición de las Piezas

/* VARIABLES GLOBALES USADAS*/
#define FILTABLERO 7
#define COLTABLERO 7
int Tablero[FILTABLERO][COLTABLERO];


#define NUMMAXPRUEBAS 9000
#define NUMMAXPIEZASPROBADAS 400
#define NUMMAXPRUEBACOMBINACION 2 /* El número de veces que se probará la misma combinación tras una PIEZA COLOCADA*/

int MuestraListaResultPruebas();
int MuestraListado (int NumPrueba);
int BuscaLaSiguienteCombinacion(int NumPrueba,int* pPieza, int* pOrienta);


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
    int RevisionPrueba;
    int RevisandoPrueba;
}ListaPruebas[NUMMAXPRUEBAS];

int PuntPruebas; /* Indica en qué prueba estamos ejecutando*/
int PuntPieza; /* Indica el puntero a la pieza que se va a colocar*/
int PuntOri; /* Indica el puntero a la orientación de la pieza que se va a colocar*/
int PuntPiezas; /*Es el número de piezas que se ha probado */
int PuntOrdenPieza; /* Es el Orden la pieza que se quiere colocar*/
int PuntContColocadas; /*cuenta el número de piezas colocadas en la prueba en curso */
int FaseProceso=0;
int ProfundidadFunc=0;
int PrepararNuevaPrueba=0;

struct{
    int BuffPieza;
    int BuffOri;
}BufferPiezasAColocar[9];
int PuntBuf=0xffff;

struct{
    int BuffPieza;
    int BuffOri;
}BuffPiezasActual[CANTIDADPIEZAS-1];
int PuntBufActual=0xffff;

/* DEMO */
#define DEBUGPINTAFICHAS 1
#define TESTDEDEMO 2
int contTestDemo=1;

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

int PintaTestResumen(int NumTest)
{
    
    int ContPiezas=0;
    int i;
    
    if(NumTest<=PuntPruebas)
    {
        /*Se pinta un resumen del Test NumTest*/
        printf(" PRUEBA: %u Result: %u Revis: [%u] Test: %u ", NumTest,ListaPruebas[NumTest].ResultadoPrueba,ListaPruebas[NumTest].RevisandoPrueba,ListaPruebas[NumTest].RevisionPrueba);
        
        ContPiezas=ListaPruebas[NumTest].NumPiezasColocadas;
        printf("   %u Piezas colocadas: ",ContPiezas);
        for (i=0;i<ContPiezas;i++)
        {
            printf("[%u-%u] ",ListaPruebas[NumTest].CombinacionColocadas[i].PiezaColocada,ListaPruebas[NumTest].CombinacionColocadas[i].OrientaColocada);
        }
        printf( "\r");
        return 0;
    }
    return 0xffff;/* ERROR de parámetros*/
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
    int DesplaIzq=0;
    
    ptFil=tFil;
    ptCol=tCol;
    
    
    if( contTestDemo<TESTDEDEMO || DEBUGPINTAFICHAS)
    {
        //            printf("Tablero Antes:\n");
        //            PintaTablero();
        
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
            tmp2=Tablero[tFil+i][tCol+j-DesplaIzq];
            if(tmp1!=0 && tmp2!=0) Entra++; /* Entra dirá el número de piezas que NO entran */
            //            printf("Tablero [%u][%u]=%u\r",tFil+i,tCol+j,tmp2 );
            //            printf("Pieza[%u][%u][%u][%u]=%u\r",pNum,pOri,i,j,tmp1);
        }
    if(contTestDemo<TESTDEDEMO || DEBUGPINTAFICHAS)
    {
        if(Entra!=0) printf("Hay %u Casillas que no entran\n\r",Entra);
        else printf("Sí entra\n\r");
    }
    if(Entra==0){
        /* Cabe, entonces la colocamos*/
        for(i=0;i<FilPiezas;i++)
            for(j=0;j<ColPiezas;j++){
                tmp1=Piezas[pNum][pOri][i][j];
                if(tmp1!=0) Tablero[tFil+i][tCol+j-DesplaIzq]=tmp1;
            }
    }
    if( contTestDemo<TESTDEDEMO || DEBUGPINTAFICHAS){
        printf("Tablero Después:\n");
        PintaTablero();
    }
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
int MuestraListaResultPruebas()
{
    /* Muestra el listado de los resultados de todas las pruebas realizadas*/
    int TmpContPrueba,i,j,ContPiezas=0;
    
    
    for(TmpContPrueba=0;TmpContPrueba<=PuntPruebas;TmpContPrueba++){
        
        printf(" PRUEBA: %u Result: %u Revis: [%u] Test: %u ", TmpContPrueba,ListaPruebas[TmpContPrueba].ResultadoPrueba,ListaPruebas[TmpContPrueba].RevisandoPrueba,ListaPruebas[TmpContPrueba].RevisionPrueba);
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
int MuestraListado (int NumPrueba){
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
     int RevisionPrueba;
     int RevisandoPrueba;
     }ListaPruebas[NUMMAXPRUEBAS];*/
    
    if(NumPrueba<NUMMAXPRUEBAS)
    {
        printf("Mostramos los registros de la prueba [%u] \n",NumPrueba);
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

void LimpiaBuffPiezasAColocar()
{
    int i;
    
    PuntBuf=0;
    
    for(i=0;i<CANTIDADPIEZAS;i++)
    {
        BufferPiezasAColocar[i].BuffPieza = 0xffff;
        BufferPiezasAColocar[i].BuffOri = 0xffff;
    }
}

void RellenaBuffPiezasAColocar(int NumPrueba,int numPiezas)
{
    int i,j;
    //    struct{
    //        int BuffPieza;
    //        int BuffOri;
    //    }BufferPiezasAColocar[9];
    //    int PuntBuf=0xffff;
    /* OJO El buffer se rellena al revés Para ir */
    
    LimpiaBuffPiezasAColocar();
    
    for(i=0,j=numPiezas;i<numPiezas+1;i++,j--)
    {
        BufferPiezasAColocar[i].BuffPieza = ListaPruebas[NumPrueba].CombinacionColocadas[j].PiezaColocada;
        BufferPiezasAColocar[i].BuffOri = ListaPruebas[NumPrueba].CombinacionColocadas[j].OrientaColocada;
        
    }
    PuntBuf=numPiezas; /*Ojo empieza desde 0*/
    
}

int ResuelveTableroAvance(){
    /* La función devuelve:
     200: Se han probado NUMMAXPIEZASPROBADAS sin tener resultado final -> Este no debería pasar, lo normal es salir con 400
     400: Desde colocar una pieza, se ha probado NUMMAXPRUEBACOMBINACION la misma combinación
     500: Se han probado el resto de piezas y no caben
     55: Esta prueba se debe parar porque el Tablero resultante se ha bloqueado
     99: El Tablero se ha terminado ¡ÉXITO!
     */
    int tmpfilaTab,tmpcolTab;/*Usados para buscar hueco*/
    int tmp=0,tmpTab=0;
    int i,j;
    int SeHaColocadoAlgo=0;
    int ptmpResultadoFunc=0;
    int ActPuntPruebas,ActPuntPieza,ActPuntOri;
    int ActPuntPiezas,ActPuntOrdenPieza,ActResultadoPieza;
    int IndPiezaColocada=0;
    int ContadorMismaPrueba=0;
    
    /* Comprobamos primero Si el buffer de piezas a colocar hay algo*/
    if(PuntBuf!=0xffff){
        /* Hay algo que colocar*/
        /* El puntero apunta a la pieza a colocar*/
        
        PuntPieza=BufferPiezasAColocar[PuntBuf].BuffPieza;
        PuntOri=BufferPiezasAColocar[PuntBuf].BuffOri;
        if(PuntBuf==0) PuntBuf=0xffff;
        else PuntBuf=PuntBuf-1;
    }
    
    if(ListaPruebas[PuntPruebas].Piezascolocadas[PuntPieza]==0)
    {
        /* Revisamos si la siguiente combinación ya se ha probado al menos NUMMAXPRUEBACOMBINACION*/
        /* la última fila probada está en: PuntPiezas */
        
        /* Salvo la situación actual de los punteros*/
        ActPuntPruebas=PuntPruebas;
        ActPuntPieza=PuntPieza;
        ActPuntOri=PuntOri;
        ActPuntPiezas=PuntPiezas;
        ActPuntOrdenPieza=PuntOrdenPieza;
        
        for(i=PuntPiezas;i!=0;i--){
            /* Buscamos la última pieza Colocada (Resultado Prueba =0*/
            if(ListaPruebas[PuntPruebas].PiezaProbada[i].ResultadoPieza==0)
                IndPiezaColocada=i;
        }
        for(i=IndPiezaColocada+1;i<ActPuntPiezas;i++)
        {
            if(ListaPruebas[PuntPruebas].PiezaProbada[i].OrdenPieza==ActPuntOrdenPieza &&
               ListaPruebas[PuntPruebas].PiezaProbada[i].numPieza==ActPuntPieza &&
               ListaPruebas[PuntPruebas].PiezaProbada[i].OrientaPieza==ActPuntOri &&
               ListaPruebas[PuntPruebas].PiezaProbada[i].ResultadoPieza!=0)
                ContadorMismaPrueba=ContadorMismaPrueba+1;
            if(ContadorMismaPrueba==NUMMAXPRUEBACOMBINACION){
                ListaPruebas[PuntPruebas].ResultadoPrueba=400;
                return 400;
            }
            
        }
        BuscaHuecoEnTablero(Tablero,&tmpfilaTab,&tmpcolTab);
        if(contTestDemo<TESTDEDEMO || DEBUGPINTAFICHAS)
            printf("Coloca la pieza [%u-%u] en fila:%u, columna%u\r\n",PuntPieza,PuntOri,tmpfilaTab,tmpcolTab);
        tmp=ColocaPieza(tmpfilaTab,tmpcolTab,PuntPieza,PuntOri);
        
        /*Si tmp =0 colocada, otros valores NO cabe*/
        /*Apuntamos el resultado*/
        /*La pieza PuntPieza (PuntOri) se ha intentado colocar*/
        ListaPruebas[PuntPruebas].PiezaProbada[PuntPiezas].numPieza=PuntPieza;
        ListaPruebas[PuntPruebas].PiezaProbada[PuntPiezas].OrientaPieza=PuntOri;
        ListaPruebas[PuntPruebas].PiezaProbada[PuntPiezas].ResultadoPieza=tmp;
        ListaPruebas[PuntPruebas].PiezaProbada[PuntPiezas].OrdenPieza=PuntOrdenPieza;
        PuntPiezas=PuntPiezas+1;
        if(PuntPiezas>NUMMAXPIEZASPROBADAS)
        {/*paramos de probar piezas*/
            ListaPruebas[PuntPruebas].ResultadoPrueba=200;
            return 200;
        }else{
            if(tmp==0)
            {
                /*La pieza se ha colocado */
                
                /*Marcamos FFFF en las casillas donde se ha usado piezas*/
                ListaPruebas[PuntPruebas].Piezascolocadas[PuntPieza]=0xffff;
                
                ListaPruebas[PuntPruebas].CombinacionColocadas[PuntContColocadas].PiezaColocada=PuntPieza;
                ListaPruebas[PuntPruebas].CombinacionColocadas[PuntContColocadas].OrientaColocada=PuntOri;
                PuntContColocadas=PuntContColocadas+1;
                ListaPruebas[PuntPruebas].NumPiezasColocadas=PuntContColocadas;
                
                PuntOri=0; /*Para que vuelva a la orientación*/
                /*Si la pieza se ha colocado pasamos a la siguiente pieza*/
                SeHaColocadoAlgo=1;
                
                /* Vamos a ver si el tablero está bien */
                tmpTab=RevisaTablero(Tablero);
                if(tmpTab==99){
                    /*Tablero terminado!!!*/
                    ListaPruebas[PuntPruebas].ResultadoPrueba=99;
                    return 99;
                }else{
                    if(tmpTab>50){
                        /*Tablero Bloqueado */
                        ListaPruebas[PuntPruebas].ResultadoPrueba=55;
                        return 55;
                    }
                }
            }
        }
        if(SeHaColocadoAlgo){
            /* Ojo esto hace que la siguiente que se prueba siempre sea la 0-0 */
            PuntPieza=0;
            PuntOri=0;
            PuntOrdenPieza=PuntOrdenPieza+1;
            
        }else
        { /*No se ha colocado*/
            if(PuntPieza>CANTIDADPIEZAS-1)
            {
                ListaPruebas[PuntPruebas].ResultadoPrueba=500;
                return 500; /*Fin cambiando la primera pieza */
            }
            else
            {
                BuscaLaSiguienteCombinacion(PuntPruebas,&PuntPieza,&PuntOri);
            }
        }
        
    }
    else
    { /* La pieza que toca ya se ha usado (Colocado en esta prueba*/
        PuntPieza=PuntPieza+1;
        if(PuntPieza>8) PuntPieza=0;
        PuntOri=0;
    }
    
    ptmpResultadoFunc=ResuelveTableroAvance();
    return ptmpResultadoFunc;
}

int InicializaTablero()
{
    LimpiaTablero(Tablero);
    /*Definimos el reto*/
    Tablero[3][2]=9; /*Donde está el 9 es la Chincheta*/
    return 0;
}

int BuscaPrueba55()
{
    /* Busca la primera prueba cuyo resultado es 55 y que no se haya revisada ya (las revisadas se marcan como 33 o 44*/
    int i;
    for(i=0;i<PuntPruebas;i++){
        if(ListaPruebas[i].ResultadoPrueba==55 && ListaPruebas[i].RevisionPrueba==0)
            return i;
    }
    return 0xffFF; /* NO hay ninguna prueba 55 que no se haya probado*/
}

int BuscaPruebasRepetidas(){
    /* Busca de todas las pruebas que No se han revisado (RevisiónPrueba !=33 cuales no están repetidas
     Si está repetida Se marca como 44 => Repetidas NO se vuelven a tratar*/
    int PuntTestRev;
    int PuntRevis;
    int i=0;
    int SonIguales=1;
    
    for(PuntTestRev=0;PuntTestRev<=PuntPruebas;PuntTestRev++){
        for(PuntRevis=PuntTestRev+1;PuntRevis<=PuntPruebas;PuntRevis++){
            if(ListaPruebas[PuntRevis].RevisionPrueba==0){
                for(i=0,SonIguales=1;i<9;i++)
                {
                    if(ListaPruebas[PuntTestRev].CombinacionColocadas[i].PiezaColocada!=ListaPruebas[PuntRevis].CombinacionColocadas[i].PiezaColocada || ListaPruebas[PuntTestRev].CombinacionColocadas[i].OrientaColocada!=ListaPruebas[PuntRevis].CombinacionColocadas[i].OrientaColocada)
                        SonIguales=0;
                }
                if(SonIguales){
                    ListaPruebas[PuntRevis].RevisionPrueba=44;
                    SonIguales=1;
                    if(contTestDemo<TESTDEDEMO || DEBUGPINTAFICHAS) printf("El Test %u es igual al %u -> Marcamos con 44\n",PuntTestRev,PuntRevis);
                }
            }
        }
    }
    
    return 0;
}

int BuscaSiLaPruebaEsRepetida(int NumPrueba){
    /* Función llamada tras finalizar una prueba.
     Se recorre el listado desde la prueba 0 hasta la NumPrueba-1 para ver si la que se acaba de hacer está repetida
     Si está repetida Se marca como 44 => Repetidas NO se vuelven a tratar
     Devuelve
     0= el Test NumPrueba NO se ha encontrado prueba igual
     0xffff= El Test NumPrueba se ha encontrado un Test Igual y NumPrueba se ha marcado con 44
     */
    int PuntTestRev;
    int i=0;
    int SonIguales=1;
    
    for(PuntTestRev=0;PuntTestRev<NumPrueba;PuntTestRev++){
        for(i=0,SonIguales=1;i<9;i++)
        {
            if(ListaPruebas[PuntTestRev].CombinacionColocadas[i].PiezaColocada!=ListaPruebas[NumPrueba].CombinacionColocadas[i].PiezaColocada || ListaPruebas[PuntTestRev].CombinacionColocadas[i].OrientaColocada!=ListaPruebas[NumPrueba].CombinacionColocadas[i].OrientaColocada)
                SonIguales=0;
        }
        if(SonIguales){
            ListaPruebas[NumPrueba].RevisionPrueba=44;
            SonIguales=1;
            if(contTestDemo<TESTDEDEMO || DEBUGPINTAFICHAS) printf("La Prueba %u es igual a la %u -> Marcamos [%u] con 44\n",NumPrueba,PuntTestRev,NumPrueba);
            
            return 0xffff;
        }
    }
    return 0;
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


void IncrementaOrienta(int* pPieza, int* pOrienta)
{ /* Incrementa la Pieza a la siguiente orientación y si llega a la Pieza [8-3] paas a la [0-0]*/
    if(*pPieza==8){
        if(*pOrienta==3) *pPieza=0;
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

struct  {
    int NumPrueba;
    int Profundidad;
    int PiezaIni;
    int OrienIni;
    int PiezaActual;
    int OrienActual;
    int NivelProbando;/* Es la que voy */
    int TestNivelProbando; /*Es la prueba donde hemos cambiado la pieza de Nivel Probando*/
    int NivelSecundario;
    int FinPrueba;
}PruebasClave[50];

int PuntPruebaClave=0;
int CreandoPruebaClave=0;

int BuscaLaSiguienteCombinacion(int NumPrueba,int* pPieza, int* pOrienta)
{
    /* Función llamada cuando toca probar la siguiente pieza
     nos encontramos que en Combinación colocadas tenemos las piezas colocadas ya en esta prueba (Se han colocado NumPiezas colocadas
     Busco hacia atrás una prueba en la que se hayan colocado las mismas piezas.
     
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
     int RevisionPrueba;
     int RevisandoPrueba;
     }ListaPruebas[NUMMAXPRUEBAS];
     
     En ListaPruebas[NumPrueba].CombinacionColocadas[] tenemos las NumPiezas Colocadas que se han colocado
     Buscamos desde NumPrueba hasta 0 si ya se ha probado esa combinación y devuelve la siguiente pieza que se debería probar que es la Última + 1
     
     */
    int PuntTestRev;
    int PuntTestInicial;
    int i=0;
    int SonIguales=1;
    int HayQueIncrementar=0;
    int tmpNumColocadas;
    int sigPieza1=0xffff, sigOrienta1=0xffff;/* aqui se guarda la mayor*/
    int ContadorPruebasIguales=0;
    
    struct {
        int tmpPiezaColoc;
        int tmpOrientaColoc;
    } CombiColocadasTmp[9];
    
    //    *pPieza=5;
    //    *pOrienta=2;
    //    return 0;
    
    /* Comprobamos primero Si el buffer de piezas a colocar hay algo*/
    if(PuntBuf!=0xffff){
        /* Hay algo que colocar*/
        /* El puntero apunta a la pieza a colocar*/
        
        *pPieza=BufferPiezasAColocar[PuntBuf].BuffPieza;
        *pOrienta=BufferPiezasAColocar[PuntBuf].BuffOri;
        if(PuntBuf==0) PuntBuf=0xffff;
        else PuntBuf=PuntBuf-1;
    }
    else{
        /*No hay mas piezas que colocar en BufferPiezas a Colocar*/
        
        /* y ya No estamos creando una prueba clave Pero en PuntPRuebaClave está la prueba que tenemos que atender
         PruebaClave Profundidad es el número de piezas que tiene esta prueba NivelProbando; indica la pieza que estamos probando*/
        
        tmpNumColocadas=ListaPruebas[NumPrueba].NumPiezasColocadas;
        if(1 || tmpNumColocadas>0)
        {
            printf("[BUSCO]****BUSCO COMBINACIÓN Prueba Actual: [%u] *******\n",NumPrueba);
            printf("[BUSCO] La Siguiente Pieza es [%u-%u]\n",*pPieza,*pOrienta);
            /* Inicializo CombicolocadasTmp con el valor 0xffff*/
            for(i=0;i<9;i++){
                CombiColocadasTmp[i].tmpPiezaColoc=0xffff;
                CombiColocadasTmp[i].tmpOrientaColoc=0xffff;
            }
            /* Relleno CombicolocadasTmp con la combinación de la prueba que quiero revisar*/
            printf("[BUSCO]La Combinación de la prueba [%u] es:",NumPrueba);
            for(i=0;i<tmpNumColocadas;i++){
                CombiColocadasTmp[i].tmpPiezaColoc=ListaPruebas[NumPrueba].CombinacionColocadas[i].PiezaColocada;
                printf("[%u-",CombiColocadasTmp[i].tmpPiezaColoc);
                CombiColocadasTmp[i].tmpOrientaColoc=ListaPruebas[NumPrueba].CombinacionColocadas[i].OrientaColocada;
                printf("%u]",CombiColocadasTmp[i].tmpOrientaColoc);
            }
            printf("\n");
            
            PuntTestInicial=PruebasClave[PuntPruebaClave].NumPrueba;
            
            
            for(PuntTestRev=PuntTestInicial;PuntTestRev<NumPrueba;PuntTestRev++)
            {
                /* Revisamos desde La prueba que toca de Clave hasta la prueba anterior hasta el anterior al actual */
                /* en al prueba acual tenemos las pruebas colocadas*/
                for(i=0,SonIguales=1;i<tmpNumColocadas;i++)
                {
                    if(ListaPruebas[PuntTestRev].CombinacionColocadas[i].PiezaColocada != CombiColocadasTmp[i].tmpPiezaColoc || ListaPruebas[PuntTestRev].CombinacionColocadas[i].OrientaColocada != CombiColocadasTmp[i].tmpOrientaColoc)
                        SonIguales=0;
                }
                if(SonIguales)
                { /* Las tmpNuColocadas piezas de NumPrueba son iguales la prueba PuntTestRev*/
                    /* Miramos si hay otra pieza colocada en en PuntTestRev*/
                    
                    if(ListaPruebas[PuntTestRev].NumPiezasColocadas>tmpNumColocadas)
                    {
                        printf("[BUSCO] Encontrada Prueba igual en [%u] que tiene %u Piezas\n",PuntTestRev,ListaPruebas[PuntTestRev].NumPiezasColocadas);
                        /*Al menos hay 1 pieza mas colocada, guardamos esa en */
                        sigPieza1=ListaPruebas[PuntTestRev].CombinacionColocadas[tmpNumColocadas].PiezaColocada;
                        sigOrienta1=ListaPruebas[PuntTestRev].CombinacionColocadas[tmpNumColocadas].OrientaColocada;
                        if( PiezaEsMayor(sigPieza1,sigOrienta1,*pPieza,*pOrienta))
                        { /* La nueva Pieza es mayor que la que teníamos guardada*/
                            *pPieza=sigPieza1;
                            *pOrienta=sigOrienta1;
                            HayQueIncrementar=0;
                            IncrementaOrienta(&*pPieza,&*pOrienta);
                            ContadorPruebasIguales=ContadorPruebasIguales+1;
                            printf("[BUSCO] La nueva Pieza <Mayor> es:[%u-%u] Probada %u veces\n",*pPieza,*pOrienta,ContadorPruebasIguales);
                            if(*pPieza==8 && *pOrienta==3){
                                printf("OJO llegamos a la 8-3\n");
                                /*Comprobamos si la pieza 8 (Laúltima) ya se ha puesto en la combinación*/
                                if(ListaPruebas[PuntPruebas].Piezascolocadas[*pPieza]==0xffff)
                                {
                                    printf("OJO llegamos a la 8-3 y ya no hay mas\n");
                                }
                            }
                        }
                    }
                    SonIguales=1;
                }
            }
        }
        
        if(HayQueIncrementar){
            /* Incrementa la pieza para la siguiente*/
            IncrementaOrienta(&*pPieza,&*pOrienta);
            
            printf("[BUSCO] Resultado Incrementado [%u-%u]\n",*pPieza,*pOrienta);
        }
        return 0;
    }
    return 0;
}

int BuscaPruebaNoRevisada()
{
    /* Busca la primera prueba cuyo resultado es >50 y que no se haya revisada ya (las revisadas se marcan como 33 o 44 o 22*/
    int i;
    for(i=0;i<PuntPruebas;i++){
        if(ListaPruebas[i].ResultadoPrueba>50){
            if(ListaPruebas[i].RevisionPrueba==0 || ListaPruebas[i].RevisionPrueba<10 )
                return i;
        }
        
    }
    return 0xFFFF; /* NO hay ninguna prueba >100 que no se haya probado*/
}



void IniciaBuffActual()
{
    /*
     struct{
     int BuffPieza;
     int BuffOri;
     }BuffPiezasActual[CANTIDADPIEZAS-1];
     int PuntBufActual=0xffff;
     */
    int i;
    for(i=0;i<CANTIDADPIEZAS;i++){
        BuffPiezasActual[i].BuffPieza=0xffff;
        BuffPiezasActual[i].BuffOri=0xffff;
        PuntBufActual=0;
    }
    return;
}
int MeteBuffActual(int PiezaEntra,int OrientaEntra)
{
    if(PuntBufActual<CANTIDADPIEZAS)
    {
        BuffPiezasActual[PuntBufActual].BuffPieza=PiezaEntra;
        BuffPiezasActual[PuntBufActual].BuffOri=OrientaEntra;
        PuntBufActual=PuntBufActual+1;
    }
    else
        return 0xffff;
    return 0;
}
void PintaBuffActual(){
    int i;
    
    printf("Punt:<%u>",PuntBufActual);
    for (i=0;i<CANTIDADPIEZAS;i++)
    {
        printf("[%u-%u] ",BuffPiezasActual[i].BuffPieza,BuffPiezasActual[i].BuffOri);
    }
}


void MuestraTitulosCredito()
{
    printf("PROGRAMA para 'decodificar' un puzzle ***********\n\r");
    printf("(c) Miguel Ruiz - 2022 -\n\r");
    
    printf("Consiste en un tablero de %ux%u\n",FILTABLERO,COLTABLERO);
    printf("en el que hay que colocar %u Piezas, las cuales se pueden colocar en %u Orientaciones\n\r",CANTIDADPIEZAS,CANTIDADORIENTACIONES);
    printf("El Tablero tiene una pieza que se puede colocar en distintas coordenadas (Se marca con '9')\r");
    printf("El tablero es:\n\r");
    PintaTablero();
    printf("y las piezas son: \n\r");
    PintaTodasPiezas();
    printf("Estan preparadas %u pruebas\n",NUMMAXPRUEBAS);
    
    printf("\r\n");
    
}

void MuestraPanelPruebasClave()
{
//    struct  {
//        int NumPrueba;
//        int Profundidad;
//        int PiezaIni;
//        int OrienIni;
//        int PiezaActual;
//        int OrienActual;
//        int NivelProbando;/* Es la que voy */
//        int TestNivelProbando; /*Es la prueba donde hemos cambiado la pieza de Nivel Probando*/
//        int NivelSecundario;
//        int FinPrueba;
//    }PruebasClave[50];
    //
    //int PuntPruebaClave=0;
    //int CreandoPruebaClave=0;
    
    int i=0;
    int Seguimos=1;
    printf("[CLAVE] PanelPruebas Clave\n" );
    
    while(Seguimos){
        printf(" <%u> Prueba Clave [%u]: Pieza Inicial [%u-%u] Ultim Pieza [%u-%u] Profund[%u] FIN <%u> NivProb <%u> TestNivProb <%u> NivSec <%u> \n" ,i,PruebasClave[i].NumPrueba,PruebasClave[i].PiezaIni,PruebasClave[i].OrienIni,PruebasClave[i].PiezaActual,PruebasClave[i].OrienActual,PruebasClave[i].Profundidad, PruebasClave[i].FinPrueba, PruebasClave[i].NivelProbando,PruebasClave[i].TestNivelProbando,PruebasClave[i].NivelSecundario);
        i=i+1;
        if(PruebasClave[i].NumPrueba==0)
            Seguimos=0;
    }
    
    return;
}


int ResuelveTablero()
{
    int ptmpResultadoFunc=0;
    int tmpTab;
    int SeguimosBucle=1;
    int i,j;
    int tmpPieza,tmpOrienta;
    int SalirBucle=0;
    
    PuntPieza=0;
    PuntOri=0;
    
    while(SeguimosBucle)
    {
        /* Comenzamos pruebas*/
        
        if(PuntPruebas!=0)
            BuscaLaSiguienteCombinacion(PuntPruebas,&PuntPieza,&PuntOri);
        
        if(ListaPruebas[PuntPruebas].Piezascolocadas[PuntPieza]==0)
        {
            
            /*La pieza PuntPieza (PuntOri) se intenta colocar*/
            ListaPruebas[PuntPruebas].PiezaProbada[PuntPiezas].numPieza=PuntPieza;
            ListaPruebas[PuntPruebas].PiezaProbada[PuntPiezas].OrientaPieza=PuntOri;
            ListaPruebas[PuntPruebas].PiezaProbada[PuntPiezas].ResultadoPieza=0; /* Pieza colocada*/
            ListaPruebas[PuntPruebas].PiezaProbada[PuntPiezas].OrdenPieza=PuntOrdenPieza;
            
            /*Se ha colocado una pieza*/
            
            PuntOrdenPieza=PuntOrdenPieza+1;
            
            /*La pieza se ha colocado */
           
            
            /*Marcamos FFFF en las casillas donde se ha usado piezas*/
            ListaPruebas[PuntPruebas].Piezascolocadas[PuntPieza]=0xffff;
            
            ListaPruebas[PuntPruebas].CombinacionColocadas[PuntContColocadas].PiezaColocada=PuntPieza;
            ListaPruebas[PuntPruebas].CombinacionColocadas[PuntContColocadas].OrientaColocada=PuntOri;
            PuntContColocadas=PuntContColocadas+1;
            ListaPruebas[PuntPruebas].NumPiezasColocadas=PuntContColocadas;
            
            PintaCombinacionColocadas(PuntPruebas);
            
            if(CreandoPruebaClave)
            {
                PruebasClave[PuntPruebaClave].Profundidad=ProfundidadFunc;
                PruebasClave[PuntPruebaClave].FinPrueba=0;
                PruebasClave[PuntPruebaClave].NivelProbando=PruebasClave[PuntPruebaClave].NivelProbando+1;
                
            }
            PruebasClave[PuntPruebaClave].PiezaActual=PuntPieza;
            PruebasClave[PuntPruebaClave].OrienActual=PuntOri;
            if (PruebasClave[PuntPruebaClave].NivelSecundario<CANTIDADPIEZAS)
                PruebasClave[PuntPruebaClave].NivelSecundario=PruebasClave[PuntPruebaClave].NivelSecundario+1;
            
            /* Vamos a ver si el tablero está bien */
//            tmpTab=RevisaTablero(Tablero);
//            if(tmpTab==99){
//                /*Tablero terminado!!!*/
//                ListaPruebas[PuntPruebas].ResultadoPrueba=99;
//                ProfundidadFunc=ProfundidadFunc-1;
//                return 99;
//            }else{
//                if(tmpTab>50){
//                    /*Tablero Bloqueado */
//                    ListaPruebas[PuntPruebas].ResultadoPrueba=55;
//                    ProfundidadFunc=ProfundidadFunc-1;
//                    return 55;
//                }
//            }
            
            
            
            if(ListaPruebas[PuntPruebas].NumPiezasColocadas==CANTIDADPIEZAS)
            {
                ProfundidadFunc=ProfundidadFunc-1;
                PrepararNuevaPrueba=1;
                if(CreandoPruebaClave)
                {
                    CreandoPruebaClave=0;
                    /*Para comenzar a rellenar*/
                    PruebasClave[PuntPruebaClave].NivelSecundario=9;
                    PruebasClave[PuntPruebaClave].NivelProbando=8;
                    PruebasClave[PuntPruebaClave].TestNivelProbando=PuntPruebas;
                    MuestraPanelPruebasClave();
                    
                }
                return 0;
            }
            
            
            
            ProfundidadFunc=ProfundidadFunc+1;
            ptmpResultadoFunc=ResuelveTablero();
            if(ProfundidadFunc==0){
                
                switch(ptmpResultadoFunc){
                    case 99:
                        break;
                    default:
                        break;
                }
                if(PrepararNuevaPrueba){
                    PintaTestResumen(PuntPruebas);
                    PuntPruebas=PuntPruebas+1;
                    
                    PuntOrdenPieza=0;
                    PuntContColocadas=0;
                    PuntPiezas=0;
                    
                    
                    PrepararNuevaPrueba=0;
                    PuntPieza=0;
                    PuntOri=0;
                    printf("[NEW] COMIENZO PRUEBA [%u] **********\n",PuntPruebas);
                    if(PuntPruebas==39)
                        i=i;
                    /* En PuntPruebaClave tenemos la Prueba Clave que estamos usando */
                    /* Nivel Probando indica la pieza que estamos colocando del la Clave
                     Ej: de la clave (0) [0-0][1-0][2-0][3-0][4-0][5-0][6-0][7-0][8-0]
                     Nivel probando = 6 significa que estamos colocando hasta la [6-0]
                     Nivel secundario será =7 si estamos llenado la [7-1]*/
//                    if(PruebasClave[PuntPruebaClave].PiezaActual==8 && PruebasClave[PuntPruebaClave].OrienActual==3)
                    if(PruebasClave[PuntPruebaClave].OrienActual==3)
                    { /* ya hemos llegado a la [x-3]*/
                        
                        if(PruebasClave[PuntPruebaClave].NivelProbando==0){
                            /*Se han acabado las pruebas*/
                            i=i;
                        }
                        else
                        {
                            /* Decremento el nivel secundario mientras las piezas son -3*/
                            SalirBucle=1;
                            while(SalirBucle){
                                PruebasClave[PuntPruebaClave].NivelSecundario=PruebasClave[PuntPruebaClave].NivelSecundario-1;
                                i=PruebasClave[PuntPruebaClave].NivelSecundario;
                                if(ListaPruebas[PuntPruebas-1].CombinacionColocadas[i-1].OrientaColocada!=3)
                                    SalirBucle=0;
                            }
                            
                            if(PruebasClave[PuntPruebaClave].NivelProbando==PruebasClave[PuntPruebaClave].NivelSecundario)
                            {
                                PruebasClave[PuntPruebaClave].NivelProbando=PruebasClave[PuntPruebaClave].NivelProbando-1;
                                PruebasClave[PuntPruebaClave].NivelSecundario=PruebasClave[PuntPruebaClave].NivelProbando;
                                PruebasClave[PuntPruebaClave].TestNivelProbando=PuntPruebas-1;
                            }
                            else
                            {
                                PruebasClave[PuntPruebaClave].NivelSecundario=PruebasClave[PuntPruebaClave].NivelSecundario-1;
                            }

                        }
                        
                        if(PruebasClave[PuntPruebaClave].NivelSecundario==CANTIDADPIEZAS)
                        {
                            PruebasClave[PuntPruebaClave].NivelSecundario=PruebasClave[PuntPruebaClave].NivelSecundario-1;
                            i=PruebasClave[PuntPruebaClave].NivelSecundario;
                            
                        }
                        else
                        { /* No hemos llegado al último nivel*/
                            PruebasClave[PuntPruebaClave].NivelSecundario=PruebasClave[PuntPruebaClave].NivelSecundario+1;
                            i=PruebasClave[PuntPruebaClave].NivelSecundario;
                            
                        }
                        j=PruebasClave[PuntPruebaClave].TestNivelProbando;
                        RellenaBuffPiezasAColocar(j,i-2);
        
                    }
                    else
                    {
                        /* La última ficha NO es la [8-3]*/
                        i=PruebasClave[PuntPruebaClave].NivelSecundario;
                        j=PruebasClave[PuntPruebaClave].TestNivelProbando;
                        j=PuntPruebas-1;
                        RellenaBuffPiezasAColocar(j,i-2);
                    }
                    
                                      
                }
                
            }
            else
            {
                ProfundidadFunc=ProfundidadFunc-1;
                return ptmpResultadoFunc;
            }
            
        }
        else
        { /*Esta pieza ya se ha utilizado*/
            
            IncrementaPieza(&PuntPieza,&PuntOri);
            
            PruebasClave[PuntPruebaClave].Profundidad=ProfundidadFunc;
            PruebasClave[PuntPruebaClave].PiezaActual=PuntPieza;
            PruebasClave[PuntPruebaClave].OrienActual=PuntOri;
    
            
        }
        
    }
    return 0;
}

//struct  {
//    int NumPrueba;
//    int Profundidad;
//    int PiezaIni;
//    int OrienIni;
//    int PiezaActual;
//    int OrienActual;
//    int NivelProbando;/* Es la que voy */
//    int NivelSecundario;
//    int FinPrueba;
//}PruebasClave[50];
//
//int PuntPruebaClave=0;
//int CreandoPruebaClave=0;

int main(int argc, const char * argv[]) {
    
    int tmpfilaTab,tmpcolTab;/*Usados para buscar hueco*/
    int Piezainicio=0;
    
    
    int i,j;
    int P1,O1,P2,O2;
    int OrdenPieza=0;
    
    tmpfilaTab=0;
    tmpcolTab=0;
    
    PuntPruebas=0;
    PuntOrdenPieza=0;
    PuntPiezas=0;
    ProfundidadFunc=0;
    PrepararNuevaPrueba=0;
    
    /* Se inicializa el buffer de Pruebas "Clave"*/
    PuntPruebaClave=0;
    CreandoPruebaClave=1;
    PuntPieza=0;
    PuntOri=0;
    
    PruebasClave[PuntPruebaClave].NumPrueba=0;
    PruebasClave[PuntPruebaClave].Profundidad=0;
    PruebasClave[PuntPruebaClave].PiezaIni=PuntPieza;
    PruebasClave[PuntPruebaClave].OrienIni=PuntOri;
    PruebasClave[PuntPruebaClave].PiezaActual=PuntPieza;
    PruebasClave[PuntPruebaClave].OrienActual=PuntOri;
    PruebasClave[PuntPruebaClave].FinPrueba=0;
    PruebasClave[PuntPruebaClave].NivelSecundario=0;
    
    
    ResuelveTablero();
    
    
    return 0;
    
    
    InicializaTablero();
    MuestraTitulosCredito();
    
    PuntPruebas=0;
    PuntPiezas=0; /* El índice marca el número de pieza que se ha probado */
    PuntOrdenPieza=1;
    PuntContColocadas=0;
    FaseProceso=1;
    
    printf("COMENZAMOS 1ª FASE :*********************\n");
    /* Comenzamos 1ª FASE
     Empezamos por la ficha [0-0] y por cada primera ficha vamos probando el resto de segundas piezas, así adelante
     */
    //    ResuelveTableroInicial();
    
    printf("COMENZAMOS 2ª FASE :*********************\n");
    /* Comenzamos 2ª FASE
     1o Los que han dado Resultado >100 (Se han acabado las fichas y no han encontrado una combinación
     Por cada Prueba con Resultado >100 colocamos en Test el número de piezas que vamos a probar
     Ejemplo combinación: [6-3] [0-0] [1-1] [8-1] 4 piezas colocadas
     Ponemos Test = 4  (Un valor de Test >0 y < 10 Indica estamos probando
     Pues generaremos 3 pruebas
     Primer Test: [6-3] [0-1]
     Segundo Test:  [6-3] [0-0] [1-2]
     Tercer Test:  [6-3] [0-0] [1-1] [8-2]
     cuando Test = 1 => ya se han probado todas las combinaciones Test = 22
     */
    FaseProceso=2;
    
    //    ResuelveTableroFase2();
    
    MuestraListaResultPruebas();
    
    return 0;
    
    
    
    /* 15/01/22 - Solución al tablero [0-0] [3-0] [1-0] [2-0] [5-0] [7-0] [4-0] [6-0] [8-0]
     BuscaHuecoEnTablero(Tablero,&tmpfilaTab,&tmpcolTab);
     printf("Coloca la pieza en fila:%u, columna%u\r\n",tmpfilaTab,tmpcolTab);
     tmp=ColocaPieza(tmpfilaTab,tmpcolTab,0,0);
     printf("Coloca devuelve %u\r\n",tmp);
     BuscaHuecoEnTablero(Tablero,&tmpfilaTab,&tmpcolTab);
     printf("Coloca la pieza en fila:%u, columna%u\r\n",tmpfilaTab,tmpcolTab);
     tmp=ColocaPieza(tmpfilaTab,tmpcolTab,3,0);
     printf("Coloca devuelve %u\r\n",tmp);
     BuscaHuecoEnTablero(Tablero,&tmpfilaTab,&tmpcolTab);
     printf("Coloca la pieza en fila:%u, columna%u\r\n",tmpfilaTab,tmpcolTab);
     tmp=ColocaPieza(tmpfilaTab,tmpcolTab,1,0);
     printf("Coloca devuelve %u\r\n",tmp);
     BuscaHuecoEnTablero(Tablero,&tmpfilaTab,&tmpcolTab);
     printf("Coloca la pieza en fila:%u, columna%u\r\n",tmpfilaTab,tmpcolTab);
     tmp=ColocaPieza(tmpfilaTab,tmpcolTab,2,0);
     printf("Coloca devuelve %u\r\n",tmp);
     BuscaHuecoEnTablero(Tablero,&tmpfilaTab,&tmpcolTab);
     printf("Coloca la pieza en fila:%u, columna%u\r\n",tmpfilaTab,tmpcolTab);
     tmp=ColocaPieza(tmpfilaTab,tmpcolTab,5,0);
     printf("Coloca devuelve %u\r\n",tmp);
     BuscaHuecoEnTablero(Tablero,&tmpfilaTab,&tmpcolTab);
     printf("Coloca la pieza en fila:%u, columna%u\r\n",tmpfilaTab,tmpcolTab);
     tmp=ColocaPieza(tmpfilaTab,tmpcolTab,7,0);
     printf("Coloca devuelve %u\r\n",tmp);
     BuscaHuecoEnTablero(Tablero,&tmpfilaTab,&tmpcolTab);
     printf("Coloca la pieza en fila:%u, columna%u\r\n",tmpfilaTab,tmpcolTab);
     tmp=ColocaPieza(tmpfilaTab,tmpcolTab,4,0);
     printf("Coloca devuelve %u\r\n",tmp);
     BuscaHuecoEnTablero(Tablero,&tmpfilaTab,&tmpcolTab);
     printf("Coloca la pieza en fila:%u, columna%u\r\n",tmpfilaTab,tmpcolTab);
     tmp=ColocaPieza(tmpfilaTab,tmpcolTab,6,0);
     printf("Coloca devuelve %u\r\n",tmp);
     BuscaHuecoEnTablero(Tablero,&tmpfilaTab,&tmpcolTab);
     printf("Coloca la pieza en fila:%u, columna%u\r\n",tmpfilaTab,tmpcolTab);
     tmp=ColocaPieza(tmpfilaTab,tmpcolTab,8,0);
     printf("Coloca devuelve %u\r\n",tmp);
     printf("Situación:%u\r\n",RevisaTablero(Tablero));
     return 0;*/
    
    
    printf("¿Por cual pieza empezamos?:");
    scanf("%u",&Piezainicio);
    
    
    
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

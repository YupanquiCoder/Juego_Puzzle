//
//  main.c
//  Juego_Puzzle
//
//  Created by Miguel Ruiz on 11/1/22.
//

#include <stdio.h>
#include "piezas.h" // Definición de las Piezas

/* VARIABLES GLOBALES USADAS*/
int Tablero[7][7];

#define NUMMAXPRUEBAS 200
#define NUMMAXPIEZASPROBADAS 400
#define NUMMAXPRUEBACOMBINACION 2 /* El número de veces que se probará la misma combinación tras una PIEZA COLOCADA*/

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

struct{
    int BuffPieza;
    int BuffOri;
}BufferPiezasAColocar[9];
int PuntBuf=0xff;



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
    printf("|-------------------| TABLERO\r");
    for(fila=0;fila<7;fila++){
        printf(" ");
        for(col=0;col<7;col++){
            tmp=Tablero[fila][col];
            if(tmp<10) printf(" ");
            printf("%u,",tmp);
        }
        printf("\r\n");
    }
    printf("|-------------------|\n\r");
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
    int DesplaIzq=0;
    
    ptFil=tFil;
    ptCol=tCol;
    
    
    printf("Tablero Antes:\n");
    PintaTablero();
    
    printf("Pieza a Colocar\n");
    PintaPieza(pNum,pOri);
    
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
    if(Entra!=0) printf("Hay %u Casillas que no entran\n\r",Entra);
    else printf("Sí entra\n\r");
    
    if(Entra==0){
        /* Cabe, entonces la colocamos*/
        for(i=0;i<FilPiezas;i++)
            for(j=0;j<ColPiezas;j++){
                tmp1=Piezas[pNum][pOri][i][j];
                if(tmp1!=0) Tablero[tFil+i][tCol+j-DesplaIzq]=tmp1;
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
    
    
    for(TmpContPrueba=0;TmpContPrueba<NUMMAXPRUEBAS;TmpContPrueba++){
        
        printf(" PRUEBA: %u Resultado: %u Revis: [%u] Test: %u ", TmpContPrueba,ListaPruebas[TmpContPrueba].ResultadoPrueba,ListaPruebas[TmpContPrueba].RevisandoPrueba,ListaPruebas[TmpContPrueba].RevisionPrueba);
        for (i=0,ContPiezas=0;i<9;i++)
        {
            if(ListaPruebas[TmpContPrueba].Piezascolocadas[i]==0xff)
                ContPiezas=ContPiezas+1;
        }
        printf("   %u Piezas colocadas: ",ContPiezas);
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
        printf("Mostramos los registros de la prueba %u \n",NumPrueba);
        printf(" Se han Usado las piezas: \n");
        for (i=0;i<9;i++)
        {
            printf("   Pieza %u: ",i);
            if(ListaPruebas[NumPrueba].Piezascolocadas[i]==0xff) {
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
                printf ("    La Prueba No ha finalizado");
                break;
            case 55:
                printf ("    El Tablero quedó bloqueado");
                break;
            case 99:
                printf ("    El Tablero finalizó!!!! CONSEGUIDO");
                break;
            case 200:
                printf ("    Se paró la prueba por haber probado ya %u Pieas",NUMMAXPIEZASPROBADAS);
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
                printf("    La Pieza: %u Orientación: %u En el Orden: %u  ",ListaPruebas[NumPrueba].PiezaProbada[i].numPieza,ListaPruebas[NumPrueba].PiezaProbada[i].OrientaPieza,ListaPruebas[NumPrueba].PiezaProbada[i].OrdenPieza);
                printf("Resultado: ");
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
    if(PuntBuf!=0xff){
        /* Hay algo que colocar*/
       /* El puntero apunta a la pieza a colocar*/
        
        PuntPieza=BufferPiezasAColocar[PuntBuf].BuffPieza;
        PuntOri=BufferPiezasAColocar[PuntBuf].BuffOri;
        if(PuntBuf==0) PuntBuf=0xff;
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
        printf("Coloca la pieza en fila:%u, columna%u\r\n",tmpfilaTab,tmpcolTab);
        tmp=ColocaPieza(tmpfilaTab,tmpcolTab,PuntPieza,PuntOri);
        printf("Coloca devuelve %u\r\n",tmp);
        
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
            if(tmp==0) {
                /*La pieza se ha colocado */
                
                /*Marcamos FF en las casillas donde se ha usado piezas*/
                ListaPruebas[PuntPruebas].Piezascolocadas[PuntPieza]=0xff;
                
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
        
    }
    else {
        PuntPieza=PuntPieza+1;
        PuntOri=0;
    }
    if(SeHaColocadoAlgo){
        PuntPieza=0;
        PuntOri=0;
        PuntOrdenPieza=PuntOrdenPieza+1;
        
    }else{ /*No se ha colocado*/
        if(PuntPieza>8){
            ListaPruebas[PuntPruebas].ResultadoPrueba=500;
            return 500; /*Fin cambiando la primera pieza */
        } else{
            if(PuntPieza==8){
                if(PuntOri==3) PuntPieza=0;
                else PuntOri=PuntOri+1;
            }else{
                if(PuntOri==3) {
                    PuntPieza=PuntPieza+1;
                    PuntOri=0;
                }else PuntOri=PuntOri+1;
                
            }
        }
    }
    
    ptmpResultadoFunc=ResuelveTableroAvance();
    return ptmpResultadoFunc;
}

int InicializaTablero()
{
    LimpiaTablero(Tablero);
    /*Definimos el reto*/
    Tablero[3][2]=9; /*Donde está el 9 es la Chincheta*/
    PintaTablero();
    return 0;
}

int BuscaPrueba55(){
    /* Busca la primera prueba cuyo resultado es 55 y que no se haya revisada ya (las revisadas se marcan como 33 o 44*/
    int i;
    for(i=0;i<PuntPruebas;i++){
        if(ListaPruebas[i].ResultadoPrueba==55 && ListaPruebas[i].RevisionPrueba==0)
            return i;
    }
    return 0xFF; /* NO hay ninguna prueba 55 que no se haya probado*/
}

int BuscaPruebasRepetidas(){
    /* Busca de todas las pruebas que No se han revisado (RevisiónPrueba !=33 cuales no están repetidas
     Si está repetida Se marca como 44 => Repetidas NO se vuelven a tratar*/
    int PuntTestRev;
    int PuntRevis;
    int i=0;
    int SonIguales=1;
    
    for(PuntTestRev=0;PuntTestRev<PuntPruebas;PuntTestRev++){
        for(PuntRevis=PuntTestRev+1;PuntRevis<PuntPruebas;PuntRevis++){
            if(ListaPruebas[PuntTestRev].RevisionPrueba==0){
                for(i=0,SonIguales=1;i<9;i++)
                {
                    if(ListaPruebas[PuntTestRev].CombinacionColocadas[i].PiezaColocada!=ListaPruebas[PuntRevis].CombinacionColocadas[i].PiezaColocada && ListaPruebas[PuntTestRev].CombinacionColocadas[i].OrientaColocada!=ListaPruebas[PuntRevis].CombinacionColocadas[i].OrientaColocada)
                        SonIguales=0;
                }
                if(SonIguales){
                    ListaPruebas[PuntRevis].RevisionPrueba=44;
                    SonIguales=1;
                }
        }
        }
    }
    
    return 0;
}

int ResuelveTablero55(){
    int i,j,k;
    int PuntTestPrueba=0;
    int tmpResultadoFunc=0;
    
    MuestraListaResultPruebas();
    BuscaPruebasRepetidas();
    MuestraListaResultPruebas();
    PuntTestPrueba=BuscaPrueba55();
    while (PuntTestPrueba!=0xff){
        PuntBuf=0;
        for(k=ListaPruebas[PuntTestPrueba].NumPiezasColocadas,i=ListaPruebas[PuntTestPrueba].NumPiezasColocadas-1,j=0;k>0;i--,j++,k--){
            BufferPiezasAColocar[j].BuffPieza=ListaPruebas[PuntTestPrueba].CombinacionColocadas[i].PiezaColocada;
            BufferPiezasAColocar[j].BuffOri=ListaPruebas[PuntTestPrueba].CombinacionColocadas[i].OrientaColocada;
            PuntBuf=PuntBuf+1;
        }
        
        /*la pieza Indice 0 hay que pasar a la siguiente */
        if(BufferPiezasAColocar[0].BuffOri==3){
            if(BufferPiezasAColocar[0].BuffPieza<8){
                BufferPiezasAColocar[0].BuffPieza=BufferPiezasAColocar[0].BuffPieza+1;
                BufferPiezasAColocar[0].BuffOri=0;
            } else{
                BufferPiezasAColocar[0].BuffPieza=0;
                BufferPiezasAColocar[0].BuffOri=0;
            }
        }else BufferPiezasAColocar[0].BuffOri=BufferPiezasAColocar[0].BuffOri+1;
        PuntBuf=PuntBuf-1;
        PuntPiezas=0; /* El índice marca el número de pieza que se ha probado */
        PuntOrdenPieza=1;
        PuntContColocadas=0;
        ListaPruebas[PuntPruebas].RevisandoPrueba=PuntTestPrueba;
        
        printf("COMIENZO PRUEBA [%u] **********\n",PuntPruebas);
        tmpResultadoFunc=ResuelveTableroAvance();
        ListaPruebas[PuntTestPrueba].RevisionPrueba=33;
        switch(tmpResultadoFunc){
            case 99:
            case 55:
                printf("Se ha acabado el tablero [%u]\r\n",tmpResultadoFunc);
                break;
            case 200:
                printf("Paramos las pruebas [%u]\r\n",tmpResultadoFunc);
                break;
            case 400:
                printf("Se para porque ya se ha probado la misma combinación %u veces [%u]\r\n",NUMMAXPRUEBACOMBINACION, tmpResultadoFunc);
                break;
            case 500:
                printf("Se ha terminado las 8 piezas de inicio [%u]\r\n",tmpResultadoFunc);
                break;
            default:
                break;
        }
        BuscaPruebasRepetidas();
        PuntTestPrueba=BuscaPrueba55();
        /* Preparamos la siguiente Prueba*/
        PuntPruebas=PuntPruebas+1;
        if(PuntPruebas==NUMMAXPRUEBAS){
            MuestraListado(PuntPruebas);
            return 900;
        }
        ListaPruebas[PuntPruebas].RevisandoPrueba=0xff;
        InicializaTablero();
        
        
    }

    
    MuestraListado(PuntPruebas);
    return 0;
}

int main(int argc, const char * argv[]) {
    
    int tmpfilaTab,tmpcolTab;/*Usados para buscar hueco*/
    int Piezainicio=0;
    int tmpResultadoFunc=0;
    int PuntPiezaComienzo,PuntOriComienzo;
  
    int i,j;
    
    tmpfilaTab=0;
    tmpcolTab=0;
    
    InicializaTablero();
    PuntPruebas=0;
    PuntPiezas=0; /* El índice marca el número de pieza que se ha probado */
    PuntOrdenPieza=1;
    PuntContColocadas=0;
    
    /* Comenzamos pruebas*/
    for(PuntPiezaComienzo=0;PuntPiezaComienzo<8;PuntPiezaComienzo++){
        for(PuntOriComienzo=0;PuntOriComienzo<4;PuntOriComienzo++){
            printf("COMIENZO PRUEBA [%u] **********\n",PuntPruebas);
            PuntPieza=PuntPiezaComienzo;
            PuntOri=PuntOriComienzo;
            tmpResultadoFunc=ResuelveTableroAvance();
            switch(tmpResultadoFunc){
                case 99:
                case 55:
                    printf("Se ha acabado el tablero [%u]\r\n",tmpResultadoFunc);
                    break;
                case 200:
                    printf("Paramos las pruebas [%u]\r\n",tmpResultadoFunc);
                    break;
                case 400:
                    printf("Se para porque ya se ha probado la misma combinación %u veces [%u]\r\n",NUMMAXPRUEBACOMBINACION, tmpResultadoFunc);
                    break;
                case 500:
                    printf("Se ha terminado las 8 piezas de inicio [%u]\r\n",tmpResultadoFunc);
                    break;
                default:
                    break;
            }
            MuestraListado(PuntPruebas);
            /* Preparamos la siguiente Prueba*/
            PuntPruebas=PuntPruebas+1;
            ListaPruebas[PuntPruebas].RevisandoPrueba=0xff;
            PuntPiezas=0; /* El índice marca el número de pieza que se ha probado */
            PuntOrdenPieza=1;
            PuntContColocadas=0;
            InicializaTablero();
            
        }
    }
    MuestraListaResultPruebas();

    printf("COMENZAMOS 2ª FASE :*********************\n");
    /* Comenzamos 2ª FASE
     1o Los que han dado Resultado 55 (La última pieza ha Bloqueado el tablero Quitamos solo la última pieza y seguimos con la siguiente */
    
    ResuelveTablero55();
    
    
    MuestraListaResultPruebas();

    return 0;
    
    
    
    /* 15/01/22 - Solución al tablero
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

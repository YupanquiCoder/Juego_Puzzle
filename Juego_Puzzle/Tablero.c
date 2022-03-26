//
//  Tablero.c
//  Juego_Puzzle
//
//  Created by Miguel Ruiz on 27/2/22.
//

#include "Tablero.h"
#include "Punteros.h"

int Tablero[FILTABLERO][COLTABLERO];
int TableroSoluciones[FILTABLERO][COLTABLERO];

/* Lista Negra de Combinaciones */

struct ListaNegraPunteros_ ListaNegraPunteros [NUMMAXLISTANEGRA];
long int ContCombNegra=0; /* Contador de Combinaciones en la Lista Negra*/

int InicializaTablero(int pTablero[][7])
{
    LimpiaTablero(pTablero);
    /*Definimos el reto*/
    pTablero[3][2]=9; /*Donde está el 9 es la Chincheta*/
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
    
    printf(" TABLERO\r");
    printf(" ┌─────────────────────┐\r");
    for(fila=0;fila<7;fila++){
        printf(" │");
        for(col=0;col<7;col++){
            tmp=pTablero[fila][col];
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
        //        printf("!!! Solución !!!!!\n");
        //        MuestraListado(PuntPruebas);
        //        PintaTablero(Tablero);
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

int ResuelveTablero()
{ /* Esta función se llama cíclicamente
   En cada ciclo, se crea una nueva PRUEBA
   Se incrementa los punteros
   Se toma una combinación posible
   Se prueba pieza a pieza
   Y se actualiza la Lista Negra y el puntero */
    /* La función devuelve:
     400: Desde colocar una pieza, se ha probado NUMMAXPRUEBACOMBINACION la misma combinación
     500: Se han probado el resto de piezas y no caben
     55: Esta prueba se debe parar porque el Tablero resultante se ha bloqueado
     99: El Tablero se ha terminado ¡ÉXITO!
     */
    int i,j;
    int PuntBuffColoca=0;
    int tmpfilaTab,tmpcolTab;/*Usados para buscar hueco*/
    int tmp,tmpTab;
    int ResultadoColoca=0;
    struct ListaNegraPunteros_ CeldaListaNegra;
    struct ListaSoluciones_ CeldaSoluciones;
    
    /*Preparamos la nueva Prueba*/
    PuntPiezasProbadas=0;
    PuntContColocadas=0;
    if(PuntPruebas==13 || PuntPruebas==7)
        i=i;
    if(!DameSiguientePunteroValido())
    {
        /* el siguiente puntero válido está en: CasillaPieza_ BufferPuntero*/
        /* Estamos comenzando una prueba Rellenamos cual es la combinación que se va a probar*/
        for(i=0;i<CANTIDADPIEZAS;i++){
            ListaPruebas[PuntPruebas].CombinacionPrueba[i].PiezaPrueba=BufferPuntero[i].BuffPieza;
            ListaPruebas[PuntPruebas].CombinacionPrueba[i].OrientaPrueba=BufferPuntero[i].BuffOri;
        }
        
        /* Comenzamos a probar piezas: son las que apunta PuntBuffColoca*/
        for(PuntBuffColoca=0;PuntBuffColoca<CANTIDADPIEZAS;PuntBuffColoca++){
            
            PuntPieza=BufferPuntero[PuntBuffColoca].BuffPieza;
            PuntOri=BufferPuntero[PuntBuffColoca].BuffOri;
            
            BuscaHuecoEnTablero(Tablero,&tmpfilaTab,&tmpcolTab);
            if(contTestDemo<TESTDEDEMO || DEBUGPINTAFICHAS)
                printf("Coloca la pieza [%u-%u] en fila:%u, columna%u\r\n",PuntPieza,PuntOri,tmpfilaTab,tmpcolTab);
            tmp=ColocaPieza(tmpfilaTab,tmpcolTab,PuntPieza,PuntOri,Tablero,0);
            
            /*Apuntamos el resultado*/
            /*La pieza [PuntPieza-PuntOri] se ha intentado colocar*/
            ListaPruebas[PuntPruebas].PiezaProbada[PuntPiezasProbadas].numPieza=PuntPieza;
            ListaPruebas[PuntPruebas].PiezaProbada[PuntPiezasProbadas].OrientaPieza=PuntOri;
            ListaPruebas[PuntPruebas].PiezaProbada[PuntPiezasProbadas].ResultadoPieza=tmp;
            ListaPruebas[PuntPruebas].PiezaProbada[PuntPiezasProbadas].OrdenPieza=PuntOrdenPieza;
            PuntPiezasProbadas=PuntPiezasProbadas+1;
            /*Si tmp =0 colocada, otros valores NO cabe*/
            if(tmp==0)
            {
                /*La pieza se ha colocado */
                
                /*Marcamos FFFF en las casillas donde se ha usado piezas*/
                ListaPruebas[PuntPruebas].Piezascolocadas[PuntPieza]=0xffff;
                
                ListaPruebas[PuntPruebas].CombinacionColocadas[PuntContColocadas].PiezaColocada=PuntPieza;
                ListaPruebas[PuntPruebas].CombinacionColocadas[PuntContColocadas].OrientaColocada=PuntOri;
                PuntContColocadas=PuntContColocadas+1;
                ListaPruebas[PuntPruebas].NumPiezasColocadas=PuntContColocadas;
                
                /* Vamos a ver si el tablero está bien */
                tmpTab=RevisaTablero(Tablero);
                if(tmpTab==99){
                    /*Tablero terminado!!!*/
                    ResultadoColoca=99;
                }else{
                    if(tmpTab>50){
                        /*Tablero Bloqueado */
                        ResultadoColoca=55;
                    }
                }
                
            }
            else
            {
                /* Tmp!=0 => La pieza no se ha colocado*/
                ResultadoColoca=66; /* La pieza NO se ha colocado*/
            }
            if(ResultadoColoca!=0) /* No se continua probando*/
            {
                ListaPruebas[PuntPruebas].ResultadoPrueba=ResultadoColoca;
                break; /* Se sale del bucle FOR*/
            }
        }
        /* Se ha finalizado */
        switch(ResultadoColoca){
            case 55:
                /* El Tablero Se ha bloqueado*/
                /* Tenemos que añadir a la lista negra las piezas colocadas */
                j=ListaPruebas[PuntPruebas].NumPiezasColocadas;
                for(i=0;i<j;i++)
                {
                    CeldaListaNegra.CombinacionNegra[i].BuffPieza=ListaPruebas[PuntPruebas].CombinacionColocadas[i].PiezaColocada;
                    CeldaListaNegra.CombinacionNegra[i].BuffOri=ListaPruebas[PuntPruebas].CombinacionColocadas[i].OrientaColocada;
                }
                if(PuntPruebas==7)
                    i=i;
                MeteEnListaNegra(CeldaListaNegra,j);
                //                printf("Se mete en Lista Negra:");
                //                PintaCeldaListaNegra(ContCombNegra-1);
                //                printf("\n");
                //            PintaListaNegra();
                
                /* Incrementamos el puntero para "salvar" la lista negra*/
                SaltaCeldasListaNegra(ContCombNegra-1);
                
                break;
            case 66:
                /* La última Pieza NO se ha colocado*/
                /* Tenemos que añadir a la lista negra las piezas colocadas + la que NO se ha colocado*/
                j=ListaPruebas[PuntPruebas].NumPiezasColocadas;
                for(i=0;i<j;i++)
                {
                    CeldaListaNegra.CombinacionNegra[i].BuffPieza=ListaPruebas[PuntPruebas].CombinacionColocadas[i].PiezaColocada;
                    CeldaListaNegra.CombinacionNegra[i].BuffOri=ListaPruebas[PuntPruebas].CombinacionColocadas[i].OrientaColocada;
                }
                CeldaListaNegra.CombinacionNegra[i].BuffPieza=PuntPieza;
                CeldaListaNegra.CombinacionNegra[i].BuffOri=PuntOri;
                MeteEnListaNegra(CeldaListaNegra,j+1);
                //                printf("Se mete en Lista Negra:");
                //                PintaCeldaListaNegra(ContCombNegra-1);
                //                printf("\n");
                //            PintaListaNegra();
                
                /* Incrementamos el puntero para "salvar" la lista negra*/
                SaltaCeldasListaNegra(ContCombNegra-1);
                
                break;
            case 99:
                /* El tablero se ha completado*/
                /* Tablero completado EXITO*/
                /* Tenemos que añadir a la lista de Soluciones las piezas colocadas */
                j=ListaPruebas[PuntPruebas].NumPiezasColocadas; /*Deberían ser 9*/
                for(i=0;i<j;i++)
                {
                    CeldaSoluciones.CombinacionSolucion[i].BuffPieza=ListaPruebas[PuntPruebas].CombinacionColocadas[i].PiezaColocada;
                    CeldaSoluciones.CombinacionSolucion[i].BuffOri=ListaPruebas[PuntPruebas].CombinacionColocadas[i].OrientaColocada;
                }
                MeteEnListaSoluciones(CeldaSoluciones,j);
                printf("!!! Solución !!!!!\n");
                MuestraListado(PuntPruebas);
                PintaTablero(Tablero);
                PintaListaSoluciones();
                break;
        }
        /* Preparar NUEVA Prueba*/
        PintaTestResumen(PuntPruebas);
        PuntPruebas=PuntPruebas+1;
        
        PuntOrdenPieza=0;
        PuntContColocadas=0;
        PuntPiezasProbadas=0;
        
        contTestDemo=contTestDemo+1;
        InicializaTablero(Tablero);
        
        return 0;
    }
    else
        return 1; /* Se finalizó la cuenta de punteros*/
}

int PintaTestResumen(long int NumTest)
{
    
    int ContPiezas=0;
    int i;
    
    if(NumTest<=PuntPruebas)
    {
        /*Se pinta un resumen del Test NumTest*/
        printf(" PRUEBA: %ld Result: <%u> ", NumTest,ListaPruebas[NumTest].ResultadoPrueba);
        printf("Combinación Probada: ");
        for (i=0;i<CANTIDADPIEZAS;i++)
        {
            printf("[%u-%u] ",ListaPruebas[NumTest].CombinacionPrueba[i].PiezaPrueba,ListaPruebas[NumTest].CombinacionPrueba[i].OrientaPrueba);
        }
        printf( "\r");
        ContPiezas=ListaPruebas[NumTest].NumPiezasColocadas;
        printf("                            %u Piezas colocadas: ",ContPiezas);
        for (i=0;i<ContPiezas;i++)
        {
            printf("[%u-%u] ",ListaPruebas[NumTest].CombinacionColocadas[i].PiezaColocada,ListaPruebas[NumTest].CombinacionColocadas[i].OrientaColocada);
        }
        printf( "\r\r");
        return 0;
    }
    return 0xffff;/* ERROR de parámetros*/
}

int PintaUnaSolucion(int pNumSolucion, int DebugCompleto)
{
    /* Se pasa una solución de las que están en la Lista de Soluciones */
    /* DebugCompleto =1: Se muestra todo el proceso de colocación
       DebugCompleto =0: Sólo se muestra el Tablero completo*/
    int pfilaTab,pcolTab;
    int pPuntPieza,pPuntOri;
    int i,tmp,tmpTab;
    
    printf("Mostramos Solución [%u]: ",pNumSolucion);
    for(i=0;i<CANTIDADPIEZAS;i++)
        printf("[%u-%u] ",ListaSoluciones[pNumSolucion].CombinacionSolucion[i].BuffPieza, ListaSoluciones[pNumSolucion].CombinacionSolucion[i].BuffOri);
        printf("\r\n");
    InicializaTablero(TableroSoluciones);
    if(!DebugCompleto) printf("Debug reducido- solo Tablero final\r");

    if(DebugCompleto) PintaTablero(TableroSoluciones);
    for(i=0;i<CANTIDADPIEZAS;i++){
        pPuntPieza= ListaSoluciones[pNumSolucion].CombinacionSolucion[i].BuffPieza;
        pPuntOri=ListaSoluciones[pNumSolucion].CombinacionSolucion[i].BuffOri;
        BuscaHuecoEnTablero(TableroSoluciones,&pfilaTab,&pcolTab);
        if(DebugCompleto) printf("Coloca la pieza [%u-%u] en fila:%u, columna%u\r\n",pPuntPieza,pPuntOri,pfilaTab,pcolTab);
        tmp=ColocaPieza(pfilaTab,pcolTab,pPuntPieza,pPuntOri,TableroSoluciones,DebugCompleto);
        /*Si tmp =0 colocada, otros valores NO cabe*/
        if(tmp==0)
        {
            /*La pieza se ha colocado */
            /* Vamos a ver si el tablero está bien */
            tmpTab=RevisaTablero(TableroSoluciones);
            if(tmpTab==99){
                /*Tablero terminado!!! Es lo correcto */
                if(!DebugCompleto) PintaTablero(TableroSoluciones);
                return 99;
            }else{
                if(tmpTab>50){
                    /*Tablero Bloqueado */
                    printf("ERROR: Al pintar una solución se bloquea el Tablero\r");
                    return 55;
                }
            }
        }
        else{
            printf("ERROR: Al pintar una solución hay una pieza que no entra\r");
            return 0xff;
        }
    }
    
    return 0;
}


long int MeteEnListaNegra(struct ListaNegraPunteros_ BuffCheck,int NumPiezas)
{
    int i;
    for(i=0;i<NumPiezas;i++)
    {
        ListaNegraPunteros[ContCombNegra].CombinacionNegra[i].BuffPieza=BuffCheck.CombinacionNegra[i].BuffPieza;
        ListaNegraPunteros[ContCombNegra].CombinacionNegra[i].BuffOri=BuffCheck.CombinacionNegra[i].BuffOri;
    }
    for(i=NumPiezas;i<CANTIDADPIEZAS;i++)
    {
        ListaNegraPunteros[ContCombNegra].CombinacionNegra[i].BuffPieza=0xffff;
        ListaNegraPunteros[ContCombNegra].CombinacionNegra[i].BuffOri=0xffff;
    }
    ListaNegraPunteros[ContCombNegra].NumPiezasCombi=NumPiezas;
    ContCombNegra=ContCombNegra+1;
    return ContCombNegra;
}

void PintaListaNegra(void)
{
    long int i,j;
    printf("Lista Negra: \n");
    for(j=0;j<ContCombNegra;j++){
        printf("List [%ld] %u Piezas: ",j,ListaNegraPunteros[j].NumPiezasCombi);
        for(i=0;i<ListaNegraPunteros[j].NumPiezasCombi;i++)
            printf("[%u-%u] ",ListaNegraPunteros[j].CombinacionNegra[i].BuffPieza,ListaNegraPunteros[j].CombinacionNegra[i].BuffOri);
        printf("\r\n");
    }

}

void PintaCeldaListaNegra(long int NumCeldaListaNegra)
{
    int i;


        printf("Celda Lista Negra [%ld] %u Piezas: ",NumCeldaListaNegra,ListaNegraPunteros[NumCeldaListaNegra].NumPiezasCombi);
        for(i=0;i<ListaNegraPunteros[NumCeldaListaNegra].NumPiezasCombi;i++)
            printf("[%u-%u] ",ListaNegraPunteros[NumCeldaListaNegra].CombinacionNegra[i].BuffPieza,ListaNegraPunteros[NumCeldaListaNegra].CombinacionNegra[i].BuffOri);
        printf("\r\n");


}

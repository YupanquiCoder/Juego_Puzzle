//
//  Soluciones.c
//  Juego_Puzzle
//
//  Created by Miguel Ruiz on 3/4/22.
//

#include "Soluciones.h"
#include "main.h"

struct BloquesSoluciones_ BloquesSoluciones[NUMMAXPOSCHINCHETA];


void InicializaSoluciones(void)
{
    int i;
    for (i=0;i<NUMMAXPOSCHINCHETA;i++)
        BloquesSoluciones[i].ContadorSoluciones=0;
}

void InicializaBloque(void){
    /* Se llama cuando vamos a comenzar a probar un nuevo bloque*/
    InicializaPunteros();
    InicializaTablero(Tablero);
    SeHaFinalizadoLaCuenta=0;
    
}
int MeteEnListaSoluciones(struct ListaSoluciones_ BuffCheck,long int NumPrueba)
{
    int i,j;
    int SolucionYaExiste=0;
    /* Mete en lista de soluciones, incrementando el Contador de Soluciones:
     Devuelve: El número de solución que se ha añadido
     NUMMAXSOLUCIONES: Si la solución ya existía */
    
    for(j=0;j<BloquesSoluciones[PosChinchetaActual].ContadorSoluciones;j++){
        SolucionYaExiste=1;
        for(i=0;i<CANTIDADPIEZAS;i++){
            if(BloquesSoluciones[PosChinchetaActual].ListaSoluciones[j].CombinacionSolucion[i].BuffPieza != BuffCheck.CombinacionSolucion[i].BuffPieza ||
               BloquesSoluciones[PosChinchetaActual].ListaSoluciones[j].CombinacionSolucion[i].BuffOri != BuffCheck.CombinacionSolucion[i].BuffOri)
            {
                SolucionYaExiste=0;
                break;
            }
        }
        if(SolucionYaExiste){
            printf("Solución ya estaba en la lista -> No se añade\r\n");
            return NUMMAXSOLUCIONES;
        }
           
    }
    /* Se han revisado todas las soluciones ya guardadas y NINGUNA es igual a la nueva que se va a añadir
     Añadimos una nueva solución a la lista */
    BloquesSoluciones[PosChinchetaActual].ListaSoluciones[BloquesSoluciones[PosChinchetaActual].ContadorSoluciones].NumPruebaSolucion=PuntPruebas;
    
    
    for(i=0;i<CANTIDADPIEZAS;i++){
        BloquesSoluciones[PosChinchetaActual].ListaSoluciones[BloquesSoluciones[PosChinchetaActual].ContadorSoluciones].CombinacionSolucion[i].BuffPieza=BuffCheck.CombinacionSolucion[i].BuffPieza;
        BloquesSoluciones[PosChinchetaActual].ListaSoluciones[BloquesSoluciones[PosChinchetaActual].ContadorSoluciones].CombinacionSolucion[i].BuffOri=BuffCheck.CombinacionSolucion[i].BuffOri;
    }
    BloquesSoluciones[PosChinchetaActual].ContadorSoluciones=BloquesSoluciones[PosChinchetaActual].ContadorSoluciones+1;
    return BloquesSoluciones[PosChinchetaActual].ContadorSoluciones;
}

void PintaSituacionBloquesSoluciones(void)
{
    int i,j;
    printf("De las %u Posiciones de la 'chincheta' este es el listado de las probadas:\n\r",NUMMAXPOSCHINCHETA);
    for(i=0;i<NUMMAXPOSCHINCHETA;i++){
        printf("\nPos Chincheta <%u>: [%u-%u] ",i,Chinchetas[i].FilaChin,Chinchetas[i].ColumnChin);
        if(BloquesSoluciones[i].ContadorSoluciones==0)
            printf(" NO se han buscado soluciones");
        else
            printf("Encontradas %u soluciones en %ld Pruebas",BloquesSoluciones[i].ContadorSoluciones,BloquesSoluciones[i].NumeroPruebasRealizadas);
    }
}
void PintaListaSoluciones(void)
{
    int i,j;
    printf("Hay <%u> Soluciones que son: \n",BloquesSoluciones[PosChinchetaActual].ContadorSoluciones);
    for(j=0;j<BloquesSoluciones[PosChinchetaActual].ContadorSoluciones;j++){
        printf("Solución [%u]: ",j);
        for(i=0;i<CANTIDADPIEZAS;i++)
            printf("[%u-%u] ",BloquesSoluciones[PosChinchetaActual].ListaSoluciones[j].CombinacionSolucion[i].BuffPieza, BloquesSoluciones[PosChinchetaActual].ListaSoluciones[j].CombinacionSolucion[i].BuffOri);
        printf("\r\n");
    }
    
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
        printf("[%u-%u] ",BloquesSoluciones[PosChinchetaActual].ListaSoluciones[pNumSolucion].CombinacionSolucion[i].BuffPieza, BloquesSoluciones[PosChinchetaActual].ListaSoluciones[pNumSolucion].CombinacionSolucion[i].BuffOri);
    printf("\r\n");
    InicializaTablero(TableroSoluciones);
    if(!DebugCompleto) printf("Debug reducido- solo Tablero final\r");
    
    if(DebugCompleto) PintaTablero(TableroSoluciones);
    for(i=0;i<CANTIDADPIEZAS;i++){
        pPuntPieza= BloquesSoluciones[PosChinchetaActual].ListaSoluciones[pNumSolucion].CombinacionSolucion[i].BuffPieza;
        pPuntOri=BloquesSoluciones[PosChinchetaActual].ListaSoluciones[pNumSolucion].CombinacionSolucion[i].BuffOri;
        BuscaHuecoEnTablero(TableroSoluciones,&pfilaTab,&pcolTab);
        if(DebugCompleto) printf("Coloca la pieza [%u-%u] en fila:%u, columna: %u\r\n",pPuntPieza,pPuntOri,pfilaTab,pcolTab);
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

void PintaArrayUnaSolucion(int NumSolucion)
{
    int i;
    printf("Solución <%u>: ",NumSolucion);
    for(i=0;i<9;i++)
        printf("[%u-%u] ",BloquesSoluciones[PosChinchetaActual].ListaSoluciones[NumSolucion].CombinacionSolucion[i].BuffPieza,BloquesSoluciones[PosChinchetaActual].ListaSoluciones[NumSolucion].CombinacionSolucion[i].BuffOri);
    printf("\r\n");
}

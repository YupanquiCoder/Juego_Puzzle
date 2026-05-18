//
//  Soluciones.c
//  Juego_Puzzle
//
//  Created by Miguel Ruiz on 3/4/22.
//

#include "Soluciones.h"
#include "main.h"

/* Simetría — definidas en piezas.c */
extern int UnicosPorPieza[];
int DivisorSimetrias(void);

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
    contTestDemo=TESTDEDEMO;
    MostrarCadaPunteroValido=0;
    MostrarCadaIncrementoDePuntero=0;

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
            printf("Solución ya estaba en la lista -> No se añade\n");
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
    int i;
    int divisor = DivisorSimetrias();
    printf("De las %u Posiciones de la 'chincheta' este es el listado de las probadas:\n",NUMMAXPOSCHINCHETA);
    for(i=0;i<NUMMAXPOSCHINCHETA;i++){
        printf("\nPos Chincheta <%u>: [%u-%u] ",i,BloquesSoluciones[i].PosicionesChincheta.FilaChin,BloquesSoluciones[i].PosicionesChincheta.ColumnChin);
        if(BloquesSoluciones[i].ContadorSoluciones==0)
            printf(" NO se han buscado soluciones");
        else
            printf("Encontradas %u soluciones (%u unicas) en %ld Pruebas",
                   BloquesSoluciones[i].ContadorSoluciones,
                   BloquesSoluciones[i].ContadorSoluciones / divisor,
                   BloquesSoluciones[i].NumeroPruebasRealizadas);
    }
    printf("\n");
}
void PintaListaSoluciones(void)
{
    int i, j, k, esdup, numSim, numVariantes;
    int piezasSim[CANTIDADPIEZAS];
    unsigned int total = BloquesSoluciones[PosChinchetaActual].ContadorSoluciones;
    int divisor = DivisorSimetrias();
    printf("Hay <%u> Soluciones (%u unicas, divisor simetria x%d):\n", total, total / divisor, divisor);
    for (j = 0; j < (int)total; j++) {
        /* Si es duplicado de alguna anterior, saltar */
        esdup = 0;
        for (k = 0; k < j && !esdup; k++) {
            numSim = 0;
            if (EsDuplicadoSimetrico(j, k, piezasSim, &numSim)) esdup = 1;
        }
        if (esdup) continue;

        /* Contar variantes simétricas que genera esta solución canónica */
        numVariantes = 0;
        for (k = j + 1; k < (int)total; k++) {
            numSim = 0;
            if (EsDuplicadoSimetrico(k, j, piezasSim, &numSim)) numVariantes++;
        }

        /* Imprimir: (*) en piezas simétricas, + variantes si las hay */
        printf("Solucion [%u]: ", j);
        for (i = 0; i < CANTIDADPIEZAS; i++) {
            int p = BloquesSoluciones[PosChinchetaActual].ListaSoluciones[j].CombinacionSolucion[i].BuffPieza;
            int o = BloquesSoluciones[PosChinchetaActual].ListaSoluciones[j].CombinacionSolucion[i].BuffOri;
            if (UnicosPorPieza[p] < CANTIDADORIENTACIONES)
                printf("[%u-%u(*)] ", p, o);
            else
                printf("[%u-%u] ", p, o);
        }
        if (numVariantes > 0) printf("-> +%d variantes", numVariantes);
        printf("\n");
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
    printf("\n");
    InicializaTablero(TableroSoluciones);
    if(!DebugCompleto) printf("Debug reducido- solo Tablero final\n");
    
    if(DebugCompleto) PintaTablero(TableroSoluciones);
    for(i=0;i<CANTIDADPIEZAS;i++){
        pPuntPieza= BloquesSoluciones[PosChinchetaActual].ListaSoluciones[pNumSolucion].CombinacionSolucion[i].BuffPieza;
        pPuntOri=BloquesSoluciones[PosChinchetaActual].ListaSoluciones[pNumSolucion].CombinacionSolucion[i].BuffOri;
        BuscaHuecoEnTablero(TableroSoluciones,&pfilaTab,&pcolTab);
        if(DebugCompleto) printf("Coloca la pieza [%u-%u] en fila:%u, columna: %u\n",pPuntPieza,pPuntOri,pfilaTab,pcolTab);
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
                    printf("ERROR: Al pintar una solución se bloquea el Tablero\n");
                    return 55;
                }
            }
        }
        else{
            printf("ERROR: Al pintar una solución hay una pieza que no entra\n");
            return 0xff;
        }
    }
    
    return 0;
}

void PintaArrayUnaSolucion(int NumSolucion)
{
    int i, p, o;
    printf("Solucion <%u>: ", NumSolucion);
    for (i = 0; i < 9; i++) {
        p = BloquesSoluciones[PosChinchetaActual].ListaSoluciones[NumSolucion].CombinacionSolucion[i].BuffPieza;
        o = BloquesSoluciones[PosChinchetaActual].ListaSoluciones[NumSolucion].CombinacionSolucion[i].BuffOri;
        if (UnicosPorPieza[p] < CANTIDADORIENTACIONES)
            printf("[%u-%u(*)] ", p, o);
        else
            printf("[%u-%u] ", p, o);
    }
    printf("\n");
}

int EsDuplicadoSimetrico(int solTest, int solRef, int piezasSim[], int *numSim)
{
    /* Compara solTest contra solRef.
       Si todas las diferencias se deben a orientaciones equivalentes de la misma pieza
       (misma forma, distinto número de orientación), devuelve 1.
       piezasSim[] se rellena con los índices de esas piezas. */
    int i, p1, o1, p2, o2;
    *numSim = 0;
    for (i = 0; i < CANTIDADPIEZAS; i++) {
        p1 = BloquesSoluciones[PosChinchetaActual].ListaSoluciones[solRef].CombinacionSolucion[i].BuffPieza;
        o1 = BloquesSoluciones[PosChinchetaActual].ListaSoluciones[solRef].CombinacionSolucion[i].BuffOri;
        p2 = BloquesSoluciones[PosChinchetaActual].ListaSoluciones[solTest].CombinacionSolucion[i].BuffPieza;
        o2 = BloquesSoluciones[PosChinchetaActual].ListaSoluciones[solTest].CombinacionSolucion[i].BuffOri;

        if (p1 != p2) return 0;          /* pieza distinta — no es duplicado simétrico */
        if (o1 != o2) {
            if (!OrientacionesIguales(p1, o1, o2)) return 0; /* forma distinta — no es dup */
            piezasSim[(*numSim)++] = p1;
        }
    }
    return (*numSim > 0) ? 1 : 0;
}

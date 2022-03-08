//
//  Punteros.c
//  Juego_Puzzle
//
//  Created by Miguel Ruiz on 26/2/22.
//

#include "Punteros.h"
#include "main.h"


int Punteros[9];

int SeHaFinalizadoLaCuenta=0;

struct CasillaPieza_ OpcionesPuntero[36];

struct CasillaPieza_ BufferPuntero[9]; /* Cada vez que se incremente se colocan las piezas en este Buffer */

/* Lista Negra de Combinaciones */

struct ListaNegraPunteros_ ListaNegraPunteros [NUMMAXLISTANEGRA];
int ContCombNegra=0; /* Contador de Combinaciones en la Lista Negra*/

struct ListaSoluciones_ ListaSoluciones[NUMMAXSOLUCIONES];
int ContadorSoluciones; /* Indica el número de soluciones encontradas*/

/* Prototipos */
void RellenaSolucionesConocidas(void);

void InicializaPunteros()
{
    int i;
    RellenaOpcionesPuntero();
    
    for(i=0;i<9;i++)
        Punteros[i]=0;
    /* ponemos la primera combinación posible*/
    Punteros[0]=0; /* [0-0]*/
    Punteros[1]=4; /* [1-0]*/
    Punteros[2]=8; /* [2-0]*/
    Punteros[3]=12; /* [3-0]*/
    Punteros[4]=16; /* [4-0]*/
    Punteros[5]=20; /* [5-0]*/
    Punteros[6]=24; /* [6-0]*/
    Punteros[7]=28; /* [7-0]*/
    Punteros[8]=31; /* [7-3] Pongo el anterior, para que al incrementar la primera vez se prueba el [8-0] */
    
    if(0)
    { /* Inicialización para que llegue pronto la solución posible primera*/
        /* La primera solución es: [0-0] [3-0] [1-0] [2-0] [5-0] [7-0] [4-0] [6-0] [8-0] */
        Punteros[0]=0; /* [0-0]*/
        Punteros[1]=12; /* [3-0]*/
        Punteros[2]=4; /* [1-0]*/
        Punteros[3]=8; /* [2-0]*/
        Punteros[4]=20; /* [5-0]*/
        Punteros[5]=28; /* [7-0]*/
        Punteros[6]=16; /* [4-0]*/
        Punteros[7]=24; /* [6-0]*/
        Punteros[8]=0; /* [0-0] Pongo unas anteriores , para que al incrementar la primera vez se prueba el [8-0] */
    }
    if(0)
    { /* Inicialización para que llegue pronto El final de la cuenta*/
        /* La primera solución es: [8-3] [8-3] [8-3] [8-3] [8-3] [8-3] [8-3] [8-3] [0-0] */
        Punteros[0]=35; /* [8-3]*/
        Punteros[1]=35; /* [8-3]*/
        Punteros[2]=35; /* [8-3]*/
        Punteros[3]=35; /* [8-3]*/
        Punteros[4]=35; /* [8-3]*/
        Punteros[5]=35; /* [8-3]*/
        Punteros[6]=35; /* [8-3]*/
        Punteros[7]=35; /* [8-3]*/
        Punteros[8]=0; /* [0-0] Pongo unas anteriores , para que al incrementar la primera vez se prueba el [8-0] */
    }

    if(1)
    { /* Inicialización para que Llegue al cambio de la primera ficha*/
        /* 6/02/22 - Seguimos las pruebas donde lo dejamos (tras 4 resultados buenos
           colocamos el puntero en [0-1] [8-0] [7-3] [1-0] [2-0] [3-0] [4-0] [5-0] [6-0]
         Toda la tarde incrementando el puntero sin conseguirlo
         Paro en:  [0-2] [0-1] [7-1] [6-2] [1-1] [2-1] [2-3] [6-1] [0-2] y
         Paso directamente al [0-2] [1-0] [2-0] [3-0] [4-0] [5-0] [6-0] [7-0] [8-0]
        */
        Punteros[0]=2; /* [0-2]*/
        Punteros[1]=4; /* [1-0]*/
        Punteros[2]=8; /* [2-0]*/
        Punteros[3]=12; /* [3-0]*/
        Punteros[4]=16; /* [4-0]*/
        Punteros[5]=20; /* [5-0]*/
        Punteros[6]=24; /* [6-0]*/
        Punteros[7]=28; /* [7-0]*/
        Punteros[8]=31; /* [7-3] Pongo el anterior, para que al incrementar la primera vez se prueba el [8-0] */
    }
    RellenaSolucionesConocidas();
    
    RellenaOpcionesPuntero(); /* Rellena Opciones Puerto con las Piezas*/
    ContCombNegra=0;
    
    RellenaBufferPuntero();
    /* inicializo el array de pruebas*/
    PuntPruebas=0;
}

void RellenaSolucionesConocidas()
{
    struct ListaSoluciones_ CeldaSoluciones;
    int i;
    /* Para poder parar y continuar rellenamos la lista de soluciones conocidas*/
    /*
     Hay <4> Soluciones que son:
    Solución [0]: [0-0] [3-0] [1-0] [2-0] [5-0] [7-0] [4-0] [6-0] [8-0] {0, 12, 4, 8, 20, 28, 16, 24, 32}
    Solución [1]: [0-0] [3-0] [1-0] [2-0] [5-0] [7-0] [4-0] [6-0] [8-2] {0, 12, 4, 8, 20, 28, 16, 24, 34}
    Solución [2]: [0-0] [3-0] [1-0] [2-0] [5-0] [7-0] [4-0] [6-2] [8-0] {0, 12, 4, 8, 20, 28, 16, 26, 32}
    Solución [3]: [0-0] [3-0] [1-0] [2-0] [5-0] [7-0] [4-0] [6-2] [8-2] {0, 12, 4, 8, 20, 28, 16, 26, 34}*/
    /* Rellenamos El puntero */
    CeldaSoluciones.PunteroSolucion[0]=0;
    CeldaSoluciones.PunteroSolucion[1]=12;
    CeldaSoluciones.PunteroSolucion[2]=4;
    CeldaSoluciones.PunteroSolucion[3]=8;
    CeldaSoluciones.PunteroSolucion[4]=20;
    CeldaSoluciones.PunteroSolucion[5]=28;
    CeldaSoluciones.PunteroSolucion[6]=16;
    CeldaSoluciones.PunteroSolucion[7]=24;
    CeldaSoluciones.PunteroSolucion[8]=32;
    for(i=0;i<CANTIDADPIEZAS;i++){
        CeldaSoluciones.CombinacionSolucion[i].BuffPieza=OpcionesPuntero[CeldaSoluciones.PunteroSolucion[i]].BuffPieza;
        CeldaSoluciones.CombinacionSolucion[i].BuffOri=OpcionesPuntero[CeldaSoluciones.PunteroSolucion[i]].BuffOri;
    }
    MeteEnListaSoluciones(CeldaSoluciones,9);
    
    /*Solución [1]: [0-0] [3-0] [1-0] [2-0] [5-0] [7-0] [4-0] [6-0] [8-2] {0, 12, 4, 8, 20, 28, 16, 24, 34}*/
    CeldaSoluciones.PunteroSolucion[0]=0;
    CeldaSoluciones.PunteroSolucion[1]=12;
    CeldaSoluciones.PunteroSolucion[2]=4;
    CeldaSoluciones.PunteroSolucion[3]=8;
    CeldaSoluciones.PunteroSolucion[4]=20;
    CeldaSoluciones.PunteroSolucion[5]=28;
    CeldaSoluciones.PunteroSolucion[6]=16;
    CeldaSoluciones.PunteroSolucion[7]=24;
    CeldaSoluciones.PunteroSolucion[8]=34;
    for(i=0;i<CANTIDADPIEZAS;i++){
        CeldaSoluciones.CombinacionSolucion[i].BuffPieza=OpcionesPuntero[CeldaSoluciones.PunteroSolucion[i]].BuffPieza;
        CeldaSoluciones.CombinacionSolucion[i].BuffOri=OpcionesPuntero[CeldaSoluciones.PunteroSolucion[i]].BuffOri;
    }
    MeteEnListaSoluciones(CeldaSoluciones,9);
    /* Solución [2]: [0-0] [3-0] [1-0] [2-0] [5-0] [7-0] [4-0] [6-2] [8-0] {0, 12, 4, 8, 20, 28, 16, 26, 32}*/
    CeldaSoluciones.PunteroSolucion[0]=0;
    CeldaSoluciones.PunteroSolucion[1]=12;
    CeldaSoluciones.PunteroSolucion[2]=4;
    CeldaSoluciones.PunteroSolucion[3]=8;
    CeldaSoluciones.PunteroSolucion[4]=20;
    CeldaSoluciones.PunteroSolucion[5]=28;
    CeldaSoluciones.PunteroSolucion[6]=16;
    CeldaSoluciones.PunteroSolucion[7]=26;
    CeldaSoluciones.PunteroSolucion[8]=32;
    for(i=0;i<CANTIDADPIEZAS;i++){
        CeldaSoluciones.CombinacionSolucion[i].BuffPieza=OpcionesPuntero[CeldaSoluciones.PunteroSolucion[i]].BuffPieza;
        CeldaSoluciones.CombinacionSolucion[i].BuffOri=OpcionesPuntero[CeldaSoluciones.PunteroSolucion[i]].BuffOri;
    }
    MeteEnListaSoluciones(CeldaSoluciones,9);
    /* Solución [3]: [0-0] [3-0] [1-0] [2-0] [5-0] [7-0] [4-0] [6-2] [8-2] {0, 12, 4, 8, 20, 28, 16, 26, 34}*/
    CeldaSoluciones.PunteroSolucion[0]=0;
    CeldaSoluciones.PunteroSolucion[1]=12;
    CeldaSoluciones.PunteroSolucion[2]=4;
    CeldaSoluciones.PunteroSolucion[3]=8;
    CeldaSoluciones.PunteroSolucion[4]=20;
    CeldaSoluciones.PunteroSolucion[5]=28;
    CeldaSoluciones.PunteroSolucion[6]=16;
    CeldaSoluciones.PunteroSolucion[7]=26;
    CeldaSoluciones.PunteroSolucion[8]=34;
    for(i=0;i<CANTIDADPIEZAS;i++){
        CeldaSoluciones.CombinacionSolucion[i].BuffPieza=OpcionesPuntero[CeldaSoluciones.PunteroSolucion[i]].BuffPieza;
        CeldaSoluciones.CombinacionSolucion[i].BuffOri=OpcionesPuntero[CeldaSoluciones.PunteroSolucion[i]].BuffOri;
    }
    MeteEnListaSoluciones(CeldaSoluciones,9);
    
}

int IncrementaPunteros()
{
    int i;
    /* Cada vez que se invoca se incrementa el puntero (desde el 9 al 0 */
    if(Punteros[8]<35)Punteros[8]=Punteros[8]+1;
    else
    {
        Punteros[8]=0;
        if(Punteros[7]<35) Punteros[7]=Punteros[7]+1;
        else{
            Punteros[7]=0;
            if(Punteros[6]<35) Punteros[6]=Punteros[6]+1;
            else{
                Punteros[6]=0;
                if(Punteros[5]<35) Punteros[5]=Punteros[5]+1;
                else{
                    Punteros[5]=0;
                    if(Punteros[4]<35) Punteros[4]=Punteros[4]+1;
                    else{
                        Punteros[4]=0;
                        if(Punteros[3]<35) Punteros[3]=Punteros[3]+1;
                        else{
                            Punteros[3]=0;
                            if(Punteros[2]<35) Punteros[2]=Punteros[2]+1;
                            else{
                                Punteros[2]=0;
                                if(Punteros[1]<35) Punteros[1]=Punteros[1]+1;
                                else{
                                    Punteros[1]=0;
                                    if(Punteros[0]<35) Punteros[0]=Punteros[0]+1;
                                    else{
                                        for(i=0;i<CANTIDADPIEZAS;i++)
                                            Punteros[i]=35;
                                        RellenaBufferPuntero();
                                        SeHaFinalizadoLaCuenta=1;
                                        if(MostrarCadaIncrementoDePuntero) PintaBufferPuntero();
                                        return 1; /* Se ha acabado de incrementar*/
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    RellenaBufferPuntero();
    if(MostrarCadaIncrementoDePuntero) PintaBufferPuntero();
    return 0;
}

void PintaPunteros()
{
    int i;
    printf("Situación Punteros: ");
    for(i=0;i<9;i++)
        printf("<%u> ",Punteros[i]);
    printf("\r\n");
}

void RellenaOpcionesPuntero()
{
    
    //    struct{
    //        int BuffPieza;
    //        int BuffOri;
    //    }OpcionesPuntero[36];
    
    int i,j,tmpPunt=0;
    
    for(i=0;i<CANTIDADPIEZAS;i++){
        for(j=0;j<CANTIDADORIENTACIONES;j++,tmpPunt++){
            OpcionesPuntero[tmpPunt].BuffPieza=i;
            OpcionesPuntero[tmpPunt].BuffOri=j;
        }
    }
}

void PintaOpcionesPuntero()
{
    
    //    struct{
    //        int BuffPieza;
    //        int BuffOri;
    //    }OpcionesPuntero[36];
    int i,j;
    
    printf("El Puntero (Contador de pruebas), cada valor se traduce en:\n");
    for(i=0,j=1;i<36;i++,j++)
    {
        if(i<10) printf(" ");
        printf("<%u>:[%u-%u] ",i,OpcionesPuntero[i].BuffPieza,OpcionesPuntero[i].BuffOri);
        if(j==4){
            printf("\n");
            j=0;
        }
    }
}

void RellenaBufferPuntero(){
    /* Una vez tenemos el puntero actual rellenamos el Buffer con las Piezas que corresponden*/
    int i;
    int tmpPunt=0;
    
    for(i=0;i<CANTIDADPIEZAS;i++){
        BufferPuntero[i].BuffPieza=OpcionesPuntero[Punteros[i]].BuffPieza;
        BufferPuntero[i].BuffOri=OpcionesPuntero[Punteros[i]].BuffOri;
    }
}

void PintaBufferPuntero()
{
    int i;
    printf("Buffer Punteros: ");
    for(i=0;i<9;i++)
        printf("[%u-%u] ",BufferPuntero[i].BuffPieza,BufferPuntero[i].BuffOri);
    printf("\r\n");
}

int PunteroEsPosible(struct CasillaPieza_ BuffCheck[CANTIDADPIEZAS]){
    /* Esta función decide si la combinación que se le pasa como parámetro (BuffCheck) es una combinación posible:
     Criterios:
     1) No pueden haber dos piezas iguales
     2) No puede estar en la lista negra
     
     Devuelve:
     0- La combinación es posible
     1- Combinación No posible porque se repiten las piezas
     2- Combinación en la lista negra */
    
    int i,j;
    int HayPiezasIguales=0;
    int tmpBuffPiezas[CANTIDADPIEZAS]={0,0,0,0,0,0,0,0,0};
    int EstaEnListaNegra=0;
    int HayAlgunaPiezaDistinta=0;
    
    for (i=0;i<CANTIDADPIEZAS;i++)
    {
        j=BuffCheck[i].BuffPieza;
        if(tmpBuffPiezas[j]==1)
        {/* Pieza ya ocupada*/
            HayPiezasIguales=1;
        }
        else
        {
            tmpBuffPiezas[j]=1;
        }
    }
    if(HayPiezasIguales) return 1;
    
    if(0){/* Anulo la prueba de si está en lista negra*/
        
        /* Pasamos a probar si esta Combinación está en la lista negra*/
        for(i=0,HayAlgunaPiezaDistinta=0;i<ContCombNegra && HayAlgunaPiezaDistinta==0;i++){
            /* Pasamos por todas las combinaciones que están en la lista negra y se comprueba si BuffCheck está*/
            j=ListaNegraPunteros[i].NumPiezasCombi; /* solo para DEBUG*/
            for(j=0;j<ListaNegraPunteros[i].NumPiezasCombi && HayAlgunaPiezaDistinta==0;j++){
                if(BuffCheck[j].BuffPieza!=ListaNegraPunteros[i].CombinacionNegra[j].BuffPieza || BuffCheck[j].BuffOri!=ListaNegraPunteros[i].CombinacionNegra[j].BuffOri)
                    HayAlgunaPiezaDistinta=1;
            }
        }
        
        if(HayAlgunaPiezaDistinta==0 && ContCombNegra!=0) EstaEnListaNegra=1;
        if(EstaEnListaNegra)
            return 2;
    }
    return 0; /* La combinación es posible*/
}

int MeteEnListaNegra(struct ListaNegraPunteros_ BuffCheck,int NumPiezas)
{
    int i;
    for(i=0;i<NumPiezas;i++){
        ListaNegraPunteros[ContCombNegra].CombinacionNegra[i].BuffPieza=BuffCheck.CombinacionNegra[i].BuffPieza;
        ListaNegraPunteros[ContCombNegra].CombinacionNegra[i].BuffOri=BuffCheck.CombinacionNegra[i].BuffOri;
    }
    for(i=NumPiezas;i<CANTIDADPIEZAS;i++){
        ListaNegraPunteros[ContCombNegra].CombinacionNegra[i].BuffPieza=0xffff;
        ListaNegraPunteros[ContCombNegra].CombinacionNegra[i].BuffOri=0xffff;
    }
    ListaNegraPunteros[ContCombNegra].NumPiezasCombi=NumPiezas;
    ContCombNegra=ContCombNegra+1;
    return ContCombNegra;
}

void PintaListaNegra(void)
{
    int i,j;
    printf("Lista Negra: \n");
    for(j=0;j<ContCombNegra;j++){
        printf("List [%u] %u Piezas: ",j,ListaNegraPunteros[j].NumPiezasCombi);
        for(i=0;i<ListaNegraPunteros[j].NumPiezasCombi;i++)
            printf("[%u-%u] ",ListaNegraPunteros[j].CombinacionNegra[i].BuffPieza,ListaNegraPunteros[j].CombinacionNegra[i].BuffOri);
        printf("\r\n");
    }
    
}

void SaltaCeldasListaNegra(int NumCeldaListaNegra){
    /* Se invoca cuando se acaba de meter algo en la lista negra.
     Si una Combinación No es buena [0-0] [1-0] y la siguiente [2-0] no se puede colocar
     Se mete en lista negra [0-0] [1-0] [2-0] y el puntero se coloca en [0-0] [1-0] [2-1] [3-0] [4-0] [5-0] [6-0] [7-0] [7-3].. para
     que la siguiente incremento pase a la ficha siguiente*/
    
    int i,j,k;
    int PiezasUsadas[9]={0,0,0,0,0,0,0,0,0};
    int BufferPiezas[9]={0,4,8,12,16,20,24,28,32}; /* [0-0] [1-0] [2-0] [3-0] [4-0] [5-0] [6-0] [7-0] [8-0]*/
    int PuntBuffPiezas=0;
    
    k=ListaNegraPunteros[NumCeldaListaNegra].NumPiezasCombi;/* El número de celdas del Punteros que están en la lista negra*/
    /* Incremente en 1 la pieza que ha causado que sea metida en al lista negra*/
    Punteros[k-1]=Punteros[k-1]+1;
    RellenaBufferPuntero();
//    PintaBufferPuntero();
    for(i=0;i<k;i++)
    {
        j=BufferPuntero[i].BuffPieza;
        PiezasUsadas[j]=0xff;
    }
    
    for(j=k,PuntBuffPiezas=0;j<CANTIDADPIEZAS;j++){
        while(PiezasUsadas[PuntBuffPiezas]==0xff) PuntBuffPiezas=PuntBuffPiezas+1;
        Punteros[j]=BufferPiezas[PuntBuffPiezas];
        PuntBuffPiezas=PuntBuffPiezas+1;
    }
    /* Decremento la última pieza para que al incrementar llegue a la combinación que queremos*/
    
    Punteros[CANTIDADPIEZAS-1]=Punteros[CANTIDADPIEZAS-1]-1;
    
    RellenaBufferPuntero();
//    PintaBufferPuntero();
}

int MeteEnListaSoluciones(struct ListaSoluciones_ BuffCheck,int NumPrueba)
{
    int i;
    
    ListaSoluciones[ContadorSoluciones].NumPruebaSolucion=PuntPruebas;
    
 
    for(i=0;i<CANTIDADPIEZAS;i++){
        ListaSoluciones[ContadorSoluciones].CombinacionSolucion[i].BuffPieza=BuffCheck.CombinacionSolucion[i].BuffPieza;
        ListaSoluciones[ContadorSoluciones].CombinacionSolucion[i].BuffOri=BuffCheck.CombinacionSolucion[i].BuffOri;
        ListaSoluciones[ContadorSoluciones].PunteroSolucion[i]=BuffCheck.PunteroSolucion[i];
    }
    ContadorSoluciones=ContadorSoluciones+1;
    return ContadorSoluciones;
}

void PintaListaSoluciones(void)
{
    int i,j;
    printf("Hay <%u> Soluciones que son: \n",ContadorSoluciones);
    for(j=0;j<ContadorSoluciones;j++){
        printf("Solución [%u]: ",j);
        for(i=0;i<CANTIDADPIEZAS;i++)
            printf("[%u-%u] ",ListaSoluciones[j].CombinacionSolucion[i].BuffPieza, ListaSoluciones[j].CombinacionSolucion[i].BuffOri);
        printf ("{");
        for(i=0;i<CANTIDADPIEZAS;i++){
            printf("%u",ListaSoluciones[j].PunteroSolucion[i]);
            if(i!=CANTIDADPIEZAS-1) printf(", ");
        }
            
        printf("}");
        printf("\r\n");
    }
    
}

int DameSiguientePunteroValido()
{ /* Incrementa los punteros hasta que encuentra una función válida*/
    
    do{
        IncrementaPunteros();
        if(SeHaFinalizadoLaCuenta) break;
    }while(PunteroEsPosible(BufferPuntero)!=0);
    
    if(SeHaFinalizadoLaCuenta) {
        printf("Se ha finalizado de incrementar el Puntero\n");
        return 1;
    }
    if(MostrarCadaPunteroValido)
    {
    printf("\nCombinación a probar: ");
    PintaBufferPuntero();
    printf("\n");
    }
    
    return 0;
}

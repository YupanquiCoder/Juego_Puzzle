//
//  Punteros.c
//  Juego_Puzzle
//
//  Created by Miguel Ruiz on 26/2/22.
//

#include "Punteros.h"
#include "main.h"


int Punteros[9];

struct CasillaPieza_ OpcionesPuntero[36];

struct CasillaPieza_ BufferPuntero[9];

/* Lista Negra de Combinaciones */

struct ListaNegraPunteros_ ListaNegraPunteros [NUMMAXLISTANEGRA];
int ContCombNegra=0; /* Contador de Combinaciones en la Lista Negra*/

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
    Punteros[8]=32; /* [8-0]*/
    
    RellenaOpcionesPuntero(); /* Rellena Opciones Puerto con las Piezas*/
    ContCombNegra=0;
    
}

int IncrementaPunteros()
{
    /* Cada vez que se invoca se incrementa el puntero (desde el 9 al 0 */
    if(Punteros[8]<36)Punteros[8]=Punteros[8]+1;
    else
    {
        Punteros[8]=0;
        if(Punteros[7]<36) Punteros[7]=Punteros[7]+1;
        else{
            Punteros[7]=0;
            if(Punteros[6]<36) Punteros[6]=Punteros[6]+1;
            else{
                Punteros[6]=0;
                if(Punteros[5]<36) Punteros[5]=Punteros[5]+1;
                else{
                    Punteros[5]=0;
                    if(Punteros[4]<36) Punteros[4]=Punteros[4]+1;
                    else{
                        Punteros[4]=0;
                        if(Punteros[3]<36) Punteros[3]=Punteros[3]+1;
                        else{
                            Punteros[3]=0;
                            if(Punteros[2]<36) Punteros[2]=Punteros[2]+1;
                            else{
                                Punteros[2]=0;
                                if(Punteros[1]<36) Punteros[1]=Punteros[1]+1;
                                else{
                                    Punteros[1]=0;
                                    if(Punteros[0]<36) Punteros[0]=Punteros[0]+1;
                                    else{
                                        Punteros[0]=Punteros[0];
                                        RellenaBufferPuntero();
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
    
    for(i=0,j=1;i<36;i++,j++)
    {
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
    printf("Situación Buffer Punteros: ");
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
    if(EstaEnListaNegra) return 2;
    
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

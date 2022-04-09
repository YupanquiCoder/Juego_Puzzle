//
//  Punteros.c
//  Juego_Puzzle
//
//  Created by Miguel Ruiz on 26/2/22.
//

#include "Punteros.h"



int Punteros[9];

int SeHaFinalizadoLaCuenta=0;

struct CasillaPieza_ BufferPuntero[9]; /* Cada vez que se incremente se colocan las piezas en este Buffer */




void InicializaPunteros()
{
    
    /* ponemos la primera combinación posible*/
    BufferPuntero[0].BuffPieza=0;/* [0-0]*/
    BufferPuntero[0].BuffOri=0;
    BufferPuntero[1].BuffPieza=1;/* [1-0]*/
    BufferPuntero[1].BuffOri=0;
    BufferPuntero[2].BuffPieza=2;/* [2-0]*/
    BufferPuntero[2].BuffOri=0;
    BufferPuntero[3].BuffPieza=3;/* [3-0]*/
    BufferPuntero[3].BuffOri=0;
    BufferPuntero[4].BuffPieza=4;/* [4-0]*/
    BufferPuntero[4].BuffOri=0;
    BufferPuntero[5].BuffPieza=5;/* [5-0]*/
    BufferPuntero[5].BuffOri=0;
    BufferPuntero[6].BuffPieza=6;/* [6-0]*/
    BufferPuntero[6].BuffOri=0;
    BufferPuntero[7].BuffPieza=7;/* [7-0]*/
    BufferPuntero[7].BuffOri=0;
    BufferPuntero[8].BuffPieza=7;/* [7-3] Pongo unas anteriores , para que al incrementar la primera vez se prueba el [8-0]*/
    BufferPuntero[8].BuffOri=3;
    
    ContCombNegra=0;
    
    /* inicializo el array de pruebas*/
    PuntPruebas=0;

}


int IncrementaPunteros()
{
    /* Cada vez que se invoca se incrementa el puntero (desde el 9 al 0 */
    IncrementaBufferPuntero();
    if(MostrarCadaIncrementoDePuntero) PintaBufferPuntero();
    return 0;
}

int IncrementaPiezaBuffer(int Posicion)
{
    /* Incrementa el Buffer Puntero de la pieza Posición
     OJO se llama recursivamente
     Devuelve: Posición de la última pieza incrementada
     99- Se ha terminado de incrementar todo el puntero la pieza 0 ha llegado a la 8-3
     */
    int i,j;
    int PiezaSiguienteMasBaja;
    int PiezaActual;
    int PiezaIncrementadaEsta=0;
    int PiezasUsadas[9]={0,0,0,0,0,0,0,0,0};
    
    /* Se incrementa el BufferPuntero pero teniendo en cuenta que el resultado sea un puntero válido
     Un puntero válido será el que No tenga piezas iguales */
    /* struct CasillaPieza_ BufferPuntero[9];*/
    
    if(BufferPuntero[Posicion].BuffOri!=3)
        BufferPuntero[Posicion].BuffOri=BufferPuntero[Posicion].BuffOri+1; /* Solo incrementamos Orientación*/
    else
    { /* Hay que incrementar la pieza Posición Comprobamos*/
        if(BufferPuntero[Posicion].BuffPieza!=8)
        {
            BufferPuntero[Posicion].BuffPieza=BufferPuntero[Posicion].BuffPieza+1; /* Incrementamos pieza "Siguiente"*/
            PiezaActual=BufferPuntero[Posicion].BuffPieza;
            /* Confirmamos si esa pieza ya está colocada*/
            for (i=0;i<Posicion;i++)
            {
                if(BufferPuntero[i].BuffPieza==PiezaActual)
                    PiezaIncrementadaEsta=1;
            }
            
            if(!PiezaIncrementadaEsta)
            {
                /* La Pieza que se ha incrementado No está ya puesta -> seguimos*/
                BufferPuntero[Posicion].BuffOri=0;
                return Posicion;
            }
            else
            { /* La Pieza incrementaada ya está - buscamos la pieza "menor" que sea mas alta que la actual */
                /* No buscamos la mas baja de las que NO estén*/
                if(Posicion==8){
                    /* Si es la última pieza no hay mas que incrementar la siguiente*/
                    return IncrementaPiezaBuffer(Posicion-1);
                }
                else
                {
                    PiezaSiguienteMasBaja=9;
                    for(i=0;i<Posicion-1;i++)
                    {
                        j=BufferPuntero[i].BuffPieza;
                        PiezasUsadas[j]=0xff;
                        if(j<PiezaSiguienteMasBaja) PiezaSiguienteMasBaja=j;
                        
                    }
                    
                    /* ej PiezaSiguienteMasBaja está la primera pieza qu no está ha usado*/
                    if(PiezaSiguienteMasBaja>PiezaActual)
                    {
                        /* Se ha encontrado una pieza adecuada*/
                        BufferPuntero[Posicion].BuffPieza=PiezaSiguienteMasBaja;
                        BufferPuntero[Posicion].BuffOri=0;
                        return Posicion;
                    }
                    else
                    {
                        /* No se ha encontrado una pieza adecuada hay que incrementar la pieza siguiente*/
                        if(Posicion==0)
                        { /* Es la primera Pieza*/
                            if(BufferPuntero[Posicion].BuffPieza==8)
                            { /* Se ha finalizado de incrementar el buffer*/
                                return 99;
                            }
                            else
                            {
                                BufferPuntero[Posicion].BuffPieza=BufferPuntero[Posicion].BuffPieza+1;
                                BufferPuntero[Posicion].BuffOri=0;
                            }
                        }
                        else
                        { /* No es la primera Pieza*/
                            return IncrementaPiezaBuffer(Posicion-1);
                        }
                    }
                    
                }
                
            }
        }
        else
        { /* La pieza a incrementar es ya 8*/
            return IncrementaPiezaBuffer(Posicion-1);
        }
    }
    return Posicion;
}

int IncrementaBufferPuntero(void)
{
    int i,j;
    int Posicion;
    int PiezasUsadas[9]={0,0,0,0,0,0,0,0,0};
    int PuntBuffPiezas=0;
    
    Posicion=IncrementaPiezaBuffer(8);
    /* Devuelve la Posición de la última pieza incrementada*/
//    printf("Posicion:%u\n",Posicion);
    if(Posicion==99)
        SeHaFinalizadoLaCuenta=1;
    else
    {
        /* Hay que rellenar el resto de piezas con las que no se repitan
         Desde la Posición  i + 1*/
        for(i=0;i<Posicion+1;i++)
        {
            j=BufferPuntero[i].BuffPieza;
            PiezasUsadas[j]=0xff;
        }
//        /* DEBUG*/
//        printf("Antes de ajuste:");
//        PintaBufferPuntero();
//        /* DEBUG*/
        if(Posicion!=8){
            for(j=Posicion+1,PuntBuffPiezas=0;j<CANTIDADPIEZAS;j++){
                while(PiezasUsadas[PuntBuffPiezas]==0xff) PuntBuffPiezas=PuntBuffPiezas+1;
                BufferPuntero[j].BuffPieza=PuntBuffPiezas;
                BufferPuntero[j].BuffOri=0;
                PuntBuffPiezas=PuntBuffPiezas+1;
            }
        }
//        /* DEBUG*/
//        printf("Después de ajuste:");
//        PintaBufferPuntero();
//        /* DEBUG*/
    }
    return 0;
}

void PintaBufferPuntero()
{
    int i;
    printf("Combinación Actual: ");
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
    
    long int i,j;
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
    if(HayPiezasIguales){
        PintaBufferPuntero();
        return 1;
    }
    
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



void SaltaCeldasListaNegra(long int NumCeldaListaNegra){
    /* Se invoca cuando se acaba de meter algo en la lista negra.
     Si una Combinación No es buena [0-0] [1-0] y la siguiente [2-0] no se puede colocar
     Se mete en lista negra [0-0] [1-0] [2-0] y el puntero se coloca en [0-0] [1-0] [2-1] [3-0] [4-0] [5-0] [6-0] [7-0] [7-3].. para
     que la siguiente incremento pase a la ficha siguiente*/
    
    int i,j,k;
    int PiezasUsadas[9]={0,0,0,0,0,0,0,0,0};
    int PuntBuffPiezas=0;
    struct CasillaPieza_ tmpPieza;
    int SeguirBuscando=1;
    int PosicionAIncrementar=0;
    int PiezaRepetida=0;

   /* DEBUG*/
//    if(PuntPruebas==13 ||PuntPruebas==14 ||PuntPruebas==0)
//    {
//        printf ("Buffer Puntero antes de incrementar tras lista negra: Ceda lista Negra %ld\n",NumCeldaListaNegra);
//           PintaCeldaListaNegra(NumCeldaListaNegra);
//           PintaBufferPuntero();
//    }
    /* DEBUG*/

//    if(PuntPruebas==1195273){
//        DumpError();
//    }

    k=ListaNegraPunteros[NumCeldaListaNegra].NumPiezasCombi;/* El número de celdas del Punteros que están en la lista negra*/
    PosicionAIncrementar=k-1;

    if(ListaNegraPunteros[NumCeldaListaNegra].CombinacionNegra[PosicionAIncrementar].BuffPieza==8 &&
       ListaNegraPunteros[NumCeldaListaNegra].CombinacionNegra[PosicionAIncrementar].BuffOri==3)
    {
        if(PosicionAIncrementar>0)
            PosicionAIncrementar=PosicionAIncrementar-1;
        else{
            /* la primera pieza es la 8-3 -> Se ha temrinado ya, no se puede decrementar*/
            SeguirBuscando=0;
            SeHaFinalizadoLaCuenta=1;
        }
            
    }/* Si la pieza que ha causado la lista negra es [8-3] Hay que incrementar la anterior */

    /* Incremente en 1 la pieza que ha causado que sea metida en la lista negra*/
    while(SeguirBuscando){
        /* En k tenemos la pieza que ha causado la lista negra
         Ej. [6-2] [8-3] K=2 ya que la 8-3 no ha cabido
         Tendremos que oncrementar a [6-3][0-0]...*/
        /* Rellenamos el buffer de Piezas Usadas desde el 0 hasta Posición a incrementar*/
        for(i=0;i<CANTIDADPIEZAS;i++)
        {
            PiezasUsadas[i]=0x00;
        }
        for(i=0;i<PosicionAIncrementar;i++)
        {
            j=BufferPuntero[i].BuffPieza;
            PiezasUsadas[j]=0xff;
        }

        PiezaRepetida=0;

        tmpPieza.BuffPieza=ListaNegraPunteros[NumCeldaListaNegra].CombinacionNegra[PosicionAIncrementar].BuffPieza;
        tmpPieza.BuffOri=ListaNegraPunteros[NumCeldaListaNegra].CombinacionNegra[PosicionAIncrementar].BuffOri;
        do{
            
            
        IncrementaOrienta(&tmpPieza.BuffPieza,&tmpPieza.BuffOri);
        if(tmpPieza.BuffPieza==0 && tmpPieza.BuffOri==0)
        {
            /* ya se ha llegado al final luego hay que parar de incrementar*/
            break;
        }
            if(PiezasUsadas[tmpPieza.BuffPieza]==0xff && PosicionAIncrementar!=0)
                PiezaRepetida=1;
            else
                PiezaRepetida=0;
        }while(PiezaRepetida);

        if(tmpPieza.BuffPieza==0 && tmpPieza.BuffOri==0)
        {
            /* La pieza a incrementar era la 8-3 hay que incrementar la anterior*/
            if(PosicionAIncrementar==0)
            {
                /* Se ha llegado al final de la cuenta*/
                SeHaFinalizadoLaCuenta=1;
                SeguirBuscando=0;
            }
            else
            {
                PosicionAIncrementar=PosicionAIncrementar-1;
            }
        }
        else
        {/* La pieza No es la 8-3 luego se ha incrementado bien*/
            SeguirBuscando=0;
        }
    }

//    /* DEBUG*/
//    /* Limpio Buffer Puntero */
//    for(i=0;i<CANTIDADPIEZAS;i++)
//    {
//        BufferPuntero[i].BuffPieza=0xff;
//        BufferPuntero[i].BuffOri=0xff;
//    }
//    /* DEBUG*/

    /* Rellenamos el buffer de Puntero con la nueva combinación*/
    /* Lista Negra desde 0-> Posición a incrementar*/
    for(i=0;i<PosicionAIncrementar;i++)
    {
        BufferPuntero[i].BuffPieza=ListaNegraPunteros[NumCeldaListaNegra].CombinacionNegra[i].BuffPieza;
        BufferPuntero[i].BuffOri=ListaNegraPunteros[NumCeldaListaNegra].CombinacionNegra[i].BuffOri;
    }
    BufferPuntero[PosicionAIncrementar].BuffPieza=tmpPieza.BuffPieza;
    BufferPuntero[PosicionAIncrementar].BuffOri=tmpPieza.BuffOri;

    for(i=0;i<PosicionAIncrementar+1;i++)
    {
        j=BufferPuntero[i].BuffPieza;
        PiezasUsadas[j]=0xff;
    }

    for(j=PosicionAIncrementar+1,PuntBuffPiezas=0;j<CANTIDADPIEZAS;j++){
        while(PiezasUsadas[PuntBuffPiezas]==0xff) PuntBuffPiezas=PuntBuffPiezas+1;
        BufferPuntero[j].BuffPieza=PuntBuffPiezas;
        BufferPuntero[j].BuffOri=0;
        PuntBuffPiezas=PuntBuffPiezas+1;
    }
    /* Decremento la última pieza para que al incrementar probemos esta última*/
    tmpPieza.BuffPieza=BufferPuntero[CANTIDADPIEZAS-1].BuffPieza;
    tmpPieza.BuffOri=BufferPuntero[CANTIDADPIEZAS-1].BuffOri;
    DecrementaOrienta(&tmpPieza.BuffPieza,&tmpPieza.BuffOri);
    BufferPuntero[CANTIDADPIEZAS-1].BuffPieza=tmpPieza.BuffPieza;
    BufferPuntero[CANTIDADPIEZAS-1].BuffOri=tmpPieza.BuffOri;
}


int DameSiguientePunteroValido()
{ /* Incrementa los punteros hasta que encuentra una función válida*/
    
    do{
        IncrementaBufferPuntero();
        if(SeHaFinalizadoLaCuenta) break;
    }while(PunteroEsPosible(BufferPuntero)!=0);
    
    if(SeHaFinalizadoLaCuenta) {
        printf("Se ha finalizado de incrementar el Puntero\n");
        return 1;
    }
    if(MostrarCadaPunteroValido)
    {
        PintaBufferPuntero();
    }
    
    return 0;
}

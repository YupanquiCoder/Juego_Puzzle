//
//  Punteros.c
//  Juego_Puzzle
//
//  Created by Miguel Ruiz on 26/2/22.
//

#include "Punteros.h"
#include "main.h"
#include "Tablero.h"


int Punteros[9];

int SeHaFinalizadoLaCuenta=0;

struct CasillaPieza_ BufferPuntero[9]; /* Cada vez que se incremente se colocan las piezas en este Buffer */



struct ListaSoluciones_ ListaSoluciones[NUMMAXSOLUCIONES];
int ContadorSoluciones=0; /* Indica el número de soluciones encontradas*/

/* Prototipos */
void RellenaSolucionesConocidas(void);

void InicializaPunteros()
{
    int i;
    
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
    
    if(0)
    { /* Inicialización para que llegue pronto la solución posible primera*/
        /* La primera solución es: [0-0] [3-0] [1-0] [2-0] [5-0] [7-0] [4-0] [6-0] [8-0] */
        BufferPuntero[0].BuffPieza=0;/* [0-0]*/
        BufferPuntero[0].BuffOri=0;
        BufferPuntero[1].BuffPieza=3;/* [3-0]*/
        BufferPuntero[1].BuffOri=0;
        BufferPuntero[2].BuffPieza=1;/* [1-0]*/
        BufferPuntero[2].BuffOri=0;
        BufferPuntero[3].BuffPieza=2;/* [2-0]*/
        BufferPuntero[3].BuffOri=0;
        BufferPuntero[4].BuffPieza=5;/* [5-0]*/
        BufferPuntero[4].BuffOri=0;
        BufferPuntero[5].BuffPieza=7;/* [7-0]*/
        BufferPuntero[5].BuffOri=0;
        BufferPuntero[6].BuffPieza=4;/* [4-0]*/
        BufferPuntero[6].BuffOri=0;
        BufferPuntero[7].BuffPieza=6;/* [6-0]*/
        BufferPuntero[7].BuffOri=0;
        BufferPuntero[8].BuffPieza=7;/* [7-3] Pongo unas anteriores , para que al incrementar la primera vez se prueba el [8-0]*/
        BufferPuntero[8].BuffOri=3;
    
    }
    if(0)
    { /* Inicialización para que llegue pronto El final de la cuenta*/
        /* La primera solución es: [8-3] [8-3] [8-3] [8-3] [8-3] [8-3] [8-3] [8-3] [0-0] */
        BufferPuntero[0].BuffPieza=6;/* [6-2]*/
        BufferPuntero[0].BuffOri=2;
        BufferPuntero[1].BuffPieza=8;/* [8-3]*/
        BufferPuntero[1].BuffOri=3;
        BufferPuntero[2].BuffPieza=7;/* [7-3]*/
        BufferPuntero[2].BuffOri=3;
        BufferPuntero[3].BuffPieza=1;/* [1-3]*/
        BufferPuntero[3].BuffOri=3;
        BufferPuntero[4].BuffPieza=5;/* [5-3]*/
        BufferPuntero[4].BuffOri=3;
        BufferPuntero[5].BuffPieza=4;/* [4-3]*/
        BufferPuntero[5].BuffOri=3;
        BufferPuntero[6].BuffPieza=3;/* [3-3]*/
        BufferPuntero[6].BuffOri=3;
        BufferPuntero[7].BuffPieza=2;/* [2-3]*/
        BufferPuntero[7].BuffOri=3;
        BufferPuntero[8].BuffPieza=0;/* [0-3]*/
        BufferPuntero[8].BuffOri=3;
     
    }
    
    if(0)
    {
        /* Inicializamos para continuar con la siguiente solución ya inicializada */
        /* Solución [3]: [0-0] [3-0] [1-0] [2-0] [5-0] [7-0] [4-0] [6-2] [8-2] */
        BufferPuntero[0].BuffPieza=0;/* [0-0]*/
        BufferPuntero[0].BuffOri=0;
        BufferPuntero[1].BuffPieza=3;/* [3-0]*/
        BufferPuntero[1].BuffOri=0;
        BufferPuntero[2].BuffPieza=1;/* [1-0]*/
        BufferPuntero[2].BuffOri=0;
        BufferPuntero[3].BuffPieza=2;/* [2-0]*/
        BufferPuntero[3].BuffOri=0;
        BufferPuntero[4].BuffPieza=5;/* [5-0]*/
        BufferPuntero[4].BuffOri=0;
        BufferPuntero[5].BuffPieza=7;/* [7-0]*/
        BufferPuntero[5].BuffOri=0;
        BufferPuntero[6].BuffPieza=4;/* [4-0]*/
        BufferPuntero[6].BuffOri=0;
        BufferPuntero[7].BuffPieza=6;/* [6-2]*/
        BufferPuntero[7].BuffOri=2;
        BufferPuntero[8].BuffPieza=8;/* [8-2]*/
        BufferPuntero[8].BuffOri=2;
       
    }
    
    
    RellenaSolucionesConocidas();
    
    ContCombNegra=0;
    
    /* inicializo el array de pruebas*/
    PuntPruebas=0;
    
    /* DEBUG*/
//    PintaUnaSolucion(1,0); /* Solución 1 Sin Debug completo*/
}

void RellenaSolucionesConocidas()
{
    struct ListaSoluciones_ CeldaSoluciones;

    /* Para poder parar y continuar rellenamos la lista de soluciones conocidas*/
    /*
     Hay <188> Soluciones que son:
     Solución [0]: [0-0] [3-0] [1-0] [2-0] [5-0] [7-0] [4-0] [6-0] [8-0]
     Solución [1]: [0-0] [3-0] [1-0] [2-0] [5-0] [7-0] [4-0] [6-0] [8-2]
     Solución [2]: [0-0] [3-0] [1-0] [2-0] [5-0] [7-0] [4-0] [6-2] [8-0]
     Solución [3]: [0-0] [3-0] [1-0] [2-0] [5-0] [7-0] [4-0] [6-2] [8-2]
     Solución [4]: [0-1] [7-3] [1-1] [6-1] [4-2] [2-2] [5-1] [3-1] [8-0]
     Solución [5]: [0-1] [7-3] [1-1] [6-1] [4-2] [2-2] [5-1] [3-1] [8-2]
     Solución [6]: [0-1] [7-3] [1-1] [6-3] [4-2] [2-2] [5-1] [3-1] [8-0]
     Solución [7]: [0-1] [7-3] [1-1] [6-3] [4-2] [2-2] [5-1] [3-1] [8-2]
     Solución [8]: [1-0] [0-0] [6-1] [2-0] [8-1] [5-2] [4-0] [3-3] [7-1]
     Solución [9]: [1-0] [0-0] [6-1] [2-0] [8-3] [5-2] [4-0] [3-3] [7-1]
     Solución [10]: [1-0] [0-0] [6-3] [2-0] [8-1] [5-2] [4-0] [3-3] [7-1]
     Solución [11]: [1-0] [0-0] [6-3] [2-0] [8-3] [5-2] [4-0] [3-3] [7-1]
     Solución [12]: [1-0] [6-0] [3-3] [0-1] [2-0] [5-2] [4-2] [7-0] [8-0]
     Solución [13]: [1-0] [6-0] [3-3] [0-1] [2-0] [5-2] [4-2] [7-0] [8-2]
     Solución [14]: [1-0] [6-2] [3-3] [0-1] [2-0] [5-2] [4-2] [7-0] [8-0]
     Solución [15]: [1-0] [6-2] [3-3] [0-1] [2-0] [5-2] [4-2] [7-0] [8-2]
     Solución [16]: [1-0] [7-3] [2-0] [3-1] [8-1] [5-0] [4-0] [0-2] [6-0]
     Solución [17]: [1-0] [7-3] [2-0] [3-1] [8-1] [5-0] [4-0] [0-2] [6-2]
     Solución [18]: [1-0] [7-3] [2-0] [3-1] [8-3] [5-0] [4-0] [0-2] [6-0]
     Solución [19]: [1-0] [7-3] [2-0] [3-1] [8-3] [5-0] [4-0] [0-2] [6-2]
     Solución [20]: [1-3] [7-3] [4-0] [3-0] [8-1] [0-1] [6-0] [5-1] [2-3]
     Solución [21]: [1-3] [7-3] [4-0] [3-0] [8-1] [0-1] [6-2] [5-1] [2-3]
     Solución [22]: [1-3] [7-3] [4-0] [3-0] [8-1] [2-0] [6-0] [5-1] [0-2]
     Solución [23]: [1-3] [7-3] [4-0] [3-0] [8-1] [2-0] [6-2] [5-1] [0-2]
     Solución [24]: [1-3] [7-3] [4-0] [3-0] [8-3] [0-1] [6-0] [5-1] [2-3]
     Solución [25]: [1-3] [7-3] [4-0] [3-0] [8-3] [0-1] [6-2] [5-1] [2-3]
     Solución [26]: [1-3] [7-3] [4-0] [3-0] [8-3] [2-0] [6-0] [5-1] [0-2]
     Solución [27]: [1-3] [7-3] [4-0] [3-0] [8-3] [2-0] [6-2] [5-1] [0-2]
     Solución [28]: [1-3] [7-3] [5-3] [8-1] [4-0] [6-1] [3-0] [0-0] [2-3]
     Solución [29]: [1-3] [7-3] [5-3] [8-1] [4-0] [6-3] [3-0] [0-0] [2-3]
     Solución [30]: [1-3] [7-3] [5-3] [8-3] [4-0] [6-1] [3-0] [0-0] [2-3]
     Solución [31]: [1-3] [7-3] [5-3] [8-3] [4-0] [6-3] [3-0] [0-0] [2-3]
     Solución [32]: [1-3] [8-1] [3-2] [4-2] [0-1] [7-0] [5-3] [6-1] [2-3]
     Solución [33]: [1-3] [8-1] [3-2] [4-2] [0-1] [7-0] [5-3] [6-3] [2-3]
     Solución [34]: [1-3] [8-3] [3-2] [4-2] [0-1] [7-0] [5-3] [6-1] [2-3]
     Solución [35]: [1-3] [8-3] [3-2] [4-2] [0-1] [7-0] [5-3] [6-3] [2-3]
     Solución [36]: [2-0] [0-0] [1-0] [4-1] [6-0] [5-2] [3-1] [7-0] [8-0]
     Solución [37]: [2-0] [0-0] [1-0] [4-1] [6-0] [5-2] [3-1] [7-0] [8-2]
     Solución [38]: [2-0] [0-0] [1-0] [4-1] [6-2] [5-2] [3-1] [7-0] [8-0]
     Solución [39]: [2-0] [0-0] [1-0] [4-1] [6-2] [5-2] [3-1] [7-0] [8-2]
     Solución [40]: [2-0] [5-3] [1-0] [6-0] [4-3] [3-2] [7-0] [0-1] [8-0]
     Solución [41]: [2-0] [5-3] [1-0] [6-0] [4-3] [3-2] [7-0] [0-1] [8-2]
     Solución [42]: [2-0] [5-3] [1-0] [6-2] [4-3] [3-2] [7-0] [0-1] [8-0]
     Solución [43]: [2-0] [5-3] [1-0] [6-2] [4-3] [3-2] [7-0] [0-1] [8-2]
     Solución [44]: [2-0] [5-3] [6-0] [1-1] [4-3] [3-2] [7-0] [0-1] [8-0]
     Solución [45]: [2-0] [5-3] [6-0] [1-1] [4-3] [3-2] [7-0] [0-1] [8-2]
     Solución [46]: [2-0] [5-3] [6-2] [1-1] [4-3] [3-2] [7-0] [0-1] [8-0]
     Solución [47]: [2-0] [5-3] [6-2] [1-1] [4-3] [3-2] [7-0] [0-1] [8-2]
     Solución [48]: [2-0] [6-0] [3-0] [1-0] [5-0] [4-3] [7-0] [0-1] [8-0]
     Solución [49]: [2-0] [6-0] [3-0] [1-0] [5-0] [4-3] [7-0] [0-1] [8-2]
     Solución [50]: [2-0] [6-2] [3-0] [1-0] [5-0] [4-3] [7-0] [0-1] [8-0]
     Solución [51]: [2-0] [6-2] [3-0] [1-0] [5-0] [4-3] [7-0] [0-1] [8-2]
     Solución [52]: [2-1] [1-0] [0-1] [4-1] [6-0] [5-2] [3-1] [7-0] [8-0]
     Solución [53]: [2-1] [1-0] [0-1] [4-1] [6-0] [5-2] [3-1] [7-0] [8-2]
     Solución [54]: [2-1] [1-0] [0-1] [4-1] [6-2] [5-2] [3-1] [7-0] [8-0]
     Solución [55]: [2-1] [1-0] [0-1] [4-1] [6-2] [5-2] [3-1] [7-0] [8-2]
     Solución [56]: [3-2] [7-0] [1-3] [4-2] [8-1] [0-1] [2-2] [5-1] [6-0]
     Solución [57]: [3-2] [7-0] [1-3] [4-2] [8-1] [0-1] [2-2] [5-1] [6-2]
     Solución [58]: [3-2] [7-0] [1-3] [4-2] [8-3] [0-1] [2-2] [5-1] [6-0]
     Solución [59]: [3-2] [7-0] [1-3] [4-2] [8-3] [0-1] [2-2] [5-1] [6-2]
     Solución [60]: [3-2] [7-0] [1-3] [8-1] [2-0] [0-3] [5-1] [4-3] [6-0]
     Solución [61]: [3-2] [7-0] [1-3] [8-1] [2-0] [0-3] [5-1] [4-3] [6-2]
     Solución [62]: [3-2] [7-0] [1-3] [8-3] [2-0] [0-3] [5-1] [4-3] [6-0]
     Solución [63]: [3-2] [7-0] [1-3] [8-3] [2-0] [0-3] [5-1] [4-3] [6-2]
     Solución [64]: [3-2] [7-0] [6-0] [5-0] [0-1] [1-1] [2-2] [4-0] [8-0]
     Solución [65]: [3-2] [7-0] [6-0] [5-0] [0-1] [1-1] [2-2] [4-0] [8-2]
     Solución [66]: [3-2] [7-0] [6-0] [5-0] [4-3] [1-1] [2-2] [0-1] [8-0]
     Solución [67]: [3-2] [7-0] [6-0] [5-0] [4-3] [1-1] [2-2] [0-1] [8-2]
     Solución [68]: [3-2] [7-0] [6-2] [5-0] [0-1] [1-1] [2-2] [4-0] [8-0]
     Solución [69]: [3-2] [7-0] [6-2] [5-0] [0-1] [1-1] [2-2] [4-0] [8-2]
     Solución [70]: [3-2] [7-0] [6-2] [5-0] [4-3] [1-1] [2-2] [0-1] [8-0]
     Solución [71]: [3-2] [7-0] [6-2] [5-0] [4-3] [1-1] [2-2] [0-1] [8-2]
     Solución [72]: [3-2] [7-3] [5-1] [0-3] [8-1] [2-0] [4-3] [1-0] [6-0]
     Solución [73]: [3-2] [7-3] [5-1] [0-3] [8-1] [2-0] [4-3] [1-0] [6-2]
     Solución [74]: [3-2] [7-3] [5-1] [0-3] [8-1] [6-1] [4-0] [1-0] [2-3]
     Solución [75]: [3-2] [7-3] [5-1] [0-3] [8-1] [6-3] [4-0] [1-0] [2-3]
     Solución [76]: [3-2] [7-3] [5-1] [0-3] [8-3] [2-0] [4-3] [1-0] [6-0]
     Solución [77]: [3-2] [7-3] [5-1] [0-3] [8-3] [2-0] [4-3] [1-0] [6-2]
     Solución [78]: [3-2] [7-3] [5-1] [0-3] [8-3] [6-1] [4-0] [1-0] [2-3]
     Solución [79]: [3-2] [7-3] [5-1] [0-3] [8-3] [6-3] [4-0] [1-0] [2-3]
     Solución [80]: [4-1] [2-1] [8-1] [7-2] [5-0] [0-1] [1-1] [3-0] [6-1]
     Solución [81]: [4-1] [2-1] [8-1] [7-2] [5-0] [0-1] [1-1] [3-0] [6-3]
     Solución [82]: [4-1] [2-1] [8-3] [7-2] [5-0] [0-1] [1-1] [3-0] [6-1]
     Solución [83]: [4-1] [2-1] [8-3] [7-2] [5-0] [0-1] [1-1] [3-0] [6-3]
     Solución [84]: [4-1] [5-3] [6-0] [2-0] [1-1] [0-2] [7-1] [3-3] [8-0]
     Solución [85]: [4-1] [5-3] [6-0] [2-0] [1-1] [0-2] [7-1] [3-3] [8-2]
     Solución [86]: [4-1] [5-3] [6-2] [2-0] [1-1] [0-2] [7-1] [3-3] [8-0]
     Solución [87]: [4-1] [5-3] [6-2] [2-0] [1-1] [0-2] [7-1] [3-3] [8-2]
     Solución [88]: [4-1] [8-0] [2-0] [1-2] [0-0] [7-0] [3-0] [5-3] [6-0]
     Solución [89]: [4-1] [8-0] [2-0] [1-2] [0-0] [7-0] [3-0] [5-3] [6-2]
     Solución [90]: [4-1] [8-2] [2-0] [1-2] [0-0] [7-0] [3-0] [5-3] [6-0]
     Solución [91]: [4-1] [8-2] [2-0] [1-2] [0-0] [7-0] [3-0] [5-3] [6-2]
     Solución [92]: [4-3] [1-0] [3-2] [2-0] [0-3] [8-1] [7-0] [5-1] [6-0]
     Solución [93]: [4-3] [1-0] [3-2] [2-0] [0-3] [8-1] [7-0] [5-1] [6-2]
     Solución [94]: [4-3] [1-0] [3-2] [2-0] [0-3] [8-3] [7-0] [5-1] [6-0]
     Solución [95]: [4-3] [1-0] [3-2] [2-0] [0-3] [8-3] [7-0] [5-1] [6-2]
     Solución [96]: [4-3] [8-0] [0-3] [5-3] [2-0] [3-3] [1-1] [6-1] [7-1]
     Solución [97]: [4-3] [8-0] [0-3] [5-3] [2-0] [3-3] [1-1] [6-3] [7-1]
     Solución [98]: [4-3] [8-2] [0-3] [5-3] [2-0] [3-3] [1-1] [6-1] [7-1]
     Solución [99]: [4-3] [8-2] [0-3] [5-3] [2-0] [3-3] [1-1] [6-3] [7-1]
     Solución [100]: [5-3] [0-0] [2-2] [8-1] [4-1] [6-1] [3-0] [1-1] [7-1]
     Solución [101]: [5-3] [0-0] [2-2] [8-1] [4-1] [6-3] [3-0] [1-1] [7-1]
     Solución [102]: [5-3] [0-0] [2-2] [8-1] [6-0] [4-3] [3-2] [1-1] [7-1]
     Solución [103]: [5-3] [0-0] [2-2] [8-1] [6-2] [4-3] [3-2] [1-1] [7-1]
     Solución [104]: [5-3] [0-0] [2-2] [8-3] [4-1] [6-1] [3-0] [1-1] [7-1]
     Solución [105]: [5-3] [0-0] [2-2] [8-3] [4-1] [6-3] [3-0] [1-1] [7-1]
     Solución [106]: [5-3] [0-0] [2-2] [8-3] [6-0] [4-3] [3-2] [1-1] [7-1]
     Solución [107]: [5-3] [0-0] [2-2] [8-3] [6-2] [4-3] [3-2] [1-1] [7-1]
     Solución [108]: [5-3] [1-0] [6-1] [8-1] [3-1] [7-0] [4-3] [0-2] [2-3]
     Solución [109]: [5-3] [1-0] [6-1] [8-3] [3-1] [7-0] [4-3] [0-2] [2-3]
     Solución [110]: [5-3] [1-0] [6-3] [8-1] [3-1] [7-0] [4-3] [0-2] [2-3]
     Solución [111]: [5-3] [1-0] [6-3] [8-3] [3-1] [7-0] [4-3] [0-2] [2-3]
     Solución [112]: [5-3] [2-1] [8-1] [0-3] [4-1] [6-1] [3-0] [1-1] [7-1]
     Solución [113]: [5-3] [2-1] [8-1] [0-3] [4-1] [6-3] [3-0] [1-1] [7-1]
     Solución [114]: [5-3] [2-1] [8-1] [0-3] [6-0] [4-3] [3-2] [1-1] [7-1]
     Solución [115]: [5-3] [2-1] [8-1] [0-3] [6-2] [4-3] [3-2] [1-1] [7-1]
     Solución [116]: [5-3] [2-1] [8-1] [6-1] [1-3] [4-3] [3-3] [0-2] [7-1]
     Solución [117]: [5-3] [2-1] [8-1] [6-3] [1-3] [4-3] [3-3] [0-2] [7-1]
     Solución [118]: [5-3] [2-1] [8-3] [0-3] [4-1] [6-1] [3-0] [1-1] [7-1]
     Solución [119]: [5-3] [2-1] [8-3] [0-3] [4-1] [6-3] [3-0] [1-1] [7-1]
     Solución [120]: [5-3] [2-1] [8-3] [0-3] [6-0] [4-3] [3-2] [1-1] [7-1]
     Solución [121]: [5-3] [2-1] [8-3] [0-3] [6-2] [4-3] [3-2] [1-1] [7-1]
     Solución [122]: [5-3] [2-1] [8-3] [6-1] [1-3] [4-3] [3-3] [0-2] [7-1]
     Solución [123]: [5-3] [2-1] [8-3] [6-3] [1-3] [4-3] [3-3] [0-2] [7-1]
     Solución [124]: [6-0] [5-1] [3-2] [2-0] [8-1] [1-3] [4-0] [0-3] [7-1]
     Solución [125]: [6-0] [5-1] [3-2] [2-0] [8-3] [1-3] [4-0] [0-3] [7-1]
     Solución [126]: [6-0] [7-3] [8-1] [2-0] [0-0] [5-0] [4-0] [1-1] [3-0]
     Solución [127]: [6-0] [7-3] [8-1] [2-1] [5-0] [0-1] [4-0] [1-1] [3-0]
     Solución [128]: [6-0] [7-3] [8-1] [2-1] [5-0] [4-3] [0-1] [1-1] [3-0]
     Solución [129]: [6-0] [7-3] [8-1] [2-1] [5-0] [4-3] [1-2] [0-3] [3-0]
     Solución [130]: [6-0] [7-3] [8-3] [2-0] [0-0] [5-0] [4-0] [1-1] [3-0]
     Solución [131]: [6-0] [7-3] [8-3] [2-1] [5-0] [0-1] [4-0] [1-1] [3-0]
     Solución [132]: [6-0] [7-3] [8-3] [2-1] [5-0] [4-3] [0-1] [1-1] [3-0]
     Solución [133]: [6-0] [7-3] [8-3] [2-1] [5-0] [4-3] [1-2] [0-3] [3-0]
     Solución [134]: [6-2] [5-1] [3-2] [2-0] [8-1] [1-3] [4-0] [0-3] [7-1]
     Solución [135]: [6-2] [5-1] [3-2] [2-0] [8-3] [1-3] [4-0] [0-3] [7-1]
     Solución [136]: [6-2] [7-3] [8-1] [2-0] [0-0] [5-0] [4-0] [1-1] [3-0]
     Solución [137]: [6-2] [7-3] [8-1] [2-1] [5-0] [0-1] [4-0] [1-1] [3-0]
     Solución [138]: [6-2] [7-3] [8-1] [2-1] [5-0] [4-3] [0-1] [1-1] [3-0]
     Solución [139]: [6-2] [7-3] [8-1] [2-1] [5-0] [4-3] [1-2] [0-3] [3-0]
     Solución [140]: [6-2] [7-3] [8-3] [2-0] [0-0] [5-0] [4-0] [1-1] [3-0]
     Solución [141]: [6-2] [7-3] [8-3] [2-1] [5-0] [0-1] [4-0] [1-1] [3-0]
     Solución [142]: [6-2] [7-3] [8-3] [2-1] [5-0] [4-3] [0-1] [1-1] [3-0]
     Solución [143]: [6-2] [7-3] [8-3] [2-1] [5-0] [4-3] [1-2] [0-3] [3-0]
     Solución [144]: [7-2] [2-1] [0-3] [8-1] [6-1] [5-3] [1-2] [4-1] [3-0]
     Solución [145]: [7-2] [2-1] [0-3] [8-1] [6-3] [5-3] [1-2] [4-1] [3-0]
     Solución [146]: [7-2] [2-1] [0-3] [8-3] [6-1] [5-3] [1-2] [4-1] [3-0]
     Solución [147]: [7-2] [2-1] [0-3] [8-3] [6-3] [5-3] [1-2] [4-1] [3-0]
     Solución [148]: [7-2] [5-3] [0-0] [8-1] [6-1] [3-3] [1-3] [4-2] [2-3]
     Solución [149]: [7-2] [5-3] [0-0] [8-1] [6-3] [3-3] [1-3] [4-2] [2-3]
     Solución [150]: [7-2] [5-3] [0-0] [8-3] [6-1] [3-3] [1-3] [4-2] [2-3]
     Solución [151]: [7-2] [5-3] [0-0] [8-3] [6-3] [3-3] [1-3] [4-2] [2-3]
     Solución [152]: [7-2] [8-0] [0-3] [4-0] [3-0] [2-2] [1-2] [6-0] [5-1]
     Solución [153]: [7-2] [8-0] [0-3] [4-0] [3-0] [2-2] [1-2] [6-2] [5-1]
     Solución [154]: [7-2] [8-0] [0-3] [4-0] [3-0] [2-2] [1-3] [5-1] [6-0]
     Solución [155]: [7-2] [8-0] [0-3] [4-0] [3-0] [2-2] [1-3] [5-1] [6-2]
     Solución [156]: [7-2] [8-2] [0-3] [4-0] [3-0] [2-2] [1-2] [6-0] [5-1]
     Solución [157]: [7-2] [8-2] [0-3] [4-0] [3-0] [2-2] [1-2] [6-2] [5-1]
     Solución [158]: [7-2] [8-2] [0-3] [4-0] [3-0] [2-2] [1-3] [5-1] [6-0]
     Solución [159]: [7-2] [8-2] [0-3] [4-0] [3-0] [2-2] [1-3] [5-1] [6-2]
     Solución [160]: [7-3] [0-0] [3-1] [4-1] [8-1] [1-2] [5-3] [6-1] [2-3]
     Solución [161]: [7-3] [0-0] [3-1] [4-1] [8-1] [1-2] [5-3] [6-3] [2-3]
     Solución [162]: [7-3] [0-0] [3-1] [4-1] [8-3] [1-2] [5-3] [6-1] [2-3]
     Solución [163]: [7-3] [0-0] [3-1] [4-1] [8-3] [1-2] [5-3] [6-3] [2-3]
     Solución [164]: [8-0] [3-3] [2-1] [4-3] [6-0] [7-3] [1-2] [5-1] [0-3]
     Solución [165]: [8-0] [3-3] [2-1] [4-3] [6-2] [7-3] [1-2] [5-1] [0-3]
     Solución [166]: [8-0] [3-3] [6-0] [2-3] [4-3] [7-3] [1-2] [5-1] [0-3]
     Solución [167]: [8-0] [3-3] [6-2] [2-3] [4-3] [7-3] [1-2] [5-1] [0-3]
     Solución [168]: [8-1] [2-0] [5-3] [6-0] [0-3] [1-3] [4-0] [3-3] [7-1]
     Solución [169]: [8-1] [2-0] [5-3] [6-0] [1-1] [0-1] [4-0] [3-3] [7-1]
     Solución [170]: [8-1] [2-0] [5-3] [6-2] [0-3] [1-3] [4-0] [3-3] [7-1]
     Solución [171]: [8-1] [2-0] [5-3] [6-2] [1-1] [0-1] [4-0] [3-3] [7-1]
     Solución [172]: [8-1] [7-2] [0-0] [3-3] [5-3] [1-1] [4-0] [2-3] [6-0]
     Solución [173]: [8-1] [7-2] [0-0] [3-3] [5-3] [1-1] [4-0] [2-3] [6-2]
     Solución [174]: [8-1] [7-2] [0-0] [6-0] [1-0] [5-3] [4-0] [3-3] [2-3]
     Solución [175]: [8-1] [7-2] [0-0] [6-2] [1-0] [5-3] [4-0] [3-3] [2-3]
     Solución [176]: [8-2] [3-3] [2-1] [4-3] [6-0] [7-3] [1-2] [5-1] [0-3]
     Solución [177]: [8-2] [3-3] [2-1] [4-3] [6-2] [7-3] [1-2] [5-1] [0-3]
     Solución [178]: [8-2] [3-3] [6-0] [2-3] [4-3] [7-3] [1-2] [5-1] [0-3]
     Solución [179]: [8-2] [3-3] [6-2] [2-3] [4-3] [7-3] [1-2] [5-1] [0-3]
     Solución [180]: [8-3] [2-0] [5-3] [6-0] [0-3] [1-3] [4-0] [3-3] [7-1]
     Solución [181]: [8-3] [2-0] [5-3] [6-0] [1-1] [0-1] [4-0] [3-3] [7-1]
     Solución [182]: [8-3] [2-0] [5-3] [6-2] [0-3] [1-3] [4-0] [3-3] [7-1]
     Solución [183]: [8-3] [2-0] [5-3] [6-2] [1-1] [0-1] [4-0] [3-3] [7-1]
     Solución [184]: [8-3] [7-2] [0-0] [3-3] [5-3] [1-1] [4-0] [2-3] [6-0]
     Solución [185]: [8-3] [7-2] [0-0] [3-3] [5-3] [1-1] [4-0] [2-3] [6-2]
     Solución [186]: [8-3] [7-2] [0-0] [6-0] [1-0] [5-3] [4-0] [3-3] [2-3]
     Solución [187]: [8-3] [7-2] [0-0] [6-2] [1-0] [5-3] [4-0] [3-3] [2-3] */
    
    return; /* NO rellenamos ninguna solución */
    /* Rellenamos El puntero */
    /*Solución [0]: [0-0] [3-0] [1-0] [2-0] [5-0] [7-0] [4-0] [6-0] [8-0]*/
    CeldaSoluciones.CombinacionSolucion[0].BuffPieza=0;
    CeldaSoluciones.CombinacionSolucion[0].BuffOri=0;
    CeldaSoluciones.CombinacionSolucion[1].BuffPieza=3;
    CeldaSoluciones.CombinacionSolucion[1].BuffOri=0;
    CeldaSoluciones.CombinacionSolucion[2].BuffPieza=1;
    CeldaSoluciones.CombinacionSolucion[2].BuffOri=0;
    CeldaSoluciones.CombinacionSolucion[3].BuffPieza=2;
    CeldaSoluciones.CombinacionSolucion[3].BuffOri=0;
    CeldaSoluciones.CombinacionSolucion[4].BuffPieza=5;
    CeldaSoluciones.CombinacionSolucion[4].BuffOri=0;
    CeldaSoluciones.CombinacionSolucion[5].BuffPieza=7;
    CeldaSoluciones.CombinacionSolucion[5].BuffOri=0;
    CeldaSoluciones.CombinacionSolucion[6].BuffPieza=4;
    CeldaSoluciones.CombinacionSolucion[6].BuffOri=0;
    CeldaSoluciones.CombinacionSolucion[7].BuffPieza=6;
    CeldaSoluciones.CombinacionSolucion[7].BuffOri=0;
    CeldaSoluciones.CombinacionSolucion[8].BuffPieza=8;
    CeldaSoluciones.CombinacionSolucion[8].BuffOri=0;

    MeteEnListaSoluciones(CeldaSoluciones,9);
    
/* Solución: [0-1] [7-3] [1-1] [6-3] [4-2] [2-2] [5-1] [3-1] [8-2]*/
    CeldaSoluciones.CombinacionSolucion[0].BuffPieza=0;
    CeldaSoluciones.CombinacionSolucion[0].BuffOri=1;
    CeldaSoluciones.CombinacionSolucion[1].BuffPieza=7;
    CeldaSoluciones.CombinacionSolucion[1].BuffOri=3;
    CeldaSoluciones.CombinacionSolucion[2].BuffPieza=1;
    CeldaSoluciones.CombinacionSolucion[2].BuffOri=1;
    CeldaSoluciones.CombinacionSolucion[3].BuffPieza=6;
    CeldaSoluciones.CombinacionSolucion[3].BuffOri=3;
    CeldaSoluciones.CombinacionSolucion[4].BuffPieza=4;
    CeldaSoluciones.CombinacionSolucion[4].BuffOri=2;
    CeldaSoluciones.CombinacionSolucion[5].BuffPieza=2;
    CeldaSoluciones.CombinacionSolucion[5].BuffOri=2;
    CeldaSoluciones.CombinacionSolucion[6].BuffPieza=5;
    CeldaSoluciones.CombinacionSolucion[6].BuffOri=1;
    CeldaSoluciones.CombinacionSolucion[7].BuffPieza=3;
    CeldaSoluciones.CombinacionSolucion[7].BuffOri=1;
    CeldaSoluciones.CombinacionSolucion[8].BuffPieza=8;
    CeldaSoluciones.CombinacionSolucion[8].BuffOri=2;

    MeteEnListaSoluciones(CeldaSoluciones,9);
    
}

int IncrementaPunteros()
{
    int i;
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
    printf("\n\rCombinación Actual: ");
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



    k=ListaNegraPunteros[NumCeldaListaNegra].NumPiezasCombi;/* El número de celdas del Punteros que están en la lista negra*/
    PosicionAIncrementar=k-1;

    if(ListaNegraPunteros[NumCeldaListaNegra].CombinacionNegra[PosicionAIncrementar].BuffPieza==8 &&
    ListaNegraPunteros[NumCeldaListaNegra].CombinacionNegra[PosicionAIncrementar].BuffOri==3)
        PosicionAIncrementar=PosicionAIncrementar-1; /* Si la pieza que ha causado la lista negra es [8-3] Hay que incrementar la anterior */

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

int MeteEnListaSoluciones(struct ListaSoluciones_ BuffCheck,long int NumPrueba)
{
    int i,j;
    int SolucionYaExiste=0;
    /* Mete en lista de soluciones, incrementando el Contador de Soluciones:
     Devuelve: El número de solución que se ha añadido
     NUMMAXSOLUCIONES: Si la solución ya existía */
    
    for(j=0;j<ContadorSoluciones;j++){
        SolucionYaExiste=1;
        for(i=0;i<CANTIDADPIEZAS;i++){
            if(ListaSoluciones[j].CombinacionSolucion[i].BuffPieza != BuffCheck.CombinacionSolucion[i].BuffPieza ||
               ListaSoluciones[j].CombinacionSolucion[i].BuffOri != BuffCheck.CombinacionSolucion[i].BuffOri)
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
    /* Se han revisado todas las soluciones ya guardadas y NINGUNA es igua a la nueva que se va a añadir
     Añadimos una nueva solución a la lista */
    ListaSoluciones[ContadorSoluciones].NumPruebaSolucion=PuntPruebas;
    
    
    for(i=0;i<CANTIDADPIEZAS;i++){
        ListaSoluciones[ContadorSoluciones].CombinacionSolucion[i].BuffPieza=BuffCheck.CombinacionSolucion[i].BuffPieza;
        ListaSoluciones[ContadorSoluciones].CombinacionSolucion[i].BuffOri=BuffCheck.CombinacionSolucion[i].BuffOri;
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
        printf("\r\n");
    }
    
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

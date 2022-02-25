////
////  rutinas.c
////  Juego_Puzzle
////
////  Created by Miguel Ruiz on 11/2/22.
////
////  Repositorio de rutinas previas
////
//
//int ResuelveTableroRevisa()
//{
//    /* 1o Los que han dado Resultado >50 (Se incluye a los 55) (Se han acabado las fichas y no han encontrado una combinación
//     Por cada Prueba con Resultado >100 colocamos en Test el número de piezas que vamos a probar
//     Ejemplo combinación: [6-3] [0-0] [1-1] [8-1] 4 piezas colocadas
//     Ponemos Test = 4  (Un valor de Test >0 y < 10 Indica estamos probando
//     Pues generaremos 3 pruebas
//     Primer Test: [6-3] [0-1]
//     Segundo Test:  [6-3] [0-0] [1-2]
//     Tercer Test:  [6-3] [0-0] [1-1] [8-2]
//     cuando Test = 1 => ya se han probado todas las combinaciones Test = 22
//     */
//    int i,j,k;
//    int PuntTestPrueba=0;
//    int tmpResultadoFunc=0;
//    
//    //        BuscaPruebasRepetidas();
//    PuntTestPrueba=BuscaPruebaNoRevisada();
//    while (PuntTestPrueba!=0xffff){
//        /* La Prueba encontrada tendrá Test =0 Ponemos Test y Número de Piezas colocadas*/
//        if(ListaPruebas[PuntTestPrueba].RevisionPrueba==0)
//        {
//            ListaPruebas[PuntTestPrueba].RevisionPrueba=ListaPruebas[PuntTestPrueba].NumPiezasColocadas;
//        }
//        else
//        {
//            if(ListaPruebas[PuntTestPrueba].RevisionPrueba==1)
//                ListaPruebas[PuntTestPrueba].RevisionPrueba=22;
//        }
//        
//        PuntBuf=0;
//        for(k=ListaPruebas[PuntTestPrueba].RevisionPrueba,i=ListaPruebas[PuntTestPrueba].RevisionPrueba-1,j=0;k>0;i--,j++,k--){
//            BufferPiezasAColocar[j].BuffPieza=ListaPruebas[PuntTestPrueba].CombinacionColocadas[i].PiezaColocada;
//            BufferPiezasAColocar[j].BuffOri=ListaPruebas[PuntTestPrueba].CombinacionColocadas[i].OrientaColocada;
//            PuntBuf=PuntBuf+1;
//        }
//        
//        /*la pieza Indice 0 hay que pasar a la siguiente */
//        if(BufferPiezasAColocar[0].BuffOri==3){
//            if(BufferPiezasAColocar[0].BuffPieza<8){
//                BufferPiezasAColocar[0].BuffPieza=BufferPiezasAColocar[0].BuffPieza+1;
//                BufferPiezasAColocar[0].BuffOri=0;
//            } else{
//                BufferPiezasAColocar[0].BuffPieza=0;
//                BufferPiezasAColocar[0].BuffOri=0;
//            }
//        }else BufferPiezasAColocar[0].BuffOri=BufferPiezasAColocar[0].BuffOri+1;
//        PuntBuf=PuntBuf-1;
//        ListaPruebas[PuntTestPrueba].RevisionPrueba=ListaPruebas[PuntTestPrueba].RevisionPrueba-1;
//        if(ListaPruebas[PuntTestPrueba].RevisionPrueba==1)
//            ListaPruebas[PuntTestPrueba].RevisionPrueba=22;
//        
//        PuntPiezas=0; /* El índice marca el número de pieza que se ha probado */
//        PuntOrdenPieza=1;
//        PuntContColocadas=0;
//        ListaPruebas[PuntPruebas].RevisandoPrueba=PuntTestPrueba;
//        printf("[BUSCO] COMIENZO PRUEBA [%u] **********\n",PuntPruebas);
//        if(PuntPruebas==36)
//            PuntPruebas=PuntPruebas;
//        
//        
//        if(contTestDemo<TESTDEDEMO || DEBUGPINTAFICHAS) printf("COMIENZO PRUEBA [%u] **********\n",PuntPruebas);
//        tmpResultadoFunc=ResuelveTableroAvance();
//        if(contTestDemo<TESTDEDEMO || DEBUGPINTAFICHAS)
//        {
//            switch(tmpResultadoFunc){
//                case 99:
//                case 55:
//                    printf("Se ha acabado el tablero [%u]\r\n",tmpResultadoFunc);
//                    break;
//                case 200:
//                    printf("Paramos las pruebas [%u]\r\n",tmpResultadoFunc);
//                    break;
//                case 400:
//                    printf("Se para porque ya se ha probado la misma combinación %u veces [%u]\r\n",NUMMAXPRUEBACOMBINACION, tmpResultadoFunc);
//                    break;
//                case 500:
//                    printf("Se ha terminado las 8 piezas de inicio [%u]\r\n",tmpResultadoFunc);
//                    break;
//                default:
//                    break;
//            }
//        }
//        BuscaSiLaPruebaEsRepetida(PuntPruebas);
//        if(contTestDemo<TESTDEDEMO || DEBUGPINTAFICHAS)
//            MuestraListado(PuntPruebas);
//        else
//            PintaTestResumen(PuntPruebas);
//        
//        //            BuscaPruebasRepetidas();
//        
//        PuntTestPrueba=BuscaPruebaNoRevisada();
//        /* Preparamos la siguiente Prueba*/
//        PuntPruebas=PuntPruebas+1;
//        
//        /* [BUSCO]*/
////        ContadorPruebasIguales=0;
//        
//        contTestDemo=contTestDemo+1;
//        if(PuntPruebas>=NUMMAXPRUEBAS){
//            MuestraListado(PuntPruebas);
//            PuntPruebas=NUMMAXPRUEBAS;
//            return 900;
//        }
//        ListaPruebas[PuntPruebas].RevisandoPrueba=0xffff;
//        InicializaTablero();
//    }
//    MuestraListado(PuntPruebas);
//    return 0;
//}
//
//void ResuelveTableroInicial()
//{
//    int PuntPiezaComienzo,PuntOriComienzo;
//    int tmpResultadoFunc=0;
//    
//    /* Comenzamos pruebas*/
//    for(PuntPiezaComienzo=0;PuntPiezaComienzo<CANTIDADPIEZAS;PuntPiezaComienzo++){
//        for(PuntOriComienzo=0;PuntOriComienzo<CANTIDADORIENTACIONES;PuntOriComienzo++){
//            if(contTestDemo<TESTDEDEMO || DEBUGPINTAFICHAS) printf("COMIENZO PRUEBA [%u] **********\n",PuntPruebas);
//            PuntPieza=PuntPiezaComienzo;
//            PuntOri=PuntOriComienzo;
//            tmpResultadoFunc=ResuelveTableroAvance();
//            if(contTestDemo<TESTDEDEMO || DEBUGPINTAFICHAS)
//            {
//                switch(tmpResultadoFunc){
//                    case 99:
//                    case 55:
//                        printf("Se ha acabado el tablero [%u]\r\n",tmpResultadoFunc);
//                        break;
//                    case 200:
//                        printf("Paramos las pruebas [%u]\r\n",tmpResultadoFunc);
//                        break;
//                    case 400:
//                        printf("Se para porque ya se ha probado la misma combinación %u veces [%u]\r\n",NUMMAXPRUEBACOMBINACION, tmpResultadoFunc);
//                        break;
//                    case 500:
//                        printf("Se ha terminado las 8 piezas de inicio [%u]\r\n",tmpResultadoFunc);
//                        break;
//                    default:
//                        break;
//                }
//            }
//            
//            BuscaSiLaPruebaEsRepetida(PuntPruebas);
//            if(contTestDemo<TESTDEDEMO || DEBUGPINTAFICHAS)
//                MuestraListado(PuntPruebas);
//            else
//                PintaTestResumen(PuntPruebas);
//            /* Preparamos la siguiente Prueba*/
//            
//            PuntPruebas=PuntPruebas+1;
//            contTestDemo=contTestDemo+1;
//            ListaPruebas[PuntPruebas].RevisandoPrueba=0xffff;
//            PuntPiezas=0; /* El índice marca el número de pieza que se ha probado */
//            PuntOrdenPieza=1;
//            PuntContColocadas=0;
//            InicializaTablero();
//            
//        }
//    }
//}
//
//int ColocaPiezasFase2(int NumOrdenPieza)
//{
//    /*
//     OJO esta función se llama de modo recurrente.
//     La función devuelve:
//     200: Se han probado NUMMAXPIEZASPROBADAS sin tener resultado final -> Este no debería pasar, lo normal es salir con 400
//     400: Desde colocar una pieza, se ha probado NUMMAXPRUEBACOMBINACION la misma combinación
//     500: Se han probado el resto de piezas y no caben
//     55: Esta prueba se debe parar porque el Tablero resultante se ha bloqueado
//     99: El Tablero se ha terminado ¡ÉXITO!
//     
//     El parámetro: NumOrdenPieza indica el orden de la pieza que estamos colocando.
//     En BuffPiezasActual Está la combinación que se ha colocado hasta ahora.
//     EJ. [0-0] [1-0] En este caso PuntBufActual debe ser 2 (porque ya se ha colocado la 0 y la 1 y la que hay que colocar es la 3
//     */
//    int tmpfilaTab,tmpcolTab;/*Usados para buscar hueco*/
//    int tmp=0,tmpTab=0;
//    int i,j;
//    int SeHaColocadoAlgo=0;
//    int ptmpResultadoFunc=0;
//    int ActPuntPruebas,ActPuntPieza,ActPuntOri;
//    int ActPuntPiezas,ActPuntOrdenPieza,ActResultadoPieza;
//    int IndPiezaColocada=0;
//    int ContadorMismaPrueba=0;
//    
//    int PuntPiezaComienzo,PuntOriComienzo;
//    int tmpResultadoFunc=0;
//    
//    
//    /* Comenzamos pruebas*/
//    for(PuntPiezaComienzo=0;PuntPiezaComienzo<CANTIDADPIEZAS;PuntPiezaComienzo++){
//        for(PuntOriComienzo=0;PuntOriComienzo<CANTIDADORIENTACIONES;PuntOriComienzo++){
//            
//            if(ListaPruebas[PuntPruebas].Piezascolocadas[PuntPieza]==0)
//            {
//                /* Revisamos si la siguiente combinación ya se ha probado al menos NUMMAXPRUEBACOMBINACION*/
//                /* la última fila probada está en: PuntPiezas */
//                
//                /* Salvo la situación actual de los punteros*/
//                ActPuntPruebas=PuntPruebas;
//                ActPuntPieza=PuntPieza;
//                ActPuntOri=PuntOri;
//                ActPuntPiezas=PuntPiezas;
//                ActPuntOrdenPieza=PuntOrdenPieza;
//                
//                for(i=PuntPiezas;i!=0;i--){
//                    /* Buscamos la última pieza Colocada (Resultado Prueba =0*/
//                    if(ListaPruebas[PuntPruebas].PiezaProbada[i].ResultadoPieza==0)
//                        IndPiezaColocada=i;
//                }
//                for(i=IndPiezaColocada+1;i<ActPuntPiezas;i++)
//                {
//                    if(ListaPruebas[PuntPruebas].PiezaProbada[i].OrdenPieza==ActPuntOrdenPieza &&
//                       ListaPruebas[PuntPruebas].PiezaProbada[i].numPieza==ActPuntPieza &&
//                       ListaPruebas[PuntPruebas].PiezaProbada[i].OrientaPieza==ActPuntOri &&
//                       ListaPruebas[PuntPruebas].PiezaProbada[i].ResultadoPieza!=0)
//                        ContadorMismaPrueba=ContadorMismaPrueba+1;
//                    if(ContadorMismaPrueba==NUMMAXPRUEBACOMBINACION){
//                        ListaPruebas[PuntPruebas].ResultadoPrueba=400;
//                        return 400;
//                    }
//                    
//                }
//                BuscaHuecoEnTablero(Tablero,&tmpfilaTab,&tmpcolTab);
//                if(contTestDemo<TESTDEDEMO || DEBUGPINTAFICHAS)
//                    printf("Coloca la pieza [%u-%u] en fila:%u, columna%u\r\n",PuntPieza,PuntOri,tmpfilaTab,tmpcolTab);
//                tmp=ColocaPieza(tmpfilaTab,tmpcolTab,PuntPieza,PuntOri);
//                
//                /*Si tmp =0 colocada, otros valores NO cabe*/
//                /*Apuntamos el resultado*/
//                /*La pieza PuntPieza (PuntOri) se ha intentado colocar*/
//                ListaPruebas[PuntPruebas].PiezaProbada[PuntPiezas].numPieza=PuntPieza;
//                ListaPruebas[PuntPruebas].PiezaProbada[PuntPiezas].OrientaPieza=PuntOri;
//                ListaPruebas[PuntPruebas].PiezaProbada[PuntPiezas].ResultadoPieza=tmp;
//                ListaPruebas[PuntPruebas].PiezaProbada[PuntPiezas].OrdenPieza=PuntOrdenPieza;
//                PuntPiezas=PuntPiezas+1;
//                if(PuntPiezas>NUMMAXPIEZASPROBADAS)
//                {/*paramos de probar piezas*/
//                    ListaPruebas[PuntPruebas].ResultadoPrueba=200;
//                    return 200;
//                }else{
//                    if(tmp==0)
//                    {
//                        /*La pieza se ha colocado */
//                        
//                        /*Marcamos FFFF en las casillas donde se ha usado piezas*/
//                        ListaPruebas[PuntPruebas].Piezascolocadas[PuntPieza]=0xffff;
//                        
//                        ListaPruebas[PuntPruebas].CombinacionColocadas[PuntContColocadas].PiezaColocada=PuntPieza;
//                        ListaPruebas[PuntPruebas].CombinacionColocadas[PuntContColocadas].OrientaColocada=PuntOri;
//                        PuntContColocadas=PuntContColocadas+1;
//                        ListaPruebas[PuntPruebas].NumPiezasColocadas=PuntContColocadas;
//                        
//                        PuntOri=0; /*Para que vuelva a la orientación*/
//                        /*Si la pieza se ha colocado pasamos a la siguiente pieza*/
//                        SeHaColocadoAlgo=1;
//                        
//                        /* Vamos a ver si el tablero está bien */
//                        tmpTab=RevisaTablero(Tablero);
//                        if(tmpTab==99){
//                            /*Tablero terminado!!!*/
//                            ListaPruebas[PuntPruebas].ResultadoPrueba=99;
//                            return 99;
//                        }else{
//                            if(tmpTab>50){
//                                /*Tablero Bloqueado */
//                                ListaPruebas[PuntPruebas].ResultadoPrueba=55;
//                                return 55;
//                            }
//                        }
//                    }
//                }
//                if(SeHaColocadoAlgo){
//                    /* Ojo esto hace que la siguiente que se prueba siempre sea la 0-0 */
//                    PuntPieza=0;
//                    PuntOri=0;
//                    PuntOrdenPieza=PuntOrdenPieza+1;
//                    
//                }else
//                { /*No se ha colocado*/
//                    if(PuntPieza>CANTIDADPIEZAS-1)
//                    {
//                        ListaPruebas[PuntPruebas].ResultadoPrueba=500;
//                        return 500; /*Fin cambiando la primera pieza */
//                    }
//                    
//                }
//                
//            }
//            else
//            { /* La pieza que toca ya se ha usado (Colocado en esta prueba*/
//                //                PuntPieza=PuntPieza+1;
//                //                if(PuntPieza>8) PuntPieza=0;
//                //                PuntOri=0;
//                IncrementaPieza(&PuntPieza,&PuntOri);
//            }
//            
//        }}
//    
//    ptmpResultadoFunc=ColocaPiezasFase2(NumOrdenPieza);
//    return ptmpResultadoFunc;
//}
//
//
//int ResuelveTableroFase2()
//{
//    /* Se han probado (en la FASE 1) todas las primeras fichas (de 0-0 a 8-3 y se ha ido avanzando.
//     Ahora volvemos a probar cada primera ficha,
//     Cogemos la primera ficha buscamos de las pruebas ya realizadas
//     
//     1o Los que han dado Resultado >50 (Se incluye a los 55) (Se han acabado las fichas y no han encontrado una combinación
//     Por cada Prueba con Resultado >100 colocamos en Test el número de piezas que vamos a probar
//     Ejemplo combinación: [6-3] [0-0] [1-1] [8-1] 4 piezas colocadas
//     Ponemos Test = 4  (Un valor de Test >0 y < 10 Indica estamos probando
//     Pues generaremos 3 pruebas
//     Primer Test: [6-3] [0-1]
//     Segundo Test:  [6-3] [0-0] [1-2]
//     Tercer Test:  [6-3] [0-0] [1-1] [8-2]
//     cuando Test = 1 => ya se han probado todas las combinaciones Test = 22
//     */
//    int PuntPiezaComienzo,PuntOriComienzo;
//    int tmpResultadoFunc=0;
//    
//    /* Comenzamos pruebas*/
//    if(1||contTestDemo<TESTDEDEMO || DEBUGPINTAFICHAS) printf("COMIENZO PRUEBA [%u] **********\n",PuntPruebas);
//    /* Inicializamos las pruebas */
//    PuntPiezas=0; /* El índice marca el número de pieza que se ha probado */
//    PuntOrdenPieza=1;
//    PuntContColocadas=0;
//    InicializaTablero();
//    IniciaBuffActual();
//    PuntPieza=0;
//    PuntOri=0;
//    
//    tmpResultadoFunc=ColocaPiezasFase2(PuntPiezas);
//    if(1||contTestDemo<TESTDEDEMO || DEBUGPINTAFICHAS)
//    {
//        switch(tmpResultadoFunc){
//            case 99:
//            case 55:
//                printf("Se ha acabado el tablero [%u]\r\n",tmpResultadoFunc);
//                break;
//            case 200:
//                printf("Paramos las pruebas [%u]\r\n",tmpResultadoFunc);
//                break;
//            case 400:
//                printf("Se para porque ya se ha probado la misma combinación %u veces [%u]\r\n",NUMMAXPRUEBACOMBINACION, tmpResultadoFunc);
//                break;
//            case 500:
//                printf("Se ha terminado las 8 piezas de inicio [%u]\r\n",tmpResultadoFunc);
//                break;
//            default:
//                break;
//        }
//    }
//    
//    MuestraListado(PuntPruebas);
//    return 0;
//}
//
//*/
//int BuscaLaSiguienteCombinacion(int NumPrueba,int* pPieza, int* pOrienta)
//{
//    /* Función llamada cuando toca probar la siguiente pieza
//     nos encontramos que en Combinación colocadas tenemos las piezas colocadas ya en esta prueba (Se han colocado NumPiezas colocadas
//     Busco hacia atrás una prueba en la que se hayan colocado las mismas piezas.
//     
//     struct ListaPruebas {
//     int NumPrueba;
//     int Piezascolocadas[9];
//     int NumPiezasColocadas;
//     struct {
//     int PiezaColocada;
//     int OrientaColocada;
//     } CombinacionColocadas[9];
//     struct {
//     int OrdenPieza;
//     int numPieza;
//     int OrientaPieza;
//     int ResultadoPieza;
//     }PiezaProbada[NUMMAXPIEZASPROBADAS];
//     int ResultadoPrueba;
//     int RevisionPrueba;
//     int RevisandoPrueba;
//     }ListaPruebas[NUMMAXPRUEBAS];
//     
//     En ListaPruebas[NumPrueba].CombinacionColocadas[] tenemos las NumPiezas Colocadas que se han colocado
//     Buscamos desde NumPrueba hasta 0 si ya se ha probado esa combinación y devuelve la siguiente pieza que se debería probar que es la Última + 1
//     
//     */
//    int PuntTestRev;
//    int i=0;
//    int SonIguales=1;
//    int HayQueIncrementar=0;
//    int tmpNumColocadas;
//    int sigPieza1=0xffff, sigOrienta1=0xffff;/* aqui se guarda la mayor*/
//    int ContadorPruebasIguales=0;
//    
//    struct {
//        int tmpPiezaColoc;
//        int tmpOrientaColoc;
//    } CombiColocadasTmp[9];
//    
//    //    *pPieza=5;
//    //    *pOrienta=2;
//    //    return 0;
//    
//    tmpNumColocadas=ListaPruebas[NumPrueba].NumPiezasColocadas;
//    if(1 || tmpNumColocadas>0)
//    {
////        printf("[BUSCO]****BUSCO COMBINACIÓN Prueba Actual: [%u] *******\n",NumPrueba);
////        printf("[BUSCO] La Siguiente Pieza es [%u-%u]\n",*pPieza,*pOrienta);
//        /* Inicializo CombicolocadasTmp con el valor 0xffff*/
//        for(i=0;i<9;i++){
//            CombiColocadasTmp[i].tmpPiezaColoc=0xffff;
//            CombiColocadasTmp[i].tmpOrientaColoc=0xffff;
//        }
//        /* Relleno CombicolocadasTmp con la combinación de la prueba que quiero revisar*/
//        printf("[BUSCO]La Combinación de la prueba [%u] es:",NumPrueba);
//        for(i=0;i<tmpNumColocadas;i++){
//            CombiColocadasTmp[i].tmpPiezaColoc=ListaPruebas[NumPrueba].CombinacionColocadas[i].PiezaColocada;
//            printf("[%u-",CombiColocadasTmp[i].tmpPiezaColoc);
//            CombiColocadasTmp[i].tmpOrientaColoc=ListaPruebas[NumPrueba].CombinacionColocadas[i].OrientaColocada;
//            printf("%u]",CombiColocadasTmp[i].tmpOrientaColoc);
//        }
//        printf("\n");
//        for(PuntTestRev=0;PuntTestRev<NumPrueba;PuntTestRev++)
//        {
//            /* Revisamos desde 0 hasta la prueba anterior hasta el anterior al actual */
//            /* en al prueba acual tenemos las pruebas colocadas*/
//            for(i=0,SonIguales=1;i<tmpNumColocadas;i++)
//            {
//                if(ListaPruebas[PuntTestRev].CombinacionColocadas[i].PiezaColocada != CombiColocadasTmp[i].tmpPiezaColoc || ListaPruebas[PuntTestRev].CombinacionColocadas[i].OrientaColocada != CombiColocadasTmp[i].tmpOrientaColoc)
//                    SonIguales=0;
//            }
//            if(SonIguales)
//            { /* Las tmpNuColocadas piezas de NumPrueba son iguales la prueba PuntTestRev*/
//                /* Miramos si hay otra pieza colocada en en PuntTestRev*/
//                
//                if(ListaPruebas[PuntTestRev].NumPiezasColocadas>tmpNumColocadas)
//                {
////                    printf("[BUSCO] Encontrada Prueba igual en [%u] que tiene %u Piezas\n",PuntTestRev,ListaPruebas[PuntTestRev].NumPiezasColocadas);
//                    /*Al menos hay 1 pieza mas colocada, guardamos esa en */
//                    sigPieza1=ListaPruebas[PuntTestRev].CombinacionColocadas[tmpNumColocadas].PiezaColocada;
//                    sigOrienta1=ListaPruebas[PuntTestRev].CombinacionColocadas[tmpNumColocadas].OrientaColocada;
//                    if( PiezaEsMayor(sigPieza1,sigOrienta1,*pPieza,*pOrienta))
//                    { /* La nueva Pieza es mayor que la que teníamos guardada*/
//                        *pPieza=sigPieza1;
//                        *pOrienta=sigOrienta1;
//                        HayQueIncrementar=0;
//                        IncrementaPieza(&*pPieza,&*pOrienta);
//                        ContadorPruebasIguales=ContadorPruebasIguales+1;
////                        printf("[BUSCO] La nueva Pieza <Mayor> es:[%u-%u] Probada %u veces\n",*pPieza,*pOrienta,ContadorPruebasIguales);
//                        if(*pPieza==8 && *pOrienta==3){
////                            printf("OJO llegamos a la 8-3\n");
//                            /*Comprobamos si la pieza 8 (Laúltima) ya se ha puesto en la combinación*/
//                            if(ListaPruebas[PuntPruebas].Piezascolocadas[PuntPieza]==0xffff)
//                            {
////                                printf("OJO llegamos a la 8-3 y ya no hay mas\n");
//                            }
//                        }
//                    }
//                }
//                SonIguales=1;
//            }
//        }
//    }
//    
//    if(HayQueIncrementar){
//        /* Incrementa la pieza para la sigueinte*/
//        IncrementaPieza(&*pPieza,&*pOrienta);
//        
//        //        printf("[BUSCO] Resultado Incrementado [%u-%u]\n",*pPieza,*pOrienta);
//    }
//    return 0;
//}

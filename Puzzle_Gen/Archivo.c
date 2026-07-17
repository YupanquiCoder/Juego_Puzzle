//
//  Archivo.c
//  Juego_Puzzle
//
//  Created by Miguel Ruiz
//

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Archivo.h"
#include "Soluciones.h"

static char rutaArchivo[2048] = "soluciones.dat"; /* fallback si falla la construcción de la ruta */

void InicializaRutaArchivo(void)
{
    /* __FILE__ es la ruta de este archivo fuente en tiempo de compilación: apunta siempre
       a Puzzle_Gen/Puzzle_Gen/Archivo.c dentro del proyecto, sin importar dónde se compile
       o desde dónde se ejecute el binario resultante. Subimos dos niveles (quitamos el
       nombre del archivo y la carpeta Puzzle_Gen) para llegar a la raíz del proyecto,
       donde vive Archivo_Dat/. */
    char rutaFuente[2048];
    char *ultimo;

    snprintf(rutaFuente, sizeof(rutaFuente), "%s", __FILE__);
    ultimo = strrchr(rutaFuente, '/');
    if (ultimo) {
        *ultimo = '\0';
        ultimo = strrchr(rutaFuente, '/');
        if (ultimo) {
            *ultimo = '\0';
            snprintf(rutaArchivo, sizeof(rutaArchivo), "%s/Archivo_Dat/soluciones.dat", rutaFuente);
        }
    }
    printf("Archivo de soluciones: %s\n", rutaArchivo);
}

int GuardaSoluciones(void)
{
    FILE *f = fopen(rutaArchivo, "wb");
    if (!f) {
        printf("ERROR: No se pudo abrir '%s' para guardar\n", rutaArchivo);
        return 0;
    }
    fwrite(&PosChinchetaActual, sizeof(PosChinchetaActual), 1, f);
    fwrite(BloquesSoluciones, sizeof(BloquesSoluciones), 1, f);
    fclose(f);
    printf("Soluciones guardadas en '%s'\n", rutaArchivo);
    return 1;
}

int CargaSoluciones(void)
{
    FILE *f = fopen(rutaArchivo, "rb");
    if (!f) return 0; /* No existe el archivo — primera vez, es normal */

    size_t ok1 = fread(&PosChinchetaActual, sizeof(PosChinchetaActual), 1, f);
    size_t ok2 = fread(BloquesSoluciones, sizeof(BloquesSoluciones), 1, f);
    fclose(f);

    if (ok1 == 1 && ok2 == 1) {
        printf("Soluciones cargadas (bloque activo: %d)\n", PosChinchetaActual);
        return 1;
    }
    printf("AVISO: El archivo parece corrupto — se ignora\n");
    PosChinchetaActual = 0;
    return 0;
}

void BorraArchivoSoluciones(void)
{
    remove(rutaArchivo);
    InicializaSoluciones();
    printf("Archivo borrado. Todas las soluciones eliminadas.\n");
}

void BorraBloqueSoluciones(int numBloque)
{
    BloquesSoluciones[numBloque].ContadorSoluciones = 0;
    BloquesSoluciones[numBloque].NumeroPruebasRealizadas = 0;
    GuardaSoluciones();
    printf("Bloque <%d> reseteado. Listo para volver a buscar.\n", numBloque);
}

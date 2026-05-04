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

static char rutaArchivo[2048] = "soluciones.dat"; /* fallback si falla realpath */

void InicializaRutaArchivo(const char* rutaEjecutable)
{
    char *rutaReal = realpath(rutaEjecutable, NULL);
    if (rutaReal) {
        char *ultimo = strrchr(rutaReal, '/');
        if (ultimo) {
            *ultimo = '\0';
            snprintf(rutaArchivo, sizeof(rutaArchivo), "%s/soluciones.dat", rutaReal);
        }
        free(rutaReal);
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

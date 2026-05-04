//
//  Archivo.c
//  Juego_Puzzle
//
//  Created by Miguel Ruiz
//

#include <stdio.h>
#include "Archivo.h"
#include "Soluciones.h"

int GuardaSoluciones(void)
{
    FILE *f = fopen(NOMBRE_ARCHIVO, "wb");
    if (!f) {
        printf("ERROR: No se pudo abrir '%s' para guardar\n", NOMBRE_ARCHIVO);
        return 0;
    }
    fwrite(BloquesSoluciones, sizeof(BloquesSoluciones), 1, f);
    fclose(f);
    printf("Soluciones guardadas en '%s'\n", NOMBRE_ARCHIVO);
    return 1;
}

int CargaSoluciones(void)
{
    FILE *f = fopen(NOMBRE_ARCHIVO, "rb");
    if (!f) return 0; /* No existe el archivo — primera vez, es normal */

    size_t leidos = fread(BloquesSoluciones, sizeof(BloquesSoluciones), 1, f);
    fclose(f);

    if (leidos == 1) {
        printf("Soluciones cargadas desde '%s'\n", NOMBRE_ARCHIVO);
        return 1;
    }
    printf("AVISO: El archivo '%s' parece corrupto — se ignora\n", NOMBRE_ARCHIVO);
    return 0;
}

void BorraArchivoSoluciones(void)
{
    remove(NOMBRE_ARCHIVO);
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

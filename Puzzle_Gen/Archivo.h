//
//  Archivo.h
//  Juego_Puzzle
//
//  Created by Miguel Ruiz
//

#ifndef Archivo_h
#define Archivo_h

#define NOMBRE_ARCHIVO "soluciones.dat"

/* Guarda BloquesSoluciones completo en binario.
   Devuelve 1 si OK, 0 si error. */
int GuardaSoluciones(void);

/* Carga BloquesSoluciones desde el archivo al arrancar.
   Devuelve 1 si cargó, 0 si el archivo no existe (primera vez). */
int CargaSoluciones(void);

/* Borra el archivo y resetea todos los bloques en memoria. */
void BorraArchivoSoluciones(void);

/* Resetea un bloque concreto (para volver a buscar sus soluciones)
   y guarda el archivo actualizado. */
void BorraBloqueSoluciones(int numBloque);

#endif /* Archivo_h */

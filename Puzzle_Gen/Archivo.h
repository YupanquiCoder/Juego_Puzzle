//
//  Archivo.h
//  Juego_Puzzle
//
//  Created by Miguel Ruiz
//

#ifndef Archivo_h
#define Archivo_h

/* Debe llamarse al inicio de main().
   Calcula la ruta del archivo en Archivo_Dat/, junto al código fuente del proyecto
   (no junto al ejecutable, que cambia de sitio según cómo se compile/ejecute). */
void InicializaRutaArchivo(void);

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

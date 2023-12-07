#ifndef ARCHIVOS_H
#define ARCHIVOS_H
#include "structs.h"

typedef enum codArchivos{ErrorApertura=-1, ErrorEscritura=0, ExitoOperacion=1} eCodArchivos;

void EscribirArchivoBinario(const sAsistencias* ListaAsistencias, int numElementos, ofstream &archi);
void LlenarListaClientes_(str& nombreArchivo, sCliente* ListaClientes, int cantClientes);
void LlenarListaClases_(str& nombreArchivo, sClase* ListaClases, int cantClases);

#endif // ARCHIVOS_H

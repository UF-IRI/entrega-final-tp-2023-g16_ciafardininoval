#ifndef ARCHIVOS_H
#define ARCHIVOS_H
#include "structs.h"

typedef enum codArchivos{ErrorApertura=-1, ErrorEscritura=0, ExitoOperacion=1} eCodArchivos;

void LlenarListaClases(ifstream& archi,int counter,sClase* &ListaClases);
void LlenarListaClientes(ifstream& archi, int counter, sCliente* &ListaClientes);
void EscribirArchivoBinario(const sAsistencias* ListaAsistencias, int numElementos, ofstream &archi);

#endif // ARCHIVOS_H

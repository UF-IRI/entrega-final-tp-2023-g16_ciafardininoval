#ifndef ARCHIVOS_H
#define ARCHIVOS_H
#include <structs.h>

typedef enum codArchivos{ErrorApertura=-1, ErrorEscritura=0, ExitoOperacion=1} eCodArchivos;
sClase* LlenarListaClases(std::fstream *archi);
sCliente* LlenaListaClientes(std::fstream *archi);
sAsistencias* CargarDataAsistencias(std::fstream *archi);

class archivos
{
public:
    archivos();
};

#endif // ARCHIVOS_H

#include "archivos.h"
#include <fstream>
#include <sstream>
#include <iostream>

using namespace std;

archivos::archivos()
{

}
sClase* LlenarListaClases(std::fstream *archi){

    ifstream infile(archi);

    if (!infile.is_open()) {
        return eCodArchivos::ErrorApertura;
    }
    int counter=0;
    str line;
    str header;
    getline(infile,header); //leemos el header y pasamos a la siguiente linea
    while ( getline( infile, line) )  // cantidad de lineas en el archivo
        counter++;

    sClase* ListaClases = new ListaClases[counter];

    for (int i = 0; i < counter; i++) {

        infile >> ListaClases[i].id >> ListaClases[i].tipo >> ListaClases[i].hora;
    }
    infile.close();
    return ListaClases;
}

sCliente* LlenaListaClientes(std::fstream *archi)
{
    ifstream infile(archi);

    if (!infile.is_open()) {
        return eCodArchivos::ErrorApertura;
    }
    int counter=0;
    str line;
    str header;
    getline(infile,header); //leemos el header y pasamos a la siguiente linea
    while ( getline( infile, line) )  // cantidad de lineas en el archivo
        counter++;

    sCliente* ListaClientes = new ListaClientes[counter];

    for (int i = 0; i < counter; i++) {

        infile >> ListaClientes[i].ID >> ListaClientes[i].nombre >> ListaClientes[i].apellido >> ListaClientes[i].email
             >> ListaClientes[i].telefono >> ListaClientes[i].fechaNac >> ListaClientes[i].pago;
    }
    infile.close();
    return ListaClientes;
}
sAsistencias* CargarDataAsistencias(std::fstream *archi)
{
    ifstream infile(archi);

    if (!infile.is_open()) {
        return eCodArchivos::ErrorApertura;
    }
    sAsistencias elemento=new sAsistencias;

    infile.seekg(0, std::ios::end);
    std::streampos fileSize = file.tellg();
    file.seekg(0, std::ios::beg);

    const std::size_t elementSize = sizeof(elemento);
    const int tam = fileSize / elementSize;

    sAsistencias ListaAsistencias[tam];
    file.read(reinterpret_cast<char*>(&sAsistencias), sizeof(ListaAsistencias) * tam);

    delete elemento;
    return ListaAsistencias;
}


#include "archivos.h"
#include <fstream>
#include <sstream>
#include <iostream>

using namespace std;

/*void LlenarListaClases(std::ifstream& archi,int counter,sClase* &ListaClases)
{
    for (int i = 0; i < counter; i++) {

        archi >> ListaClases[i].id >> ListaClases[i].tipo >> ListaClases[i].hora;
    }

}*/
void LlenarListaClases(ifstream& archi, int counter, sClase* &ListaClases)
{
    for (int i = 0; i < counter; i++)
    {
        str linea;
        if (getline(archi, linea))
        {
            istringstream ss(linea);
            str valor;

            // Leer datos separados por comas
            getline(ss, valor, ',');
            ListaClases[i].id = stoi(valor);
            getline(ss, ListaClases[i].tipo, ',');
            ss >> ListaClases[i].hora; // Leer el campo hora directamente como un float
        }
        else
        {
            // Manejar errores de lectura de línea
            throw runtime_error("Error al leer línea del archivo de clases.");
        }
    }
}

/*void LlenarListaClientes(std::ifstream& archi, int counter, sCliente* &ListaClientes)
{ 
    for (int i = 0; i < counter; i++) {

        archi >> ListaClientes[i].ID >> ListaClientes[i].nombre >> ListaClientes[i].apellido >> ListaClientes[i].email >> ListaClientes[i].telefono >> ListaClientes[i].fechaNac >> ListaClientes[i].pago;
    }
}*/
void LlenarListaClientes(ifstream& archi, int counter, sCliente* &ListaClientes)
{
    str linea;
    for (int i = 0; i < counter; i++)
    {
        if (getline(archi, linea))
        {
            istringstream ss(linea);
            string valor;

            // Leer datos separados por comas
            getline(ss, valor, ',');
            ListaClientes[i].ID = std::stoi(valor);

            getline(ss, ListaClientes[i].nombre, ',');
            getline(ss, ListaClientes[i].apellido, ',');
            getline(ss, ListaClientes[i].email, ',');
            getline(ss, ListaClientes[i].telefono, ',');
            getline(ss, ListaClientes[i].fechaNac, ',');
            ss >> ListaClientes[i].pago;  // Utilizar >> para leer el double directamente

        }
        else
        {
            // Manejar errores de lectura de línea
            throw runtime_error("Error al leer línea del archivo de clientes");
        }
    }
}
void EscribirArchivoBinario(const sAsistencias* ListaAsistencias, int numElementos, ofstream& archi)
{

    // Escribe el array en el archivo binario
    archi.write(reinterpret_cast<const char*>(ListaAsistencias), sizeof(sAsistencias) * numElementos);

}

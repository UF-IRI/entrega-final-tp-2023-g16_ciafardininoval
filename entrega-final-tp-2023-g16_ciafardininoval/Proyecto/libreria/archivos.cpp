#include "archivos.h"
#include <fstream>
#include <sstream>
#include <iostream>

using namespace std;


void LlenarListaClientes_(str& nombreArchivo, sCliente* ListaClientes, int cantClientes)
{
    ifstream archivo(nombreArchivo);
    if (archivo.is_open()) {
        str linea;
        int clienteActual = 0;
        str header;
        getline(archivo,header);
        while (getline(archivo, linea) && clienteActual < cantClientes) {
            istringstream ss(linea);
            str token;

            // Leer cada campo separado por comas
            getline(ss, token, ',');
            ListaClientes[clienteActual].ID = stoi(token);

            getline(ss, ListaClientes[clienteActual].nombre, ',');
            getline(ss, ListaClientes[clienteActual].apellido, ',');
            getline(ss, ListaClientes[clienteActual].email, ',');
            getline(ss, ListaClientes[clienteActual].telefono, ',');
            getline(ss, ListaClientes[clienteActual].fechaNac, ',');
            getline(ss, token, ',');
            ListaClientes[clienteActual].pago = stof(token);

            clienteActual++;
        }

        archivo.close();
    } else {
        cout << "No se pudo abrir el archivo: " << nombreArchivo << endl;
    }
}
void LlenarListaClases_(str& nombreArchivo, sClase* ListaClases, int cantClases)
{
    ifstream archivo(nombreArchivo);
    if (archivo.is_open()) {
        str linea;
        int claseActual = 0;
        str header;
        getline(archivo,header);
        while (getline(archivo, linea) && claseActual < cantClases) {
            istringstream ss(linea);
            str token;

            // Leer cada campo separado por comas
            getline(ss, token, ',');
            ListaClases[claseActual].id = stoi(token);

            getline(ss, ListaClases[claseActual].tipo, ',');
            getline(ss, token, ',');
            ListaClases[claseActual].hora = stof(token);

            claseActual++;
        }

        archivo.close();
    } else {
        cout << "No se pudo abrir el archivo: " << nombreArchivo << endl;
    }
}

void EscribirArchivoBinario(const sAsistencias* ListaAsistencias, int numElementos, ofstream& archi)
{

    // Escribe el array en el archivo binario
    archi.write(reinterpret_cast<const char*>(ListaAsistencias), sizeof(sAsistencias) * numElementos);

}

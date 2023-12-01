#include <iostream>
#include <fstream>
#include "archivos.h"
#include "gimnasio.h"

using namespace std;

int main()
{
    str ArchivoClientes = "../../Proyecto/Dataset TP/iriClientesGYM.csv";
    str ArchivoClases = "../../Proyecto/Dataset TP/iriClasesGYM.csv";

    ifstream infileClientes(ArchivoClientes);
    ifstream infileClases(ArchivoClases);

    if (!infileClientes.is_open())
    {
        cout << "Error al abrir el archivo CSV.Clientes" << endl;
        return 1;
    }
    if (!infileClases.is_open())
    {
        cout << "Error al abrir el archivo CSV.Clases" << endl;
        return 1;
    }
//----------------------------------------------------------------------------------------------------------------------------------
    // Llenando ListaClientes
    int counterClientes = 0;
    str line_cliente;
    str header_cliente;
    getline(infileClientes,header_cliente); // Leemos el header y pasamos a la siguiente linea
    while(getline(infileClientes, line_cliente))
    {
        counterClientes = counterClientes + 1;// Cantidad de lineas en el archivo
    }
    sCliente* ListaClientes = new sCliente[counterClientes];
    LlenarListaClientes(infileClientes,counterClientes,ListaClientes);
//----------------------------------------------------------------------------------------------------------------------------------
    // Llenando ListaClases
    int counterClases = 0;
    str line_clase;
    str header_clase;
    getline(infileClases,header_clase);// Leemos el header y pasamos a la siguiente linea
    while(getline(infileClases, line_clase))
    {
        counterClases = counterClases + 1;// Cantidad de lineas en el archivo
    }
    sClase* ListaClases = new sClase[counterClases];
    LlenarListaClases(infileClases,counterClases,ListaClases);
//----------------------------------------------------------------------------------------------------------------------------------
    sAsistencias* ListaAsistencias = new sAsistencias[10];

    sCliente clienteActual;
    int id_cliente,cantclases = 0;
    int id_clase = 0;
    for(int i = 0; i < 10; i++){
        id_cliente = rand() % counterClientes; //obtenemos el id de un cliente random
        ListaAsistencias[i].idCliente = id_cliente;
        clienteActual = BuscarCliente(id_cliente,ListaClientes,counterClientes);
        cout << "Cliente: " << clienteActual.nombre << " " << clienteActual.apellido << " ID: " << id_cliente << endl;
        cantclases = (rand() % 3) + 1; //cantidad de clases entre 1 y 3
        ListaAsistencias[i].cantInscriptos = cantclases;
        for(int j = 0; j < cantclases; j++)
        {
            cout << "Reservando clase numero " << (j + 1) << "..." << endl;
            id_clase = rand() % counterClases; // Id random de clase
            clienteActual.claseActual = BuscarClase(id_clase,ListaClases,counterClases);
            cout << " " << ErrorToString(reservar(clienteActual,ListaClases,ListaClientes,counterClases,counterClientes)) << endl;
        }
    }

    // Cerramos archivos CSV
    infileClientes.close();
    infileClases.close();

    str ArchivoAsistencias = "Asistencias.bin";
    // Abrimos archivos BIN
    ofstream outfileAsistencias(ArchivoAsistencias, ios::binary);
    if (!outfileAsistencias.is_open())
    {
        cout << "Error opening binary file" << endl;
        return 1;
    }

    int numElementos = 10;
    EscribirArchivoBinario(ListaAsistencias,numElementos,outfileAsistencias);

    // Cerramos archivos BIN
    outfileAsistencias.close();

    // Deletes
    delete[] ListaAsistencias;
    delete[] ListaClientes;
    delete[] ListaClases;

    return 1;
}

#include "archivos.h"
#include <iostream>
#include <fstream>
#include <gimnasio.h>
#include <structs.h>
#include <sstream>

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
        counterClientes++;// Cantidad de lineas en el archivo
    }
    sCliente* ListaClientes = new sCliente[counterClientes];
    infileClientes.seekg(0); //vuelve al inicio del archivo
    LlenarListaClientes_(ArchivoClientes,ListaClientes,counterClientes);
    completarLlenadoClientes(ListaClientes,counterClientes);
//----------------------------------------------------------------------------------------------------------------------------------
    // Llenando ListaClases
    int counterClases = 0;
    str line_clase;
    str header_clase;
    getline(infileClases,header_clase);// Leemos el header y pasamos a la siguiente linea
    while(getline(infileClases, line_clase))
    {
        counterClases++;// Cantidad de lineas en el archivo
    }
    sClase* ListaClases = new sClase[counterClases];
    infileClases.seekg(0); //vuelve al inicio del archivo
    LlenarListaClases_(ArchivoClases,ListaClases,counterClases);
    CompletarLlenadoClases(ListaClases,counterClases);
//----------------------------------------------------------------------------------------------------------------------------------
   //probamos sin uso de archivos:--------------------------------------------------------------------------------------------------
   /*sCliente* ListaClientes = new sCliente[6];
   ListaClientes[0]={"Gaspar","Arreceygor",1,"garreceygor@gmail.com","1123455","21-11-01",true,0.0,0,ClaseNula,{ClaseNula,ClaseNula,ClaseNula,ClaseNula,ClaseNula}};
   ListaClientes[1]={"Ekaterina","Ciafardini",2,"ekaciafa@gmail.com","116473","27-11-03",true,40.0,0,ClaseNula,{ClaseNula,ClaseNula,ClaseNula,ClaseNula,ClaseNula}};
   ListaClientes[2]={"Lola","Noval",3,"lolanoval@gmail.com","1129393","06-05-02",true,-10.0,0,ClaseNula,{ClaseNula,ClaseNula,ClaseNula,ClaseNula,ClaseNula}};
   ListaClientes[3]={"Sofia","Guerra",4,"soguerra@gmail.com","1109483","21-11-01",true,0.0,0,ClaseNula,{ClaseNula,ClaseNula,ClaseNula,ClaseNula,ClaseNula}};
   ListaClientes[4]={"Pilar","Noval",5,"pilinoval@gmail.com","1184920","21-11-01",true,0.0,0,ClaseNula,{ClaseNula,ClaseNula,ClaseNula,ClaseNula,ClaseNula}};
   ListaClientes[5]={"Griselda","Oujo",6,"grioujo@gmail.com","11032893","21-11-01",true,0.0,0,ClaseNula,{ClaseNula,ClaseNula,ClaseNula,ClaseNula,ClaseNula}};

   //prueba del error del main:
   sCliente clienteprueba=ListaClientes[4];
   clienteprueba.cantClases++;

   sClase* ListaClases=new sClase[4];
   ListaClases[0]={1,"Pilates",9.0,eSala::pilates_s,eCupo::pilates_c,10};
   ListaClases[1]={2,"Musculacion",9.0,eSala::musculacion_s,eCupo::musuclacion_c,5};
   ListaClases[2]={3,"Boxeo",15.0,eSala::boxeo_s,eCupo::boxeo_c,0};
   ListaClases[3]={4,"Yoga",20.0,eSala::yoga_s,eCupo::yoga_c,4};

   int counterClases=4;
   int counterClientes=6;*/
   //---------------------------------------------------------------------------------------------------------------------------------

   sAsistencias* ListaAsistencias = new sAsistencias[10];

    sCliente clienteActual;
    int id_cliente,cantclases = 0;
    int id_clase = 0;
    eResClase error;
    for(int i = 0; i < 10; i++){
        id_cliente = (rand() % counterClientes)+1; //obtenemos el id de un cliente random
        ListaAsistencias[i].idCliente = id_cliente;
        clienteActual = BuscarCliente(id_cliente,ListaClientes,counterClientes);
        cout << "Cliente: " << clienteActual.nombre << " " << clienteActual.apellido << " ID: " << id_cliente << endl;
        cantclases = (rand() % 3) + 1; //cantidad de clases entre 1 y 3
        ListaAsistencias[i].cantInscriptos = cantclases;
        for(int j = 0; j < cantclases; j++)
        {

            cout << "Reservando clase numero " << (j + 1) << "..." << endl;
            id_clase = (rand() % counterClases)+1; // Id random de clase
           clienteActual.claseActual = BuscarClase(id_clase,ListaClases,counterClases);
            error=reservar(clienteActual,ListaClases,ListaClientes,counterClases,counterClientes);
            cout << " " << ErrorToString(error) << endl;
            if(ErrorToString(error)=="Se reservo exitosamente")
            {
                clienteActual.clases[clienteActual.cantClases]=clienteActual.claseActual;
                clienteActual.cantClases++;
                clienteActual.claseActual=ClaseNula;
            }
        }
        cout<<"------------------------------------------------------"<<endl;
        cout<<endl;
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

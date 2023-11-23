#include <iostream>
#include <archivos.cpp>
#include <clientes.cpp>
#include <gimnasio.cpp>
#include <libreria.cpp>

using namespace std;

int main() {

    sAsistencias *ListaAsistencias =CargarDataAsistencias("asistencias_1697673600000.dat");
    sCliente *ListaClientes=LlenaListaClientes("iriClientesGYM.csv");
    sClase *ListaClases=LlenarListaClases("iriClasesGYM.csv");

    int tamListaAsistencias = (sizeof(ListaAsistencias)/sizeof(ListaAsistencias[0]);

    for(int i=0;i<tamListaAsistencias;i++)
    {
        sCliente clienteActual=BuscarCliente(ListaAsistencias[i].idCliente,ListaClientes);
        if(clienteActual!=nullptr)
        {
            cout<<"Nombre del cliente: "<<clienteActual.nombre<<" "<<clienteActual.apellido<<endl;
            for(int j=0;j<ListaAsistencias[i].cantInscriptos;j++)
            {
                cout<<"Reservando clase numero "<<j<<"..."<<endl;
                clienteActual.claseActual=BuscarClase(ListaAsistencias[i].cursosInscriptos[j].idCurso,ListaClases);
                cout<<ErrorToString(reservar(clienteActual,ListaClases,ListaClientes)<<endl;
            }
        }
    }


}

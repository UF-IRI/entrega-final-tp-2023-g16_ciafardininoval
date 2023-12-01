#include "gimnasio.h"

using namespace std;

void AgregarClaseCliente(sCliente cliente, sClase clase)
{
    if(cliente.ID != -1)
    {
        cliente.clases[cliente.cantClases]=clase;
        cliente.cantClases++;
    }
}
void PagoAlDia(sCliente cliente)
{
    if(cliente.pago >=0.0)
        cliente.pagoAlDia=true;
    else if(cliente.pago<0.0)
        cliente.pagoAlDia=false;

}
sCliente BuscarCliente(int id, sCliente* ListaClientes, int numClientes)
{
    int tam=numClientes;
    for(int i=0;i<tam;i++)
    {
        if(ListaClientes[i].ID==id)
        {
            return ListaClientes[i];
        }
    }
    return ClienteNulo;
}
sClase BuscarClase(int id, sClase* ListaClases, int numClases)
{
    int tam=numClases;
    for(int i=0;i<tam;i++)
    {
        if(ListaClases[i].id==id)
            return ListaClases[i];
    }
    return ClaseNula;
}

eResClase reservarClase(sCliente cliente, sClase* ListaClases, int numClases)
{
    //no chequeamos que cliente sea distinto a nullptr pq ya lo chequeamos antes
    int id=cliente.claseActual.id;
    int pos =0;
    int i,j,k=0;
    for(i=0;i<(numClases+1);i++)
    {
        if(id==ListaClases[i].id)//se fija que le id de la clase corresponda con algun id de las clases en la lista
        {
            pos = i;
            break;
        }
    }
    if(pos==(numClases+1))
    {
        return eResClase::ErrNonExClass; //non existent class
    }
    for(k=0;k<5;k++)
    {
        if(cliente.claseActual.id==cliente.clases[k].id)
            return eResClase::ErrAlrInThisClass; //ya se encuentra anotado en esta clase

    }
    float horario=cliente.claseActual.hora;

    for(j=0;j<5;j++) //compara con la lista de clases a la q esta anotado el cliente
    {
        if(cliente.clases[j].hora==horario)
        {
            return eResClase::ErrAlrInOtherClass; //already in other class
        }
    }
    if(ListaClases[i].inscriptos < ListaClases[i].cupo) //chequea q haya lugar en la clase
    {
        ListaClases[i].inscriptos++;
        AgregarClaseCliente(cliente,cliente.claseActual); //le agregamos la clase actual a la lista de clases a las cuales esta anotado/a
        cliente.claseActual=ClaseNula;
        return eResClase::ExitoReserva;
    }
    else
    {
        return eResClase::ErrNoCupo; //no hay cupo podemos ver de agregar otra alternativa!!
    }
}
eResClase reservar(sCliente cliente,sClase* ListaClases,sCliente* ListaClientes, int numClases, int numClientes) //la lista de clientes se define en el main c la funcion de archivos LlenarListaClientes
{
    if(ListaClases==nullptr)
    {
       return eResClase::ErrNullPtr;
    }
    if(cliente.ID == -1)
    {
        return eResClase::ErrNullPtr;
    }
    if(ListaClientes==nullptr)
    {
        return eResClase::ErrNullPtr;
    }
    PagoAlDia(cliente); //pago al dia se encuentra actualizado

    if(!cliente.pagoAlDia)
       return eResClase::ErrNoPago;
    else
    {
       return reservarClase(cliente,ListaClases, numClases); //tanto si reserva clase como musculacion es la misma funcion
    }
}

sCliente* Resize(sCliente* ListaClientes, u_int tam, u_int nuevoTam)
{
    // nuevoTam es el nuevo tamaño que quiero darle a la lista (agrandarla o achicarla)
    // La voy a llamar cuando se alcance la capacidad max por ejemplo

    u_int longitud = (tam < nuevoTam) ? tam : nuevoTam; // Si se cumple que tam es mas chico, devuelve tam, si es false, devuelve nuevoTam
    sCliente *aux= new sCliente[nuevoTam];
    if(aux != nullptr)// No se le asigno memoria
    {
        for(u_int i=0;i<longitud;i++)
        {
           aux[i]=ListaClientes[i];// *(miLista+i)
        }
        delete[] ListaClientes;
        return aux;// Devulve la lista de contactos con el nuevo tamaño
    }
    return nullptr;
}
str ErrorToString(eResClase resultado)
{
    switch (resultado)
    {
    case -6:
        return "Error: Ya se encuentra inscripto en esta clase";
        break;
    case -5:
        return "Error: Pago no al dia";
        break;
    case -4:
        return "Error: No hay cupo";
        break;
    case -3:
        return "Error: Ya tiene una clase reservada en el horario seleccionado";
        break;
    case -2:
        return "Error: NullPtr";
        break;
    case -1:
        return "Error: No existe la clase";
        break;
    case 1:
        return "Se reservo exitosamente";
        break;
    default:
        return "ERROR NO ENCONTRADO"; // mejoras posibles: salvacion de errores
        break;
    }
}




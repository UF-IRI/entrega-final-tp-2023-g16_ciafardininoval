#include "gimnasio.h"
#include "structs.h"
#include "clientes.h"
#include "archivos.h"

using namespace std;

gimnasio::gimnasio()
{

}
sCliente BuscarCliente(int id, sCliente* ListaClientes)
{
    int tam=CounterClientes(ListaClientes);
    for(int i=0;i<tam;i++)
    {
        if(ListaClientes[i].ID==id)
            return ListaClientes[i];
    }
    return nullptr;
}
sClase BuscarClase(int id, sClase* ListaClases)
{
    int tam=CounterClases(ListaClases);
    for(int i=0;i<tam;i++)
    {
        if(ListaClases[i].id==id)
            return ListaClases[i];
    }
   // return nullptr; ver qué devolver
}
int CounterClases(sClase* ListaClases){
    int counter = (sizeof(ListaClases)/sizeof(ListaClases[0]));
    return counter;
}
int CounterClientes(sCliente* ListaClientes)
{
    int counter = (sizeof(ListaClientes)/sizeof(ListaClientes[0]));
    return counter;
}
void CheckCliente(sCliente *cliente, sCliente* ListaClientes)
{
    //no chequeamos que cliente sea distinto a nullptr pq lo chequeamos antes
    int id_aux;
    int counter=0;

    while(id_aux!=cliente->ID && counter<(CounterClientes(ListaClientes)+1))
    {
        id_aux=ListaClientes[counter].ID;
        counter++;
    }
    if(counter==(CounterClientes(ListaClientes)+1)) //hay que agregar el cliente
    {
        AgregarCliente(cliente, ListaClientes);
    }
}
eResClase reservar(sCliente cliente,sClase* ListaClases,sCliente* ListaClientes) //la lista de clientes se define en el main c la funcion de archivos LlenarListaClientes
{
    if(ListaClases==nullptr)
    {
       return eResClase::ErrNullPtr;
    }
    if(cliente == nullptr)//ver que cambiar aca, hacer cliente const nulo
    {
        return eResClase::ErrNullPtr;
    }
    PagoAlDia(cliente); //pago al dia se encuentra actualizado
    //CheckCliente(cliente,ListaClientes); //me fijo si existe el cliente, sino lo agrego a la lista

    if(!cliente->pagoAlDia)
       return eResClase::ErrNoPago;
    else
    {
        reservarClase(cliente,ListaClases); //tanto si reserva clase como musculacion es la misma funcion
    }
}
eResClase reservarClase(sCliente *cliente, sClase* ListaClases)
{
    //no chequeamos que cliente sea distinto a nullptr pq ya lo chequeamos antes
    int id=cliente->claseActual.id;
    int i,j,k=0;
    for( i=0;i<(CounterClases(ListaClases)+1);i++)
    {
        if(id==ListaClases[i].id) //se fija que le id de la clase corresponda con algun id de las clases en la lista
            break;
    }
    if(i==(CounterClases(ListaClases)+1))
    {
       return eResClase::ErrNonExClass; //non existent class
       // break;
    }
    for( k=0;k<(CounterClases(cliente->clases));k++)
    {
        if(&cliente->claseActual==&cliente->clases[k])
          return eResClase::ErrAlrInThisClass; //ya se encuentra anotado en esta clase
        //break;
    }
    float horario=cliente->claseActual.hora;

    for( j=0;j<(CounterClases(cliente->clases)+1);i++) //compara con la lista de clases a la q esta anotado el cliente
    {
        if(cliente->clases[j].hora==horario)
        {
           return eResClase::ErrAlrInOtherClass; //already in other class
            //break;
        }
    }
    if(ListaClases[i].inscriptos < ListaClases[i].cupo) //chequea q haya lugar en la clase
    {
        ListaClases[i].inscriptos++;
        cliente->clases+cliente->claseActual; //le agregamos la clase actual a la lista de clases a las cuales esta anotado/a
        // tenemos que crear la funcion que agregue la clase a la lista de clases
      //cliente->claseActual==nullptr; hay que hacer lo de crear una clase const que sea nula
        return eResClase::ExitoReserva;
    }
    else
    {
       return eResClase::ErrNoCupo; //no hay cupo podemos ver de agregar otra alternativa!!
    }
}

void AgregarCliente(sCliente cliente, sCliente* ListaClientes)
{
    if(cliente == nullptr)//hay q igualarlo al cliente nulo, q hay q crearlo
    {
        //error de nullptr
       //break; no se puede usar break pq no hay un loop-> buscar como terminar la funcion aca
    }
    if(ListaClientes == nullptr)
    {
        //error nullptr
        //break;
    }
    if(!ListaClientes+cliente) //no se puede agregar el cliente por falta de espacio
    //hay q crear la funcion q agregue el cliente
    {
        u_int tam= CounterClientes(ListaClientes);
        u_int nuevoTam= tam+10;
        AgregarCliente(cliente,(Resize(ListaClientes,tam,nuevoTam)));
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
}
str ErrorToString(eResClase resultado)
{
    enum eResClase   { ErrAlrInThisClass=-6,ErrNoPago=-5,ErrNoCupo=-4,ErrAlrInOtherClass=-3,ErrNullPtr = -2,ErrNonExClass=-1,  ExitoReserva = 1 };

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




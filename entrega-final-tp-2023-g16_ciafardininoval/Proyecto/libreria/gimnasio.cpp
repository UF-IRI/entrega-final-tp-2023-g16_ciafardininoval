#include "gimnasio.h"

using namespace std;

void CompletarLlenadoClases(sClase* ListaClases, int contadorClases)
{
    for(int i=0;i<contadorClases;i++)
    {
        if(ListaClases[i].tipo=="Spinning")
        {
            ListaClases[i].cupo=eCupo::spinning_c;
            ListaClases[i].sala=eSala::spinning_s;
            ListaClases[i].inscriptos=0;
        }
        if(ListaClases[i].tipo=="Yoga")
        {
            ListaClases[i].cupo=eCupo::yoga_c;
            ListaClases[i].sala=eSala::yoga_s;
            ListaClases[i].inscriptos=0;
        }
        if(ListaClases[i].tipo=="Pilates")
        {
            ListaClases[i].cupo=eCupo::pilates_c;
            ListaClases[i].sala=eSala::pilates_s;
            ListaClases[i].inscriptos=0;
        }
        if(ListaClases[i].tipo=="Stretching")
        {
            ListaClases[i].cupo=eCupo::stretching_c;
            ListaClases[i].sala=eSala::stretching_s;
            ListaClases[i].inscriptos=0;
        }
        if(ListaClases[i].tipo=="Zumba")
        {
            ListaClases[i].cupo=eCupo::zumba_c;
            ListaClases[i].sala=eSala::zumba_s;
            ListaClases[i].inscriptos=0;
        }
        if(ListaClases[i].tipo=="Boxeo")
        {
            ListaClases[i].cupo=eCupo::boxeo_c;
            ListaClases[i].sala=eSala::boxeo_s;
            ListaClases[i].inscriptos=0;
        }
        if(ListaClases[i].tipo=="Musculacion")
        {
            ListaClases[i].cupo=eCupo::musuclacion_c;
            ListaClases[i].sala=eSala::musculacion_s;
            ListaClases[i].inscriptos=0;
        }
    }
}
bool PagoAlDia(sCliente cliente)
{
    if(cliente.pago >=0.0)
    {
        return true;
    }

    if(cliente.pago<0.0)
    {
        return false;
    }

}
void completarLlenadoClientes(sCliente* ListaClientes, int contadorClientes)
{
    for(int i=0;i<contadorClientes;i++)
    {
        //actualizamos bool de pago al dia:
        //PagoAlDia(ListaClientes[i]);
        ListaClientes[i].cantClases=0; //la cantidad de clases a las q esta inscripto se incializa en 0
        ListaClientes[i].claseActual=ClaseNula; //no apunta a ninguna clase en un principio
        for(int j=0;j<5;j++)
        {
            ListaClientes[i].clases[j]=ClaseNula;
        }
    }
}

void AgregarClaseCliente(sCliente cliente, sClase clase)
{
        cliente.clases[cliente.cantClases]=clase;
        cliente.cantClases++;

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
void AsignarClase(int id, sClase* ListaClases, int numClases,sCliente cliente)
{
    int i=0;
    int pos=0;
    do
    {
        if(ListaClases[i].id==id)
            pos=i;
        i++;
    }while(i<numClases);
    /*for(i=0;i<numClases;i++)
    {
        if(ListaClases[i].id==id)
        {
            break;
        }
    }*/
    cliente.claseActual.cupo=ListaClases[pos].cupo;
    cliente.claseActual.hora=ListaClases[pos].hora;
    cliente.claseActual.id=ListaClases[pos].id;
    cliente.claseActual.inscriptos=ListaClases[pos].inscriptos;
    cliente.claseActual.sala=ListaClases[pos].sala;
    cliente.claseActual.tipo=ListaClases[pos].tipo;
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
       // cliente.clases[cliente.cantClases]=cliente.claseActual;
        //cliente.cantClases++;
       // AgregarClaseCliente(cliente,cliente.claseActual); //le agregamos la clase actual a la lista de clases a las cuales esta anotado/a
       // cliente.claseActual=ClaseNula;
        return eResClase::ExitoReserva;
    }
    else
    {
        return eResClase::ErrNoCupo; //no hay cupo podemos ver de agregar otra alternativa!!
    }
}
eResClase reservar(sCliente cliente,sClase* ListaClases,sCliente* ListaClientes, int numClases, int numClientes) //la lista de clientes se define en el main c la funcion de archivos LlenarListaClientes
{
    if(cliente.claseActual.id==-1)
    {
        return eResClase::ErrNonExClass;
    }
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

    if(!(PagoAlDia(cliente)))
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




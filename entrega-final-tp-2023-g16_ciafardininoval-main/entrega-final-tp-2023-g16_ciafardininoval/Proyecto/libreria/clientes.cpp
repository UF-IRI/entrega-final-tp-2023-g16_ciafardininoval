#include "clientes.h"
#include "structs.h"
clientes::clientes()
{

}
void PagoAlDia(sCliente cliente)
{
    if(cliente.pago >=0)
        cliente.pagoAlDia==true;
    else if(cliente.pago<0)
        cliente.pagoAlDia==false;

}

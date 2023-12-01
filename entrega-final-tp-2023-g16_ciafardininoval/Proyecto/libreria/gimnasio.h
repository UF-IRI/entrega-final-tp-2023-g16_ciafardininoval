#ifndef GIMNASIO_H
#define GIMNASIO_H
#include "structs.h"

const sClase ClaseNula = { -1, " ", 0.0, eSala::ninguna_s, eCupo::ninguno_c,0};
const sCliente ClienteNulo = {" "," ",-1," "," "," ",false,0.0,0,ClaseNula,{ClaseNula,ClaseNula,ClaseNula,ClaseNula,ClaseNula}};

enum eResClase { ErrAlrInThisClass=-6,ErrNoPago=-5,ErrNoCupo=-4,ErrAlrInOtherClass=-3,ErrNullPtr = -2,ErrNonExClass=-1,  ExitoReserva = 1 };

void AgregarClaseCliente(sCliente cliente, sClase clase);
void PagoAlDia(sCliente cliente);
sCliente BuscarCliente(int id, sCliente* ListaClientes, int numClientes);
sClase BuscarClase(int id, sClase* ListaClases, int numClases);
eResClase reservarClase(sCliente cliente, sClase* ListaClases, int numClases);
eResClase reservar(sCliente cliente,sClase* ListaClases,sCliente* ListaClientes, int numClases, int numClientes);
sCliente* Resize(sCliente* ListaClientes, u_int tam, u_int nuevoTam);
str ErrorToString(eResClase resultado);

#endif // GIMNASIO_H

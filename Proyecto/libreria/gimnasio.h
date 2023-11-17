#ifndef GIMNASIO_H
#define GIMNASIO_H
#include <structs.h>

//const sCliente ClienteNulo = {" "," "," "," ",false,0.0,nullptr,nullptr};
//const sClase ClaseNula = { " ", " ", 0.0, eSala::ninguna_s, eCupo::ninguno_c,0};

enum eResClase { ErrAlrInThisClass=-6,ErrNoPago=-5,ErrNoCupo=-4,ErrAlrInOtherClass=-3,ErrNullPtr = -2,ErrNonExClass=-1,  ExitoReserva = 1 };

eResClase reservar(sCliente* cliente,sClase ListaClases[],sCliente ListaClientes[]);
eResClase reservarClase(sCliente *cliente, sClase ListaClases[]);
//void reservarMusculacion(sCliente *cliente);
void AgregarCliente(sCliente *cliente, sCliente ListaClientes[]);
sCliente* Resize(sCliente ListaClientes[], u_int tam, u_int nuevoTam);
str ErrorToString(eResClase resultado);
sCliente* BuscarCliente(int id, sCliente ListaClientes[]);
sClase* BuscarClase(int id, sClase ListaClases[]);
int CounterClases(sClase ListaClases[]);
int CounterClientes(sCliente ListaClientes[]);
void CheckCliente(sCliente *cliente, sCliente ListaClientes[]);

class gimnasio
{
public:
    gimnasio();

};

#endif // GIMNASIO_H

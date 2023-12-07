#include <catch2/catch.hpp>
#include <gimnasio.h>
#include <structs.h>
/*void AgregarClaseCliente(sCliente cliente, sClase clase);
eResClase reservarClase(sCliente cliente, sClase* ListaClases, int numClases);
eResClase reservar(sCliente cliente,sClase* ListaClases,sCliente* ListaClientes, int numClases, int numClientes);
*/
TEST_CASE("Creamos datos requeridos")
{
    //creamos lista de clientes:
    sCliente* ListaClientes = new sCliente[5];
    ListaClientes[0]={"Gaspar","Arreceygor",1,"garreceygor@gmail.com","1123455","21-11-01",true,0.0,0,ClaseNula,{ClaseNula,ClaseNula,ClaseNula,ClaseNula,ClaseNula}};
    ListaClientes[1]={"Ekaterina","Ciafardini",2,"ekaciafa@gmail.com","116473","27-11-03",true,40.0,0,ClaseNula,{ClaseNula,ClaseNula,ClaseNula,ClaseNula,ClaseNula}};
    ListaClientes[2]={"Lola","Noval",3,"lolanoval@gmail.com","1129393","06-05-02",true,-10.0,0,ClaseNula,{ClaseNula,ClaseNula,ClaseNula,ClaseNula,ClaseNula}};
    ListaClientes[3]={"Sofia","Guerra",4,"soguerra@gmail.com","1109483","21-11-01",true,0.0,0,ClaseNula,{ClaseNula,ClaseNula,ClaseNula,ClaseNula,ClaseNula}};
    ListaClientes[4]={"Pilar","Noval",5,"pilinoval@gmail.com","1184920","21-11-01",true,0.0,0,ClaseNula,{ClaseNula,ClaseNula,ClaseNula,ClaseNula,ClaseNula}};
    ListaClientes[5]={"Griselda","Oujo",6,"grioujo@gmail.com","11032893","21-11-01",true,0.0,0,ClaseNula,{ClaseNula,ClaseNula,ClaseNula,ClaseNula,ClaseNula}};
    SECTION("Pago Al Dia")
    {
        PagoAlDia(ListaClientes[0]); //tiene pago al dia
        REQUIRE(ListaClientes[0].pago==true);
        PagoAlDia(ListaClientes[1]);// debe plata
        REQUIRE(ListaClientes[1].pago==false);
    }
    SECTION("Buscar Cliente")
    {
        sCliente clienteActual = BuscarCliente(1,ListaClientes,6);
        REQUIRE(clienteActual.ID==1);
        sCliente clienteActual2 = BuscarCliente(2,ListaClientes,6);
        REQUIRE(clienteActual2.ID==2);

    }
    //creamos lista de clases:
    sClase* ListaClases=new sClase[3];
    ListaClases[0]={1,"Pilates",9.0,eSala::pilates_s,eCupo::pilates_c,10};
    ListaClases[1]={2,"Musculacion",11.0,eSala::musculacion_s,eCupo::musuclacion_c,5};
    ListaClases[2]={3,"Boxeo",15.0,eSala::boxeo_s,eCupo::boxeo_c,0};
    ListaClases[3]={4,"Yoga",20.0,eSala::yoga_s,eCupo::yoga_c,4};
    SECTION("Buscar Clase")
    {
       sClase claseActual= BuscarClase(1,ListaClases,4);
        REQUIRE(claseActual.id==1);
       sClase claseActual2=BuscarClase(4,ListaClases,4);
        REQUIRE(claseActual.id==4);
    }
    SECTION("Reservar") //llama tambien a reservar clase y agregarClaseCliente
    {
        ListaClientes[0].claseActual=ListaClases[0];
        reservar(ListaClientes[0],ListaClases,ListaClientes,4,6);
        //si se agrego con exito
        REQUIRE(ListaClientes[0].cantClases==1);
        REQUIRE(ListaClientes[0].clases[0].id==1);
    }
    //borramos uso de memoria dinamica
    delete[] ListaClientes;
    delete[] ListaClases;

}

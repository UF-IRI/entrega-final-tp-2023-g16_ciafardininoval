#include <catch2/catch.hpp>
#include <archivos.h>
#include <gimnasio.h>
#include <fstream>

TEST_CASE("Llenar Lista Clientes")
{
    SECTION("LLeno la lista correctamente")
    {
        //Abro el archivo en formato escritura
        str archivo = "archivo_prueba_clientes.csv";
        ofstream archivoPrueba(archivo);
        archivoPrueba << "1,Juan,Perez,juan@example.com,1234567890,01-01-1990,100.0\n";
        archivoPrueba << "2,Maria,Lopez,maria@example.com,9876543210,02-02-1995,150.0\n";
        archivoPrueba << "3,Carlos,Gonzalez,carlos@example.com,5555555555,03-03-1985,200.0\n";
        archivoPrueba.close();

        //Abro el archivo en formato lectura
        ifstream archi(archivo);

        REQUIRE(archi.is_open());
        int contador = 3;
        sCliente* listaClientes = new sCliente[contador];
        REQUIRE(listaClientes != nullptr);

        LlenarListaClientes_(archivo,listaClientes,contador);

        archi.close();

        REQUIRE(listaClientes[0].ID == 1);
        REQUIRE(listaClientes[0].nombre == "Juan");
        REQUIRE(listaClientes[0].apellido == "Perez");
        REQUIRE(listaClientes[0].email == "juan@example.com");
        REQUIRE(listaClientes[0].telefono == "1234567890");
        REQUIRE(listaClientes[0].fechaNac == "01-01-1990");
        REQUIRE(listaClientes[0].pago == 100.0);

        REQUIRE(listaClientes[1].ID == 2);
        REQUIRE(listaClientes[1].nombre == "Maria");
        REQUIRE(listaClientes[1].apellido == "Lopez");
        REQUIRE(listaClientes[1].email == "maria@example.com");
        REQUIRE(listaClientes[1].telefono == "9876543210");
        REQUIRE(listaClientes[1].fechaNac == "02-02-1995");
        REQUIRE(listaClientes[1].pago == 150.0);

        REQUIRE(listaClientes[2].ID == 3);
        REQUIRE(listaClientes[2].nombre == "Carlos");
        REQUIRE(listaClientes[2].apellido == "Gonzalez");
        REQUIRE(listaClientes[2].email == "carlos@example.com");
        REQUIRE(listaClientes[2].telefono == "5555555555");
        REQUIRE(listaClientes[2].fechaNac == "03-03-1985");
        REQUIRE(listaClientes[2].pago == 200.0);

        delete [] listaClientes;
    }
    SECTION("Dato incorrecto")
    {
        //Abro el archivo en formato escritura
        str archivo = "archivo_prueba_clientes.csv";
        ofstream archivoPrueba(archivo);
        archivoPrueba << "1,Juan,Perez,juan@example.com,1234567890,01-01-1990,100.0\n";
        archivoPrueba << "dos,Maria,Lopez,maria@example.com,9876543210,02-02-1995,150.0\n";  // Error
        archivoPrueba << "3,Carlos,Gonzalez,carlos@example.com,5555555555,03-03-1985,200.0\n";
        archivoPrueba.close();

        //Abro el archivo en formato lectura
        ifstream archi(archivo);

        REQUIRE(archi.is_open());
        int contador = 3;
        sCliente* listaClientes = new sCliente[contador];
        REQUIRE(listaClientes != nullptr);

        // Al intentar llenar la lista, debería ocurrir un error debido al formato incorrecto en la segunda línea
        REQUIRE_THROWS(LlenarListaClientes_(archivo, listaClientes, contador)); // NO SE SI ESTA BIEN

        archi.close();
        delete [] listaClientes;
    }
    SECTION("Cliente existente")
    {
        //Abro el archivo en formato escritura
        str archivo = "archivo_prueba_clientes.csv";
        ofstream archivoPrueba(archivo);
        archivoPrueba << "1,Juan,Perez,juan@example.com,1234567890,01-01-1990,100.0\n";
        archivoPrueba << "2,Maria,Lopez,maria@example.com,9876543210,02-02-1995,150.0\n";
        archivoPrueba << "3,Carlos,Gonzalez,carlos@example.com,5555555555,03-03-1985,200.0\n";
        archivoPrueba << "2,Maria,Lopez,maria@example.com,9876543210,02-02-1995,150.0\n";  // Cliente duplicado
        archivoPrueba.close();

        //Abro el archivo en formato lectura
        ifstream archi("archivo_prueba_clientes.csv");

        REQUIRE(archi.is_open());
        int contador = 4;  // Ajusta el contador según la cantidad de líneas en el archivo
        sCliente* listaClientes = new sCliente[contador];
        REQUIRE(listaClientes != nullptr);

        // Al intentar llenar la lista, debería ocurrir un error debido al cliente duplicado
        REQUIRE_THROWS(LlenarListaClientes_(archivo, listaClientes, contador));

        archi.close();
        delete [] listaClientes;
    }
}
TEST_CASE("Llenar Lista Clases")
{
    SECTION("LLena correctamente")
    {
        //Abro el archivo en formato escritura
        str archivo = "archivo_prueba_clases.csv";
        ofstream archivoPrueba(archivo);
        archivoPrueba << "1,Yoga,10.0\n";
        archivoPrueba << "2,Pilates,14.0\n";
        archivoPrueba << "3,Spinning,18.0\n";
        archivoPrueba.close();

        //Abro el archivo en formato lectura
        ifstream archi(archivo);

        REQUIRE(archi.is_open());
        int contador = 3;
        sClase* listaClases = new sClase[contador];
        REQUIRE(listaClases != nullptr);

        LlenarListaClases_(archivo, listaClases, contador);

        archi.close();

        REQUIRE(listaClases[0].id == 1);
        REQUIRE(listaClases[0].tipo == "Yoga");
        REQUIRE(listaClases[0].hora == 10.0);

        REQUIRE(listaClases[1].id == 2);
        REQUIRE(listaClases[1].tipo == "Pilates");
        REQUIRE(listaClases[1].hora == 14.0);

        REQUIRE(listaClases[2].id == 3);
        REQUIRE(listaClases[2].tipo == "Spinning");
        REQUIRE(listaClases[2].hora == 18.0);

        delete[] listaClases;
    }
    SECTION("Faltan datos")
    {
        //Abro el archivo en formato escritura
        str archivo = "archivo_prueba_clases.csv";
        ofstream archivoPrueba(archivo);
        archivoPrueba << "1,Yoga\n";  // Falta el último valor (hora)
        archivoPrueba << "2,Pilates,14:30\n";
        archivoPrueba << "3,Spinning,18:45\n";
        archivoPrueba.close();

        //Abro el archivo en formato lectura
        ifstream archi("archivo_prueba_clases.csv");

        REQUIRE(archi.is_open());
        int contador = 3;
        sClase* listaClases = new sClase[contador];
        REQUIRE(listaClases != nullptr);

        REQUIRE_THROWS(LlenarListaClases_(archivo, listaClases, contador));

        archi.close();

        delete[] listaClases;
    }
}

TEST_CASE("Escribir ArchivoBinario")
{
    SECTION("Verificacion de tamaño")
    {
        sAsistencias listaAsistencias[3];

        // Abrir un archivo binario para escritura
        ofstream archivoBinario("archivoBin_prueba.dat", ios::binary);

        // Verificar si la apertura del archivo fue exitosa
        REQUIRE(archivoBinario.is_open());

        // Llamar a la funcion para escribir el array en el archivo binario
        EscribirArchivoBinario(listaAsistencias, 3, archivoBinario);

        // Cerrar el archivo
        archivoBinario.close();

        // Verificar el tamaño del archivo
        ifstream archivoLeido("archivoBin_prueba.dat", ios::binary | ios::ate);
        REQUIRE(archivoLeido.is_open());

        // Obtener el tamaño del archivo
        streamsize fileSize = archivoLeido.tellg();
        archivoLeido.close();

        // Verificar si el tamaño del archivo coincide con el tamaño esperado del array
        REQUIRE(fileSize == sizeof(sAsistencias) * 3);
    }

}
TEST_CASE("Prueba Gimnasio")
{
    //creamos lista de clientes:
    sCliente* ListaClientes = new sCliente[5];
    ListaClientes[0]={"Gaspar","Arreceygor",1,"garreceygor@gmail.com","1123455","21-11-01",0.0,0,ClaseNula,{ClaseNula,ClaseNula,ClaseNula,ClaseNula,ClaseNula}};
    ListaClientes[1]={"Ekaterina","Ciafardini",2,"ekaciafa@gmail.com","116473","27-11-03",40.0,0,ClaseNula,{ClaseNula,ClaseNula,ClaseNula,ClaseNula,ClaseNula}};
    ListaClientes[2]={"Lola","Noval",3,"lolanoval@gmail.com","1129393","06-05-02",-10.0,0,ClaseNula,{ClaseNula,ClaseNula,ClaseNula,ClaseNula,ClaseNula}};
    ListaClientes[3]={"Sofia","Guerra",4,"soguerra@gmail.com","1109483","21-11-01",0.0,0,ClaseNula,{ClaseNula,ClaseNula,ClaseNula,ClaseNula,ClaseNula}};
    ListaClientes[4]={"Pilar","Noval",5,"pilinoval@gmail.com","1184920","21-11-01",0.0,0,ClaseNula,{ClaseNula,ClaseNula,ClaseNula,ClaseNula,ClaseNula}};
    ListaClientes[5]={"Griselda","Oujo",6,"grioujo@gmail.com","11032893","21-11-01",0.0,0,ClaseNula,{ClaseNula,ClaseNula,ClaseNula,ClaseNula,ClaseNula}};
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

#include <catch2/catch.hpp>
#include <archivos.h>
#include <gimnasio.h>
#include <fstream>

TEST_CASE("Llenar Lista Clientes")
{
    //Clientes:
    //Abro el archivo en formato escritura
    str archivo_ = "archivo_prueba_clientes.csv";
    ofstream archivoPrueba_(archivo_);
    archivoPrueba_<<"ID,Nombre,Apellido,mail,Numero,fechaNac,estado\n";
    archivoPrueba_ << "1,Juan,Perez,juan@example.com,1234567890,01-01-1990,100.0\n";
    archivoPrueba_ << "2,Maria,Lopez,maria@example.com,9876543210,02-02-1995,-150.0\n";
    archivoPrueba_ << "3,Carlos,Gonzalez,carlos@example.com,5555555555,03-03-1985,200.0\n";
    archivoPrueba_.close();

    //Abro el archivo en formato lectura
    ifstream archi_(archivo_);

    REQUIRE(archi_.is_open());
    int contador_ = 3;
    sCliente* listaClientes = new sCliente[contador_];
    REQUIRE(listaClientes != nullptr);

    LlenarListaClientes_(archivo_,listaClientes,contador_);
    completarLlenadoClientes(listaClientes,contador_);

    archi_.close();

    //Clases:
    //Abro el archivo en formato escritura
    str archivo = "archivo_prueba_clases.csv";
    ofstream archivoPrueba(archivo);
    archivoPrueba<<"id,Nombre,hora\n";
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
    CompletarLlenadoClases(listaClases,contador);

    archi.close();

    SECTION("LLeno la lista correctamente")
    {
        CHECK(listaClientes[0].ID == 1);
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
        REQUIRE(listaClientes[1].pago == -150.0);

        REQUIRE(listaClientes[2].ID == 3);
        REQUIRE(listaClientes[2].nombre == "Carlos");
        REQUIRE(listaClientes[2].apellido == "Gonzalez");
        REQUIRE(listaClientes[2].email == "carlos@example.com");
        REQUIRE(listaClientes[2].telefono == "5555555555");
        REQUIRE(listaClientes[2].fechaNac == "03-03-1985");
        REQUIRE(listaClientes[2].pago == 200.0);
    }
    SECTION("LLena correctamente")
    {

        CHECK(listaClases[0].id == 1);
        REQUIRE(listaClases[0].tipo == "Yoga");
        REQUIRE(listaClases[0].hora == 10.0);

        REQUIRE(listaClases[1].id == 2);
        REQUIRE(listaClases[1].tipo == "Pilates");
        REQUIRE(listaClases[1].hora == 14.0);

        REQUIRE(listaClases[2].id == 3);
        REQUIRE(listaClases[2].tipo == "Spinning");
        REQUIRE(listaClases[2].hora == 18.0);
    }
    SECTION("Pago Al Dia")
    {
        REQUIRE(PagoAlDia(listaClientes[0])==true); //tiene pago al dia
        REQUIRE(PagoAlDia(listaClientes[1])==false); //debe plata
    }
    SECTION("Buscar Cliente")
    {
        sCliente clienteActual = BuscarCliente(1,listaClientes,3);
        REQUIRE(clienteActual.ID==1);
        sCliente clienteActual2 = BuscarCliente(2,listaClientes,3);
        REQUIRE(clienteActual2.ID==2);
    }
    SECTION("Buscar Clase")
    {
        sClase claseActual= BuscarClase(1,listaClases,3);
        REQUIRE(claseActual.id==1);
        sClase claseActual2=BuscarClase(2,listaClases,3);
        REQUIRE(claseActual2.id==2);
    }
    SECTION("Reservar") //llama tambien a reservar clase y agregarClaseCliente
    {
        listaClientes[0].claseActual=listaClases[0];
        reservar(listaClientes[0],listaClases,listaClientes,3,3);
        if(ErrorToString(reservar(listaClientes[0],listaClases,listaClientes,3,3))=="Se reservo exitosamente")
        {
            listaClientes[0].clases[listaClientes[0].cantClases]=listaClientes[0].claseActual;
            listaClientes[0].cantClases++;
            listaClientes[0].claseActual=ClaseNula;
        }
        //si se agrego con exito
        CHECK(listaClientes[0].cantClases==1);
        REQUIRE(listaClientes[0].clases[0].id==1);
    }


    delete [] listaClientes;
    delete[] listaClases;

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

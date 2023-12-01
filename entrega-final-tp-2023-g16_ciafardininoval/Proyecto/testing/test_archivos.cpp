#include <catch2/catch.hpp>
#include <archivos.h>
#include <fstream>

TEST_CASE("LlenarListaClientes")
{
    SECTION("LLeno la lista correctamente")
    {
        //Abro el archivo en formato escritura
        ofstream archivoPrueba("archivo_prueba_clientes.csv");
        archivoPrueba << "1,Juan,Perez,juan@example.com,1234567890,01-01-1990,100.0\n";
        archivoPrueba << "2,Maria,Lopez,maria@example.com,9876543210,02-02-1995,150.0\n";
        archivoPrueba << "3,Carlos,Gonzalez,carlos@example.com,5555555555,03-03-1985,200.0\n";
        archivoPrueba.close();

        //Abro el archivo en formato lectura
        ifstream archivo("archivo_prueba_clientes.csv");

        REQUIRE(archivo.is_open());
        int contador = 3;
        sCliente* listaClientes = new sCliente[contador];
        REQUIRE(listaClientes != nullptr);

        LlenarListaClientes(archivo,contador,listaClientes);

        archivo.close();

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
        ofstream archivoPrueba("archivo_prueba_clientes.csv");
        archivoPrueba << "1,Juan,Perez,juan@example.com,1234567890,01-01-1990,100.0\n";
        archivoPrueba << "dos,Maria,Lopez,maria@example.com,9876543210,02-02-1995,150.0\n";  // Error
        archivoPrueba << "3,Carlos,Gonzalez,carlos@example.com,5555555555,03-03-1985,200.0\n";
        archivoPrueba.close();

        //Abro el archivo en formato lectura
        ifstream archivo("archivo_prueba_clientes.csv");

        REQUIRE(archivo.is_open());
        int contador = 3;
        sCliente* listaClientes = new sCliente[contador];
        REQUIRE(listaClientes != nullptr);

        // Al intentar llenar la lista, debería ocurrir un error debido al formato incorrecto en la segunda línea
        REQUIRE_THROWS(LlenarListaClientes(archivo, contador, listaClientes)); // NO SE SI ESTA BIEN

        archivo.close();
        delete [] listaClientes;
    }
    SECTION("Cliente existente")
    {
        //Abro el archivo en formato escritura
        ofstream archivoPrueba("archivo_prueba_clientes.csv");
        archivoPrueba << "1,Juan,Perez,juan@example.com,1234567890,01-01-1990,100.0\n";
        archivoPrueba << "2,Maria,Lopez,maria@example.com,9876543210,02-02-1995,150.0\n";
        archivoPrueba << "3,Carlos,Gonzalez,carlos@example.com,5555555555,03-03-1985,200.0\n";
        archivoPrueba << "2,Maria,Lopez,maria@example.com,9876543210,02-02-1995,150.0\n";  // Cliente duplicado
        archivoPrueba.close();

        //Abro el archivo en formato lectura
        ifstream archivo("archivo_prueba_clientes.csv");

        REQUIRE(archivo.is_open());
        int contador = 4;  // Ajusta el contador según la cantidad de líneas en el archivo
        sCliente* listaClientes = new sCliente[contador];
        REQUIRE(listaClientes != nullptr);

        // Al intentar llenar la lista, debería ocurrir un error debido al cliente duplicado
        REQUIRE_THROWS(LlenarListaClientes(archivo, contador, listaClientes));

        archivo.close();
        delete [] listaClientes;
    }
}
TEST_CASE("LlenarListaClientes")
{
    SECTION("LLena correctamente")
    {
        //Abro el archivo en formato escritura
        ofstream archivoPrueba("archivo_prueba_clases.txt");
        archivoPrueba << "1,Yoga,10.0\n";
        archivoPrueba << "2,Pilates,14.0\n";
        archivoPrueba << "3,Spinning,18.0\n";
        archivoPrueba.close();

        //Abro el archivo en formato lectura
        ifstream archivo("archivo_prueba_clases.txt");

        REQUIRE(archivo.is_open());
        int contador = 3;
        sClase* listaClases = new sClase[contador];
        REQUIRE(listaClases != nullptr);

        LlenarListaClases(archivo, contador, listaClases);

        archivo.close();

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
        ofstream archivoPrueba("archivo_prueba_clases.txt");
        archivoPrueba << "1,Yoga\n";  // Falta el último valor (hora)
        archivoPrueba << "2,Pilates,14:30\n";
        archivoPrueba << "3,Spinning,18:45\n";
        archivoPrueba.close();

        //Abro el archivo en formato lectura
        ifstream archivo("archivo_prueba_clases.txt");

        REQUIRE(archivo.is_open());
        int contador = 3;
        sClase* listaClases = new sClase[contador];
        REQUIRE(listaClases != nullptr);

        REQUIRE_THROWS(LlenarListaClases(archivo, contador, listaClases));

        archivo.close();

        delete[] listaClases;
    }
}

TEST_CASE("EscribirArchivoBinario")
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

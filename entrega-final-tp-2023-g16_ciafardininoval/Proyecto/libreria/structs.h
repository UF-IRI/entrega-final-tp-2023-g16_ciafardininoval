#ifndef STRUCTS_H
#define STRUCTS_H
#include "encabezados.h"
using namespace std;

enum eCupo{ spinning_c = 45, yoga_c = 25, pilates_c = 15, stretching_c = 40, zumba_c = 50, boxeo_c = 30, musuclacion_c = 30,ninguno_c=0};
enum eSala{ spinning_s = 1, yoga_s = 2, pilates_s = 3, stretching_s = 4, zumba_s = 5, boxeo_s = 6, musculacion_s = 7,ninguna_s=0};

struct Clase{
    int id;
    str tipo;
    float hora;
    eSala sala;
    eCupo cupo;
    int inscriptos;
};typedef struct Clase sClase;

struct Cliente{
    str nombre;
    str apellido;
    int ID;
    str email;
    str telefono;
    str fechaNac;
    bool pagoAlDia;
    float pago;
    int cantClases;
    sClase claseActual;
    sClase clases[5];
};typedef struct Cliente sCliente;

struct CursosInscriptos{
    int idCurso;
    int FechaInscripcion;
};typedef struct CursosInscriptos sCursosInscriptos;

struct Asistencias{
    int idCliente;
    int cantInscriptos;
    CursosInscriptos cursosInscriptos[5];
};typedef struct Asistencias sAsistencias;


#endif // STRUCTS_H

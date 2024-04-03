#include "Estudiante.h"

using namespace std;


Estudiante::Estudiante(string nombre, int edad, string carrera, string institucion) : Asistente(nombre,edad) {
    this->carrera = carrera;
    this->institucion = institucion;
}

Estudiante::~Estudiante(){}

string &Estudiante::mostrarInformacion()
{
    string informacion = "Nombre: "+nombre+", edad: "+to_string(edad)+" años. Estudiante de "+carrera+ "en "+institucion; 
    return informacion;
}
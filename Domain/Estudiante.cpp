#include "Estudiante.h"
using namespace std;


Estudiante::Estudiante(string nombre, string dni, int edad, string carrera, string institucion) : Persona(nombre, dni, edad) {
    this->carrera = carrera;
    this->institucion = institucion;
}

Estudiante::~Estudiante(){}

string Estudiante::mostrarInformacion()
{
    return "Nombre: "+nombre+", edad: "+to_string(edad)+" años. Estudiante de "+carrera+" en "+institucion; 
}

string Estudiante::getAtributoDiferencial1()
{
    return carrera;
}

string Estudiante::getTipo()
{
    return "Estudiante";
}

int Estudiante::getEdad() {
    return edad;
}

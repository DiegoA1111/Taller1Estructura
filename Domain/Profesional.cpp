#include "Profesional.h"

using namespace std;


Profesional::Profesional(string nombre, string dni ,int edad, string ocupacion, string empresa) : Persona(nombre, dni, edad) {
    this->ocupacion = ocupacion;
    this->empresa = empresa;
}

Profesional::~Profesional(){}

string Profesional::mostrarInformacion()
{
   return "Nombre: "+nombre+", edad: "+to_string(edad)+" años. Ocupación: "+ocupacion+ " en "+empresa; 
}
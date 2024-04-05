#include "Persona.h"

using namespace std;

Persona::Persona(string nombre, string dni, int edad){
    this->nombre = nombre;
    this->dni = dni;
    this->edad = edad;
}

Persona::~Persona(){}

string Persona::getDni()
{
    return dni;
}
string Persona::getNombre(){
    return nombre;
}


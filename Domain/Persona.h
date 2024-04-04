#pragma once
#include <iostream>

using namespace std;

class Persona{
    protected:
    string nombre, dni;
    int edad;

    public:
    Persona(string, string, int);
    ~Persona();
    virtual string mostrarInformacion() = 0;
    string getDni();
    string getNombre();
};
#pragma once
#include <iostream>
#include "Persona.h"

using namespace std;

class Profesional : public Persona{
    private:
    string ocupacion;
    string empresa;
    public:
    Profesional(string, int, string, string);
    ~Profesional();
    string mostrarInformacion();

};
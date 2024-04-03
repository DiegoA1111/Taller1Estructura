#pragma once
#include <iostream>
#include "Asistente.h"

using namespace std;

class Profesional : public Asistente{
    private:
    string ocupacion;
    string empresa;
    public:
    Profesional(string, int, string, string);
    ~Profesional();
    string mostrarInformacion();

};
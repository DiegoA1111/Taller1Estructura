#pragma once
#include <iostream>
#include "Asistente.h"

using namespace std;

class Estudiante : public Asistente{
    private:
    string carrera;
    string institucion;
    public:
    Estudiante(string, int, string, string);
    ~Estudiante();
    string mostrarInformacion();

};
#pragma once
#include <iostream>
#include "Persona.h"

using namespace std;

class Estudiante : public Persona{
    private:
    string carrera;
    string institucion;
    public:
    Estudiante(string, string, int, string, string);
    ~Estudiante();
    string mostrarInformacion();
    string getAtributoDiferencial1() override;
    string getCarrera();
    string getTipo() override;
    int getEdad() override;


};
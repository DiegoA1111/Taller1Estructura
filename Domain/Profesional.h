#pragma once
#include <iostream>
#include "Persona.h"

using namespace std;

class Profesional : public Persona{
    private:
    string ocupacion;
    string empresa;
    public:
    Profesional(string, string, int, string, string);
    ~Profesional();
    string mostrarInformacion();
    string getOcupacion();
    string getAtributoDiferencial1() override;
    string getTipo() override;
    int getEdad() override;

};
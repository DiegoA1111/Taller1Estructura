#pragma once
#include <iostream>
#include <vector>
#include "Persona.h"

using namespace std;

class Evento{
    protected:
    string ubicacion, id;
    int duracion, capacidad;
    vector<Persona*> listadoAsistentes;
    public:
    Evento(string id,string ubicacion, int duracion, int capacidad);
    ~Evento();
    virtual string mostrarInformacion() = 0;
    string getId();

};
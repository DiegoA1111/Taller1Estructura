#pragma once
#include <iostream>
#include <vector>
#include "Asistente.h"

using namespace std;

class Evento{
    protected:
    string ubicacion;
    int duracion, capacidad;
    vector<Asistente*> listadoAsistentes;
    public:
    Evento(string, int, int);
    ~Evento();

};
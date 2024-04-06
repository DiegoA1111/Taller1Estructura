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
    virtual string getTipo() = 0;
    virtual string mostrarInformacion() = 0;
    int getCantidadAsistentes();
    int obtenerPromedioAsistentes();
    int obtenerPorcentajeAsistencia();
    string mostrarInformacionAsistentes();
    string getId();
    bool agregarAsistente(Persona *persona);

};
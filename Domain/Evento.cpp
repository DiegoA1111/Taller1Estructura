#include "Evento.h"

Evento::Evento(string id, string ubicacion, int duracion, int capacidad) {
    this->id = id;
    this->ubicacion = ubicacion;
    this->duracion = duracion;
    this->capacidad = capacidad;
    listadoAsistentes = vector<Persona*>();
}

Evento::~Evento(){}

string Evento::getId()
{
    return id;
}

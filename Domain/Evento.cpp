#include "Evento.h"

Evento::Evento(string ubicacion, int duracion, int capacidad) {
    this->ubicacion = ubicacion;
    this->duracion = duracion;
    this->capacidad = capacidad;
    listadoAsistentes = vector<Asistente*>();
}

Evento::~Evento(){}
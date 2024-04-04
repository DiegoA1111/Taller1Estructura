#include "Conferencia.h"

Conferencia::Conferencia(string id, string ubicacion, int duracion, int capacidad, string orador, string tema) 
: Evento(id,ubicacion,duracion,capacidad){
    this->orador = orador;
    this->tema = tema;
}

string Conferencia::mostrarInformacion()
{
    return "Conferencia | Orador: "+ orador + "Tema: " +tema;
}
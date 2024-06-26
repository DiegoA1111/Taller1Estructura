#include "Conferencia.h"

Conferencia::Conferencia(string id, string ubicacion, int duracion, int capacidad, string orador, string tema) 
: Evento(id,ubicacion,duracion,capacidad){
    this->orador = orador;
    this->tema = tema;
}

string Conferencia::mostrarInformacion()
{
    return "[Conferencia] Id evento: "+id+" Orador: "+orador+", duración del evento: "+to_string(duracion)+" minutos. Tema: "+ tema +" ubicación: "+ubicacion;
}

string Conferencia::getTipo()
{
    return "Conferencia";
}

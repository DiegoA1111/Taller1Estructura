#include "Evento.h"
#include "Concierto.h"

Concierto::Concierto(string id, string ubicacion, int duracion, int capacidad, string artista) 
: Evento(id,ubicacion,duracion,capacidad) {
    this->artista = artista;
}

Concierto::~Concierto(){}

string Concierto::mostrarInformacion()  {
    return "Concierto | Artista invitado: " + artista;
}
    
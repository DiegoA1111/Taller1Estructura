#include "Evento.h"

Evento::Evento(string id, string ubicacion, int duracion, int capacidad) {
    this->id = id;
    this->ubicacion = ubicacion;
    this->duracion = duracion;
    this->capacidad = capacidad;
    listadoAsistentes = vector<Persona*>();
}

Evento::~Evento(){}

int Evento::getCantidadAsistentes() {
    return listadoAsistentes.size();
}

int Evento::obtenerPromedioAsistentes() {    
    return getCantidadAsistentes()/capacidad;
}

int Evento::obtenerPorcentajeAsistencia()
{
    return obtenerPromedioAsistentes()*100;
}

string Evento::mostrarInformacionAsistentes()
{
    string cadena;
    if(listadoAsistentes.size() > 0){
        for(int i = 0; i < listadoAsistentes.size(); i++){
            Persona *persona = listadoAsistentes[i];
            cadena += "    " + persona->mostrarInformacion() + "\n";
        }
    } else{ cadena = "    No hay asistentes."; }
    return cadena;
}

string Evento::getId()
{
    return id;
}

bool Evento::agregarAsistente(Persona *persona) {
    if(listadoAsistentes.size() < capacidad) { listadoAsistentes.push_back(persona); return true; }
    return false;
}

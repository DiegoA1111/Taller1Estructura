#pragma once
#include "Evento.h"
#include <iostream>
using namespace std;

class Concierto : public Evento{
    private:
    string artista;
    public:
    Concierto(string, string, int, int, string );
    ~Concierto();
    string mostrarInformacion();
};
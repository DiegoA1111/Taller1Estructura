#pragma once
#include <iostream>

using namespace std;

class Asistente{
    protected:
    string nombre;
    int edad;

    public:
    Asistente(string, int);
    ~Asistente();
    virtual string& mostrarInformacion() = 0;
};
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include "../Domain/Evento.h"
//#include "../Domain/Concierto.h"
//#include "../Domain/Conferencia.h"
#include "../Domain/Asistente.h"
#include "../Domain/Estudiante.h"
#include "../Domain/Profesional.h"


using namespace std;

vector <Evento*> listadoEventos = vector <Evento*>();
vector <Asistente*> listadoAsistentes = vector <Asistente*>();

string toLowerCase(string& cadenaInicial){
    string cadenaFinal;
    for(char c: cadenaInicial){ cadenaFinal += tolower(c); }
    return cadenaFinal;
}

bool verificarArchivos(string rutaTxt, string ruta2Txt){
    ifstream file(rutaTxt);
    ifstream file2(ruta2Txt);

    if(!file.is_open() || !file2.is_open()){
        if(!file.is_open() && file2.is_open()){ file2.close(); }
        else if(file.is_open() && !file2.is_open()){ file.close(); }
        //cout<<"Archivo no encontrado"<<endl;
        return false;
    } else{
        return true;
    }

}

void leerArchivo1(string rutaTxt){
    ifstream file(rutaTxt);
}

void leerArchivo2(string rutaTxt){
    ifstream file(rutaTxt);
    string line;
    while(getline(file,line)){
        vector <string> partes;
        stringstream ss(line);
        string parte;

        while(getline(ss,parte,'/')){
            partes.push_back(parte);
        }
        string tipo = partes[0];
        string nombre = partes[1];
        int edad = stoi(partes[2]);

        if(toLowerCase(tipo) == "estudiante"){
            cout<<"Es estudiante" <<endl;
            string carrera = partes[3];
            string institucion = partes[4];
            listadoAsistentes.push_back(new Estudiante(nombre,edad,carrera,institucion));

        } else if(toLowerCase(tipo) == "profesional"){
            cout<<"Es profesional"<<endl;
            string ocupacion = partes[3];
            string empresa = partes[4];
            listadoAsistentes.push_back(new Profesional(nombre,edad,ocupacion,empresa));

        }    
    }
}


int main(int argc, char const *argv[])
{   
    bool status = verificarArchivos("../../Data/eventos.txt","../../Data/asistentes.txt");
    if(status != false){
        //leerArchivo1("../../Data/eventos.txt");
        leerArchivo2("../../Data/asistentes.txt");
        for(size_t i = 0; i < listadoAsistentes.size(); ++i){
            Asistente* asistenteActual = listadoAsistentes[i];
            asistenteActual->mostrarInformacion();
        }
    
    
    
    
    } else { cout << "[!] Archivo(s) no encontrado(s), revise la ruta especificada e intente nuevamente." << endl; }
    
    return 0;
}

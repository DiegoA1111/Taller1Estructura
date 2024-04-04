#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include "../Domain/Evento.h"
#include "../Domain/Asistente.h"
#include "../Domain/Estudiante.h"
#include "../Domain/Profesional.h"
#include "../Domain/Concierto.h"

using namespace std;


vector <Evento*> listadoEventos = vector <Evento*>();
vector <Asistente*> listadoAsistentes = vector <Asistente*>();

string toLowerCase(string& cadenaInicial){
    string cadenaFinal;
    for(char c: cadenaInicial){ cadenaFinal += tolower(c); }
    return cadenaFinal;
}

bool existeEvento(string idEvento){
    for(int i = 0; i < listadoEventos.size(); i++){
        Evento *evento = listadoEventos[i]; string idObjeto = evento->getId();
        if(toLowerCase(idObjeto) == toLowerCase(idEvento)){ return true; }
    }
    return false;
}

bool crearEvento(){
    cout << "Indique tipo de evento (Concierto/Conferencia)"<<endl;
    string tipo; getline(cin,tipo);
    if(toLowerCase(tipo) == "concierto"){
        string id, ubicacion, artista; int duracion, capacidad;
        cout << "Ingrese un id único para el evento: "<<endl; getline(cin,id);
        if(existeEvento(id)){
            cout << "[!] Un evento con esa ID ya existe."<<endl;
            
        } else{
            cout << "Ingrese el nombre del/la artista o banda: " <<endl; getline(cin,artista);
            cout << "Ingrese ubicación del evento: " << endl; getline(cin,ubicacion);
            cout << "Ingrese la duración en minutos del evento: " <<endl; cin>>duracion;
            cout << "Ingrese la capacidad de asistentes del evento: " <<endl; cin>>capacidad;
            Evento *evento = new Concierto(id,ubicacion,duracion,capacidad,artista); 
            listadoEventos.push_back(evento);
            return true;
        }

    } else if(toLowerCase(tipo) == "conferencia"){
        
        return true;
    }
    return false;
}

void menuPrincipal(){
    cout << "Bienvenido al menú de Gestión de Eventos" << endl;
    cout <<"Por favor, ingrese una de las siguientes opciones: "<<endl; int opcion;
    cout << "1) Crear nuevo evento \n2) Registrar asistente \n3) Consultar listado de asistentes \n4) Generar informes"<<endl;
    do {
        cin>>opcion;
        switch (opcion)
        {
        case 1:
            crearEvento(); break;
        case 2:
            break;
        default:
            break;
        }

    } while (opcion != 0);
    

}


bool verificarArchivos(string rutaTxt, string ruta2Txt){
    ifstream file(rutaTxt);
    ifstream file2(ruta2Txt);
    cout<<"Entré aqui"<<endl;

    if(!file.is_open() || !file2.is_open()){
        if(!file.is_open() && file2.is_open()){ file2.close(); }
        else if(file.is_open() && !file2.is_open()){ file.close(); }
        return false;
    } else{
        //cout << "[i] Ambos archivos han sido encontrados" <<endl;
        return true;
    }

}

void leerArchivo1(string rutaTxt){
    ifstream file(rutaTxt);
    string line;
    while(getline(file,line)){
        vector <string> partes;
        stringstream ss(line);
        string parte;

        while(getline(ss,parte,'/')){
            partes.push_back(parte);
        }
    }
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
            Asistente *estudiante = new Estudiante(nombre,edad,carrera,institucion);
            listadoAsistentes.push_back(estudiante);
            listadoAsistentes.push_back(new Estudiante(nombre,edad,carrera,institucion));

        } else if(toLowerCase(tipo) == "profesional"){
            cout<<"Es profesional"<<endl;
            string ocupacion = partes[3];
            string empresa = partes[4];
            Asistente *profesional = new Profesional(nombre,edad,ocupacion,empresa);
            listadoAsistentes.push_back(profesional);
            listadoAsistentes.push_back(new Profesional(nombre,edad,ocupacion,empresa));
        }    
    }
}


int main(int argc, char const *argv[]) {  
    bool status = verificarArchivos("Data/eventos.txt","Data/asistentes.txt");
    if(status != false){
        //leerArchivo1("eventos.txt");
        leerArchivo2("asistentes.txt");
        for(size_t i = 0; i < listadoAsistentes.size(); ++i){
            Asistente *asistenteActual = listadoAsistentes[i];
            cout << asistenteActual->mostrarInformacion() << endl;
        } 
        menuPrincipal();

        //Evento *e = new Concierto("Movistar Arena",25,10);
        //cout << "evento creado"<< endl;
        //delete e;
    
    } else { cout << "[!] Archivo(s) no encontrado(s), revise la ruta especificada e intente nuevamente." << endl; }
    


    return 0;
}

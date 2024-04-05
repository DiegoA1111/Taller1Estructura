#include <iostream>
#include <fstream>
#include <string>
#include <limits>
#include <sstream>
#include <vector>
#include "../Domain/Evento.h"
#include "../Domain/Concierto.h"
#include "../Domain/Conferencia.h"
#include "../Domain/Persona.h"
#include "../Domain/Estudiante.h"
#include "../Domain/Profesional.h"

using namespace std;


vector <Evento*> listadoEventos = vector <Evento*>();
vector <Persona*> listadoAsistentes = vector <Persona*>();

string toLowerCase(string& cadenaInicial){
    string cadenaFinal;
    for(char c: cadenaInicial){ cadenaFinal += tolower(c); }
    return cadenaFinal;
}

void mostrarListadoEventos(){
    cout << " --- Listado de Eventos del Sistema --- "<<endl;
    for(int i = 0; i < listadoEventos.size(); i++){
        Evento *evento = listadoEventos[i];
        cout <<" "<< i+1 << ") " << evento->mostrarInformacion() << " | Id: "<<evento->getId()<< endl;
    }
}

void mostrarListadoPersonas(){
    cout << " --- Listado de Personas del Sistema --- "<<endl;
    for(int i = 0; i < listadoAsistentes.size(); i++){
        Persona *persona = listadoAsistentes[i];
        cout <<" "<< i+1 << ") " << persona->mostrarInformacion() << " | Id: "<<persona->getDni()<< endl;
    }
}

bool existeEvento(string idBuscado){
    for(int i = 0; i < listadoEventos.size(); i++){
        Evento *evento = listadoEventos[i]; string idEvento = evento->getId();
        if(toLowerCase(idEvento) == toLowerCase(idBuscado)){ return true; }
    }
    return false;
}

Persona* buscarPersona(string dniBuscado){
    for(int i = 0; i < listadoAsistentes.size(); i++){
        Persona *persona = listadoAsistentes[i]; string dniPersona = persona->getDni();
        if(toLowerCase(dniPersona) == toLowerCase(dniBuscado)){ return persona; }
    }
    return nullptr;
}

Evento* buscarEvento(string idBuscado){
    for(int i = 0; i < listadoEventos.size(); i++){
        Evento *evento = listadoEventos[i]; string idEvento = evento->getId();
        if(toLowerCase(idBuscado) == toLowerCase(idEvento)){ return evento; }
    }
    return nullptr;
}


bool registrarAsistente(){
    cout<< "Para registrar un asistente a evento, por favor ingrese DNI: " << endl; string dni; getline(cin,dni);
    Persona *persona = buscarPersona(dni);
    if(persona != nullptr){
        cout << "Persona identificada. Nombre: " << persona->getNombre() <<endl;
        if(listadoEventos.size() > 0){
            mostrarListadoEventos();
            cout << "Indique el número del Evento de la lista para asignación de asistente (desde 1 hasta N): "<<endl;
            int indice; cin>> indice; Evento *evento = listadoEventos.at(indice-1); if(evento->agregarAsistente(persona)){return true;}
        }
    } else{
        string ans;
        cout << "[i] Persona no registrada. ¿Desea ingresarla al sistema? (SI/NO): "<< endl; getline(cin,ans);
        if(toLowerCase(ans) == "si"){
            cout << "Indique tipo (Estudiante ó Profesional): "<<endl; string tipo; getline(cin, tipo);
            cout << "Ingrese nombre: "<<endl; string nombre; getline(cin,nombre);
            cout << "Ingrese edad: "<<endl; int edad; cin>>edad;
            if(toLowerCase(tipo) == "estudiante"){
                cout << "Indique que carrera estudia: "<<endl; string carrera; getline(cin,carrera);
                cout << "Indique la institución donde estudia: "<<endl; string institucion; getline(cin,institucion);
                Persona *persona = new Estudiante(nombre,dni,edad,carrera,institucion);
                if(listadoEventos.size() > 0){
                mostrarListadoEventos(); cout << "Indique el número del Evento de la lista para asignación de asistente (Ej: 1): "<<endl;
                int indice; cin>> indice; Evento *evento = listadoEventos.at(indice-1); if(evento->agregarAsistente(persona)){return true;}
                }
            } else if(toLowerCase(tipo) == "profesional"){
                cout << "Indique su ocupación: "<<endl; string ocupacion; getline(cin,ocupacion);
                cout << "Indique la empresa/corporación donde trabaja: "<<endl; string empresa; getline(cin,empresa);
                Persona *persona = new Profesional(nombre,dni,edad,ocupacion,empresa);
                if(listadoEventos.size() > 0){
                mostrarListadoEventos(); cout << "Indique el número del Evento de la lista para asignación de asistente (Ej: 1): "<<endl;
                int indice; cin>> indice; Evento *evento = listadoEventos.at(indice-1); if(evento->agregarAsistente(persona)){return true;}
                }
            }
        }
    }
    return false;
}

bool crearEvento(){
    cout << "Indique tipo de evento (Concierto/Conferencia): "; string tipo;
    getline(cin,tipo);
    cout << "Ingrese un id único para el evento: "<<endl; string id; getline(cin,id);
    if(existeEvento(id)){
        cout << "[!] Un evento con esa ID ya existe."<<endl;
    } else{
        string ubicacion; int duracion, capacidad;
        cout << "Ingrese ubicación del evento: " << endl; getline(cin,ubicacion);
        cout << "Ingrese la duración en minutos del evento: " <<endl; cin>>duracion;
        cin.ignore();
        cout << "Ingrese la capacidad de asistentes del evento: " <<endl; cin>>capacidad;
        cin.ignore();

        if(toLowerCase(tipo) == "concierto"){ string artista;
            cout << "Ingrese el nombre del/la artista o banda: " <<endl; getline(cin,artista);
            Evento *evento = new Concierto(id,ubicacion,duracion,capacidad,artista); 
            listadoEventos.push_back(evento); return true;

        } else if(toLowerCase(tipo) == "conferencia"){
            string orador, tema;
            cout << "Ingrese el nombre del/la orador(a): " <<endl; getline(cin,orador);
            cout << "Ingrese el tema del evento: " << endl; getline(cin,tema);
            Evento *evento = new Conferencia(id,ubicacion,duracion,capacidad,orador,tema);
            listadoEventos.push_back(evento); return true;
        }
    }        
    return false;
}

void infListaAsistentes(){
    if(listadoEventos.size()>0){
        cout << "Ingrese nombre del archivo .txt: "<<endl; 
        cout<< "[i] Tenga en cuenta que si escribe el nombre de un archivo existente, se sobrescribirá."<<endl;
        cout << "Nombre del archivo (escriba sin '.txt'): "; string fileName; getline(cin,fileName);
        ofstream archivo("Informes/"+fileName+".txt");
        if(archivo.is_open()){
            for(int i = 0; i < listadoEventos.size(); i++){
                Evento *evento = listadoEventos[i];
                archivo << to_string(i+1) << ") " << evento->mostrarInformacion() << "\n";
                string infoAsistentes = evento->mostrarInformacionAsistentes();
                archivo << infoAsistentes << "\n";
            }
            archivo.close();
        } else{
            cout << "[!] Hubo un error al intentar generar el informe. Revise los datos ingresados."<<endl;
        }
    }
}

void infListaEventos(){
    if(listadoEventos.size()>0){
        cout << "Ingrese nombre del archivo .txt: "<<endl; 
        cout<< "[i] Tenga en cuenta que si escribe el nombre de un archivo existente, se sobrescribirá."<<endl;
        cout << "Nombre del archivo (escriba sin '.txt'): "; string fileName; getline(cin,fileName);
        ofstream archivo("Informes/"+fileName+".txt");
        if(archivo.is_open()){
            for(int i = 0; i < listadoEventos.size(); i++){
                Evento *evento = listadoEventos[i];
                archivo << to_string(i+1) << ") " << evento->mostrarInformacion() << "\n";
            }
            archivo.close();
        }
    } else{
        cout <<"[!] Hubo un error al intentar generar el informe. Revise los datos ingresados."<<endl;
    }
}

void infEventoParticular(){
    if(listadoEventos.size()>0){
        cout << "Indique el número del siguiente listado de eventos (desde 1 a N): "<<endl; int posicion;
        mostrarListadoEventos(); cout << "Posicion: "; cin>>posicion;
        Evento *evento = listadoEventos[posicion-1]; evento->mostrarInformacion();

    }
    
}

void submenuInformes(){
    cout << " --- Generar Informes --- " << endl; int opcion;
    cout <<"Por favor, ingrese una de las siguientes opciones (Para finalizar digite '0'): "<<endl;
    cout << "1) Informe de listado de eventos \n2) Informe de listado de asistentes por cada evento \n3) Informe estadísticas de asistencia"<<endl;
    cout << "4) Informe de detalle de asistentes \n5) Informe sobre evento en particular"<<endl;
    cout << "Opción: "; cin >> opcion; cin.ignore();
    switch(opcion){
        case 1:
            infListaEventos();
            break;
        case 2:
            infListaAsistentes();
            break;
        case 3:
            //infEstadisticasAsist();
            break;
        case 4:
            //infDetalleAsist();
            break;
        case 5:
            infEventoParticular();
            break;
    
    }

}

void menuPrincipal(){
    int opcion;
    do {
        cout << "Bienvenido al menú de Gestión de Eventos" << endl;
        cout <<"Por favor, ingrese una de las siguientes opciones (Para finalizar digite '0'): "<<endl;
        cout << "1) Crear nuevo evento \n2) Registrar asistente \n3) Consultar listado de ASISTENTES \n4) Revisar listado de EVENTOS \n5) Generar informes"<<endl;
        cout << "Opción: ";
        cin>>opcion; cin.ignore();
        switch (opcion)
        {
        case 1:
            if(crearEvento()){ cout << "[i] Evento creado exitosamente."<<endl; } 
            break;
        case 2:
            if(registrarAsistente()){cout << "[i] Asistente agregado exitosamente."; }
            else{cout << "[!] No se pudo registrar asistente. "<<endl; } break;
        case 3:
            break;
        case 4:
            mostrarListadoEventos();
            break;
        case 5:
            submenuInformes();
            break;
        }

    } while (opcion != 0);
}

bool verificarArchivos(string rutaTxt, string ruta2Txt, string ruta3Txt){
    ifstream file(rutaTxt);
    ifstream file2(ruta2Txt);
    ifstream file3(ruta3Txt);

    if(!file.is_open() || !file2.is_open() || !file3.is_open()){
        //if(!file.is_open() && file2.is_open()){ file2.close(); }
        //else if(file.is_open() && !file2.is_open()){ file.close(); }
        file.close(); file2.close(); file3.close();
        return false;
    }
    return true;
}

void leerArchivoEventos(string rutaTxt){
    ifstream file(rutaTxt);
    string line;

    while(getline(file,line)){
        vector <string> partes;
        stringstream ss(line);
        string parte;

        while(getline(ss,parte,'/')){
            partes.push_back(parte);
        }

        string id = partes[0]; string tipo = partes[1]; string ubicacion = partes[2];
        int duracion = stoi(partes[3]); int capacidad = stoi(partes[4]);
        if(toLowerCase(tipo) == "concierto") {
            string artista = partes[5];
            Evento *evento = new Concierto(id,ubicacion,duracion,capacidad,artista);
            listadoEventos.push_back(evento);
        } else if(toLowerCase(tipo) == "conferencia") {
            string orador = partes[5]; string tema = partes[6];
            Evento *evento = new Conferencia(id,ubicacion,duracion,capacidad,orador,tema);
            listadoEventos.push_back(evento);
        }
    }
}

void leerArchivoAsistentes(string rutaTxt){
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
        string dni = partes[2];
        int edad = stoi(partes[3]);

        if(toLowerCase(tipo) == "estudiante"){
            string carrera = partes[4];
            string institucion = partes[5];
            Persona *estudiante = new Estudiante(nombre,dni,edad,carrera,institucion);
            listadoAsistentes.push_back(estudiante);

        } else if(toLowerCase(tipo) == "profesional"){
            string ocupacion = partes[4];
            string empresa = partes[5];
            Persona *profesional = new Profesional(nombre,dni,edad,ocupacion,empresa);
            listadoAsistentes.push_back(profesional);
        }    
    }
}

void leerArchivoAsistencia(string rutaTxt){
    ifstream file(rutaTxt);
    string line;
    while(getline(file,line)){
        vector <string> partes;
        stringstream ss(line);
        string parte;

        while(getline(ss,parte,'/')){
            partes.push_back(parte);
        }

        string id = partes[0]; Evento *evento = buscarEvento(id);
        if(evento != nullptr){
            for(int i = 1; i < partes.size(); i++){
                string dni = partes[i]; Persona *persona = buscarPersona(dni);
                if(persona != nullptr){
                    evento->agregarAsistente(persona);
                }
            }
        }
    }
}

int main(int argc, char const *argv[]) {  
    bool status = verificarArchivos("Data/eventos.txt","Data/asistentes.txt","Data/listadoAsistencia.txt");
    if(status != false){
        leerArchivoEventos("Data/eventos.txt");
        leerArchivoAsistentes("Data/asistentes.txt");
        leerArchivoAsistencia("Data/listadoAsistencia.txt");
        //mostrarListadoPersonas();
        menuPrincipal();
    
    } else { cout << "[!] Archivo(s) no encontrado(s), revise la ruta especificada e intente nuevamente." << endl; }
    
    return 0;
}

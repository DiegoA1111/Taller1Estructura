#include <iostream>
#include <fstream>
#include <string>
#include <limits>
#include <algorithm>
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

void destruirObjetos(){
    for(int j = 0; j < listadoAsistentes.size(); j++){
        Persona *persona = listadoAsistentes[j]; delete persona;
    }
    for(int i = 0; i < listadoEventos.size(); i++){
        Evento *evento = listadoEventos[i]; delete evento;
    }
}

string toLowerCase(string& cadenaInicial){
    string cadenaFinal;
    for(char c: cadenaInicial){ cadenaFinal += tolower(c); }
    return cadenaFinal;
}

vector<string> split(const string& linea, char separador) {
    vector<string> partes;
    stringstream ss(linea);
    string parte;
    while (getline(ss, parte, separador)) {
        partes.push_back(parte);
    }
    return partes;
}

void mostrarListadoEventos(){
    cout << " --- Listado de Eventos del Sistema --- "<<endl;
    for(int i = 0; i < listadoEventos.size(); i++){
        Evento *evento = listadoEventos[i];
        cout <<" "<< i+1 << ") " << evento->mostrarInformacion() << endl;
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

void obtenerFrecuenciaX(){
    vector<string> nombres = {"Ingeniero","Medico","Abogado","Ingenerio","Psicologo","Ingeniero","Medico"};
    vector<int> frecuencias(nombres.size(),0);
        vector<string> unicos;

   for (string nombre : nombres) {
        vector<string>::iterator iterador = find(unicos.begin(), unicos.end(), nombre);

        if (iterador == unicos.end()) {
            unicos.push_back(nombre);
            frecuencias[unicos.size() - 1]++;
        } else {
            int index = distance(unicos.begin(), iterador);
            frecuencias[index]++;
        }
    }
}

bool registrarAsistente(){
    cout<< "Para registrar un asistente a evento, por favor ingrese DNI: " << endl; string dni; getline(cin,dni);
    Persona *persona = buscarPersona(dni);
    if(persona != nullptr){
        cout << "Persona identificada. Nombre: " << persona->getNombre() <<endl;
        if(listadoEventos.size() > 0){
            mostrarListadoEventos();
            cout << "Indique el número del Evento de la lista para asignación de asistente (desde 1 hasta N): "<<endl;
            int indice; cin>> indice; 
            while(indice <= 0 || indice >= listadoEventos.size()){
                cout << "Indice inválido. Intente nuevamente. " << endl;
                cin >> indice;
            }
            cin.ignore();
            Evento *evento = listadoEventos.at(indice-1); 
            if(evento->agregarAsistente(persona)){
                ifstream inFile("listaAsistencia.txt");
                vector<string> lines;
                if (inFile.is_open()) {
                    string line;
                    while (getline(inFile, line)) {
                        lines.push_back(line);
                    }
                    inFile.close();
                }
                return true;
            }
        }
    } else{
        string ans;
        cout << "[i] Persona no registrada. ¿Desea ingresarla al sistema? (SI/NO): "<< endl; getline(cin,ans);
        if(toLowerCase(ans) == "si"){
            cout << "Indique tipo (Estudiante ó Profesional): "<<endl; string tipo; getline(cin, tipo);
            cout << "Ingrese nombre: "<<endl; string nombre; getline(cin,nombre);
            cout << "Ingrese edad: "<<endl; int edad; cin>>edad; cin.ignore();
            if(toLowerCase(tipo) == "estudiante"){
                cout << "Indique que carrera estudia: "<<endl; string carrera; getline(cin,carrera);
                cout << "Indique la institución donde estudia: "<<endl; string institucion; getline(cin,institucion);
                Persona *persona = new Estudiante(nombre,dni,edad,carrera,institucion);
                if(listadoEventos.size() > 0){
                mostrarListadoEventos(); cout << "Indique el número del Evento de la lista para asignación de asistente (Ej: 1): "<<endl;
                int indice; cin>> indice; 
                while(indice <= 0 || indice >= listadoEventos.size()){
                    cout << "Indice inválido. Intente nuevamente. " << endl;
                    cin >> indice;
                }
                cin.ignore();
                Evento *evento = listadoEventos.at(indice-1); if(evento->agregarAsistente(persona)){
                    cout << "[i] Asistente agregado con éxito."<<endl; return true;}
                }
            } else if(toLowerCase(tipo) == "profesional"){
                cout << "Indique su ocupación: "<<endl; string ocupacion; getline(cin,ocupacion);
                cout << "Indique la empresa/corporación donde trabaja: "<<endl; string empresa; getline(cin,empresa);
                Persona *persona = new Profesional(nombre,dni,edad,ocupacion,empresa);
                if(listadoEventos.size() > 0){
                mostrarListadoEventos(); cout << "Indique el número del Evento de la lista para asignación de asistente (Ej: 1): "<<endl;
                int indice; cin>> indice; 
                while(indice <= 0 || indice >= listadoEventos.size()){
                    cout << "Indice inválido. Intente nuevamente. " << endl;
                    cin >> indice;
                } 
                cin.ignore();
                Evento *evento = listadoEventos.at(indice-1); if(evento->agregarAsistente(persona)){ 
                    cout << "[i] Asistente agregado con éxito."<<endl; return true;}
                }
            }
        } else{
            cout << "[i] No se efectuaron cambios. "<<endl;
        }
    }
    return false;
}

void registrarAsistenteAEvento() {
    // Mostrar eventos disponibles con sus IDs
    cout << "Seleccione el evento al que desea registrarse:" << endl;
    mostrarListadoEventos();

    // Solicitar al usuario que elija un evento por su ID
    int indexEvento;
    cout << "Ingrese el número correspondiente al evento: ";
    cin >> indexEvento;

    // Validar la entrada del usuario
    if (indexEvento < 0 || indexEvento >= listadoEventos.size()) {
        cout << "Número de evento no válido. Volviendo al menú principal." << endl;
        return;
    }

    // Mostrar información del evento seleccionado
    cout << "Registrándose al siguiente evento:" << endl;
    cout << "ID: " << listadoEventos[indexEvento]->getId() << ", " << listadoEventos[indexEvento]->mostrarInformacion() << endl;

    // Solicitar al usuario que ingrese el DNI del asistente
    string dniAsistente;
    cout << "Ingrese el DNI del asistente que desea registrar: ";
    cin >> dniAsistente;

    Persona* asistente = nullptr;
    for (const auto& p : listadoAsistentes) {
        string dni = p->getDni();
        if (toLowerCase(dni) == toLowerCase(dniAsistente)) {
            asistente = p;
            break;
        }
    }

    if (asistente != nullptr) {
        listadoEventos[indexEvento]->agregarAsistente(asistente);
        cout << "Asistente registrado exitosamente en el evento." << endl;

        ifstream inFile("listaAsistencia.txt");
        vector<string> lines;
        if (inFile.is_open()) {
            string line;
            while (getline(inFile, line)) {
                lines.push_back(line);
            }
            inFile.close();
        }

        bool eventoExistente = false;
        for (string& line : lines) {
            if (line.find(listadoEventos[indexEvento]->getId()) != string::npos) {
                line += "/" + dniAsistente; eventoExistente = true; break;
            }
        }

        if (!eventoExistente) {
            lines.push_back(listadoEventos[indexEvento]->getId() + "/" + dniAsistente);
        }

        ofstream outFile("listaAsistencia.txt");
        if (outFile.is_open()) {
            for (const string& line : lines) {
                outFile << line << endl;
            }
            outFile.close();
            cout << "Registro actualizado en el archivo de lista de asistencia." << endl;
        } else {
            cout << "No se pudo abrir el archivo de lista de asistencia para actualizar el registro." << endl;
        }
    } else {
        cout << "No se encontró ningún asistente con el DNI proporcionado." << endl;
    }
}


bool crearEvento(){
    cout << "Indique tipo de evento (Concierto/Conferencia): "; string tipo;
    getline(cin,tipo);
    if(toLowerCase(tipo) != "concierto" && toLowerCase(tipo) != "conferencia"){
        cout << "[!] Tipo de evento indicado no existe. "<<endl;;
    } else{
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
            Evento *evento = nullptr;

            if(toLowerCase(tipo) == "concierto"){ string artista;
                cout << "Ingrese el nombre del/la artista o banda: " <<endl; getline(cin,artista);
                evento = new Concierto(id,ubicacion,duracion,capacidad,artista);
                listadoEventos.push_back(evento);
                fstream file("Data/eventos.txt", ios::app);                                 
                if(file.is_open()){
                    file <<"\n"<<id<<"/Concierto/"<<ubicacion<<"/"<<to_string(duracion)<<"/"<<to_string(capacidad)<<"/"<<artista;
                    file.close();
                    cout << "[i] Informacion Guardada" << endl;
                } else{
                    cout << "[!] No se puede abrir el archivo. Revise la ruta" << endl;
                }


            } else if(toLowerCase(tipo) == "conferencia"){
                string orador, tema;
                cout << "Ingrese el nombre del/la orador(a): " <<endl; getline(cin,orador);
                cout << "Ingrese el tema del evento: " << endl; getline(cin,tema);
                evento = new Conferencia(id,ubicacion,duracion,capacidad,orador,tema);
                listadoEventos.push_back(evento);
                ofstream file("Data/eventos.txt", ios::app);                                 
                if(file.is_open()){
                    file <<"\n"<<id<<"/Conferencia/"<<ubicacion<<"/"<<to_string(duracion)<<"/"<<to_string(capacidad)<<"/"<<orador<<"/"<<tema;
                    file.close();
                    cout << "[i] Informacion Guardada" << endl;
                } else{
                    cout << "[!] No se puede abrir el archivo. Revise la ruta" << endl;
                }
            }
            return true;
        }  
    }      
    return false;
}

float calcularPromedioEdades(){
    int sumaEdades; int cantidadAsistentes;
    if(cantidadAsistentes > 0){
        for(Persona *persona: listadoAsistentes){ sumaEdades += persona->getEdad(); }
        return sumaEdades/cantidadAsistentes;
    }
    return 0;
}

float calcularPromedioEdades(string tipoEntregado) {
    int totalEdades = 0;
    int cantidad = 0;
    if(listadoAsistentes.size() > 0){
        for (Persona *persona : listadoAsistentes) {
            string type = persona->getTipo();
            if (toLowerCase(type) == toLowerCase(tipoEntregado)) {
                totalEdades += persona->getEdad();
                cantidad++;
           }
        }
        return static_cast<float>(totalEdades)/cantidad;
    }
    return -1;
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
    } else{
        cout << "[!] El listado de Eventos está vacío.";
    }
}

void infEstadisticasAsist(){
    if(listadoEventos.size()>0){
        cout << "Ingrese nombre del archivo .txt: "<<endl; 
        cout<< "[i] Tenga en cuenta que si escribe el nombre de un archivo existente, se sobrescribirá."<<endl;
        cout << "Nombre del archivo (escriba sin '.txt'): "; string fileName; getline(cin,fileName);
        ofstream archivo("Informes/"+fileName+".txt");
        if(archivo.is_open()){
            for(int i = 0; i < listadoEventos.size(); i++){
                Evento *evento = listadoEventos[i];
                archivo << to_string(i+1) << ") " << evento->getTipo() << " Id: "<< evento->getId() << "\n";
                archivo << "    Numero de asistentes: " << evento->getCantidadAsistentes() << "\n";
                archivo << "    Promedio de asistentes: "<< evento->obtenerPromedioAsistentes() << "\n";
                archivo << "    Porcentaje de asistencia: " << evento->obtenerPorcentajeAsistencia() << "% \n";
            }
            archivo.close();
        }
    } else{
        cout <<"[!] Hubo un error al intentar generar el informe. Revise los datos ingresados."<<endl;
    }
}

void infDetalleAsist(){
    if(listadoAsistentes.size() > 0){
        float promedio = calcularPromedioEdades();
        float promedioEdadesEstudiantes = calcularPromedioEdades("Estudiante");
        float promedioEdadesProfesionales = calcularPromedioEdades("Profesional");
        float promedioEdadesGeneral = (promedioEdadesEstudiantes + promedioEdadesProfesionales) /2;
        cout << "Ingrese nombre del archivo .txt: "<<endl; 
        cout<< "[i] Tenga en cuenta que si escribe el nombre de un archivo existente, se sobrescribirá."<<endl;
        cout << "Nombre del archivo (escriba sin '.txt'): "; string fileName; getline(cin,fileName);
        ofstream archivo("Informes/"+fileName+".txt");
        if(archivo.is_open()){
            if(promedioEdadesEstudiantes == -1){ archivo << "No hay asistentes"<<"\n"; }
            else{ 
                archivo << "La edad promedio de todos los asistentes es: "<< promedioEdadesGeneral << "\n";
                if(promedioEdadesEstudiantes == -1 ){ archivo << "No hay estudiantes" << "\n"; }
                else { archivo << "La edad promedio de todos los Estudiantes es: "<< promedioEdadesEstudiantes << "\n"; }
                if(promedioEdadesProfesionales == -1) { archivo << "No hay profesionales" << "\n";}
                else { archivo << "La edad promedio de todos los Profesionales es: "<< promedioEdadesProfesionales << "\n"; }
            }            
            archivo.close();
        } else{
            cout << "[!] Hubo un error al intentar generar el informe. Revise los datos ingresados."<<endl;
        }
    } else{
        cout <<"[!] El listado de asistentes está vacío."<< endl;
    }    
}


void infEventoParticular(){
    if(listadoEventos.size()>0){
        cout << "Indique el número del siguiente listado de eventos (desde 1 a N): "<<endl; int posicion;
        mostrarListadoEventos(); cout << "Posicion: "; cin>>posicion; cin.ignore();
        cout << "Ingrese nombre del archivo .txt: "<<endl; 
        cout<< "[i] Tenga en cuenta que si escribe el nombre de un archivo existente, se sobrescribirá."<<endl;
        cout << "Nombre del archivo (escriba sin '.txt'): "; string fileName; getline(cin,fileName);
        ofstream archivo("Informes/"+fileName+".txt");
        if(archivo.is_open()){
            Evento *evento = listadoEventos[posicion-1]; 
            archivo << evento->mostrarInformacion(); archivo.close();
        } else{
            cout <<"[!] Hubo un error al intentar generar el informe. Revise los datos ingresados."<<endl;
        }
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
            infEstadisticasAsist();
            break;
        case 4:
            infDetalleAsist();
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
        switch (opcion) {
        case 1:
            if(crearEvento()){ cout << "[i] Evento creado exitosamente."<<endl; } 
            break;
        case 2:
            registrarAsistenteAEvento(); break;
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
        file.close(); file2.close(); file3.close();
        return false;
    }
    return true;
}

void leerArchivoEventos(string rutaTxt){
    ifstream file(rutaTxt);
    string line;

    while(getline(file,line)){
        vector <string> partes = split(line,'/');
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
        vector <string> partes = split(line,'/');
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
       vector <string> partes = split(line,'/');
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
        menuPrincipal();
        destruirObjetos();
    
    } else { cout << "[!] Archivo(s) no encontrado(s), revise la ruta especificada e intente nuevamente." << endl; }
    
    return 0;
}

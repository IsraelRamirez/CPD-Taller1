#include <iostream>
#include <cstdlib>
#include <fstream>
#include <ctime>
#include <string>
using namespace std;

void participante();

/**
 * Funcion para tomar un numero aleatorio entre dos valores, min y max.
 * @param min Rango mínimo de entrada
 * @param max Rango máximo de entrada
 * @return Devuelve un número aleatorio entre el rango mínimo de entrada y el de salida
 */
int numeroAleatorio(int min, int max);

/**
 * 
 * @param rut Pide el rut de un alumno
 * @return Devuelve la matrícula de un alumno, con toda la información sobre él; nem, ranking, psu matematica, psu lenguaje, psu ciencias, psu historia
 */
string infoAlumno(int rut);

/**
 * Taller computacional
 * @param argc Cantidad de argumentos ingresados por el usuario
 * @param argv Argumentos ingresados por el usuario
 * @return Retorna el código de error.
 */
int main(int argc, char** argv){
    
    srand((unsigned int)time(0));
    
    // Crea / abre el archivo matricula.csv
    ofstream archivoSalida("matricula.csv");
    
    // La información de todas las matriculas se guardará aqui.
    string TotalMatricula = "";
    
    // Recorre los ruts
    for(int rut = 14916641 ; rut <= 19932391 ; rut++){//ruts entre 14916641 - 19932391
        TotalMatricula += infoAlumno(rut);
    }
    //Ingresa la información al archivo
    archivoSalida << TotalMatricula;
    
    // Cierra el archivo usado
    archivoSalida.close();
    
    participante();
    return EXIT_SUCCESS;
}

void participante(){
    cout<< endl << "=== Tarea ===" <<endl;
    cout<< endl << "Israel Ramirez Cardoso. "<<endl;
}

int numeroAleatorio(int min, int max){
    return rand() % (max-min+1) + min;
}

string infoAlumno(int rut){
    //Guarda el rut de un alumno ingresado por parametro
    string totalInfo = to_string(rut)+";";
    
    
    //Ingresa el NEM del alumno, como numero aleatorio
    totalInfo += to_string(numeroAleatorio(475,750)) +";";
    //Ingresa el Ranking del alumno, como numero aleatorio
    totalInfo += to_string(numeroAleatorio(475,750)) +";";
    //Ingresa el puntaje en Matematicas del alumno, como numero aleatorio
    totalInfo += to_string(numeroAleatorio(475,750)) +";";
    //Ingresa el puntaje en Lenguaje del alumno, como numero aleatorio
    totalInfo += to_string(numeroAleatorio(475,750)) +";";
    //Ingresa el puntaje en Ciencias del alumno, como numero aleatorio
    totalInfo += to_string(numeroAleatorio(475,750)) +";";
    //Ingresa el puntaje en Historia del alumno, como numero aleatorio
    totalInfo += to_string(numeroAleatorio(475,750)) +"\n";
    
    
    return totalInfo;
}
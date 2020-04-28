#include <iostream>
#include <cstdlib>
#include <fstream>
#include <ctime>
#include <string>
#include <math.h>
using namespace std;

void participante();
/**
 * Funcion que lee una cierta linea de datos agrupados y separados por ";" y devuelve el promedio de puntajes
 * @param linea Es la información de un alumno entregada como cadena de caracteres separadas por ";" ej: rut;NEM;Ranking;PSU-Matematica;PSU-Lenguaje;PSU-Historia;PSU-Ciencias
 * @return Devuelve una cadena de caracteres con el rut y el promedio de puntajes separados por ";"
 */
string PromedioAlumno(string linea);
/**
 * Redondea el número con decimal ingresado segun sea el caso
 * @param numero Se ingresa el numero con decimal a redondear
 * @return Devuelve el numero redondeado si el decimal es mayor que 4 y no redondea si es menor o igual que 4
 */
int redondear(float numero);
/**
 * Taller computacional donde se toman los ruts de cada matricula y su saca el promedio de los puntajes, las matriculas se reciben en el archivo matricula.csv y los promedios en el archivo promedio.csv
 * @param argc Cantidad de argumentos ingresados por el usuario
 * @param argv Argumentos ingresados por el usuario
 * @return Retorna el código de error.
 */
int main(int argc, char** argv){
    
    // abre el archivo matricula.csv
    ifstream archivoEntrada("matricula.csv");
    // crea el archivo promedios.csv
    ofstream archivoSalida("promedio.csv");
    // Se crea la variable linea, que guardará la información del archivo correspondiente a una linea
    string linea;
    // Se recorre el archivo hasta el final de archivo (eof)
    while(!archivoEntrada.eof()){
        //Se guarda una línea del archivo en la variable linea
        getline(archivoEntrada, linea);
        //Se verifica que la linea leida no sea el final del archivo
        if(linea!="\0"){
            // Se ejecuta el promedio del alumno y se guarda en el archivo "promedio.csv"
            archivoSalida << PromedioAlumno(linea)<<endl;
        }
    }
    // Cierra los archivos usados
    archivoEntrada.close();
    archivoSalida.close();
    
    participante();
    return EXIT_SUCCESS;
}

void participante(){
    cout<< endl << "=== Tarea ===" <<endl;
    cout<< endl << "Israel Ramirez Cardoso. "<<endl;
}

string PromedioAlumno(string linea){
    /**
    * arregloSplit Es un arreglo que sirve para realizar el "split" de un string separado por ";"
    * posicionArreglo Es la posicion del arregloSplit
    * promedio Es el promedio de los puntajes
    * promedioSuma Es la suma de los puntajes que se llevaran a promedio
    * InfoTemporal Es una variable que almacena el string leido entre cada ";"
    */
    int arregloSplit[7],posicionArreglo=0,promedio;
    float promedioSuma=0;
    string InfoTemporal="";

    // Se recorre la información guarda en linea
    for(int i=0;linea[i]!='\n'&& linea[i]!='\0';i++){
        // Guarda la informacion en InfoTemporal hasta que lea un ";"
        if(linea[i]!=';'){
            InfoTemporal += linea[i];
        }
        // Si se lee un ";" ó lo siguiente en leer es un salto de linea "\n" o el final de algo "\0" se guarda la información en arregloSplit, se resetea la informacion temporal y se avanza en el arreglo
        if(linea[i]==';' || linea[i+1] == '\n' || linea[i+1] == '\0'){
            arregloSplit[posicionArreglo]=stoi(InfoTemporal);
            posicionArreglo++;
            InfoTemporal="";
        }
        
    }
    // Se realiza la suma de los puntajes
    for(int i =1; i<7 ;i++){
        promedioSuma += arregloSplit[i];
        // Si es el último puntaje se saca el promedio
        if(i == 6){
            // Se redonde al promedio
            promedio = redondear(promedioSuma/6);
        }
    }

    return to_string(arregloSplit[0])+";"+to_string(promedio);
}

int redondear(float numero){
    //Verifica si el numero es menor o igual que 4,4 redondea para abajo
    if(numero - floor(numero) < ceil(numero) - numero ){
        return floor(numero);
    }
    //Verifica si el numero es mayor o igual que 4,5 redondea para abajo
    else{
        return ceil(numero);
    }
}


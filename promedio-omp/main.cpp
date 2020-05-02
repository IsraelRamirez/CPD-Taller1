#include <iostream>
#include <cstdlib>
#include <fstream>
#include <ctime>
#include <string>
#include <omp.h>
#include <iomanip>
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
 * Taller computacional donde se toman los ruts de cada matricula y su saca el promedio de los puntajes, las matriculas se reciben en el archivo matricula.csv y los promedios en el archivo promedio.csv
 * @param argc Cantidad de argumentos ingresados por el usuario
 * @param argv Argumentos ingresados por el usuario
 * @return Retorna el código de error.
 */
int main(int argc, char** argv){
    //Comprueba que se ha entregado la ruta del archivo con los datosde los alumnos.
    if(argc > 1){
        // abre el archivo matricula.csv
        ifstream archivoEntrada(argv[1]);
        // crea el archivo promedios.csv
        ofstream archivoSalida("promedio.csv");
        // Se crea la variable linea, que guardará la información del archivo correspondiente a una linea
    
        // Se obtiene el largo en filas del archivo
        archivoEntrada.seekg(0,archivoEntrada.end);
        int largoArchivo = archivoEntrada.tellg() / 33;
        archivoEntrada.seekg(0,archivoEntrada.beg);

        archivoEntrada.close();
        #pragma omp parallel
        {
        #pragma omp for
        for(int i=0;i<=largoArchivo;i++){
            //Se abre el archivo
            ifstream archivoEntrada("matricula.csv");
            //Se coloca el puntero en la linea especificada
            archivoEntrada.seekg(i*33);
            string linea;
            //Se guarda una línea del archivo en la variable linea
            getline(archivoEntrada, linea);
            //Se cierra el archivo
            archivoEntrada.close();
            //Se verifica que la linea leida no sea el final del archivo
            if(linea!="\0"){
                
                string Informacion = PromedioAlumno(linea);
                // Se ejecuta el promedio del alumno y se guarda en el archivo "promedio.csv"
                
                #pragma omp critical
                archivoSalida << Informacion <<endl;
            }
        }
        }
        // Cierra el archivo usado
        archivoSalida.close();
        
        participante();
        return 0;
    }
    else{
        cout<<"ERROR: Se debe ingresar la ruta del archivo con los datos de los alumnos..."<<endl;
        return 1;
    }
}

void participante(){
    cout<< endl << "=== Tarea ===" <<endl;
    cout<< endl << "Israel Ramirez Cardoso. "<<endl;
    cout<< endl << "Humberto Román Matamoros." <<endl;
    cout<< endl << "Victor Araya Romero. "<<endl;
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
            promedio = promedioSuma/6;
        }
    }
    /** Se crean las variables dosDecimales y dosDecimalesSetring
     * dosDecimales es una variable que guardara los dos primeros decimales de un numero
     * dosDecimalesString es una variable que guardara los dos primeros decimales en string
    */

    // Se multiplica por 1000 para guardar los primeros 3 decimales en caso de tener que redondear
    int dosDecimales = (promedioSuma/6)*1000;
    string dosDecimalesString;
    // Se guardan solamente los 3 decimales
    dosDecimales = dosDecimales%1000;
    // Si el tercer decimal es mayor que 4 se suma 1 a los primeros 2 decimales
    if(dosDecimales%10 >4){
        dosDecimales = (dosDecimales/10)+1;
        // Si los dos decimales al sumarlos da mayor que 99 se suma 1 en el promedio
        if(dosDecimales>99){
            dosDecimales=0;
            promedio ++;
        }   
    }
    else
    {
        dosDecimales = (dosDecimales/10);
    }
     
    // En caso de que los dos decimales sean 0 se debe agregar un segundo 00 para normalizar los datos
    if(to_string(dosDecimales)=="0"){
        dosDecimalesString = "00";
    }
    else{
        dosDecimalesString = to_string(dosDecimales);
    }

    return to_string(arregloSplit[0])+";"+to_string(promedio)+"."+dosDecimalesString;
}
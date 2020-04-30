import 'dart:core';
import 'dart:io';


participante(){
  print("=== Tarea ===");
  print("Israel Ramirez Cardoso. ");
}
/**
 * Función que calcula el promedio de puntajes PSU de un alumno ingresado como Rut;NEM;Ranking;PSU-Lenguaje;PSU-Matemática;PSU-Historia; PSU-Ciencias
 * @linea Recibe una linea de información ordenada ej: Rut;NEM;Ranking;PSU-Lenguaje;PSU-Matemática;PSU-Historia; PSU-Ciencias
 * @return Devuelve el rut y con el respectivo promedio de los puntajes de la siguiente forma: rut;promedio
 */
String calcularPromedioLinea(String linea){
  //Realiza un split de la linea en un arreglo separando los datos por ";"
  var dataInLine = linea.split(';');
  //Se crea la variable suma para sumar los valores de los puntajes
  double suma =0;
  //Se recorre todo el arreglo con excepción del RUT y se suman
  for(var i = 1; i < dataInLine.length; i++){
    suma += double.parse(dataInLine[i]);
  }
  //Se saca el promedio
  suma = suma/6;
  return dataInLine[0]+";"+suma.toStringAsFixed(2);
}

main(List<String> args)  async{
  //Comprueba que se ha entregado la ruta del archivo con los datosde los alumnos.
  if(args.length >= 1){
    //Se abre el archivo donde estan los datos de la matricula y se crea un archivo para el promedio
    var OpenFile = File(args[0]);
    var ExitFile = new File('promedio.csv');
    //Se crean las variables donde se guardará la información de los archivos
    var contentOpenFile;
    var contentExitFile = ExitFile.openWrite();
    //Se lee la información del archivo con la matricula y se guarda en la variable
    if(await OpenFile.exists()){
      contentOpenFile = await OpenFile.readAsString();
    }
    //Se guardan cada linea por separado con un split de salto de linea '\n' en la variable lineas
    var lineas = contentOpenFile.toString().split('\n');
    //Se recorre cada linea guardada
    for (var linea in lineas){
      if(linea!=""){
        //Se calcula el promedio y se guarda en el archivo
        contentExitFile.write(calcularPromedioLinea(linea)+'\n');
      }
    }
    //Se cierra el archivo.
    contentExitFile.close();
    participante();
  }
  else{
    print("ERROR: Se debe ingresar la ruta del archivo con los datos de los alumnos...");
  }
}
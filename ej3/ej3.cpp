#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <set>
#include <tuple>
#include <sys/time.h>

#include "ronda.cpp"
using namespace std;

/*

timeval startt, endd;
double acum = 0;

void init_time() {
  gettimeofday(&startt, NULL);
}

double get_time() {
  gettimeofday(&endd, NULL);
  return (1000000*(endd.tv_sec-startt.tv_sec) + (endd.tv_usec-startt.tv_usec))/1000000.0;
}

Funciones y datos utilizados para la toma de tiempos
*/ 

typedef set<set<char>> bigSet;
//Renombre de estructura de datos por comodidad del codigo

void permutaciones(tuple<Ronda, int> &rondaRes, Ronda &exploradoras, int pos, bigSet amistades) {
  if (pos == exploradoras.cantidad()-1) {

    // rondaRes va almacenando la ronda más óptima
    // exploradoras tiene la siguiente permutacion a analizar

    int sumaDists = exploradoras.sumaDistancias(amistades);

    if (sumaDists < get<1>(rondaRes)) {
      get<0>(rondaRes) = exploradoras;
      get<1>(rondaRes) = sumaDists;
      // exploradoras tiene una solucion mejor que la anterior
    }
    if (sumaDists == get<1>(rondaRes)) {
      if (exploradoras < get<0>(rondaRes))
        get<0>(rondaRes) = exploradoras;
      // chequear cual es menor lexicograficamente 
    }

  } else {
    for (int i = pos ; i < exploradoras.cantidad() ; i++) {
      //if (exploradoras.exploradoraEnPos(0) == e) {
      // Esa guarda es utilizada para realizar la poda del algoritmo
        exploradoras.swap(pos, i);
        permutaciones(rondaRes, exploradoras, pos+1, amistades);
        exploradoras.swap(pos, i);
      //}
    }
  }
}

string ej3(tuple<Ronda, int> rondaRes, Ronda exploradoras, bigSet amistades) {
  //init_time();
  // Funcion utilizada para tomar datos
  int n = exploradoras.cantidad();
  //char e = exploradoras.menorExploradora();
  // En caso de querer realizar la poda, descomentar la linea anterior
  // y pasar la exploradora e por parametro
  // Luego descomentar la guarda del caso recursivo de la funcion permutaciones
  if (amistades.size() != 0 && amistades.size() != (n*(n-1))/2) {
    permutaciones(rondaRes, exploradoras, 0, amistades);
  }
  else {
    get<0>(rondaRes).ordenar();
  }
  string res;

  // Meto el resultado en un string

  int dist = get<0>(rondaRes).maxDistAmistades(amistades);

  res.append(to_string(dist));
  res.append((const char*)" ");
  
  for (int i = 0 ; i < get<0>(rondaRes).cantidad() ; i++) {
    res.push_back(get<0>(rondaRes).exploradoraEnPos(i));
  }
  //acum += get_time(); 
  // Utilizado unicamente para la toma de datos
  return res;
}


int evaluarTests(string fileTestData, string fileTestResult, string fileTestWrite) {
  bool open = true;
  int j = 1;
  string line;
  ifstream fileData (fileTestData.c_str());
  ifstream fileResult (fileTestResult.c_str());
  ofstream fileWrite (fileTestWrite.c_str());
  string s;
  string res;
  // Abri los archivos de datos y resultados
  // e instancie las variables necesarias para el problema
  // el vector de exploradoras y el vector de amistades 


  while (open) {
    bigSet amistades;
    bigSet::iterator itA;
    set<char> expl;

    getline (fileData, line);
    istringstream iss(line);
    while (getline (iss, s, ';')) {
      expl.insert(s[0]);

      // Inserto la primer exploradora al conjunto

      int i;
      for (i = 2 ; i < s.length() ; i++) {
        if (s[i] != '\r') {
          expl.insert(s[i]);

      // Como no necesariamente las exploradoras estan al principio
      // meto todas. De todas maneras es un conjunto.

          set<char> amistad;
          amistad.insert(s[0]);
          amistad.insert(s[i]);

      // Creo la amistad entre dos exploradoras
      
          amistades.insert(amistad);

      // Las agrego al conjunto de amistades
        }
      }
    }
    Ronda exploradoras(expl);
    // Lo creo a partir del conjunto por que ahi puedo
    // meter lo que quiera sin verificar repetidos
    tuple <Ronda, int> rondaRes (Ronda(expl), 1000);

    // Instancio la ronda donde voy a devolver el resultado
    // El segundo elemento de la tupla es la sumatoria de las distancias entre las amigas
    // Se inicializa en un valor absurdamente grande para poder ir cambiandolo por un menor 
    // en cada iteraciones del algoritmo

    // for (int k = 0 ; k < 100 ; k++) 
    // Ese for es utilizado para tomar tiempos del algoritmo
      res = ej3(rondaRes, exploradoras, amistades);

    /*
    double prom = acum/100;
    fileWrite << "Test numero: " << j << endl;
    fileWrite << fixed << acum << endl;
    fileWrite << fixed << prom << endl;
    acum = 0;

    Toma de datos sobre tiempos
    */

    getline (fileResult, line);

    // Leo una linea del archivo donde esta el resultado

    if (fileData.eof())
      open = false;

    // Verifico si termine de leer los archivos


    string resTest = line;

    if (res == resTest) {
      cout << endl;
      cout << "Paso el test " << j << ". Felicitaciones!" << endl;
      cout << endl;
    } else {
      cout << endl;
      cout << "Fallo el test " << j << ". :(" << endl;
      cout << "Obtuve " << res << " deberia tener " << resTest << endl;
      cout << endl;
    }

    j++;
  }
}

int main(int argc, char **argv) {
  string fileTestData(argv[1]);
  string fileTestResult(argv[2]);
  string fileTestWrite(argv[3]);
  // Recibo por parametro tres archivos
  // El primero del cual leo los datos a evaluar
  // El segundo en el cual evaluo si los resultados fueron correctos
  // El tercero donde puedo escribir datos (tiempos)

  evaluarTests(fileTestData, fileTestResult, fileTestWrite);
  return 0;
}

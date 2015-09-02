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

timeval hare, hare2;
double acum = 0;

void init_time() {
  gettimeofday(&hare, NULL);
}

double get_time() {
  gettimeofday(&hare2, NULL);
  return (1000000*(hare2.tv_sec-hare.tv_sec) + (hare2.tv_usec-hare.tv_usec))/1000000.0;
}

typedef set<set<char>> bigSet;

void permutaciones(tuple<Ronda, int> &rondaRes, Ronda &exploradoras, int pos, bigSet amistades) {
  if (pos == exploradoras.cantidad()-1) {

    // rondaRes va almacenando la ronda más óptima
    // exploradoras tiene la siguiente permutacion a analizar

    int sumaDists = exploradoras.sumaDistancias(amistades);

    if (sumaDists < get<1>(rondaRes)) {
      get<0>(rondaRes) = exploradoras;
      get<1>(rondaRes) = sumaDists;
      // exploradoras tiene un solucion mejor que la anterior
    }
    if (sumaDists == get<1>(rondaRes)) {
      if (exploradoras < get<0>(rondaRes))
        get<0>(rondaRes) = exploradoras;
      // chequear cual es menor lexicograficamente 
    }

  } else {
    for (int i = pos ; i < exploradoras.cantidad() ; i++) {
//      if (exploradoras.exploradoraEnPos(0) == 'a') {
        exploradoras.swap(pos, i);
        permutaciones(rondaRes, exploradoras, pos+1, amistades);
        exploradoras.swap(pos, i);
//      }
    }
  }
}

string ej3(tuple<Ronda, int> rondaRes, Ronda exploradoras, bigSet amistades) {
  init_time();
  int n = exploradoras.cantidad();
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
  acum += get_time(); 
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

      int i;
      for (i = 2 ; i < s.length() ; i++) {
        if (s[i] != '\r') {
          expl.insert(s[i]);
          set<char> amistad;
          amistad.insert(s[0]);
          amistad.insert(s[i]);
          amistades.insert(amistad);
        }
      }
    }
    Ronda exploradoras(expl);
    // Lo creo a partir del conjunto por que ahi puedo
    // meter lo que quiera sin verificar repetidos
    tuple <Ronda, int> rondaRes (Ronda(expl), 120);

    for (int k = 0 ; k < 100 ; k++) 
      res = ej3(rondaRes, exploradoras, amistades);

    double prom = acum/100;
    fileWrite << "Test numero: " << j << endl;
    fileWrite << fixed << acum << endl;
    fileWrite << fixed << prom << endl;
    acum = 0;
    //if (res != ("1 xyz"))
    //  res.push_back('\r');

    getline (fileResult, line);

    if (fileData.eof())
      open = false;

    ///// Lei una linea del archivo de resultados
    ///// y pregunto si ya termine de evaluar todos los tests

    string resTest = line;

    ///fileWrite << res << endl;
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

  evaluarTests(fileTestData, fileTestResult, fileTestWrite);
  return 0;
}

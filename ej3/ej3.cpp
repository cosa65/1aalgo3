#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <set>
#include <tuple>

#include "ronda.cpp"
using namespace std;

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
      exploradoras.swap(pos, i);
      permutaciones(rondaRes, exploradoras, pos+1, amistades);
      exploradoras.swap(pos, i);
    }
  }
}

// pos = 0 hago E llamadas con pos = 1
// pos = 1 hago E-1 llamadas para cada llamada, dentro de cada paso recursivo cuando pos = 0; cada
// llamada con pos = 2
// con pos = T hago E-T llamadas para cada una de las llamadas anteriores
// productoria entre 1 y E = factorial

string ej3(tuple<Ronda, int> rondaRes, Ronda exploradoras, bigSet amistades) {
  permutaciones(rondaRes, exploradoras, 0, amistades);
  string res;

  // Meto el resultado en un string

  int dist = get<0>(rondaRes).maxDistAmistades(amistades);

  res.append(to_string(dist));
  res.append((const char*)" ");
  
  for (int i = 0 ; i < get<0>(rondaRes).cantidad() ; i++) {
    res.push_back(get<0>(rondaRes).exploradoraEnPos(i));
  }

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

    res = ej3(rondaRes, exploradoras, amistades);

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


//void verIgualdad() {
//  vector<const char*> uno;
//  vector<const char*> dos;
//  vector<const char*>::iterator itU;
//  vector<const char*>::iterator itD;
//
//  itU = uno.insert(itU, "a");
//  itD = dos.insert(itD, "a");
//  itU = uno.insert(itU, "b");
//  itD = dos.insert(itD, "b");
//  if (uno == dos) {
//    cout << "2 == 3" << endl;
//  } else {
//    cout << "NO son iguales" << endl;
//  }
//  itU = uno.insert(itU, "c");
//  itD = dos.insert(itD, "d");
//  if (uno == dos) {
//    cout << "conjuntos iguales" << endl;
//  } else {
//    cout << "NO son igualasdasdes" << endl;
//  }
//}
  /*
  vector<char>::iterator itV;
  char a = char(97); 
  char b = char(98); 
  char c = char(99); 
  char d = char(100); 
  itV = exploradoras.insert(itV, a);
  itV = exploradoras.insert(itV, b);
  itV = exploradoras.insert(itV, c);
  itV = exploradoras.insert(itV, d);

  int i = 0;

  for (itA = pAmistades.begin() ; itA!=pAmistades.end() ; itA++) {
    i = 0;
    for (itV = itA->begin() ; itV!= itA->end() ; itV++) {
      cout << " elem[" << i << "] " << *itV; 
      i++;
    }
    cout << endl;
  }

*/
  //vector<char> exploradoras;
  //vector<char>::iterator itV;
  //bigVector r;
  //char a = char(97); 
  //char b = char(98); 
  //char c = char(99); 
  //char d = char(100); 
  //itV = exploradoras.insert(itV, d);
  //itV = exploradoras.insert(itV, c);
  //itV = exploradoras.insert(itV, b);
  //itV = exploradoras.insert(itV, a);

  //permutaciones(r, 0, exploradoras);
  //string res;
  //res.append("h");
  //res.append("o");
  //cout << res << endl;

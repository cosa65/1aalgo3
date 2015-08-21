#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <set>
using namespace std;

typedef set<set<char>> bigSet;
typedef vector<vector<char>> bigVector;


void swap(vector<char> &exploradoras, int pos, int i) {
  char temp = exploradoras[pos];
  exploradoras[pos] = exploradoras[i];
  exploradoras[i] = temp;
}

void permutaciones(bigVector &pExploradoras, int pos, vector<char> &exploradoras) {
  if (pos == exploradoras.size()-1) {
    pExploradoras.insert(itA, exploradoras);

  } else {
    for (int i = pos ; i < exploradoras.size() ; i++) {
      swap(exploradoras, pos, i );
      permutaciones(pExploradoras, pos+1, exploradoras);
      swap(exploradoras, pos, i );
    }
  }
}

// pos = 0 hago E llamadas con pos = 1
// pos = 1 hago E-1 llamadas para cada llamada, dentro de cada paso recursivo cuando pos = 0; cada
// llamada con pos = 2
// con pos = T hago E-T llamadas para cada una de las llamadas anteriores
// productoria entre 1 y E = factorial
// NO guardar todo, ir verificando solucion optima

string ej3(vector<char> exploradoras, bigSet amistades) {
  bigVector pExploradoras;
  bigVector::iterator itE; // iterador para las permutaciones de exploradoras
  bigSet::iterator itA; // iterador para las amistades
  permutaciones(pExploradoras, 0, exploradoras);


  for(itE = pExploradoras.begin() ; itE != pExploradoras.end() ; itE++) {
    for (itA = amistades.begin() ; itA != amistades.end() ; itA++) {
      //calcularDistancias(itE, itA);
    }
  }
  return "hare";
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
    vector<char> exploradoras;
    vector<char>::iterator itE; 
    //set<char>::iterator it;

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
    exploradoras.assign(expl.begin(), expl.end());

    res = ej3(exploradoras, amistades);

    getline (fileResult, line);

    if (fileData.eof())
      open = false;

    ///// Lei una linea del archivo de resultados
    ///// y pregunto si ya termine de evaluar todos los tests

    string resTest = line;
    ///// convierto a int

    ///fileWrite << res << endl;
/*
    if (res == resTest) {
      cout << "Paso el test " << j << ". Felicitaciones!" << endl;
    } else {
      cout << "Fallo el test " << j << ". :(" << endl;
      cout << "Obtuve " << res << " deberia tener " << resTest << endl;
    }

    j++;
    */
  }
}

int main(int argc, char **argv) {
  string fileTestData(argv[1]);
  string fileTestResult(argv[2]);
  string fileTestWrite(argv[3]);

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
  evaluarTests(fileTestData, fileTestResult, fileTestWrite);
  return 0;
}

    /* MANERA DE ITERAR EL SET<SET<CHAR>>
    for (itE = exploradoras.begin() ; itE!=exploradoras.end() ; itE++) {
      cout << "exploradora : " << *itE << endl;
    }
    cout << "hareeeeeeeeeeeeeee" << endl;
    for (itA = amistades.begin() ; itA!=amistades.end() ; itA++) {
      for (it = itA->begin() ; it!= itA->end() ; it++) {
        cout << " elem: " << *it; 
      }
      cout << endl;
    }
    cout << "hareeeeeeeeeeeeeee" << endl;
    */


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

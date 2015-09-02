#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <sys/time.h>
using namespace std;
                                      //PARA CORRERLO : "./exj1 ej1/Tp1Ej1.in ej1/Tp1Ej1.out"

////////////////////////////////////////////////////AUXILIARES////////////////////////////////////////////////////

struct ramal{
  int ciudades;
  int cable;
};

void print(vector<int> ramales, int D[],int j,int i){
  for(int eme=0; eme < ramales.size(); eme++){
    cout << ramales[eme] << " ";
    if(eme==j) {cout << "(<--JOTA)" << " ";}
    if(eme==i) {cout << "(<--EL I)" << " ";}
  }
  cout << endl;
  for(int eme=0; eme < ramales.size(); eme++){
    cout << D[eme] << " ";
    if(eme==j) {cout << "(<--JOTA)" << " ";}
    if(eme==i) {cout << "(<--EL I)" << " ";}
  }
  cout << endl;
}

void crearDists(int km, vector<int> ramales, int D[], int n){
  int r;
  int aux1,aux2;
  vector<int>::iterator it = ramales.begin();
  D[0] = *it;
  int j=0;
  while (j<n-1){
    aux1 = *it;
    it++;
    aux2 = *it;
    D[j] = aux1 - aux2;
    j++;
  } //Aca estoy pegando el 0, de la ultima ciudad
  D[n-1]=0;
}

bool meAlcanzaCable(int D[],int km, int j, ramal *acumActual){
  if(acumActual->cable + D[j] <= km) return true;
  return false;
}

void soloAgregarCiudad(int D[], int j, ramal *acumActual){
  acumActual->cable+=D[j];
  acumActual->ciudades++;
}

void quitarCiudad(int D[], int i, ramal *acumActual){
  acumActual->cable-=D[i];
  acumActual->ciudades--;
  if(acumActual->ciudades==1) acumActual->ciudades--;
}

void elegirAcumNuevo(ramal *acum1, ramal *acum2, ramal **acumActualptr){
  //Acá decido que tupla resetear y usar para el nuevo intervalo que voy crear, lo decido tomando la tupla que haya agarrado menos ciudades
  if(acum1->ciudades >= acum2->ciudades){
    acum2->ciudades = (*acumActualptr)->ciudades;
    acum2->cable = (*acumActualptr)->cable;
    *acumActualptr=acum2;
  } else {
    acum1->ciudades = (*acumActualptr)->ciudades;
    acum1->cable = (*acumActualptr)->cable;
    *acumActualptr=acum1;
  }
}

bool esTuplaNueva(int i, int j){
  //Indica si estoy empezando un nuevo intervalo con mi tupla actual (si todo vale 0)
  return (i-j==1);
}

int mayorCant(ramal acum1, ramal acum2){
  if(acum1.ciudades>=acum2.ciudades){
    int res=acum1.ciudades;
    return acum1.ciudades;
  } 
  return acum2.ciudades;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	timeval startt,endd;
void init_time()
{
    gettimeofday(&startt,NULL);
}

double get_time()
{
    gettimeofday(&endd,NULL);
    return (1000000*(endd.tv_sec-startt.tv_sec)+(endd.tv_usec-startt.tv_usec))/1000000.0;
}
int ejUno(int km, vector<int> ramales, string fileOutput) {
  ofstream fOutput(fileOutput.c_str());
	init_time();

  ramal acum1;
  ramal acum2;
  ramal *acumActual = &acum1;
  int n = ramales.size();
  int D[n];
  bool meAlcanza;



  crearDists(km, ramales, D, n);    //creo arreglo con las distancias, si la ciudades son [a,b,c,d,e,f] 
                                    //entonces D = [d(a,b), d(b,c), d(c,d), d(d,e), d(e,f)]
  acum1.cable=0; acum1.ciudades=0;
  acum2.cable=0; acum2.ciudades=0;          //tup[0]=cant de cable usado, tup[1]=cant de ciudades conectadas

  int i=n-1;
  int j=n-2;
  while(j>=0){
    meAlcanza = meAlcanzaCable(D,km,j,acumActual);  //Devuelve un int que me indica si ALCANZA, ALCANZA_SI_DESCARTO o NO_ALCANZA
    if(meAlcanza){
      if(esTuplaNueva(i,j)) {
        acumActual->ciudades++;
      }
      soloAgregarCiudad(D,j,acumActual);
      j--;
    } else {
      if(esTuplaNueva(i,j)) {
        j--;
        i--;
        D[i]=0;
      } else {
        elegirAcumNuevo(&acum1,&acum2,&acumActual);
        i--;
        quitarCiudad(D,i,acumActual);
      }
    }
  }
  int res = mayorCant(acum1,acum2);

  double tiempo = get_time();
  fOutput << fixed << tiempo << endl;
  return res;
}

int evaluarTests(string fileTestData, string fileOutput) {
  vector<int> ramales;
  int i = 1;
  int km;
  string line;
  ifstream fileData (fileTestData.c_str());
  // Abri los archivos de datos y resultados
  // e instancie las variables necesarias para el problema
  // el kilometraje y el vector de ramales

  while (getline (fileData, line)) {
    vector<int>::iterator it = ramales.begin();
    km = atoi(line.c_str());
    // Primer dato a leer es el kilometraje

    getline (fileData, line);
    istringstream iss(line);
    int aux;
    it = ramales.insert(it, 0);
    while (iss >> aux) {
      it = ramales.insert(it, aux);
    }
    // Segundo dato a leer es la linea de los ramales
    // Los inserto en un vector de atras para adelante
    // de manera tal que si el vector es [6, 8, 12, 15]
    // ramales = [15, 12, 8, 6]

    int res = ejUno(km, ramales, fileOutput);
    // Almaceno el resultado del test i

    // Lei una linea del archivo de resultados
    // y pregunto si ya termine de evaluar todos los tests

    // convierto a int

    i++;
    ramales.resize(0);
  }
}

int main(int argc, char **argv) {
  string fileTestData(argv[1]);
  string fileOutput(argv[2]);
  evaluarTests(fileTestData,fileOutput);
  return 0;
}

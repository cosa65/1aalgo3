#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
using namespace std;

#define ALCANZA ((int) 2)
#define ALCANZA_SI_DESCARTO ((int) 1)
#define NO_ALCANZA ((int) 0)
																			//PARA CORRERLO : "./exj1 ej1/Tp1Ej1.in ej1/testeando.txt ej1/Tp1Ej1.out"

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
  vector<int>::iterator it = ramales.begin();
  D[0] = *it;
  int j=0;
  while (j<n-1){
    int aux1 = *it;
    it++;
    int aux2 = *it;
    D[j] = aux1 - aux2;
    j++;
  }	//Aca estoy pegando el 0, de la ultima ciudad
  D[n-1]=0;
}

int meAlcanzaCableInit(int D[],int km, int j, int i, ramal acum1, ramal acum2, ramal *acumActual){
  if(acumActual->cable + D[j] <= km) return ALCANZA;
  return NO_ALCANZA;
}

int meAlcanzaCable(int D[],int km, int j, int i, ramal acum1, ramal acum2, ramal *acumActual){
  if(acumActual->cable + D[j] <= km) return ALCANZA;
  if((acumActual->cable + D[j]-D[i] <= km)) return ALCANZA_SI_DESCARTO;
  return NO_ALCANZA;
}

void soloAgregarCiudad(int D[], int km, int j, int i, ramal *acum1, ramal *acum2, ramal *acumActual){
  acumActual->cable+=D[j];
  acumActual->ciudades++;
}

void agregarCiudadRestando(int D[], int km, int j, int i, ramal *acum1, ramal *acum2, ramal *acumActual){
  acumActual->cable+=(D[j] - D[i]);
}

void elegirTuplaNueva(int D[], int km, int j, int i, ramal *acum1, ramal *acum2, ramal **acumActualptr){
	//Acá decido que tupla resetear y usar para el nuevo intervalo que voy crear, lo decido tomando la tupla que haya agarrado menos ciudades
	if(acum1->ciudades >= acum2->ciudades){
		*acumActualptr=acum2;
		acum2->ciudades = 0;
		acum2->cable = 0;
	} else {
		*acumActualptr=acum1;
		acum1->ciudades = 0;
		acum1->cable = 0;
	}
}

bool acaboDeEmpezar(ramal *acumActual){
	//Indica si estoy empezando un nuevo intervalo con mi tupla actual (si todo vale 0)
	return (acumActual->cable==0) && (acumActual->ciudades==0);
}

int mayorCant(ramal acum1, ramal acum2){
	if(acum1.ciudades>=acum2.ciudades){
		int res=acum1.ciudades;
		return acum1.ciudades;
	} 
	return acum2.ciudades;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int ejUno(int km, vector<int> ramales) {
  ramal acum1;
  ramal acum2;
  ramal *acumActual = &acum1;
  int n = ramales.size();
  int D[n];
  int meAlcanza;

  crearDists(km, ramales, D, n);  	//creo arreglo con las distancias, si la ciudades son [a,b,c,d,e,f] 
  									                //entonces D = [d(a,b), d(b,c), d(c,d), d(d,e), d(e,f)]
  acum1.cable=0; acum1.ciudades=0;
  acum2.cable=0; acum2.ciudades=0;					//tup[0]=cant de cable usado, tup[1]=cant de ciudades conectadas

  int i = n-1;
  int j = n-2;

  meAlcanza = meAlcanzaCableInit(D,km,j,i,acum1,acum2,acumActual);	//Este seria el caso inicial, en el que el i no importa
  if(meAlcanza==ALCANZA){
  	soloAgregarCiudad(D,km,j,i,&acum1,&acum2,acumActual);
  	acumActual->ciudades++;
  	i=n-2;
  	j=n-3;
  } else {
  	i = n-2;
  	D[i]=0;
  	j = n-3;
  }

  while(j>=0){
  	//print(ramales,D,j,i);
    meAlcanza = meAlcanzaCable(D,km,j,i,acum1,acum2,acumActual);	//Devuelve un int que me indica si ALCANZA, ALCANZA_SI_DESCARTO o NO_ALCANZA
    if(meAlcanza==ALCANZA){
      if(acaboDeEmpezar(acumActual)) {acumActual->ciudades++;}
      soloAgregarCiudad(D,km,j,i,&acum1,&acum2,acumActual);
      int debug=acumActual->ciudades;
      j--;															//Muevo el indice que selecciona las ciudades a agregar
    }else if(meAlcanza==ALCANZA_SI_DESCARTO && !(acaboDeEmpezar(acumActual))){
      agregarCiudadRestando(D,km,j,i,&acum1,&acum2,acumActual);
      j--;															//Muevo el indice que selecciona las ciudades a agregar
      i--;															//Muevo el indice que selecciona las ciudades que finalizan el intervalo
    } else { //caso meAlcanza==NO_ALCANZA
      if(acaboDeEmpezar(acumActual)) {
      	j--;
      	i--;
      } else {
      	i=j+1; 															//el final de mi nuevo intervalo es en la ciudadque termina el intervalo actual
      }
      elegirTuplaNueva(D,km,j,i,&acum1,&acum2,&acumActual);		//Modifica usotuplaNro para que decide que tupla flushear y cual conservar (se queda con la que mas ciudades encompase)
    	D[i]=0;
    }

  }
  int res = mayorCant(acum1,acum2);
  return res;
}

int evaluarTests(string fileTestData, string fileTestResult, string fileTestWrite) {
  vector<int> ramales;
  int i = 1;
  int km;
  string line;
  ifstream fileData (fileTestData.c_str());
  ifstream fileResult (fileTestResult.c_str());
  ofstream fileWrite (fileTestWrite.c_str());
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

    int res = ejUno(km, ramales);
    // Almaceno el resultado del test i
    
    getline (fileResult, line);

    // Lei una linea del archivo de resultados
    // y pregunto si ya termine de evaluar todos los tests

    int resTest = atoi(line.c_str());
    // convierto a int

    fileWrite << res << endl;

    if (res == resTest) {
      cout << "Paso el test " << i << ". Felicitaciones!" << endl;
    } else {
      cout << "Fallo el test " << i << ". :(" << endl;
      cout << "Obtuve " << res << " deberia tener " << resTest << endl;
    }

    i++;
    ramales.resize(0);
  }
}

int main(int argc, char **argv) {
  string fileTestData(argv[1]);
  string fileTestResult(argv[2]);
  string fileTestWrite(argv[3]);
  evaluarTests(fileTestData, fileTestResult, fileTestWrite);
  return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <tuple>
using namespace std;

#define ALCANZA ((int) 2)
#define ALCANZA_SI_DESCARTO ((int) 1)
#define NO_ALCANZA ((int) 0)
																			//PARA CORRERLO : "./exj1 ej1/Tp1Ej1.in ej1/testeando.txt ej1/Tp1Ej1.o"
////////////////////////////////////////////////////AUXILIARES////////////////////////////////////////////////////
void crearDists(int km, vector<int> ramales, int D[], int n){
  vector<int>::reverse_iterator it = ramales.rbegin();
  D[0] = *it;
  int j=1;
  while (j<n){
    int aux1 = *it;
    it++;
    int aux2 = *it;
    D[j] = aux2 - aux1;
    j++;
  }
}

int meAlcanzaCable(int D[],int km, int j, int i, tuple<int,int> tup1, tuple<int,int> tup2, tuple<int,int> *tupActual){
  if(get<0>(*tupActual) + D[j] <= km) return ALCANZA;
  if(get<0>(*tupActual) + D[j]-D[i] <= km) return ALCANZA_SI_DESCARTO;
  return NO_ALCANZA;
}

void soloAgregarCiudad(int D[], int km, int j, int i, tuple<int,int> *tup1, tuple<int,int> *tup2, tuple<int,int> *tupActual){
  get<0>(*tupActual)+=D[j];
  get<1>(*tupActual)++;
}

void agregarCiudadRestando(int D[], int km, int j, int i, tuple<int,int> *tup1, tuple<int,int> *tup2, tuple<int,int> *tupActual){
  get<0>(*tupActual)+=(D[j] - D[i]);
}

void elegirTuplaNueva(int D[], int km, int j, int i, tuple<int,int> *tup1, tuple<int,int> *tup2, tuple<int,int> **tupActualptr){
	//Acá decido que tupla resetear y usar para el nuevo intervalo que voy crear, lo decido tomando la tupla que haya agarrado menos ciudades
	if(get<1>(*tup1) >= get<1>(*tup2)){
		*tupActualptr=tup2;
		*tup2 = make_tuple(0,0);
	} else {
		*tupActualptr=tup1;
		*tup1 = make_tuple(0,0);
	}
}

bool acaboDeEmpezar(tuple<int,int> *tupActual){
	//Indica si estoy empezando un nuevo intervalo con mi tupla actual (si todo vale 0)
	return (get<0>(*tupActual)==0) && (get<1>(*tupActual)==0);
}

int mayorCant(tuple<int,int> tup1, tuple<int,int> tup2){
	if(get<1>(tup1)>=get<1>(tup2)){
		int res=get<1>(tup1);
		return get<1>(tup1);
	} 
	return get<1>(tup2);
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int ejUno(int km, vector<int> ramales) {
  tuple<int,int> tup1;
  tuple<int,int> tup2;
  tuple<int,int> *tupActual = &tup1;
  int n = ramales.size();
  int D[n];
  //bool noPudeAgregar=false; //me dice si la ultima iteracion no pudo agregar cable ni descartando

  crearDists(km, ramales, D, n);  //creo arreglo con las distancias, si la ciudades son [a,b,c,d,e,f] 
  																//entonces D = [d(a,b), d(b,c), d(c,d), d(d,e), d(e,f)]
 
  //hay que chequear el caso en el que no se puedan conectar nigunas ciudades
  //t1 = make_tuple(D[n], 2);
  //t2 = make_tuple(D[n-1], 2);
  get<0>(tup1)=0; get<1>(tup1)=0;
  get<0>(tup2)=0; get<1>(tup2)=0;					//tup[0]=cant de cable usado, tup[1]=cant de ciudades conectadas
  int j = n-2;
  int i = n-1;

  while(j>=0){
    int meAlcanza;
    meAlcanza = meAlcanzaCable(D,km,j,i,tup1,tup2,tupActual);	//Devuelve un int que me indica si ALCANZA, ALCANZA_SI_DESCARTO o NO_ALCANZA
    if(meAlcanza==ALCANZA){
      if(acaboDeEmpezar(tupActual)) get<1>(*tupActual)++;
      soloAgregarCiudad(D,km,j,i,&tup1,&tup2,tupActual);
      int debug=get<1>(*tupActual);
      j--;															//Muevo el indice que selecciona las ciudades a agregar
    }else if(meAlcanza==ALCANZA_SI_DESCARTO){
    	//if(acaboDeEmpezar(tupActual)) get<1>(*tupActual)++;
      agregarCiudadRestando(D,km,j,i,&tup1,&tup2,tupActual);
      j--;															//Muevo el indice que selecciona las ciudades a agregar
      i--;															//Muevo el indice que selecciona las ciudades que finalizan el intervalo
    } else { //caso meAlcanza==NO_ALCANZA
      i=j; 															//el final de mi nuevo intervalo es en la ciudadque termina el intervalo actual
      j--;
      elegirTuplaNueva(D,km,j,i,&tup1,&tup2,&tupActual);		//Modifica usotuplaNro para que decide que tupla flushear y cual conservar (se queda con la que mas ciudades encompase)
    }

  }

  int res = mayorCant(tup1,tup2);
  return res;
}
  /*while (j>0){
    //el cable alcanza para agregar ciudad
    if (get<0>(t1) + D[j] <= km){
      get<0>(t1) = get<0>(t1) + D[j];
      get<1>(t1) = get<1>(t1) + 1 ;
    } else { //el cable alcanza si suelto la ultima ciudad
      if (get<0>(t1) + D[j] - get<0>(t2) <= km){
        get<0>(t1) = get<0>(t1) + D[j] - get<0>(t2);
        //get<1>(t1) = get<1>(t1);
        get<0>(t2) = D[j];
      } else { //el cable no alcanza aunque suelte ciudad
      
      }  
    }
    j--;
  }
  return get<0>(t1);
  */

  //
  //
  // a = arreglo (numeros del texto)
 // j = tam(a) - 1 
/*  c = crearTupla(0,0)
  d = crearTupla(0,0)
  // deberian empezar en dos o algo asi
  while(j > 0) {
    if (Pi_1(c) + (a[j]-a[j-1] < cable && acum2 + (a[j]-a[j-1]) < cable)){
      // a = Pi_1(c) + (a[j]-a[j-1] < cable 
      // b = acum2 + (a[j]-a[j-1]) < cable
    c = (faumentar este numero que empieza en 2,anterior += a[j]-a[j-1])
    } else {
      if (!a && !b) {

        else {
          if (a && !b) {
          
          }
        }
      }
    }
  }*/

int evaluarTests(string fileTestData, string fileTestResult, string fileTestWrite) {
  bool open = true;
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

  while (open) {
  	vector<int>::iterator it = ramales.begin();
    getline (fileData, line);
    km = atoi(line.c_str());
    // Primer dato a leer es el kilometraje

    getline (fileData, line);
    istringstream iss(line);
    int aux;
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

    if (fileResult.eof())
      open = false;

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

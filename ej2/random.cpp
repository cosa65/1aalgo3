#include <iostream>
#include <time.h>
#include <stdlib.h>
#include <fstream>

using namespace std;

int main(int argc, char **argv){
	string fileName(argv[1]);		  //Nombre del archivo de test generado
	int longLista = atoi(argv[2]);		//Longitud de la lista
	int maximo = atoi(argv[3]);	//Maximo valor
  int valor;

	ofstream output(fileName.c_str());

	int acum = 0;
	srand(time(NULL));

	for(int i = 0; i< longLista; i++){
		valor = (rand()%maximo) + 1; //me asegura que siempre son valores positivos
		output << valor << " ";
	}
	output << endl;
}

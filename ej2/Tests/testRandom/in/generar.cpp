#include <iostream>
#include <time.h>
#include <stdlib.h>
#include <fstream>

using namespace std;

int main(int argc, char **argv){
	string fileName(argv[1]);		//Nombre del archivo de test generado
	// int tests = atoi(argv[2]);		//Cantidad de casos de tests apsados
	
	int cant = 100;
	
	int km;
	long posIn,posOut;

	ofstream output(fileName.c_str(), ofstream::app);

	int acum = 0;
	srand(time(NULL));

	for(int j = 0; j<cant; j++)
	{
		acum = (rand()%10000) + 1;
		output << acum << " ";
	}
	km = rand()%acum;
	acum=0;
	
	
	return 0;
}

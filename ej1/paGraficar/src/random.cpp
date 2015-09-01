#include <iostream>
#include <time.h>
#include <stdlib.h>
#include <fstream>

using namespace std;

int main(int argc, char **argv){
	string fileName(argv[1]);		//Nombre del archivo de test generado
	int tests = atoi(argv[2]);		//Cantidad de casos de tests apsados
	int ciudades = atoi(argv[3]);	//Cantidad de ciudades
	int interval = atoi(argv[4]);	//Maximo length de intervalo entre cada ciudad
	int km;

	ofstream output(fileName.c_str());

	int acum = 0;
	srand(time(NULL));

	for(int i = 0; i<tests; i++){
		km = (rand()%interval)*ciudades + 1;
		output << km << endl;
		for(int j = 0; j<ciudades; j++){
			acum += (rand()%interval) + 1;
			output << acum << " ";
		}
		acum=0;
		output << endl;
	}

}
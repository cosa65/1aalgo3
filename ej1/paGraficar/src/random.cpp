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
	string random(argv[5]);	
	int km;
	long posIn,posOut;

	ofstream output(fileName.c_str());

	int acum = 0;
	srand(time(NULL));
	if(random=="random"){
		for(int i = 0; i<tests; i++){
			posIn = output.tellp();		
			output << km << endl;
			for(int j = 0; j<ciudades; j++){
				acum += (rand()%interval) + 1;
				output << acum << " ";
			}
		
			posOut = output.tellp();	
			km = rand()%acum;
			output.seekp(posIn);
			output << km << endl;
			output.seekp(posOut);		
			acum=0;
			output << endl;
		}
	} else {
		for(int i = 0; i<tests; i++){
			posIn = output.tellp();		
			output << km << endl;
			for(int j = 0; j<ciudades; j++){
				acum += (rand()%interval) + 1;
				output << acum << " ";
			}

			/*acum += acum;
			output << acum;*/
		
			posOut = output.tellp();	
			km = acum/2;
			output.seekp(posIn);
			output << km<<endl;
			output.seekp(posOut);		
			acum=0;
			output << endl;	
		}
	}
	return 0;
}

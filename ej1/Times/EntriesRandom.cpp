#include <iostream>
#include <time.h>
#include <stdlib.h>
#include <fstream>

int main(int argc, char **argv){
	string fileName(argv[1]);
	int times = (int)*argv[2];
	int size = (int)*argv[3];
	int km = (int)*argv[4];
	int length = (int)*argv[5];

	ofstream output;
	output.open(fileName);

	int acum = 0;
	int seed = srand(time(NULL));

	for(int i = 0; i<times; i++){
		km = rand() % km + 1;
		output << km << endl;
		for(int j = 0; j<size; j++){
			acum += rand()% length;
			output << acum << " ";
		}
		output << endl;
	}

}
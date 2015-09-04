#include <iostream>
#include <fstream>
#include <string>
#include <queue> //priority_queue
#include <sstream> //istringstream
#include <algorithm> //lower_bound
#include <sys/time.h>
using namespace std;


void mediana(string, stringstream&);
int medianaSubarreglo(int, priority_queue<int>&, priority_queue<int, vector<int>, greater<int> >&);
void init_time();
double get_time();

int main () {

	string iline;
	stringstream oss;
	double tiempo;
	double suma = 0;
	int cantMediciones = 100000;
			 ifstream ifile ("Tests/mejorCaso/in/test1000");
		   ofstream ofile ("Tests/mejorCaso/out/mejor1000");
	ofstream timeFile ("Tests/mejorCaso/tiempos/mejor1000");

	while ( getline (ifile,iline) )
	{
		for (int i = 0; i < cantMediciones; ++i)
		{
			mediana(iline, oss);
			tiempo = get_time();
			suma += tiempo;
			timeFile << fixed << tiempo << endl;		
		}
			ofile << oss.rdbuf();
			if (ifile.eof()) break;
			ofile << "\n";
	}

	timeFile << "Cantidad de Mediciones: " << cantMediciones << endl;
	timeFile << "Promedio: " << fixed << suma/cantMediciones << endl;
	timeFile.close();
	ifile.close();

	return 0;
}

void mediana(string line, stringstream& oss)
{
	init_time();
	priority_queue<int> menores;
	priority_queue<int, vector<int>, greater<int> > mayores;
	int prox, med;
	istringstream iss(line);

	while (iss >> prox)
	{
		med = medianaSubarreglo(prox, menores, mayores);
		oss << med;		
		if (iss.eof()) break;
		oss << " ";
	}

	oss << endl;

}

int medianaSubarreglo(int prox, priority_queue<int>& menores, priority_queue<int, vector<int>, greater<int> >& mayores)
{
	
	if (menores.empty())
	{
		menores.push(prox);
	}
	else
	{
		if (prox < menores.top())
		{
			if (menores.size() > mayores.size())
			{
				mayores.push( menores.top() );
				menores.pop();
				menores.push(prox);
			}
			else
			{
				menores.push(prox);
			}
		}
		else
		{
			if (mayores.size() > menores.size())
			{
				menores.push( mayores.top() );
				mayores.pop();
				mayores.push(prox);
			}
			else
			{
				mayores.push(prox);
			}			
		}
	}

	// cout << prox << endl;

	if (menores.size() > mayores.size())
		return menores.top();
	if (menores.size() < mayores.size())
		return mayores.top();
	if (menores.size() == mayores.size())
		return (menores.top()+mayores.top())/2;

}



timeval inicio, fin;

void init_time()
{
  gettimeofday(&inicio, NULL);
}

double get_time()
{
  gettimeofday(&fin, NULL);
  return (1000000*(fin.tv_sec-inicio.tv_sec) + (fin.tv_usec-inicio.tv_usec))/1000000.0;   
}

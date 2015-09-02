#include <iostream>
#include <fstream>
#include <string>
#include <queue> //priority_queue
#include <sstream> //istringstream
#include <algorithm> //lower_bound
#include<sys/time.h>
// #include "string.h"
using namespace std;

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


void mediana(string, stringstream&);
int medianaSubarreglo(int, priority_queue<int>&, priority_queue<int, vector<int>, greater<int> >&);

int main () {
	string iline; 
	stringstream oss;
	ifstream ifile ("testRandom/test10000.in"); //para generar secuencias random --->  ./rand filename longitudLista maximoValor
	ofstream ofile ("testx.out");
  ofstream tfile ("t10000.txt");
  float suma = 0;
  unsigned int i;

	while ( getline (ifile,iline) )
  {
    cout << "hare" << endl;
    for ( i = 0; i < 100; i++ )
    {
	    mediana(iline, oss);
      suma += get_time();
	  }
	  ofile << oss.rdbuf();
	  if (ifile.eof()) break;
	  ofile << "\n";
  }
  ifile.close();
  tfile << "Promedio: " << fixed << suma/100.0 << endl;
  tfile.close();
  return 0;
 //   tfile << "Tiempo de ejecución: " << fixed << get_time() << endl;
 //   tfile << "\n";
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
  //  oss << get_time(); 
		if (iss.eof()) break;
		oss << " ";
	}

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

	//cout << prox << endl;

	if (menores.size() > mayores.size())
		return menores.top();
	if (menores.size() < mayores.size())
		return mayores.top();
	if (menores.size() == mayores.size())
		return (menores.top()+mayores.top())/2;


}

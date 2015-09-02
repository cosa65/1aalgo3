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
	ifstream ifile ("test100000.in");
	ofstream ofile ("testx.out");
  ofstream tfile ("tiempo100000.txt");
  float suma;
  unsigned int i;
  
  for ( i = 0; i < 100; i++ )
  {
	  while ( getline (ifile,iline) )
	  {
        
	    mediana(iline, oss);
      
	  	ofile << oss.rdbuf();
	  	if (ifile.eof()) break;
	  	ofile << "\n";
	  }

	  ifile.close();
    suma += get_time();
 //   tfile << "Tiempo de ejecución: " << fixed << get_time() << endl;
 //   tfile << "\n";
  }
  tfile << "Promedio: " << suma/(float)i << endl;
  tfile.close();
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

	cout << prox << endl;

	if (menores.size() > mayores.size())
		return menores.top();
	if (menores.size() < mayores.size())
		return mayores.top();
	if (menores.size() == mayores.size())
		return (menores.top()+mayores.top())/2;


}

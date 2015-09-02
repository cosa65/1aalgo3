#include <iostream>
#include <fstream>
#include <string>
#include <queue> //priority_queue
#include <sstream> //istringstream
#include <algorithm> //lower_bound
// #include "string.h"
using namespace std;


void mediana(string, stringstream&);
int medianaSubarreglo(int, priority_queue<int>&, priority_queue<int, vector<int>, greater<int> >&);

int main () {

	string iline;
	stringstream oss;
	ifstream ifile ("test.in");
	ofstream ofile ("test.out");

	while ( getline (ifile,iline) )
	{
		mediana(iline, oss);
		ofile << oss.rdbuf();
		if (ifile.eof()) break;
		ofile << "\n";
	}

	ifile.close();

	return 0;
}

void mediana(string line, stringstream& oss)
{
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
#include <vector>
#include <set>
#include <assert.h>
#include <iostream>

using namespace std;


class Ronda {

  private:   
  
    vector<char> exploradoras;

  public:

    Ronda();
    Ronda(set<char>);
    char izq(char);
    char der(char);
    int distancia(char, char);
    bool estaEnRonda(char);
    int encontrarPos(char);
    int cantidad();  
    void imprimir();
};

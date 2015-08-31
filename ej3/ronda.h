#include <vector>
#include <set>
#include <assert.h>
#include <iostream>

using namespace std;

typedef set<set<char>> bigSet;

class Ronda {

  private:   
  
    vector<char> exploradoras;

  public:

    Ronda();
    Ronda(set<char>);
    //constructores
    
    int cantidad();  
    
    int distancia(char, char);

    int encontrarPos(char);
    bool estaEnRonda(char);
    bool esMayorQue(Ronda);
    //bool esResult();
    char exploradoraEnPos(int);

    void imprimir();

    int maxDistAmistades(bigSet);

    bool operator <(Ronda);
    void ordenar();

    int sumaDistancias(bigSet);
    void swap(int, int);
};

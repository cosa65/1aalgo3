#include <vector>

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

  
};

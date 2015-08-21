#include "ronda.h"

Ronda::Ronda(set<char> conjExp){
  this->exploradoras.assign(conjExp);
}

char Ronda::izq(char exp){
  return exp;
}


char Ronda::der(char exp){
  return exp;
}

bool Ronda::estaEnRonda(char exp){
  bool res = false;
  vector<char>::iterator it;
  for(it = this->exploradoras.begin(); it != this->exploradoras.end(); it++){
    if (exp == *it)
      res = true;    
  }
  return res;
}

int Ronda::distancia(char exp1, char exp2){
  assert(estaEnRonda(exp1));
  assert(estaEnRonda(exp2));
  for
  
}

#include "ronda.h"

Ronda::Ronda(set<char> conjExp){
  this->exploradoras.assign(conjExp.begin(), conjExp.end()); 
}

int Ronda::cantidad(){
  return this->exploradoras.size();  
}

int Ronda::distancia(char exp1, char exp2){
  assert(estaEnRonda(exp1));
  assert(estaEnRonda(exp2));
  int posExp1 = encontrarPos(exp1);
  int posExp2 = encontrarPos(exp2);
  int aux = abs(posExp1 - posExp2);
  int aux2 = exploradoras.size() - aux;
  return min(aux, aux2);
}

int Ronda::encontrarPos(char exp){
  assert(estaEnRonda(exp));
  int res; 
  int i = 0;
  while (i < exploradoras.size()){
    if (exp == exploradoras[i]){
      res = i;
    }  
    i++;
  }
  return res;
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

bool Ronda::esMayorQue(Ronda r) {
  bool res = false;
  for (int i = 0 ; i < r.cantidad() ; i++) {
    if (r.exploradoraEnPos(i) > this->exploradoras[i])
      res = true;
  }
  return res;
}

char Ronda::exploradoraEnPos(int i) {
  return this->exploradoras[i];
}

void Ronda::imprimir(){
  int i = 0;
  cout << endl;
  while(i < this->exploradoras.size()){
    cout << " exp[" << i << "] " << this->exploradoras[i];
    i++;
  }
  cout << endl;
  cout << endl;
}

int Ronda::maxDistAmistades(bigSet amistades) {
  int res = 0;
  bigSet::iterator itA;
  set<char>::iterator itS;

  char exp1;
  char exp2;

  for (itA = amistades.begin() ; itA != amistades.end() ; itA++) {
    itS = itA->begin();
    exp1 = *itS;
    advance(itS, 1); // Son dos asi que me muevo al siguiente
    exp2 = *itS;
    res = max(res, this->distancia(exp1, exp2));
  }

  return res;
}

bool Ronda::operator <(Ronda r) {
  bool res;
  bool sonDistintos = false;
  int i = -1;
  while (i < r.cantidad() && !sonDistintos) {
    i++;
    sonDistintos = (this->exploradoraEnPos(i) != r.exploradoraEnPos(i));
  }

  return res = (this->exploradoraEnPos(i) < r.exploradoraEnPos(i));
}

int Ronda::sumaDistancias(bigSet amistades) {
  int res = 0;
  bigSet::iterator itA;
  set<char>::iterator itS;

  char exp1;
  char exp2;

  for (itA = amistades.begin() ; itA != amistades.end() ; itA++) {
    itS = itA->begin();
    exp1 = *itS;
    advance(itS, 1); // Son dos asi que me muevo al siguiente
    exp2 = *itS;
    res += this->distancia(exp1, exp2);
  }

  return res;
}

void Ronda::swap(int i, int j) {
  char temp = exploradoras[i];
  exploradoras[i] = exploradoras[j];
  exploradoras[j] = temp;
}

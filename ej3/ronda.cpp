#include "ronda.h"

Ronda::Ronda(set<char> conjExp){
  set<char>::iterator it;
  for(it = conjExp.begin(); it != conjExp.end(); it++){
    exploradoras.push_back(*it);
  }
  //this->exploradoras.assign(conjExp); no me andaba esto :(
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

//no anda porque no me reconoce abs() 
int Ronda::distancia(char exp1, char exp2){
  assert(estaEnRonda(exp1));
  assert(estaEnRonda(exp2));
  int posExp1 = encontrarPos(exp1);
  int posExp2 = encontrarPos(exp2);
  int aux = 2;//abs();
  int aux2 = exploradoras.size() - aux;
  return max(aux, aux2);
}

int Ronda::cantidad(){
  return exploradoras.size();  
}

void Ronda::imprimir(){
  int i = 0;
  while(i < this->exploradoras.size()){
    cout << this->exploradoras[i] << endl;
    i++;
  }
}

int main(){
  set<char> C;
  C.insert('a');
  C.insert('b');
  C.insert('c');
  C.insert('d');
  Ronda r = Ronda(C);
  r.imprimir();
  int cant = r.cantidad();
  int pos = r.encontrarPos('a');
  int pos1 = r.encontrarPos('b');
  int pos2 = r.encontrarPos('c');
  int pos3 = r.encontrarPos('d');
  cout << cant << endl;
  cout << pos << endl;
  cout << pos1 << endl;
  cout << pos2 << endl;
  cout << pos3 << endl;

  return 0;
}

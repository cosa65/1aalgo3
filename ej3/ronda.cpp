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
    cout << " exp[" << i << "]:  " << this->exploradoras[i];
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

void Ronda::ordenar() {
  for (int i = 1 ; i < this->exploradoras.size() ; i++) {
    int j = i;
    while (j > 0 && this->exploradoras[j] < this->exploradoras[j-1]) {
      char temp = this->exploradoras[j];
      this->exploradoras[j] = this->exploradoras[j-1];
      this->exploradoras[j-1] = temp;
      j--;
    }
  }
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

int generate(unsigned int *seed, int tam){
  int valor = rand_r(seed);
  return (valor % tam);
}

void Ronda::swap(int i, int j) {
  // Assert que las posiciones sean validas
  char temp = exploradoras[i];
  exploradoras[i] = exploradoras[j];
  exploradoras[j] = temp;
}

//int main(){
//  set<char> C;
//  set<set<char>> amistades;
//  C.insert('a');
//  C.insert('b');
//  C.insert('c');
//  C.insert('d');
//  C.insert('e');
////  C.insert('f');
////  C.insert('g');
////  C.insert('h');
//  Ronda r = Ronda(C);
//  unsigned int seed = time(NULL);
//  unsigned int tam = r.cantidad();
//  int pos1;
//  int pos2;
//  for(int i = 0; i < (tam*(tam-1))/2; i++) {
//    set<char> amistad;
//    pos1 = generate(&seed, tam);
//    amistad.insert(r.exploradoraEnPos(pos1));
//    pos2 = generate(&seed, tam);
//    while (pos1 == pos2) {
//      pos2 = generate(&seed, tam);
//    }
//    amistad.insert(r.exploradoraEnPos(pos2));
//    amistades.insert(amistad);
//  }  
//  set<set<char>>::iterator itA;
//  set<char>::iterator itV;
//  for (itA = amistades.begin() ; itA!=amistades.end() ; itA++) {
//    int i = 0;
//    for (itV = itA->begin() ; itV!= itA->end() ; itV++) {
//      cout << " elem[" << i << "] " << *itV; 
//      i++;
//    }
//    cout << endl;
//  }
//
//}

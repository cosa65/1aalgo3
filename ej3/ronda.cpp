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

//bool Ronda::esResult() {
//  return (this->exploradoraEnPos(0) == 'a' && this->exploradoraEnPos(1) == 'b' && 
//      this->exploradoraEnPos(2) == 'c' && this->exploradoraEnPos(3) == 'f' &&
//      this->exploradoraEnPos(4) == 'g' && this->exploradoraEnPos(5) == 'd' &&
//      this->exploradoraEnPos(6) == 'h' && this->exploradoraEnPos(7) == 'e');
//  
//}

bool Ronda::operator <(Ronda r) {
  bool res;
  bool sonDistintos = false;
  int i = -1;
  while (i < r.cantidad() && !sonDistintos) {
    i++;
    sonDistintos = (this->exploradoraEnPos(i) != r.exploradoraEnPos(i));
  }
  //if (this->exploradoraEnPos(0) == 'a' && this->exploradoraEnPos(1) == 'b' && 
  //    this->exploradoraEnPos(2) == 'c' && this->exploradoraEnPos(3) == 'f' &&
  //    this->exploradoraEnPos(4) == 'g' && this->exploradoraEnPos(5) == 'd' &&
  //    this->exploradoraEnPos(6) == 'h' && this->exploradoraEnPos(7) == 'e')
  //  cout << "ACA VIEJA EN THIS" << endl;

  //if (r.exploradoraEnPos(0) == 'a' && r.exploradoraEnPos(1) == 'b' && 
  //    r.exploradoraEnPos(2) == 'c' && r.exploradoraEnPos(3) == 'f' &&
  //    r.exploradoraEnPos(4) == 'g' && r.exploradoraEnPos(5) == 'd' &&
  //    r.exploradoraEnPos(6) == 'h' && r.exploradoraEnPos(7) == 'e')
  //  cout << "ACA VIEJA EN R" << endl;

  //if (this->exploradoraEnPos(i) == 'g' || r.exploradoraEnPos(i) == 'g') {
  //cout << "exploradores :"; 
  //  this->imprimir();
  //  cout << "rondaRes"; 
  //  r.imprimir();
  //}


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

//int main(){
//  set<char> C;
//  set<char> D;
//  C.insert('a');
//  C.insert('b');
//  C.insert('c');
//  C.insert('d');
//  C.insert('e');
//  Ronda r = Ronda(C);
//
//  D.insert('a');
//  D.insert('b');
//  D.insert('d');
//  D.insert('c');
//  D.insert('e');
//  Ronda x = Ronda(D);
//  x.swap(3, 2);
//
//  bool res = r.esMenorQue(x);
//  if(res)
//    cout << "dio true" << endl;
//  if(!res)
//    cout << "dio false" << endl;
//
//
//  cout << "R DIO ESTO" << endl;
//  r.imprimir();
//  cout << "X DIO ESTO" << endl;
//  x.imprimir();
//
//
//
//  int cant = r.cantidad();
//  int pos = r.encontrarPos('a');
//  int pos1 = r.encontrarPos('b');
//  int pos2 = r.encontrarPos('c');
//  int pos3 = r.encontrarPos('d');
//  cout << "cant: " << cant << endl;
//  cout << "pos: " << pos << endl;
//  cout << "pos: " << pos1 << endl;
//  cout << "pos: " << pos2 << endl;
//  cout << "pos: " << pos3 << endl;
//  int dis = r.distancia('a', 'b');
//  cout << "dis a,b: " << dis << endl;
//  dis = r.distancia('a', 'c');
//  cout << "dis a,c: " << dis << endl;
//  dis = r.distancia('a', 'd');
//  cout << "dis a,d: " << dis << endl;
//  dis = r.distancia('c', 'd');
//  cout << "dis c,d: " << dis << endl;
//  dis = r.distancia('b', 'd');
//  cout << "dis b,d: " << dis << endl;
//  cout << "test sumDists" << endl;
//  bigSet ami;
//  set<char> a;
//  a.insert('a');
//  a.insert('b');
//  ami.insert(a);
//  set<char> b;
//  b.insert('a');
//  b.insert('c');
//  ami.insert(b);
//  set<char> c;
//  c.insert('b');
//  c.insert('d');
//  ami.insert(c);
//  int dists = r.sumaDistancias(ami);
//  cout << "sumDists: " << dists << endl;
//  cout << "hare" << endl;
//  int maxDists = r.maxDistAmistades(ami);
//  cout << "maxDists" << maxDists << endl;
//
//
//  return 0;
//}

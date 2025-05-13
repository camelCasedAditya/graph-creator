#include <iostream>
#include <cstring>
#include "Vertex.h"
#include "Edge.h"
using namespace std;

int main() {

  Vertex* v = new Vertex();
  v->setTable(1, 5, 10);
  int** array = v->getTable();
  cout << array[1][5] << endl;

  Edge* e = new Edge();
  e->setStart(v);
  e->setWeight(25);
  cout << "Weight: " << e->getWeight() << endl;
  cout << "Start: " << e->getStart()->getTable()[1][5] << endl;
  
  return 0;
}

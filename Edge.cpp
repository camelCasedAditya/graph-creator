#include "Edge.h"
#include "Vertex.h"
#include <cstring>
#include <iostream>
using namespace std;

Edge::Edge() {
  start = NULL;
  end = NULL;
  weight = 0;
}
//Edge::~Edge() {
//delete start;
//delete end;
//}

void Edge::setStart(Vertex* newstart) {
  start = newstart;
}
Vertex* Edge::getStart() {
  return start;
}
void Edge::setEnd(Vertex* newend) {
  end = newend;
}
Vertex* Edge::getEnd() {
  return end;
}
void Edge::setWeight(int newweight) {
  weight = newweight;
}
int Edge::getWeight() {
  return weight;
}


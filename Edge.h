#ifndef EDGE_H
#define EDGE_h

#include "Vertex.h"
#include <iostream>
using namespace std;

class Edge {
 public:
  Edge();
  ~Edge();
  void setStart(Vertex* newstart);
  Vertex* getStart();
  void setEnd(Vertex* newend);
  Vertex* getEnd();
  void setWeight(int newweight);
  int getWeight();
 private:
  Vertex* start;
  Vertex* end;
  int weight;
};


#endif

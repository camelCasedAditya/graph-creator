#ifndef VERTEX_H
#define VERTEX_H

#include <iostream>
#include <cstring>
//#include "Edge.h"
using namespace std;

class Vertex {
 public:
  Vertex();
  ~Vertex();
  void setLabel(char* newlabel);
  char* getLabel();
  void setTable(int start, int end, int weight);
  int** getTable();
 private:
  char* label;
  int** table;
};

#endif

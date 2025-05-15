#include "Vertex.h"
#include <iostream>
#include <cstring>
using namespace std;

Vertex::Vertex() {
  label = new char[100];
  table = new int*[21];
  for(int i = 0; i < 21; i++) {
    table[i] = new int[21];
    for(int j = 0; j<21; j++) {
      table[i][j] = 0;
    }
  }
}

Vertex::~Vertex() {
  delete label;
  delete table;
}

void Vertex::setLabel(char* newlabel) {
  strcpy(label, newlabel);
}

char* Vertex::getLabel() {
  return label;
}

void Vertex::setTable(int start, int end, int weight) {
  table[start][end] = weight;
}

int** Vertex::getTable() {
  return table;
}

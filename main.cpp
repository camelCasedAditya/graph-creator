#include <iostream>
#include <cstring>
#include "Vertex.h"
#include "Edge.h"
using namespace std;

void addVertex(char* label, Vertex** array);
void addEdge(char* start, char* end, int weight, Vertex** array);
void printTable(Vertex* v);
void deleteVertex(char* label, Vertex** array);

int MAX = 20;

int main() {

  Vertex* vertices[20];
  for (int i = 0; i < MAX; i++) {
    vertices[i] = NULL;
  }
  
  //Vertex* v = new Vertex();
  //v->setTable(1, 5, 10);
  //int** array = v->getTable();
  //cout << array[1][5] << endl;

  //Edge* e = new Edge();
  //e->setStart(v);
  //e->setWeight(25);
  //cout << "Weight: " << e->getWeight() << endl;
  //cout << "Start: " << e->getStart()->getTable()[1][5] << endl;

  char input[100];
  strcpy(input, "node1");
  addVertex(input, vertices);
  cout << vertices[0]->getLabel() << endl;
  strcpy(input, "node2");
  addVertex(input, vertices);
  char input2[100];
  strcpy(input2, "node1");
  cout << "HERE" << endl;
  addEdge(input, input2, 5, vertices);
  cout << "HERE 2" << endl;
  printTable(vertices[0]);
  strcpy(input, "node2");
  deleteVertex(input, vertices);
  printTable(vertices[0]);
  return 0;
}

void addVertex(char* label, Vertex** array) {
  Vertex* v = new Vertex();
  v->setLabel(label);
  for (int i = 0; i < MAX; i++) {
    if (array[i] == NULL) {
      array[i] = v;
      return;
    }
  }
  cout << "The graph is full" << endl;
  return;
}

void addEdge(char* start, char* end, int weight, Vertex** array) {
  int startIndex = -1;
  Vertex* startNode;
  int endIndex = -1;
  Vertex* endNode;
  cout << "INTO FUNCTION" << endl;
  for (int i = 0; i < MAX; i++) {
    if (array[i] != NULL && strcmp(array[i]->getLabel(), start) == 0) {
      startIndex = i;
      startNode = array[i];
    }
    else if (array[i] != NULL && strcmp(array[i]->getLabel(), end) == 0) {
      endIndex = i;
      endNode = array[i];
    }
  }

  cout << "PASSED FOR LOOP" << endl;
  if (startIndex == -1 || endIndex == -1) {
    cout << "One of the labels you entered does not correspond to an existing node" << endl;
    return;
  }
  else {
    startNode->setTable(startIndex+1, endIndex+1, weight);
    endNode->setTable(startIndex+1, endIndex+1, weight);
  }
}

void printTable(Vertex* v) {
  int** array = v->getTable();
  for (int i = 0; i < MAX+1; i++) {
    for (int j = 0; j<MAX+1; j++) {
      cout << array[i][j] << " ";
    }
    cout << "" << endl;
  }
}

void deleteVertex(char* label, Vertex** array) {
  Vertex* v = NULL;
  int index = -1;
  for(int i = 0; i < MAX; i++) {
    if (array[i] != NULL && strcmp(array[i]->getLabel(), label) == 0) {
      v = array[i];
      index = i;
      array[i] = NULL;
    }
  }

  if (v == NULL || index == -1) {
    cout << "This vertex does not exist" << endl;
    return;
  }
  int** table = v->getTable();
  for (int j = 0; j < MAX+1; j++) {
    if (table[index+1][j] != 0) {
      cout << "in" << endl;
      Vertex* temp = array[j-1];
      temp->setTable(index+1, j, 0);
    }
    else if (table[j][index+1] != 0) {
      cout << "in" << endl;
      Vertex* temp = array[j-1];
      temp->setTable(j, index+1, 0);
    }
  }
  delete v;
  return;
}

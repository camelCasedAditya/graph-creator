#include <iostream>
#include <cstring>
#include "Vertex.h"
#include "Edge.h"
using namespace std;

void addVertex(char* label, Vertex** array);
void addEdge(char* start, char* end, int weight, Vertex** array);
void printTable(Vertex* v);
void deleteVertex(char* label, Vertex** array);
void deleteEdge(char* start, char* end, Vertex** array);
void shortestPathSetup(char* start, char* end, Vertex** array);
void shortestPathSearch(int startIndex, int endIndex, Vertex** array, int* totals);

int main() {

  Vertex* vertices[20];
  for (int i = 0; i < 20; i++) {
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

  //char input[100];
  //strcpy(input, "node1");
  // addVertex(input, vertices);
  //cout << vertices[0]->getLabel() << endl;
  //strcpy(input, "node2");
  // addVertex(input, vertices);
  //char input2[100];
  //strcpy(input2, "node1");
  //cout << "HERE" << endl;
  //addEdge(input, input2, 5, vertices);
  //cout << "HERE 2" << endl;
  //printTable(vertices[0]);
  //strcpy(input, "node2");
  //deleteVertex(input, vertices);
  //printTable(vertices[0]);

  bool running = true;
  while(running == 1) {
    char* input = new char[100];
    cout << "Enter one of the following commands: " << endl;
    cout << "\'ADDVERTEX\' to add a vertex" << endl;
    cout << "\'ADDEDGE\' to add an edge" << endl;
    cout << "\'DELETEVERTEX\' to delete a vertex" << endl;
    cout << "\'DELETEEDGE\' to delete an edge" << endl;
    cout << "\'PATH\' to find the shortest path" << endl;
    cout << "\'PRINT\' to print out the table" << endl;
    cout << "\'QUIT\' to close the program" << endl;
    cin >> input;
    if (strcmp(input, "ADDVERTEX") == 0) {
      cout << "Enter a label for the vertex: " << endl;
      cin >> input;
      addVertex(input, vertices);
    }
    else if (strcmp(input, "ADDEDGE") == 0) {
      char* labelone = new char[100];
      char* labeltwo = new char[100];
      int weight = 0;
      cout << "Enter the label of the start vertex: " << endl;
      cin >> labelone;

      cout << "Enter the label of the end vertex: " << endl;
      cin >> labeltwo;

      cout << "Enter a weight for the edge between 1-100" << endl;
      cin >> weight;
      while (weight <= 0 || weight > 100) {
	cout << "Enter a valid weight between 1-100" << endl;
	cin >> weight;
      }

      addEdge(labelone, labeltwo, weight, vertices);
    }
    else if (strcmp(input, "PRINT") == 0) {

      cout << "Enter the vertex you want to see the adjency table for: " << endl;
      cin >> input;
      for(int i = 0; i < 20; i++) {
	if (vertices[i] != NULL && strcmp(input, vertices[i]->getLabel()) == 0) {
	  printTable(vertices[i]);
	  break;
	}
      }
    }
    else if (strcmp(input, "PATH") == 0) {
      char* labelone = new char[100];
      char* labeltwo = new char[100];
      cout << "Enter the label of the start vertex: " << endl;
      cin >> labelone;

      cout << "Enter the label of the end vertex: " << endl;
      cin >> labeltwo;

      shortestPathSetup(labelone, labeltwo, vertices);
    }
  }
  return 0;
}

void addVertex(char* label, Vertex** array) {
  Vertex* v = new Vertex();
  v->setLabel(label);
  for (int i = 0; i < 20; i++) {
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
  for (int i = 0; i < 20; i++) {
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
  for (int i = 0; i < 21; i++) {
    for (int j = 0; j<21; j++) {
      cout << array[i][j] << " ";
    }
    cout << "" << endl;
  }
}

void deleteVertex(char* label, Vertex** array) {
  Vertex* v = NULL;
  int index = -1;
  for(int i = 0; i < 20; i++) {
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
  for (int j = 0; j < 21; j++) {
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

void deleteEdge(char* start, char* end, Vertex** array) {
  int startIndex = -1;
  Vertex* startNode;
  int endIndex = -1;
  Vertex* endNode;
  cout << "INTO FUNCTION" << endl;
  for (int i = 0; i < 20; i++) {
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
    startNode->setTable(startIndex+1, endIndex+1, 0);
    endNode->setTable(startIndex+1, endIndex+1, 0);
  }
}


void shortestPathSetup(char* start, char* end, Vertex** array) {
  int* totals = new int[20];
  for(int a = 0; a<20; a++) {
    totals[a] = 10000;
  }
  int startIndex = -1;
  Vertex* startNode;
  int endIndex = -1;
  Vertex* endNode;
  cout << "INTO FUNCTION" << endl;
  for (int i = 0; i < 20; i++) {
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
  shortestPathSearch(startIndex, endIndex, array, totals);
  return;
}

void shortestPathSearch(int startIndex, int endIndex, Vertex** array, int* totals) {
  int* distance = totals;
  int visited[20] = {0};
  for (int a = 0; a < 20; a++) {
    if (array[a] == NULL) {
      cout << "NULL: " << a << endl;
      visited[a] = 1;
    }
  }
  distance[startIndex] = 0;
  Vertex* previousVertex[20] = {NULL};
  Vertex* start = array[startIndex];
  Vertex* end = array[endIndex];
  
  for(int i = 0; i < 20; i++) {
    //if (totals[i] != -1) {
    //int** table = array[i]->getTable();
    //for(int j = 1; j<21; j++) {
    //if (table[i+1][j] != 0 && (distance[j-1] > (table[i+1][j]+distance[i]))) {
    //distance[j-1] = table[i+1][j]+distance[i];
    //	}
    //}
    //}
    int shortest = 20*100;
    int index = -1;
    for (int j = 0; j<20; j++) {
      cout << "Visited: " << visited[j];
      cout << "Distance: " << distance[i];
      if (visited[j] == 0 && distance[j] < shortest && distance[j] != -1) {
	shortest = distance[j];
	index = j;
      }
    }
    cout << "here" << endl;
    if (index == -1) {
      continue;
    }
    visited[index] = 1;
    if (array[index] == NULL) {
      cout << distance[endIndex] << endl;
      return;
    }
    int** table = array[index]->getTable();
    for (int k = 1; k < 21; k++) {
      if(table[index+1][k] != 0 && visited[k-1] == 0) {
	int d = table[index+1][k] + distance[k-1];
	if (d < distance[k-1]) {
	  distance[k-1] = d;
	  previousVertex[k-1] = array[index];
	}
      }
    }
  }

  cout << distance[endIndex] << endl;
  return;
}




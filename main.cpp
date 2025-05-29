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

// Test function to verify the graph operations and shortest path algorithm
void runTests() {
  cout << "\n===== RUNNING TESTS =====\n" << endl;
  
  Vertex* vertices[20];
  for (int i = 0; i < 20; i++) {
    vertices[i] = NULL;
  }
  
  // Test 1: Add vertices
  cout << "Test 1: Adding vertices A, B, C, D" << endl;
  char labelA[] = "A";
  char labelB[] = "B";
  char labelC[] = "C";
  char labelD[] = "D";
  
  addVertex(labelA, vertices);
  addVertex(labelB, vertices);
  addVertex(labelC, vertices);
  addVertex(labelD, vertices);
  
  // Test 2: Add edges
  cout << "\nTest 2: Adding edges" << endl;
  addEdge(labelA, labelB, 10, vertices); // A -> B (10)
  addEdge(labelB, labelC, 5, vertices);  // B -> C (5)
  addEdge(labelA, labelC, 20, vertices); // A -> C (20)
  addEdge(labelC, labelD, 7, vertices);  // C -> D (7)
  
  // Test 3: Find shortest path
  cout << "\nTest 3: Finding shortest path from A to D" << endl;
  shortestPathSetup(labelA, labelD, vertices);
  
  // Test 4: Delete edge and test path again
  cout << "\nTest 4: Deleting edge B->C and finding path again" << endl;
  deleteEdge(labelB, labelC, vertices);
  shortestPathSetup(labelA, labelD, vertices);
  
  // Test 5: Delete vertex and test path again
  cout << "\nTest 5: Deleting vertex C and finding path again" << endl;
  deleteVertex(labelC, vertices);
  shortestPathSetup(labelA, labelD, vertices);
  
  // Test 6: Add new connections and test path
  cout << "\nTest 6: Adding new edge A->D and finding path again" << endl;
  addEdge(labelA, labelD, 15, vertices);
  shortestPathSetup(labelA, labelD, vertices);
  
  cout << "\n===== TESTS COMPLETED =====\n" << endl;
}

int main() {

  Vertex* vertices[20];
  for (int i = 0; i < 20; i++) {
    vertices[i] = NULL;
  }
  

  bool running = true;
  while(running == 1) {
    char* input = new char[100];
    cout << "Enter one of the following commands: " << endl;
    cout << "\'ADDVERTEX\' to add a vertex" << endl;
    cout << "\'ADDEDGE\' to add an edge" << endl;
    cout << "\'DELETEVERTEX\' to delete a vertex" << endl;
    cout << "\'DELETEEDGE\' to delete an edge" << endl;
    cout << "\'PATH\' to find the shortest path" << endl;
    cout << "\'PRINT\' to print out the adjaceny table of a vertex" << endl;
    cout << "\'LIST\' to list all vertices" << endl;
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
    else if (strcmp(input, "DELETEVERTEX") == 0) {
      cout << "Enter a label for the vertex: " << endl;
      cin >> input;
      deleteVertex(input, vertices);
    }
    else if (strcmp(input, "DELETEEDGE") == 0) {
      char* labelone = new char[100];
      char* labeltwo = new char[100];
      int weight = 0;
      cout << "Enter the label of the start vertex: " << endl;
      cin >> labelone;

      cout << "Enter the label of the end vertex: " << endl;
      cin >> labeltwo;

      deleteEdge(labelone, labeltwo, vertices);
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
    else if (strcmp(input, "LIST") == 0) {
      cout << "Vertices: " << endl;
      for(int i = 0; i < 20; i++) {
        if (vertices[i] != NULL) {
          cout << vertices[i]->getLabel() << endl;
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
      visited[a] = 1;
    }
  }
  distance[startIndex] = 0;
  int previousVertex[20];
  for (int i = 0; i < 20; i++) {
    previousVertex[i] = -1;
  }
  
  for(int i = 0; i < 20; i++) {
    // Find the vertex with the minimum distance
    int shortest = 10000;
    int index = -1;
    for (int j = 0; j < 20; j++) {
      if (visited[j] == 0 && distance[j] < shortest) {
        shortest = distance[j];
        index = j;
      }
    }
    
    if (index == -1) {
      break; // No more reachable vertices
    }
    
    visited[index] = 1;
    
    if (index == endIndex) {
      break; // Found the destination
    }
    
    if (array[index] == NULL) {
      continue;
    }
    
    int** table = array[index]->getTable();
    for (int k = 1; k < 21; k++) {
      if (table[index+1][k] != 0 && visited[k-1] == 0) {
        int d = distance[index] + table[index+1][k];
        if (d < distance[k-1]) {
          distance[k-1] = d;
          previousVertex[k-1] = index;
        }
      }
    }
  }

  // Print the shortest path
  if (distance[endIndex] == 10000) {
    cout << "No path exists between " << array[startIndex]->getLabel() << " and " << array[endIndex]->getLabel() << endl;
    return;
  }
  
  int current = endIndex;
  int path[20];
  int pathLength = 0;
  
  while (current != -1) {
    path[pathLength] = current;
    pathLength+=1;
    current = previousVertex[current];
  }
  
  // Print the path in correct order
  cout << "Shortest path cost: " << distance[endIndex] << endl;
  cout << "Path: ";
  for (int i = pathLength - 1; i >= 0; i--) {
    cout << array[path[i]]->getLabel();
    if (i > 0) cout << " -> ";
  }
  cout << endl;
  
  return;
}




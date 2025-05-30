#include <iostream>
#include <cstring>
#include "Vertex.h"
using namespace std;

void addVertex(char* label, Vertex** array);
void addEdge(char* start, char* end, int weight, Vertex** array);
void printTable(Vertex* v);
void deleteVertex(char* label, Vertex** array);
void deleteEdge(char* start, char* end, Vertex** array);
void shortestPathSetup(char* start, char* end, Vertex** array);
void shortestPathSearch(int startIndex, int endIndex, Vertex** array, int* totals);

int main() {

  // Setup array to store all vertices in the graph
  Vertex* vertices[20];
  for (int i = 0; i < 20; i++) {
    vertices[i] = NULL;
  }
  
  // Loop to get user input and call the functions
  bool running = true;
  while(running == 1) {

    // Print instructions and get user input
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
    // Call add vertex function and ask for vertex label
    if (strcmp(input, "ADDVERTEX") == 0) {
      cout << "Enter a label for the vertex: " << endl;
      cin >> input;
      addVertex(input, vertices);
    }
    // Call add edge function and get needed info from the user
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
    // Calls delete vertex function and gets desired vertex from user to delete
    else if (strcmp(input, "DELETEVERTEX") == 0) {
      cout << "Enter a label for the vertex: " << endl;
      cin >> input;
      deleteVertex(input, vertices);
    }
    //Calls delete edge function and gets desired edge from user to delete
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
    // Function to print an adjenceny table of any vertex (used for debugging)
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
    // Calls function to list all vertices in the table
    else if (strcmp(input, "LIST") == 0) {
      cout << "Vertices: " << endl;
      for(int i = 0; i < 20; i++) {
        if (vertices[i] != NULL) {
          cout << vertices[i]->getLabel() << endl;
        }
      }
    }
    // Calls function to find the shortest path and takes in the two vertexes
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
// Function to add a vertex
void addVertex(char* label, Vertex** array) {
  // Create a new vertex object
  Vertex* v = new Vertex();
  v->setLabel(label);

  // Add vertex to next null spot in the array
  for (int i = 0; i < 20; i++) {
    if (array[i] == NULL) {
      array[i] = v;
      return;
    }
  }
  cout << "The graph is full" << endl;
  return;
}

// Function to add an edge
void addEdge(char* start, char* end, int weight, Vertex** array) {

  // Initialize variables needed for the function
  int startIndex = -1;
  Vertex* startNode;
  int endIndex = -1;
  Vertex* endNode;

  // Search through the array of vertices
  for (int i = 0; i < 20; i++) {

    // If the vertex matches the start label we store it as the start vertex
    if (array[i] != NULL && strcmp(array[i]->getLabel(), start) == 0) {
      startIndex = i;
      startNode = array[i];
    }
    // If the vertex matches the end label we store it as the end vertex
    else if (array[i] != NULL && strcmp(array[i]->getLabel(), end) == 0) {
      endIndex = i;
      endNode = array[i];
    }
  }
  // If either vertex was not found we return and inform the user
  if (startIndex == -1 || endIndex == -1) {
    cout << "One of the labels you entered does not correspond to an existing node" << endl;
    return;
  }
  // Add the edge weight into the right spot in both vertex's adjaceny table to signify and edge
  else {
    startNode->setTable(startIndex+1, endIndex+1, weight);
    endNode->setTable(startIndex+1, endIndex+1, weight);
  }
}

// Function to print an adjencey table
void printTable(Vertex* v) {
  // Get the adjency table of the vertex
  int** array = v->getTable();
  // Loop through the array and print out each item
  for (int i = 0; i < 21; i++) {
    for (int j = 0; j<21; j++) {
      cout << array[i][j] << " ";
    }
    cout << "" << endl;
  }
}

// Function to delete a vertex
void deleteVertex(char* label, Vertex** array) {
  // Initialize variables
  Vertex* v = NULL;
  int index = -1;

  // Search for vertex in the vertices array based on the inputted label
  for(int i = 0; i < 20; i++) {
    if (array[i] != NULL && strcmp(array[i]->getLabel(), label) == 0) {
      v = array[i];
      index = i;
      array[i] = NULL;
    }
  }

  // If the vertex does not exisit, inform the user and exit function
  if (v == NULL || index == -1) {
    cout << "This vertex does not exist" << endl;
    return;
  }

  // Get the adjancey table of the vertex
  int** table = v->getTable();

  // Loop through all the edges connected to the vertex and remove them from the other vertex's adjancey table
  for (int j = 0; j < 21; j++) {
    if (table[index+1][j] != 0) {
      Vertex* temp = array[j-1];
      temp->setTable(index+1, j, 0);
    }
    else if (table[j][index+1] != 0) {
      Vertex* temp = array[j-1];
      temp->setTable(j, index+1, 0);
    }
  }
  delete v;
  return;
}

// Function to delete and edge
void deleteEdge(char* start, char* end, Vertex** array) {

  // Initalize variables to store vertices
  int startIndex = -1;
  Vertex* startNode;
  int endIndex = -1;
  Vertex* endNode;

  // Loop through array and store start and end vertices
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

  // Exit function if either vertex is not found
  if (startIndex == -1 || endIndex == -1) {
    cout << "One of the labels you entered does not correspond to an existing node" << endl;
    return;
  }
  // remove the edge from the adjency table for both nodes
  else {
    startNode->setTable(startIndex+1, endIndex+1, 0);
    endNode->setTable(startIndex+1, endIndex+1, 0);
  }
}

// Function to find the shortest path between two vertices
void shortestPathSetup(char* start, char* end, Vertex** array) {

  // set the totals array to 10000 (any big number works) to set up for the algorithm
  int* totals = new int[20];
  for(int a = 0; a<20; a++) {
    totals[a] = 10000;
  }

  // Get the starting and ending vertices for the path finding algorithm
  int startIndex = -1;
  Vertex* startNode;
  int endIndex = -1;
  Vertex* endNode;
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

  // Exit function if start or end vertex don't exist
  if (startIndex == -1 || endIndex == -1) {
    cout << "One of the labels you entered does not correspond to an existing node" << endl;
    return;
  }
  // Call path finding function
  shortestPathSearch(startIndex, endIndex, array, totals);
  return;
}

// Path finding function with dijkstras algorithm
void shortestPathSearch(int startIndex, int endIndex, Vertex** array, int* totals) {

  // Create an array to track the visited vertices and distances
  int* distance = totals;
  int visited[20] = {0};
  // Set all the null array spots to visited
  for (int a = 0; a < 20; a++) {
    if (array[a] == NULL) {
      visited[a] = 1;
    }
  }
  // Set the distance to the starting vertex to 0
  distance[startIndex] = 0;

  // Create array to store previous vertex index in main graph array
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
    
    // If there is no shortest distance then there is no vertex left that can be reached
    if (index == -1) {
      break;
    }
    
    // Register the vertex we visited in the visited array
    visited[index] = 1;
    
    // If we visited the end vertex we exit the loop
    if (index == endIndex) {
      break;
    }
    
    // If the vertex does not exist in the graph we loop to the next vertex
    if (array[index] == NULL) {
      continue;
    }
    
    // Get the adjeceny table of the vertex being visited
    int** table = array[index]->getTable();

    // Loop through all the edges connected to the vertex in the geaph
    for (int k = 1; k < 21; k++) {
      // If the distance to a end vertex on one of the edges is less than the stored distance, we update the distance
      if (table[index+1][k] != 0 && visited[k-1] == 0) {
        int d = distance[index] + table[index+1][k];
        if (d < distance[k-1]) {
          distance[k-1] = d;
          previousVertex[k-1] = index;
        }
      }
    }
  }

  // If the distance is 10000, then no path has been found
  if (distance[endIndex] == 10000) {
    cout << "The is no path between " << array[startIndex]->getLabel() << " and " << array[endIndex]->getLabel() << endl;
    return;
  }
  
  // Create a current vertex index and path array
  int current = endIndex;
  int path[20];
  int pathLength = 0;
  
  // Move backwards through the previousVertex array and add the vertices to the path array
  while (current != -1) {
    path[pathLength] = current;
    pathLength+=1;
    current = previousVertex[current];
  }
  
  // Print the path in the correct order
  cout << "Shortest path cost: " << distance[endIndex] << endl;
  cout << "Path: ";
  // Loop through the path array and print out the label of the vertex
  for (int i = pathLength - 1; i >= 0; i--) {
    cout << array[path[i]]->getLabel();
    if (i > 0) cout << " -> ";
  }
  cout << "" << endl;
  
  return;
}




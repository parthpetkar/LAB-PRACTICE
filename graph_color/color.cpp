#include <iostream>
#include <vector>
#include <cstring>
using namespace std;

// Number of vertices in the graph
#define V 4

// A utility function to print the solution
void printSolution(int color[]) {
    cout << "Solution Exists: Following are the assigned colors" << "\n";
    for (int i = 0; i < V; i++)
        cout << "Vertex " << i << " --->  Color " << color[i] << "\n";
}

// A greedy function to assign colors to vertices
void greedyGraphColoring(const vector<vector<int>>& adjList) {
    int color[V];

    // Assign the first color to the first vertex
    color[0] = 0;

    // Initialize all other vertices as uncolored (indicated by -1)
    for (int i = 1; i < V; i++)
        color[i] = -1;

    // Boolean array to keep track of available colors. True value means color is available.
    bool available[V];
    memset(available, true, sizeof(available));

    // Assign colors to remaining vertices
    for (int u = 1; u < V; u++) {

        // Mark colors used by adjacent vertices as unavailable
        for (int neighbor : adjList[u]) {
            if (color[neighbor] != -1)
                available[color[neighbor]] = false;
        }

        // Find the first available color
        int cr;
        for (cr = 0; cr < V; cr++) {
            if (available[cr]) {
                break;
            }
        }

        // Assign the found color to the current vertex
        color[u] = cr;

        // Reset the available array for the next iteration
        memset(available, true, sizeof(available));
    }

    // Print the solution
    printSolution(color);
}

// Driver code
int main() {
    /* Create the following graph and test whether it is colorable
      (3)---(2)
       |   / |
       |  /  |
       | /   |
      (0)---(1)
    */
    vector<vector<int>> adjList(V);

    // Creating adjacency list
    adjList[0] = {1, 2, 3};
    adjList[1] = {0, 2};
    adjList[2] = {0, 1, 3};
    adjList[3] = {0, 2};

    // Function call for greedy graph coloring
    greedyGraphColoring(adjList);
    return 0;
}

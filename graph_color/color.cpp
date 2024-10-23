#include <iostream>
#include <vector>
#include <cstring>
using namespace std;

#define V 4

// A utility function to print the solution
void printSolution(int color[])
{
    cout << "Solution Exists: Following are the assigned colors" << "\n";
    for (int i = 0; i < V; i++)
        cout << "Vertex " << i << " --->  Color " << color[i] << "\n";
}

// A greedy function to assign colors to vertices
void greedyGraphColoring(bool graph[V][V])
{
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
        for (int i = 0; i < V; i++) {
            if (graph[u][i] && color[i] != -1)
                available[color[i]] = false;
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
int main()
{
    /* Create following graph and test whether it is 3 colorable
      (3)---(2)
       |   / |
       |  /  |
       | /   |
      (0)---(1)
    */
    bool graph[V][V] = {
        { 0, 1, 1, 1 },
        { 1, 0, 1, 0 },
        { 1, 1, 0, 1 },
        { 1, 0, 1, 0 },
    };

    // Function call for greedy graph coloring
    greedyGraphColoring(graph);
    return 0;
}

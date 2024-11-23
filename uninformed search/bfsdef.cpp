#include <iostream>
#include <vector>
#include <queue>
#include <fstream> // For file handling
#include <string>
#include <utility> // For std::pair

using namespace std;

class Graph {
    int V; // Number of vertices
    vector<vector<int>> adjList; // Adjacency list

public:
    Graph(int V) {
        this->V = V;
        adjList.resize(V);
    }

    // Add edge to the graph (undirected by default)
    void addEdge(int u, int v) {
        adjList[u].push_back(v);
        adjList[v].push_back(u); // Comment out for directed graph
    }

    // Breadth-First Search (BFS) with edge tracking
    void bfs(int start) {
        vector<bool> visited(V, false);
        queue<int> q;

        visited[start] = true;
        q.push(start);

        cout << "BFS traversal starting from vertex " << start << ": ";

        while (!q.empty()) {
            int node = q.front();
            q.pop();
            cout << node << " ";

            for (int neighbor : adjList[node]) {
                if (!visited[neighbor]) {
                    visited[neighbor] = true;
                    q.push(neighbor);
                }
            }
        }
        cout << endl;
    }

    // Depth-First Search (DFS) with edge tracking
    void dfsUtil(int node, vector<bool>& visited) {
        visited[node] = true;
        cout << node << " ";

        for (int neighbor : adjList[node]) {
            if (!visited[neighbor]) {
                dfsUtil(neighbor, visited);
            }
        }
    }

    void dfs(int start) {
        vector<bool> visited(V, false);
        cout << "DFS traversal starting from vertex " << start << ": ";
        dfsUtil(start, visited);
        cout << endl;
    }
};

int main() {
    Graph g(6); // Example graph with 6 vertices

    g.addEdge(0, 1);
    g.addEdge(0, 3);
    g.addEdge(0, 4);
    g.addEdge(1, 2);
    g.addEdge(1, 5);
    g.addEdge(4, 5);
    g.addEdge(2, 5);

    // Perform BFS and save traversal
    g.bfs(0);

    // Perform DFS and save traversal
    g.dfs(0);

    return 0;
}

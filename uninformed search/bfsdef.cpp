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
    vector<pair<int, int>> bfsEdges; // Edges traversed during BFS
    vector<pair<int, int>> dfsEdges; // Edges traversed during DFS

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
                    bfsEdges.push_back({node, neighbor}); // Track traversed edges
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
                dfsEdges.push_back({node, neighbor}); // Track traversed edges
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

    // Function to output graph in Graphviz (DOT) format and save to a file, highlighting traversal
    void saveGraphvizWithTraversalToFile(const string& filename, const string& traversalType) {
        ofstream file(filename);

        if (!file.is_open()) {
            cerr << "Error: Could not open file " << filename << endl;
            return;
        }

        file << "graph G {" << endl;
        file << "  node [shape=circle];" << endl;

        // Default edges (non-traversed)
        for (int u = 0; u < V; ++u) {
            for (int v : adjList[u]) {
                if (u < v) // Print each edge once for undirected graph
                    file << "  " << u << " -- " << v << " [color=gray];" << endl;
            }
        }

        // Highlight traversed edges
        vector<pair<int, int>> traversedEdges = (traversalType == "BFS") ? bfsEdges : dfsEdges;
        int edgeCount = 0;
        for (const auto& edge : traversedEdges) {
            file << "  " << edge.first << " -- " << edge.second
                 << " [color=red, penwidth=2, label=\"" << ++edgeCount << "\"];" << endl;
        }

        file << "}" << endl;
        file.close();
        cout << "Graph with " << traversalType << " traversal saved to " << filename << endl;
    }
};

int main() {
    Graph g(6); // Example graph with 6 vertices

    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(1, 3);
    g.addEdge(2, 4);
    g.addEdge(3, 4);
    g.addEdge(4, 5);

    // Perform BFS and save traversal
    g.bfs(0);
    g.saveGraphvizWithTraversalToFile("bfs_traversal.dot", "BFS");

    // Perform DFS and save traversal
    g.dfs(0);
    g.saveGraphvizWithTraversalToFile("dfs_traversal.dot", "DFS");

    return 0;
}

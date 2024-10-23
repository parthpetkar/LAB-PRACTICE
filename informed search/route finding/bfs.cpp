#include <bits/stdc++.h>
#include <vector>
#include <string>
#include <map>
#include <queue>
using namespace std;

class Node
{
public:
    string name;
    int heuristic;
    vector<Node *> adj; // No weights, only neighbor nodes

    Node(string n, int h) : name(n), heuristic(h) {}
};

vector<string> bestFirst(Node *start, Node *goal)
{
    // Min-heap priority queue: first is heuristic, second is Node pointer
    priority_queue<pair<int, Node *>, vector<pair<int, Node *>>, greater<pair<int, Node *>>> pq;

    map<Node *, bool> visited;
    map<Node *, Node *> parent;

    pq.push({start->heuristic, start});

    while (!pq.empty())
    {
        Node *current = pq.top().second;
        pq.pop();

        cout << current->name << " " << current->heuristic << endl;

        // If the goal is found
        if (current == goal)
        {
            vector<string> path;

            // Construct the path from start to goal
            while (current != start)
            {
                path.push_back(current->name);
                current = parent[current];
            }
            path.push_back(start->name);
            reverse(path.begin(), path.end());

            return path;
        }

        visited[current] = true;

        for (Node *neighbor : current->adj)
        {
            // If the neighbor has not been visited, process it
            if (!visited[neighbor])
            {
                pq.push({neighbor->heuristic, neighbor});
                parent[neighbor] = current;
            }
        }
    }

    cout << "Not reachable" << endl;
    return vector<string>();
}

int main()
{
    // Creating simple nodes for testing
    Node *A = new Node("A", 10);
    Node *B = new Node("B", 5);
    Node *C = new Node("C", 3);
    Node *D = new Node("D", 0); // Goal node

    // Adding edges (unweighted graph)
    A->adj = {B, C};
    B->adj = {D};
    C->adj = {D};

    cout << "Using Best First Search algorithm - " << endl;

    // Calling Best First Search to find the path from A to D
    vector<string> path = bestFirst(A, D);

    // Print the path
    cout << "Path: ";
    for (const auto &city : path)
    {
        cout << city;
        if (&city != &path.back())
            cout << " -> ";
    }
    cout << endl;

    return 0;
}

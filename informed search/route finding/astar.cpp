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
    int heuristic; // h(n): Heuristic estimate to goal
    vector<pair<Node *, int>> adj;

    Node(string n, int h) : name(n), heuristic(h) {}
};

vector<string> aStar(Node *start, Node *goal, map<Node *, int> &distances)
{
    // Priority queue where each element is a pair of (totalCost, node)
    priority_queue<pair<int, Node *>, vector<pair<int, Node *>>, greater<pair<int, Node *>>> pq;

    map<Node *, bool> visited;    // To track visited nodes
    map<Node *, Node *> parent;   // To track the path

    distances[start] = 0; // g(n): Distance from start to start is 0
    pq.push({start->heuristic, start}); // Push the start node with heuristic h(start)

    while (!pq.empty())
    {
        Node *current = pq.top().second;
        int currentCost = pq.top().first; // This cost is f(n) = g(n) + h(n)
        pq.pop();

        // If the current node is the goal, reconstruct the path
        if (current == goal)
        {
            vector<string> path;
            int distance = distances[current]; // g(goal) value
            while (current != start)
            {
                path.push_back(current->name);
                current = parent[current];
            }
            path.push_back(start->name);
            reverse(path.begin(), path.end());
            cout << "Distance: " << distance << endl;
            return path;
        }

        visited[current] = true;

        // Explore neighbors of the current node
        for (auto &edge : current->adj)
        {
            Node *neighbourNode = edge.first;
            int edgeWeight = edge.second;

            int newDistance = distances[current] + edgeWeight; // g(neighbour) = g(current) + edge weight

            // If the node is not visited or we find a shorter path
            if (!visited[neighbourNode] || newDistance < distances[neighbourNode])
            {
                parent[neighbourNode] = current;
                distances[neighbourNode] = newDistance; // Update g(neighbour)

                // f(n) = g(n) + h(n)
                int totalCost = newDistance + neighbourNode->heuristic;
                pq.push({totalCost, neighbourNode});
            }
        }
    }

    cout << "Not reachable" << endl;
    return vector<string>();
}

int main()
{
    // Create simple nodes
    Node *n1 = new Node("A", 4);
    Node *n2 = new Node("B", 2);
    Node *n3 = new Node("C", 0); // Goal node
    Node *n4 = new Node("D", 3);

    // Set up simple adjacency lists (edges)
    n1->adj = {{n2, 1}, {n4, 5}}; // A -> B (1), A -> D (5)
    n2->adj = {{n3, 2}, {n1, 1}}; // B -> C (2), B -> A (1)
    n3->adj = {};                 // Goal node has no outgoing edges
    n4->adj = {{n3, 2}};          // D -> C (2)

    // Hardcode the start and goal
    Node *start = n1; // Start at A
    Node *goal = n3;  // Goal is C

    map<Node *, int> distances;
    cout << "Using A* Search algorithm - " << endl;

    // Perform A* Search
    vector<string> path = aStar(start, goal, distances);

    // Print the path
    cout << "Path: ";
    for (const auto &city : path)
    {
        cout << city;
        if (&city != &path.back()) // Avoid printing "->" after the last city
            cout << " -> ";
    }
    cout << endl;

    return 0;
}

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
    Node *s = new Node("S", 5);
    Node *a = new Node("A", 3);
    Node *b = new Node("B", 4);
    Node *c = new Node("C", 2); // Goal node
    Node *d = new Node("D", 6);
    Node *g = new Node("G", 0);

    // Set up simple adjacency lists (edges)
    s->adj = {{a, 1}, {g, 10}}; // A -> B (1), A -> D (5)
    a->adj = {{c, 2}, {b, 2}}; // B -> C (2), B -> A (1)
    b->adj = {{d, 5}};                 // Goal node has no outgoing edges
    c->adj = {{d, 3}, {g, 4}};          // D -> C (2)
    d->adj = {{g, 2}};          // D -> C (2)
    g->adj = {};          // D -> C (2)

    // Hardcode the start and goal
    Node *start = s; // Start at A
    Node *goal = g;  // Goal is C

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

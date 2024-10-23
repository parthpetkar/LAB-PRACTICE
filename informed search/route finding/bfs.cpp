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
    vector<pair<Node *, int>> adj;

    Node(string n, int h) : name(n), heuristic(h) {}
};

vector<string> bestFirst(Node *start, Node *goal, map<Node *, int> &distances)
{
    // Min-heap priority queue: first is heuristic, second is Node pointer
    priority_queue<pair<int, Node *>, vector<pair<int, Node *>>, greater<pair<int, Node *>>> pq;

    map<Node *, int> visited;
    map<Node *, Node *> parent;

    pq.push({start->heuristic, start});
    distances[start] = 0;

    while (!pq.empty())
    {
        Node *current = pq.top().second;
        int currentH = pq.top().first;
        pq.pop();

        cout << current->name << " " << currentH << endl;

        if (current == goal)
        {
            vector<string> path;
            int distance = distances[current];

            // Construct the path from start to goal
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

        visited[current] = currentH;

        for (auto &edge : current->adj)
        {
            Node *neighbourNode = edge.first;
            int neighbourH = neighbourNode->heuristic;
            int edgeWeight = edge.second;
            int newDistance = distances[current] + edgeWeight;

            // If the neighbor is not visited or if a shorter path is found
            if (visited.find(neighbourNode) == visited.end() || newDistance < distances[neighbourNode])
            {
                pq.push({neighbourH, neighbourNode});
                parent[neighbourNode] = current;
                distances[neighbourNode] = newDistance;
            }
        }
    }
    cout << "Not reachable" << endl;
    return vector<string>();
}

int main()
{
    // Creating nodes
    Node *n1 = new Node("Arad", 366);
    Node *n2 = new Node("Zerind", 374);
    Node *n3 = new Node("Oradea", 380);
    Node *n4 = new Node("Sibiu", 253);
    Node *n5 = new Node("Timisoara", 329);
    Node *n6 = new Node("Lugoj", 244);
    Node *n7 = new Node("Mehadia", 241);
    Node *n8 = new Node("Craiova", 160);
    Node *n9 = new Node("Drobeta", 242);
    Node *n10 = new Node("Eforie", 161);
    Node *n11 = new Node("Fagaras", 176);
    Node *n12 = new Node("Giurgiu", 77);
    Node *n13 = new Node("Bucharest", 0);
    Node *n14 = new Node("Hirsova", 151);
    Node *n15 = new Node("Iasi", 226);
    Node *n16 = new Node("Neamt", 234);
    Node *n17 = new Node("Pitesti", 98);
    Node *n18 = new Node("Rimnicu Vilcea", 193);
    Node *n19 = new Node("Vaslui", 199);
    Node *n20 = new Node("Urziceni", 80);

    // Adding edges
    n1->adj = {{n2, 75}, {n4, 140}, {n5, 118}};
    n2->adj = {{n1, 75}, {n3, 71}};
    n3->adj = {{n2, 71}, {n4, 151}};
    n4->adj = {{n1, 140}, {n11, 99}, {n3, 151}, {n18, 80}};
    n5->adj = {{n1, 118}, {n6, 111}};
    n6->adj = {{n5, 111}, {n7, 70}};
    n7->adj = {{n6, 70}, {n9, 75}};
    n8->adj = {{n9, 120}, {n18, 146}, {n17, 138}};
    n9->adj = {{n7, 75}, {n8, 120}};
    n10->adj = {{n14, 86}};
    n11->adj = {{n4, 99}, {n13, 211}};
    n12->adj = {{n13, 90}};
    n13->adj = {{n12, 90}, {n17, 101}, {n20, 85}};
    n14->adj = {{n10, 86}, {n20, 98}};
    n15->adj = {{n16, 87}, {n19, 92}};
    n16->adj = {{n15, 87}};
    n17->adj = {{n18, 97}, {n13, 101}, {n8, 138}};
    n18->adj = {{n4, 80}, {n17, 97}, {n8, 146}};
    n19->adj = {{n15, 92}, {n20, 152}};
    n20->adj = {{n19, 142}, {n14, 98}, {n13, 85}};

    map<Node *, int> distances;
    cout << "Using Best First Search algorithm - " << endl;

    // Calling Best First Search to find the path from Arad to Bucharest
    vector<string> path = bestFirst(n1, n13, distances);

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

#include <iostream>
#include <vector>
using namespace std;

class Graph
{
private:
    int V;
    vector<pair<int, int>> adj[100];

public:
    Graph(int vertices) { V = vertices; }
    void addEdge(int u, int v, int weight)
    {
        adj[u].push_back({v, weight});
        adj[v].push_back({u, weight});
    }
    void display()
    {
        for (int i = 0; i < V; i++)
        {
            cout << "Vertex " << i << " : ";
            for (auto edge : adj[i])
                cout << "(" << edge.first << "," << edge.second << ") ";
            cout << endl;
        }
    }
};
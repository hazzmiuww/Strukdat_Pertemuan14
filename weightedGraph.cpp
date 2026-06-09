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

int main()
{
    Graph g(4);
    g.addEdge(0, 1, 5); // vertex 0-1, bobot 5
    g.addEdge(0, 2, 2); // vertex 0-2, bobot 2
    g.addEdge(1, 3, 3); // vertex 1-3, bobot 3
    g.addEdge(2, 3, 1); // vertex 2-3, bobot 1
    g.display();
    return 0;
}
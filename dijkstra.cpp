#include <iostream>
#include <vector>
#include <queue>
using namespace std;

const int INF = 1000000;
vector<pair<int, int>> graph[100];

void dijkstra(int start, int V)
{
    vector<int> dist(V, INF);
    priority_queue<pair<int, int>,
                   vector<pair<int, int>>,
                   greater<pair<int, int>>>
        pq;

    dist[start] = 0;
    pq.push({0, start});

    while (!pq.empty())
    {
        int u = pq.top().second;
        pq.pop();
        for (auto edge : graph[u])
        {
            int v = edge.first;
            int w = edge.second;
            if (dist[v] > dist[u] + w)
            {
                dist[v] = dist[u] + w;
                pq.push({dist[v], v});
            }
        }
    }

    cout << "Jarak Terpendek" << endl;
    for (int i = 0; i < V; i++)
        cout << i << " : " << dist[i] << endl;
}
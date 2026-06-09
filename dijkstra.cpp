#include <iostream>
#include <vector>
#include <queue>
using namespace std;

const int INF = 1000000;
vector<pair<int, int>> graph[100];

void dijkstra(int start, int V)
{
    vector<int> dist(V, INF);
    priority_queue<
        pair<int, int>,
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

    cout << "Jarak Terpendek dari vertex " << start << ":" << endl;
    for (int i = 0; i < V; i++)
        cout << "  ke " << i << " : " << dist[i] << endl;
}

int main()
{
    // Studi kasus: Surabaya(0) - Sidoarjo(1) - Gresik(2)
    graph[0].push_back({1, 5}); // Surabaya - Sidoarjo, 5 km
    graph[1].push_back({0, 5});
    graph[0].push_back({2, 3}); // Surabaya - Gresik, 3 km
    graph[2].push_back({0, 3});
    graph[1].push_back({2, 4}); // Sidoarjo - Gresik, 4 km
    graph[2].push_back({1, 4});

    dijkstra(0, 3);
    return 0;
}
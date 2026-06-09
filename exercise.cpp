#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <string>
#include <climits>
#include <algorithm>
using namespace std;

const int INF = INT_MAX;

void dfsHelper(int v, vector<vector<int>> &adj, vector<bool> &visited, vector<string> &names)
{
    visited[v] = true;
    cout << "  -> " << names[v] << "\n";
    for (int u : adj[v])
        if (!visited[u])
            dfsHelper(u, adj, visited, names);
}

void runDFS(vector<vector<int>> &adj, int V, vector<string> &names, int start)
{
    vector<bool> visited(V, false);
    cout << "\n[DFS] Telusuri semua teman yang terhubung dari " << names[start] << ":\n";
    dfsHelper(start, adj, visited, names);
}

void runBFS(vector<vector<int>> &adj, int V, vector<string> &names, int start)
{
    vector<bool> visited(V, false);
    vector<int> level(V, -1);
    queue<int> q;
    visited[start] = true;
    level[start] = 0;
    q.push(start);
    cout << "\n[BFS] Tingkat pertemanan dari " << names[start] << ":\n";
    while (!q.empty())
    {
        int v = q.front();
        q.pop();
        cout << "  Level " << level[v] << " : " << names[v];
        if (level[v] == 0)
            cout << " (kamu sendiri)";
        else if (level[v] == 1)
            cout << " (teman langsung)";
        else
            cout << " (teman dari teman, " << level[v] << " langkah)";
        cout << "\n";
        for (int u : adj[v])
        {
            if (!visited[u])
            {
                visited[u] = true;
                level[u] = level[v] + 1;
                q.push(u);
            }
        }
    }
}

void displayWeightedGraph(vector<vector<pair<int, int>>> &wadj, int V, vector<string> &names)
{
    cout << "\n[WEIGHTED GRAPH] Representasi jaringan sosial berbobot:\n";
    for (int i = 0; i < V; i++)
    {
        cout << "  " << names[i] << " -> ";
        for (auto edge : wadj[i])
            cout << names[edge.first] << "(jarak:" << edge.second << ") ";
        cout << "\n";
    }
}

void runDijkstra(vector<vector<pair<int, int>>> &wadj, int V, vector<string> &names, int start)
{
    vector<int> dist(V, INF);
    vector<int> prev(V, -1);
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    dist[start] = 0;
    pq.push({0, start});
    while (!pq.empty())
    {
        int d = pq.top().first, u = pq.top().second;
        pq.pop();
        if (d > dist[u])
            continue;
        for (auto edge : wadj[u])
        {
            int v = edge.first, w = edge.second;
            if (dist[u] + w < dist[v])
            {
                dist[v] = dist[u] + w;
                prev[v] = u;
                pq.push({dist[v], v});
            }
        }
    }
    cout << "\n[DIJKSTRA] Jalur hubungan terpendek dari " << names[start] << ":\n";
    for (int i = 0; i < V; i++)
    {
        if (i == start)
            continue;
        cout << "  " << names[start] << " -> " << names[i] << " : ";
        if (dist[i] == INF)
        {
            cout << "tidak terhubung\n";
            continue;
        }
        cout << "total jarak = " << dist[i] << " | jalur: ";
        vector<int> path;
        for (int cur = i; cur != -1; cur = prev[cur])
            path.push_back(cur);
        reverse(path.begin(), path.end());
        for (int j = 0; j < (int)path.size(); j++)
        {
            cout << names[path[j]];
            if (j < (int)path.size() - 1)
                cout << " -> ";
        }
        cout << "\n";
    }
}

int main()
{
    cout << "============================================================\n";
    cout << "     SIMULASI JARINGAN SOSIAL - STRUKTUR DATA GRAF\n";
    cout << "============================================================\n";

    int V = 8;
    vector<string> names = {"Andi", "Budi", "Citra", "Dina", "Eko", "Fara", "Gilang", "Hana"};

    cout << "\n[USERS] Daftar pengguna:\n";
    for (int i = 0; i < V; i++)
        cout << "  ID " << i << " : " << names[i] << "\n";

    vector<vector<int>> adj(V);
    auto addEdge = [&](int u, int v)
    { adj[u].push_back(v); adj[v].push_back(u); };

    addEdge(0, 1);
    addEdge(0, 2);
    addEdge(1, 3);
    addEdge(1, 4);
    addEdge(2, 4);
    addEdge(2, 5);
    addEdge(3, 6);
    addEdge(4, 7);
    addEdge(5, 6);
    addEdge(6, 7);

    cout << "\n[ADJACENCY LIST] Jaringan pertemanan:\n";
    for (int i = 0; i < V; i++)
    {
        cout << "  " << names[i] << " -> ";
        for (int u : adj[i])
            cout << names[u] << " ";
        cout << "\n";
    }

    runDFS(adj, V, names, 0);
    runBFS(adj, V, names, 0);

    vector<vector<pair<int, int>>> wadj(V);
    auto addWE = [&](int u, int v, int w)
    {
        wadj[u].push_back({v, w});
        wadj[v].push_back({u, w});
    };

    addWE(0, 1, 1);
    addWE(0, 2, 2);
    addWE(1, 3, 3);
    addWE(1, 4, 4);
    addWE(2, 4, 2);
    addWE(2, 5, 5);
    addWE(3, 6, 2);
    addWE(4, 7, 3);
    addWE(5, 6, 1);
    addWE(6, 7, 4);

    displayWeightedGraph(wadj, V, names);
    runDijkstra(wadj, V, names, 0);

    cout << "\n============================================================\n";
    cout << "                   SIMULASI SELESAI\n";
    cout << "============================================================\n";

    return 0;
}
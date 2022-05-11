#include <bits/stdc++.h>
using namespace std;

void add_edge(vector<int> adj[], int src, int dest) {
    adj[src].push_back(dest);
    adj[dest].push_back(src);
}

void remove(vector<int> adj[], int node) {
   vector<int> neighbor = adj[node]; 
   // neighbor is a vector with all vertices adjacent to node
   for (int i = 0; i < neighbor.size(); i++) {
      for (int j = 0; j < adj[neighbor[i]].size(); j++) {
         if (adj[neighbor[i]].at(j) == node) {
            adj[neighbor[i]].erase(adj[neighbor[i]].begin() + j);
         }
      }
   }
   adj[node].clear();
   return;
}

bool BFS(vector<int> adj[], int src, int dest, int v,
         int pred[], int dist[])
{
    // a queue to maintain queue of vertices whose
    // adjacency list is to be searched 
    list<int> queue;
 
    // stores the information which vertex is 
    // reached at least once in the BFS
    bool visited[v];
 
    // all vertices are unvisited
    // distamce for all is set to infinity
    for (int i = 0; i < v; i++) {
        visited[i] = false;
        dist[i] = INT_MAX;
        pred[i] = -1;
    }
 
    // source is visited first and distance
    // from source to itself is 0
    visited[src] = true;
    dist[src] = 0;
    queue.push_back(src);
 
    // BFS algorithm
    while (!queue.empty()) {
        int u = queue.front();
        queue.pop_front();
        for (int i = 0; i < adj[u].size(); i++) {
            if (visited[adj[u][i]] == false) {
                visited[adj[u][i]] = true;
                dist[adj[u][i]] = dist[u] + 1;
                pred[adj[u][i]] = u;
                queue.push_back(adj[u][i]);
 
                // stop BFS when destination
                // is found 
                if (adj[u][i] == dest)
                    return true;
            }
        }
    }
 
    return false;
}
 

int printShortestDistance(vector<int> adj[], int s,
                           int dest, int v)
{
    // predecessor[i] array stores predecessor of
    // i and distance array stores distance of i
    // from s
    int pred[v], dist[v];
 
    if (BFS(adj, s, dest, v, pred, dist) == false) {
        return -1;
    }
 
    // vector path stores the shortest path
    vector<int> path;
    int crawl = dest;
    path.push_back(crawl);
    while (pred[crawl] != -1) {
        path.push_back(pred[crawl]);
        crawl = pred[crawl];
    }
 
    // distance from source is in distance array
    return dist[dest];
}

int main(void) {

   int n, m;
   cin >> n;
   cin >> m;

   vector<int> adj[n];

   for (int i = 0; i < m; i++) {
      int node1, node2;
      cin >> node1;
      cin >> node2;
      add_edge(adj, node1 - 1, node2 - 1);
   }

   int q;
   cin >> q;
   int list[q];
   int count = 0;

   for (int i = 0; i < q; i++) {
      int operation;
      cin >> operation;
      if (operation == 1) {
         int node;
         cin >> node;
         remove(adj, node - 1);
      } else {
         int node1, node2;
         cin >> node1;
         cin >> node2;
         list[count] = printShortestDistance(adj, node1 - 1, node2 - 1, n);
         count++;
      }
   }

   for (int i = 0; i < count; i++)
      cout << list[i] << endl;

   return 0;
}
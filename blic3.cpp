#include <iostream>
#include <bits/stdc++.h>
using namespace std;
  
//Integer Pair
typedef pair<long long, long long> iPair;
  
// This class represents a directed graph using
// adjacency list representation
class Graph
{
    long long V;    // no of vertices
  
    // In a weighted graph, we need to store vertex
    // and weight pair for every edge
    list< pair<long long, long long> > *adj;
  
public:
    Graph(long long V);  // Constructor
  
    // function to add an edge to graph
    void addEdge(long long u, long long v, long long w);
  
    // prints shortest path from s
    void shortestPath(long long s);
};
  
// Allocates memory for adjacency list
Graph::Graph(long long V)
{
    this->V = V;
    adj = new list<iPair> [V];
}
  
void Graph::addEdge(long long u, long long v, long long w) {
    adj[u].push_back(make_pair(v, w));
    adj[v].push_back(make_pair(u, w));
}
  
// Prints shortest paths from src to all other vertices
void Graph::shortestPath(long long src)
{
    // Create a priority queue to store vertices that
    // are being preprocessed
    priority_queue< iPair, vector <iPair> , greater<iPair> > pq;
  
    // Create a vector for distances
    vector<long long> dist(V, LLONG_MAX);
  
    // Insert source itself in priority queue and initialize
    // its distance as 0
    pq.push(make_pair(0, src));
    dist[src] = 0;
  
    /* Looping till priority queue becomes empty (or all
      distances are not finalized) */
    while (!pq.empty())
    {
        // The first vertex in pair is the minimum distance
        // vertex, extract it from priority queue.
        long long u = pq.top().second;
        pq.pop();
  
        // 'i' is used to get all adjacent vertices of a vertex
        list< pair<long long, long long> >::iterator i;
        for (i = adj[u].begin(); i != adj[u].end(); ++i)
        {
            // Get vertex label and weight of current adjacent
            // of u.
            long long v = (*i).first;
            long long weight = (*i).second;
  
            //  If there is shorted path to v through u.
            if (dist[v] > dist[u] + weight)
            {
                // Updating distance of v
                dist[v] = dist[u] + weight;
                pq.push(make_pair(dist[v], v));
            }
        }
    }
  
   long long max = 0;
   for (long long i = 0; i < V; ++i) {
      if (dist[i] > max) {
         max = dist[i];
      }
   }
   long long path = 0;
   bool found = false;
   for (long long i = 0; i < V; ++i) {
      if (!found && dist[i] == max) {
         found = true;
         path += dist[i];
      } else {
         path += 2 * dist[i];
      }
   }
   cout << path;

}
  
// Driver program to test methods of graph class
int main() {
    long long n, m;
    cin >> n >> m;
    Graph g(n);
  
   long long g1[m], g2[m], t[m];
   for (long long i = 0; i < m; i++) {
      cin >> g1[i] >> g2[i] >> t[i];
   }
    
   for (long long i = 0; i < m; i++) {
      g.addEdge(g1[i] - 1, g2[i] - 1, t[i]);  
   }

   g.shortestPath(0);
   return 0;
}
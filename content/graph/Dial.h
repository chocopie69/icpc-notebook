/**
 * Author: Personal notebook, adapted from Yukuk's 1-K BFS tutorial
 * Source: https://codeforces.com/blog/entry/88408
 * Description: Single-source shortest paths for integer weights in [0,K], with small K.
 * Use K+1 cyclic buckets; current is the real distance, only bucket indices use modulo.
 * Skip stale entries. K=0 and zero-weight edges work; K=1 covers 0-1 BFS.
 * Allocate adj for your indexing; unreachable distances are 	exttt{LLONG\_MAX}.
 * Negative weights are invalid. Large K needs too much scanning/memory; use heap Dijkstra.
 * Usage: vector<vector<pii>> adj(n+1); // {neighbor,weight}, weights 0..9
 * adj[u].push_back({v,3}); // add reverse edge too if undirected
 * auto dist=dial(adj,1,9); // source=1, K=9
 * if (dist[target]!=LLONG_MAX) cout << dist[target];
 * // Use dial(adj,source,1) for weights only 0 and 1.
 * Time: $O(N+M+NK)$ time; $O(N+M+K)$ auxiliary memory including queued entries.
 */
#pragma once
vector<ll> dial(const vector<vector<pii>> &adj, int source, int K) {
  int bucketCount = K + 1;
  vector<queue<int>> buckets(bucketCount);
  vector<ll> dist(sz(adj), LLONG_MAX);
  ll current = 0, pending = 1;
  dist[source] = 0;
  buckets[0].push(source);
  while (pending) {
    while (buckets[current % bucketCount].empty()) current++;
    auto &bucket = buckets[current % bucketCount];
    int u = bucket.front();
    bucket.pop();
    pending--;
    if (dist[u] != current) continue; // Ignore an outdated queued distance.
    for (auto [v, weight] : adj[u]) {
      ll nextDist = current + weight;
      if (nextDist >= dist[v]) continue;
      dist[v] = nextDist;
      buckets[nextDist % bucketCount].push(v);
      pending++;
    }
  }
  return dist;
}

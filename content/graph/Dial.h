/**
 * Author: Personal notebook, adapted from Yukuk's 1-K BFS tutorial
 * Source: https://codeforces.com/blog/entry/88408
 * Description: Single-source shortest paths with integer edge weights in [0,K], for small K.
 * Uses K+1 cyclic buckets instead of a priority queue. current is the actual distance;
 * only the bucket index is taken modulo K+1. Skip stale entries after a shorter path is found.
 * Zero-weight edges are supported, including K=0. K=1 also handles every 0-1 BFS problem.
 * Vertices may be 0-based or 1-based; allocate adj accordingly. Unreachable distances are
 * \texttt{LLONG\_MAX}. K must bound every edge weight; negative weights are not supported.
 * Large K makes scanning buckets slow and consumes memory; use heap Dijkstra in that case.
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

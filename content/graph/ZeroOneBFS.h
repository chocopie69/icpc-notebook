/**
 * Author: Personal notebook
 * Source: https://cp-algorithms.com/graph/01_bfs.html
 * Description: Single-source shortest paths with edge weights only 0 or 1. Push zero-cost moves
 * to the front and unit-cost moves to the back. Vertices may be 0-based or 1-based; allocate
 * adj accordingly. Unreachable distances are \texttt{INT\_MAX}. Settle vertices when popped,
 * not pushed.
 * Usage: vector<vector<pii>> adj(n+1); // {neighbor,weight}
 * adj[u].push_back({v,0}); // add reverse edge too if undirected
 * auto d=bfs01(adj,1);
 * if (d[target]!=INT_MAX) cout << d[target];
 * // Grid example: moving freely costs 0; breaking a wall costs 1.
 * Time: $O(N+M)$ time; $O(N+M)$ auxiliary memory including queued entries.
 */
#pragma once
vector<int> bfs01(const vector<vector<pii>> &adj, int source) {
  vector<int> d(sz(adj), INT_MAX);
  vector<bool> done(sz(adj));
  deque<int> dq;
  d[source] = 0;
  dq.push_front(source);
  while (!dq.empty()) {
    int u = dq.front();
    dq.pop_front();
    if (done[u]) continue;
    done[u] = true;
    for (auto [v, weight] : adj[u]) {
      if (d[v] <= d[u] + weight) continue;
      d[v] = d[u] + weight;
      if (weight == 0)
        dq.push_front(v);
      else
        dq.push_back(v);
    }
  }
  return d;
}

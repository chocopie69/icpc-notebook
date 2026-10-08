/**
 * Author: Adam Soltan
 * Date: 2026-01-13
 * License: CC0
 * Description: Maximum bipartite matching. adj lists right neighbors for each left vertex; the two sides use
 * separate 0-based indices. Initialize matchRight with rightSize entries of -1. Returns matching
 * size; matchRight[v] is its matched left vertex, or -1.
 * Time: O(E \sqrt{V})
 * Status: stress-tested by MinimumVertexCover and tested on Library Checker
 * Usage: vector<vector<int>> adj={{0,1},{1}};
 * vector<int> matchRight(2,-1);
 * int size=hopcroftKarp(adj,matchRight); // 2
 */
#pragma once
int hopcroftKarp(vector<vector<int>> &adj, vector<int> &matchRight) {
  int n = sz(adj), matchingSize = 0;
  vector<int> matchLeft(n, -1), queue(n), dist(n);
  auto dfs = [&](auto self, int u) -> bool {
    int nextDist = exchange(dist[u], 0) + 1;
    for (int v : adj[u])
      if (matchRight[v] == -1 || (dist[matchRight[v]] == nextDist && self(self, matchRight[v])))
        return matchLeft[u] = v, matchRight[v] = u, 1;
    return 0;
  };
  for (int queueSize = 0, foundPath = 0;; queueSize = foundPath = 0, dist.assign(n, 0)) {
    for (int i = 0; i < (n); ++i)
      if (matchLeft[i] == -1) queue[queueSize++] = i, dist[i] = 1;
    for (int i = 0; i < (queueSize); ++i)
      for (int v : adj[queue[i]])
        if (matchRight[v] == -1)
          foundPath = 1;
        else if (!dist[matchRight[v]])
          dist[matchRight[v]] = dist[queue[i]] + 1, queue[queueSize++] = matchRight[v];
    if (!foundPath) return matchingSize;
    for (int i = 0; i < (n); ++i)
      if (matchLeft[i] == -1) matchingSize += dfs(dfs, i);
  }
}

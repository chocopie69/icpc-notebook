/**
 * Author: chilli, pajenegod
 * Date: 2020-02-20
 * License: CC0
 * Source: Folklore
 * Description: Binary-lifting LCA using up[u][k] and depth h[u].
 * adj is an undirected tree or directed parent-to-child tree. Default root is 1;
 * pass root=0 for a 0-based tree. time[u] is the DFS entry order for virtual trees.
 * distance returns the number of edges, not the sum of edge weights.
 * Usage: LCA tree(adj); int w = tree.lca(u,v); int p = tree.goUp(u,steps);
 * Time: $O(N \log N)$ construction and memory; $O(\log N)$ per query.
 */
#pragma once
#include "BinaryLifting.h"
struct LCA {
  int LOG = 1;
  int timer = 0;
  vector<vector<int>> up;
  vector<int> h, time;
  LCA(const vector<vector<int>> &adj, int root = 1) {
    int n = sz(adj);
    while ((1LL << LOG) <= n) LOG++;
    up.assign(n, vector<int>(LOG));
    h.assign(n, 0);
    time.assign(n, -1);
    if (root >= 0 && root < n) dfs(adj, root, root);
  }
  void dfs(const vector<vector<int>> &adj, int u, int parent) {
    time[u] = timer++;
    up[u][0] = parent;
    for (int k = 1; k < LOG; k++) up[u][k] = up[up[u][k - 1]][k - 1];
    for (int v : adj[u]) {
      if (v == parent) continue;
      h[v] = h[u] + 1;
      dfs(adj, v, u);
    }
  }
  int goUp(int u, int steps) const { return ::goUp(up, u, steps); }
  int lca(int u, int v) const { return ::lca(up, h, u, v); }
  int distance(int u, int v) const {
    int w = lca(u, v);
    return h[u] + h[v] - 2 * h[w];
  }
};

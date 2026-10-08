/**
 * Author: Personal notebook
 * Description: Euler-tour + RMQ version of LCA. Record u on entry and again after each child;
 * the LCA is the shallowest vertex between the first occurrences of u and v. This is different
 * from the entry/exit tour used by tree Mo. Build on a connected tree; default root=1.
 * Choose this for many LCA queries. Binary lifting also supports kth ancestors and jump
 * aggregates, with less tour-table overhead. Rebuild after changing edges; DFS is recursive.
 * Usage: LCAEuler tree(adj); // vector<vector<int>>, undirected or parent-to-child
 * int common=tree.lca(u,v);
 * int edges=tree.distance(u,v);
 * // With separately computed weighted root distances:
 * // length = rootDist[u] + rootDist[v]
 * //          - 2 * rootDist[common];
 * Time: $O(N \log N)$ construction and memory; $O(1)$ per LCA/distance query.
 */
#pragma once
struct LCAEuler {
  vector<int> h, first, tour;
  vector<vector<int>> table;
  LCAEuler(const vector<vector<int>> &adj, int root = 1) : h(sz(adj)), first(sz(adj), -1) {
    dfs(adj, root, root);
    table.push_back(tour);
    int m = sz(tour);
    for (int k = 1; (1LL << k) <= m; k++) {
      table.emplace_back(m - (1 << k) + 1);
      for (int i = 0; i < sz(table[k]); i++)
        table[k][i] = shallower(table[k - 1][i], table[k - 1][i + (1 << (k - 1))]);
    }
  }
  void dfs(const vector<vector<int>> &adj, int u, int parent) {
    first[u] = sz(tour);
    tour.push_back(u);
    for (int v : adj[u]) {
      if (v == parent) continue;
      h[v] = h[u] + 1;
      dfs(adj, v, u);
      tour.push_back(u);
    }
  }
  int shallower(int u, int v) const { return h[u] <= h[v] ? u : v; }
  int lca(int u, int v) const {
    int l = first[u], r = first[v];
    if (l > r) swap(l, r);
    int k = __lg(r - l + 1);
    return shallower(table[k][l], table[k][r - (1 << k) + 1]);
  }
  int distance(int u, int v) const { return h[u] + h[v] - 2 * h[lca(u, v)]; }
};

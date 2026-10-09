/**
 * Author: Personal Code::Blocks abbreviation, adapted
 * Description: Binary lifting and LCA in one snippet: up[u][k] is the ancestor $2^k$ steps above u.
 * Build on a connected tree; root defaults to 1 and is its own parent. goUp needs
 * 0<=steps<=h[u]. tin is single-entry DFS order. distance counts edges; weightedDistance sums
 * weights using ll root distances. Rebuild after edge changes; DFS is recursive.
 * Use for kth ancestors; jump aggregates need an extra table/merge per level.
 * Euler-tour + RMQ gives O(1) LCA queries. For a forest, build/query each component separately.
 * Usage: LCA tree(adj); // vector<vector<int>>, unit edge weights
 * int common=tree.lca(u,v);
 * int ancestor=tree.goUp(u,2); // requires tree.h[u]>=2
 * int edges=tree.distance(u,v);
 * vector<vector<pll>> weightedAdj(n+1);
 * // Each pair is {neighbor,weight}; add both directions for an undirected tree.
 * LCA weighted(weightedAdj);
 * ll length=weighted.weightedDistance(u,v);
 * Time: $O(N \log N)$ construction and memory; $O(\log N)$ per query.
 */
#pragma once
struct LCA {
  int LOG, timer = 0;
  vector<vector<pll>> adj;
  vector<vector<int>> up;
  vector<int> h, tin;
  vector<ll> rootDist;
  LCA(int n)
      : LOG(__lg(max(1, n)) + 1), adj(n), up(n, vector<int>(LOG)), h(n), tin(n), rootDist(n) {}
  LCA(const vector<vector<int>> &graph, int root = 1) : LCA(sz(graph)) {
    for (int u = 0; u < sz(graph); u++)
      for (int v : graph[u]) adj[u].push_back({v, 1});
    dfs(root, root);
  }
  LCA(const vector<vector<pll>> &graph, int root = 1) : LCA(sz(graph)) {
    adj = graph;
    dfs(root, root);
  }
  void dfs(int u, int parent) {
    tin[u] = timer++;
    up[u][0] = parent;
    for (int k = 1; k < LOG; k++) up[u][k] = up[up[u][k - 1]][k - 1];
    for (auto [v, weight] : adj[u]) {
      if (v == parent) continue;
      h[v] = h[u] + 1;
      rootDist[v] = rootDist[u] + weight;
      dfs(v, u);
    }
  }
  int goUp(int u, int steps) const {
    for (int k = 0; k < LOG; k++)
      if (steps >> k & 1) u = up[u][k];
    return u;
  }
  int lca(int u, int v) const {
    if (h[u] < h[v]) swap(u, v);
    u = goUp(u, h[u] - h[v]);
    if (u == v) return u;
    for (int k = LOG - 1; k >= 0; k--)
      if (up[u][k] != up[v][k]) u = up[u][k], v = up[v][k];
    return up[u][0];
  }
  int distance(int u, int v) const { return h[u] + h[v] - 2 * h[lca(u, v)]; }
  ll weightedDistance(int u, int v) const {
    return rootDist[u] + rootDist[v] - 2 * rootDist[lca(u, v)];
  }
};

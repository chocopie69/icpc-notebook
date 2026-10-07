/**
 * Author: Johan Sannemo
 * Date: 2015-02-06
 * License: CC0
 * Source: Folklore
 * Description: Ancestor table up[u][k] stores the ancestor of u after $2^k$ steps.
 * parent[root] must equal root; parent and depth must use the same vertex indices.
 * Supports either 0-based vectors or 1-based vectors with index 0 reserved.
 * goUp requires 0 <= steps <= depth[u].
 * Usage: auto up = buildAncestorTable(parent); int p = goUp(up,u,3); int w = lca(up,h,u,v);
 * Time: $O(N \log N)$ construction and memory; $O(\log N)$ per query.
 */
#pragma once
vector<vector<int>> buildAncestorTable(const vector<int> &parent) {
  int n = sz(parent);
  int LOG = 1;
  while ((1LL << LOG) <= n) LOG++;
  vector<vector<int>> up(n, vector<int>(LOG));
  for (int u = 0; u < n; u++) up[u][0] = parent[u];
  for (int k = 1; k < LOG; k++)
    for (int u = 0; u < n; u++) up[u][k] = up[up[u][k - 1]][k - 1];
  return up;
}
int goUp(const vector<vector<int>> &up, int u, int steps) {
  for (int k = 0; k < sz(up[u]); k++)
    if ((steps >> k) & 1) u = up[u][k];
  return u;
}
int lca(const vector<vector<int>> &up, const vector<int> &h, int u, int v) {
  if (h[u] < h[v]) swap(u, v);
  u = goUp(up, u, h[u] - h[v]);
  if (u == v) return u;
  for (int k = sz(up[u]) - 1; k >= 0; k--) {
    if (up[u][k] != up[v][k]) {
      u = up[u][k];
      v = up[v][k];
    }
  }
  return up[u][0];
}

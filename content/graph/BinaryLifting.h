/**
 * Author: Johan Sannemo
 * Date: 2015-02-06
 * License: CC0
 * Source: Folklore
 * Description: up[u][k] stores the ancestor $2^k$ steps above u. Build parent and depth h first;
 * parent[root]=root. Supports 0-based or 1-based vectors with index 0 reserved. goUp requires
 * 0<=steps<=h[u]. Add another table for aggregates along jumps. This is the binary-lifting
 * approach to LCA; see LCA.h for DFS setup and LCAEuler.h for the Euler-tour + RMQ alternative.
 * Usage: auto up=buildAncestorTable(parent);
 * int ancestor=goUp(up,u,2); // requires h[u]>=2
 * int common=lca(up,h,u,v);
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

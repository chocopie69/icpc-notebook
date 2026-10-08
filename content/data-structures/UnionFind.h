/**
 * Author: Personal Code::Blocks abbreviation, adapted
 * Description: Union by size with path compression, for vertices 1..n. get returns the component
 * representative; s[get(u)] is its size. This version cannot roll back merges.
 * Usage: DSU dsu(5);
 * dsu.join(1,2);
 * bool same=dsu.joined(1,2); // true
 * int size=dsu.s[dsu.get(1)]; // 2
 * Time: $O(N)$ initialization; amortized $O(\alpha(N))$ per operation.
 */
#pragma once
struct DSU {
  vector<int> par, s;
  DSU(int n) { init(n); }
  void init(int n) {
    par.resize(n + 1);
    iota(all(par), 0);
    s.assign(n + 1, 1);
  }
  int get(int u) { return par[u] == u ? u : par[u] = get(par[u]); }
  void join(int u, int v) {
    u = get(u), v = get(v);
    if (u == v) return;
    if (s[u] < s[v]) swap(u, v);
    par[v] = u;
    s[u] += s[v];
  }
  bool joined(int u, int v) { return get(u) == get(v); }
};

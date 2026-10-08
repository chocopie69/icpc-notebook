/**
 * Author: Lukas Polacek
 * Date: 2009-10-28
 * License: CC0
 * Source: Czech graph algorithms book, by Demel. (Tarjan's algorithm)
 * Description: Directed SCCs; default vertices 1..n, or pass firstVertex=0. comp[u] is a 0-based component ID
 * and components[id] lists its vertices. Inter-component edges go to smaller IDs; process IDs in
 * descending order for topological order. Build a new object after changing edges.
 * Usage: SCC scc(adj); bool same=scc.comp[u]==scc.comp[v];
 * for (int id=sz(scc.components)-1;id>=0;id--) {
 *   // Process scc.components[id] in topological order.
 * }
 * Time: $O(N+E)$ time and memory.
 */
#pragma once
struct SCC {
  int timer = 0;
  vector<int> num, low, comp, activeStack;
  vector<bool> inStack;
  vector<vector<int>> components;
  SCC(const vector<vector<int>> &adj, int firstVertex = 1) {
    int n = sz(adj);
    num.assign(n, 0);
    low.assign(n, 0);
    comp.assign(n, -1);
    inStack.assign(n, false);
    for (int u = firstVertex; u < n; u++)
      if (num[u] == 0) dfs(adj, u);
  }
  void dfs(const vector<vector<int>> &adj, int u) {
    timer++;
    num[u] = timer;
    low[u] = timer;
    activeStack.push_back(u);
    inStack[u] = true;
    for (int v : adj[u]) {
      if (num[v] == 0) {
        dfs(adj, v);
        low[u] = min(low[u], low[v]);
      } else if (inStack[v]) {
        low[u] = min(low[u], num[v]);
      }
    }
    if (low[u] != num[u]) return;
    int id = sz(components);
    components.push_back({});
    while (true) {
      int v = activeStack.back();
      activeStack.pop_back();
      inStack[v] = false;
      comp[v] = id;
      components[id].push_back(v);
      if (v == u) break;
    }
  }
};

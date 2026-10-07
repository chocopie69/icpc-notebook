/**
 * Author: Lukas Polacek
 * Date: 2009-10-28
 * License: CC0
 * Source: Czech graph algorithms book, by Demel. (Tarjan's algorithm)
 * Description: Tarjan's strongly connected components for a directed graph.
 * Default vertices are 1..n (adj[0] unused); pass firstVertex=0 for 0-based graphs.
 * comp[u] is the component ID; components[id] contains its vertices. IDs start at 0
 * in reverse topological order: an edge between components goes to a smaller ID.
 * num[u] is the DFS entry time; low[u] is the smallest entry reachable while active.
 * Usage: SCC scc(adj); int id = scc.comp[u]; int count = sz(scc.components);
 * Time: $O(N+E)$ time and memory.
 */
#pragma once
struct SCC {
  int timer = 0;
  vector<int> num, low, comp, st;
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
    st.push_back(u);
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
      int v = st.back();
      st.pop_back();
      inStack[v] = false;
      comp[v] = id;
      components[id].push_back(v);
      if (v == u) break;
    }
  }
};

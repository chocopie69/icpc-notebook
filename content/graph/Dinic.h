/**
 * Author: chilli
 * Date: 2019-04-26
 * License: CC0
 * Source: https://cp-algorithms.com/graph/dinic.html
 * Description: Flow algorithm with complexity $O(VE\log U)$ where $U = \max |\text{cap}|$.
 * $O(\min(E^{1/2}, V^{2/3})E)$ if $U = 1$; $O(\sqrt{V}E)$ for bipartite matching.
 * Dinic(n) uses vertices 0..n-1; capacities are nonnegative,
 * with distinct source and sink. Discard self-loops; sums of capacities must fit ll.
 * calc returns additional max flow and changes residual capacities. After calc,
 * leftOfMinCut tests membership in the source side; Edge::flow gives positive flow.
 * See MinCut.h for code to list both sides and the cut edges using original capacities.
 * Fresh object for another network/source-sink pair; lower bounds need a circulation reduction.
 * Full 64-bit capacity scaling: change 31 phases/shift 30 to 63 phases/shift 62.
 * Usage: Dinic d(3); d.addEdge(0,1,5); d.addEdge(1,2,3);
 * ll flow=d.calc(0,2); // 3; use reverse capacity c for an undirected edge
 * Status: Tested on SPOJ FASTFLOW and SPOJ MATCHING, stress-tested
 */
#pragma once
struct Dinic {
  struct Edge {
    int to, rev;
    ll c, oc;
    ll flow() { return max(oc - c, 0LL); } // if you need flows
  };
  vector<int> lvl, ptr, q;
  vector<vector<Edge>> adj;
  Dinic(int n) : lvl(n), ptr(n), q(n), adj(n) {}
  void addEdge(int a, int b, ll c, ll rcap = 0) {
    adj[a].push_back({b, sz(adj[b]), c, c});
    adj[b].push_back({a, sz(adj[a]) - 1, rcap, rcap});
  }
  ll dfs(int v, int t, ll f) {
    if (v == t || !f) return f;
    for (int &i = ptr[v]; i < sz(adj[v]); i++) {
      Edge &e = adj[v][i];
      if (lvl[e.to] == lvl[v] + 1)
        if (ll p = dfs(e.to, t, min(f, e.c))) {
          e.c -= p, adj[e.to][e.rev].c += p;
          return p;
        }
    }
    return 0;
  }
  ll calc(int s, int t) {
    ll flow = 0;
    q[0] = s;
    for (int L = 0; L < (31); ++L) do { // 'int L=30' maybe faster for random data
        lvl = ptr = vector<int>(sz(q));
        int qi = 0, qe = lvl[s] = 1;
        while (qi < qe && !lvl[t]) {
          int v = q[qi++];
          for (Edge e : adj[v])
            if (!lvl[e.to] && e.c >> (30 - L))
              q[qe++] = e.to, lvl[e.to] = lvl[v] + 1;
        }
        while (ll p = dfs(s, t, LLONG_MAX)) flow += p;
      } while (lvl[t]);
    return flow;
  }
  bool leftOfMinCut(int a) { return lvl[a] != 0; }
};

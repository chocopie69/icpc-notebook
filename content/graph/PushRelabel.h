/**
 * Author: Simon Lindholm
 * Date: 2015-02-24
 * License: CC0
 * Source: Wikipedia, tinyKACTL
 * Description: Push-relabel using the highest label selection rule and the gap heuristic. Quite fast in practice.
 *  To obtain the actual flow, look at positive values only.
 * Time: $O(V^2\sqrt E)$
 * Status: Tested on Kattis and SPOJ, and stress-tested
 */
#pragma once
struct PushRelabel {
  struct Edge {
    int to, rev;
    ll flow, cap;
  };
  vector<vector<Edge>> adj;
  vector<ll> excess;
  vector<Edge *> currentEdge;
  vector<vector<int>> activeByHeight;
  vector<int> height;
  PushRelabel(int n) : adj(n), excess(n), currentEdge(n), activeByHeight(2 * n), height(n) {}
  void addEdge(int s, int t, ll cap, ll reverseCap = 0) {
    if (s == t) return;
    adj[s].push_back({t, sz(adj[t]), 0, cap});
    adj[t].push_back({s, sz(adj[s]) - 1, 0, reverseCap});
  }
  void addFlow(Edge &e, ll flow) {
    Edge &reverseEdge = adj[e.to][e.rev];
    if (!excess[e.to] && flow) activeByHeight[height[e.to]].push_back(e.to);
    e.flow += flow;
    e.cap -= flow;
    excess[e.to] += flow;
    reverseEdge.flow -= flow;
    reverseEdge.cap += flow;
    excess[reverseEdge.to] -= flow;
  }
  ll calc(int s, int t) {
    int n = sz(adj);
    height[s] = n;
    excess[t] = 1;
    vector<int> heightCount(2 * n);
    heightCount[0] = n - 1;
    for (int i = 0; i < (n); ++i) currentEdge[i] = adj[i].data();
    for (Edge &e : adj[s]) addFlow(e, e.cap);

    for (int maxHeight = 0;;) {
      while (activeByHeight[maxHeight].empty())
        if (!maxHeight--) return -excess[s];
      int u = activeByHeight[maxHeight].back();
      activeByHeight[maxHeight].pop_back();
      while (excess[u] > 0) // discharge u
        if (currentEdge[u] == adj[u].data() + sz(adj[u])) {
          height[u] = 1e9;
          for (Edge &e : adj[u])
            if (e.cap && height[u] > height[e.to] + 1)
              height[u] = height[e.to] + 1, currentEdge[u] = &e;
          if (++heightCount[height[u]], !--heightCount[maxHeight] && maxHeight < n)
            for (int i = 0; i < (n); ++i)
              if (maxHeight < height[i] && height[i] < n)
                --heightCount[height[i]], height[i] = n + 1;
          maxHeight = height[u];
        } else if (currentEdge[u]->cap && height[u] == height[currentEdge[u]->to] + 1)
          addFlow(*currentEdge[u], min(excess[u], currentEdge[u]->cap));
        else
          ++currentEdge[u];
    }
  }
  bool leftOfMinCut(int a) { return height[a] >= sz(adj); }
};

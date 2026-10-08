/**
 * Author: Stanford
 * Date: Unknown
 * Source: Stanford Notebook
 * Description: Min-cost max-flow.
 *  If costs can be negative, call setpi before maxflow, but note that negative cost cycles are not supported.
 *  To obtain the actual flow, look at positive values only.
 * Status: Tested on kattis:mincostmaxflow, stress-tested against another implementation
 * Time: $O(F E \log(V))$ where F is max flow. $O(VE)$ for setpi.
 */
#pragma once

// #include <bits/extc++.h> /// include-line, keep-include

const ll INF = numeric_limits<ll>::max() / 4;
struct MinCostMaxFlow {
  struct Edge {
    int from, to, rev;
    ll cap, cost, flow;
  };
  int n;
  vector<vector<Edge>> adj;
  vector<int> seen;
  vector<ll> dist, potential;
  vector<Edge *> parentEdge;
  MinCostMaxFlow(int n) : n(n), adj(n), seen(n), dist(n), potential(n), parentEdge(n) {}
  void addEdge(int from, int to, ll cap, ll cost) {
    if (from == to) return;
    adj[from].push_back(Edge{from, to, sz(adj[to]), cap, cost, 0});
    adj[to].push_back(Edge{to, from, sz(adj[from]) - 1, 0, -cost, 0});
  }
  void path(int s) {
    fill(all(seen), 0);
    fill(all(dist), INF);
    dist[s] = 0;
    ll adjustedDist;

    __gnu_pbds::priority_queue<pair<ll, int>> pq;
    vector<decltype(pq)::point_iterator> handles(n);
    pq.push({0, s});

    while (!pq.empty()) {
      s = pq.top().second;
      pq.pop();
      seen[s] = 1;
      adjustedDist = dist[s] + potential[s];
      for (Edge &e : adj[s])
        if (!seen[e.to]) {
          ll newDist = adjustedDist - potential[e.to] + e.cost;
          if (e.cap - e.flow > 0 && newDist < dist[e.to]) {
            dist[e.to] = newDist;
            parentEdge[e.to] = &e;
            if (handles[e.to] == pq.end())
              handles[e.to] = pq.push({-dist[e.to], e.to});
            else
              pq.modify(handles[e.to], {-dist[e.to], e.to});
          }
        }
    }
    for (int i = 0; i < (n); ++i) potential[i] = min(potential[i] + dist[i], INF);
  }
  pair<ll, ll> maxflow(int s, int t) {
    ll totalFlow = 0, totalCost = 0;
    while (path(s), seen[t]) {
      ll pushed = INF;
      for (Edge *edge = parentEdge[t]; edge; edge = parentEdge[edge->from])
        pushed = min(pushed, edge->cap - edge->flow);

      totalFlow += pushed;
      for (Edge *edge = parentEdge[t]; edge; edge = parentEdge[edge->from]) {
        edge->flow += pushed;
        adj[edge->to][edge->rev].flow -= pushed;
      }
    }
    for (int i = 0; i < (n); ++i)
      for (Edge &e : adj[i]) totalCost += e.cost * e.flow;
    return {totalFlow, totalCost / 2};
  }
  // If some costs can be negative, call this before maxflow:
  void setpi(int s) { // (otherwise, leave this out)
    fill(all(potential), INF);
    potential[s] = 0;
    int roundsLeft = n, changed = 1;
    ll newPotential;
    while (changed-- && roundsLeft--)
      for (int i = 0; i < (n); ++i)
        if (potential[i] != INF)
          for (Edge &e : adj[i])
            if (e.cap)
              if ((newPotential = potential[i] + e.cost) < potential[e.to])
                potential[e.to] = newPotential, changed = 1;
    assert(roundsLeft >= 0); // negative cost cycle
  }
};

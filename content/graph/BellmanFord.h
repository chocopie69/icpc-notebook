/**
 * Author: Simon Lindholm
 * Date: 2015-02-23
 * License: CC0
 * Source: http://en.wikipedia.org/wiki/Bellman-Ford_algorithm
 * Description: Calculates shortest paths from $s$ in a graph that might have negative edge weights.
 * Unreachable nodes get dist = inf; nodes reachable through negative-weight cycles get dist = -inf.
 * Assumes $V^2 \max |w_i| < \tilde{} 2^{63}$.
 * Time: O(VE)
 * Status: Tested on kattis:shortestpath3
 */
#pragma once

const ll inf = LLONG_MAX;
struct BellmanFordEdge {
  int a, b, w, s() { return a < b ? a : -a; }
};
struct BellmanFordState {
  ll dist = inf;
  int prev = -1;
};
void bellmanFord(vector<BellmanFordState> &nodes, vector<BellmanFordEdge> &eds, int s) {
  nodes[s].dist = 0;
  sort(all(eds), [](BellmanFordEdge a, BellmanFordEdge b) { return a.s() < b.s(); });

  int lim = sz(nodes) / 2 + 2; // /3+100 with shuffled vertices
  for (int i = 0; i < (lim); ++i)
    for (BellmanFordEdge ed : eds) {
      BellmanFordState cur = nodes[ed.a], &dest = nodes[ed.b];
      if (abs(cur.dist) == inf) continue;
      ll d = cur.dist + ed.w;
      if (d < dest.dist) {
        dest.prev = ed.a;
        dest.dist = (i < lim - 1 ? d : -inf);
      }
    }
  for (int i = 0; i < (lim); ++i)
    for (BellmanFordEdge e : eds) {
      if (nodes[e.a].dist == -inf)
        nodes[e.b].dist = -inf;
    }
}

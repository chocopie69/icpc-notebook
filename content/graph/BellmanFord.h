/**
 * Author: Simon Lindholm
 * Date: 2015-02-23
 * License: CC0
 * Source: http://en.wikipedia.org/wiki/Bellman-Ford_algorithm
 * Description: Calculates shortest paths from $s$ in a graph that might have negative edge weights.
 * Unreachable nodes get dist = inf; nodes reachable through negative-weight cycles get dist = -inf.
 * Assumes $V^2 \max |w_i| < \tilde{} 2^{63}$.
 * Use fresh default-initialized nodes for each run; allocate n+1 for labels 1..n. Edges are directed;
 * add both directions for an undirected graph. prev gives a predecessor only for finite shortest
 * paths. The algorithm sorts edges in place; do not reconstruct paths through negative cycles.
 * Time: O(VE)
 * Status: Tested on kattis:shortestpath3
 * Usage: vector<BellmanFordState> nodes(3);
 * vector<BellmanFordEdge> edges={{0,1,-2},{1,2,5}};
 * bellmanFord(nodes,edges,0); // nodes[2].dist==3
 */
#pragma once

const ll inf = LLONG_MAX;
struct BellmanFordEdge {
  int from, to, weight, sortKey() { return from < to ? from : -from; }
};
struct BellmanFordState {
  ll dist = inf;
  int prev = -1;
};
void bellmanFord(vector<BellmanFordState> &nodes, vector<BellmanFordEdge> &edges, int source) {
  nodes[source].dist = 0;
  sort(all(edges), [](BellmanFordEdge first, BellmanFordEdge second) {
    return first.sortKey() < second.sortKey();
  });

  int rounds = sz(nodes) / 2 + 2; // /3+100 with shuffled vertices
  for (int i = 0; i < (rounds); ++i)
    for (BellmanFordEdge edge : edges) {
      BellmanFordState fromState = nodes[edge.from], &toState = nodes[edge.to];
      if (abs(fromState.dist) == inf) continue;
      ll newDist = fromState.dist + edge.weight;
      if (newDist < toState.dist) {
        toState.prev = edge.from;
        toState.dist = (i < rounds - 1 ? newDist : -inf);
      }
    }
  for (int i = 0; i < (rounds); ++i)
    for (BellmanFordEdge edge : edges)
      if (nodes[edge.from].dist == -inf) nodes[edge.to].dist = -inf;
}

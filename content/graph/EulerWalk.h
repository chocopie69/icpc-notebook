/**
 * Author: Simon Lindholm
 * Date: 2019-12-31
 * License: CC0
 * Source: folklore
 * Description: Hierholzer traversal uses every edge exactly once. Vertices are 0-based and edge IDs are
 * 0..edgeCount-1. For undirected edges, add both directions with the same ID; for directed
 * edges, add one entry. For an open trail, choose an odd-degree start in an undirected graph, or
 * a vertex with outdegree=indegree+1 in a directed graph. For a cycle choose a vertex incident
 * to an edge. Returns edgeCount+1 vertices or an empty vector on failure. Open trails have
 * different endpoints. For 1-based vertices allocate n+1 and pass source explicitly;
 * edge IDs remain 0-based. To require a cycle, also check walk.front()==walk.back().
 * Time: O(V + E)
 * Status: stress-tested
 * Usage: vector<vector<pii>> adj(3);
 * adj[0].push_back({1,0}); adj[1].push_back({2,1});
 * auto walk=eulerWalk(adj,2,0); // directed: {0,1,2}
 */
#pragma once
vector<int> eulerWalk(vector<vector<pii>> &adj, int edgeCount, int source = 0) {
  int n = sz(adj);
  vector<int> balance(n), nextEdge(n), usedEdge(edgeCount), walk, stack = {source};
  balance[source]++; // to allow Euler paths, not just cycles
  while (!stack.empty()) {
    int u = stack.back(), v, edgeId, &it = nextEdge[u], degree = sz(adj[u]);
    if (it == degree) {
      walk.push_back(u);
      stack.pop_back();
      continue;
    }
    tie(v, edgeId) = adj[u][it++];
    if (!usedEdge[edgeId]) {
      balance[u]--, balance[v]++;
      usedEdge[edgeId] = 1;
      stack.push_back(v);
    }
  }
  for (int degreeDelta : balance)
    if (degreeDelta < 0 || sz(walk) != edgeCount + 1) return {};
  return {walk.rbegin(), walk.rend()};
}

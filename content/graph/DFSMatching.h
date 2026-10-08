/**
 * Author: Lukas Polacek
 * Date: 2009-10-28
 * License: CC0
 * Source:
 * Description: Maximum bipartite matching for smaller graphs. adj lists right neighbors of left vertices,
 * with separate 0-based indices per side. Initialize matchRight to -1; it stores the matched
 * left vertex or -1. Returns matching size; prefer HopcroftKarp when V*E is large.
 * Time: O(VE)
 * Usage: vector<vector<int>> adj={{0,1},{1}};
 * vector<int> matchRight(2,-1);
 * int size=dfsMatching(adj,matchRight); // 2
 * Status: works
 */
#pragma once
bool find(int v, vector<vector<int>> &adj, vector<int> &matchRight, vector<int> &visited) {
  if (matchRight[v] == -1) return 1;
  visited[v] = 1;
  int matchedLeft = matchRight[v];
  for (int nextRight : adj[matchedLeft])
    if (!visited[nextRight] && find(nextRight, adj, matchRight, visited)) {
      matchRight[nextRight] = matchedLeft;
      return 1;
    }
  return 0;
}
int dfsMatching(vector<vector<int>> &adj, vector<int> &matchRight) {
  vector<int> visited;
  for (int i = 0; i < (sz(adj)); ++i) {
    visited.assign(sz(matchRight), 0);
    for (int v : adj[i])
      if (find(v, adj, matchRight, visited)) {
        matchRight[v] = i;
        break;
      }
  }
  return sz(matchRight) - (int)count(all(matchRight), -1);
}

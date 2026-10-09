/**
 * Author: Johan Sannemo, Simon Lindholm
 * Date: 2016-12-15
 * License: CC0
 * Description: Use to select the fewest vertices covering every edge in a bipartite graph,
 * e.g. minimum rows/columns covering marked cells. Cover size equals maximum matching size.
 * adj has n+1 entries, listing right indices 1..m; index 0 is unused. Returned IDs <=n are left
 * vertices; IDs n+v denote right vertex v. Vertices outside the cover form a maximum independent
 * set.
 * Time: O(E \sqrt{V})
 * Status: stress-tested
 * Usage: auto vertices=cover(adj,n,m);
 * // id<=n: left id; otherwise right id-n (both 1-based).
 */
#pragma once

#include "HopcroftKarp.h"
vector<int> cover(vector<vector<int>> &adj, int n, int m) {
  vector<int> matchRight(m + 1, -1);
  int matchingSize = hopcroftKarp(adj, matchRight);
  vector<bool> reachableLeft(n + 1, true), reachableRight(m + 1);
  for (int matchedLeft : matchRight)
    if (matchedLeft != -1) reachableLeft[matchedLeft] = false;
  vector<int> stack, cover;
  for (int i = 1; i <= n; ++i)
    if (reachableLeft[i]) stack.push_back(i);
  while (!stack.empty()) {
    int i = stack.back();
    stack.pop_back();
    reachableLeft[i] = 1;
    for (int v : adj[i])
      if (!reachableRight[v] && matchRight[v] != -1) {
        reachableRight[v] = true;
        stack.push_back(matchRight[v]);
      }
  }
  for (int i = 1; i <= n; ++i)
    if (!reachableLeft[i]) cover.push_back(i);
  for (int i = 1; i <= m; ++i)
    if (reachableRight[i]) cover.push_back(n + i);
  assert(sz(cover) == matchingSize);
  return cover;
}

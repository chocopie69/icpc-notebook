/**
 * Author: Johan Sannemo, Simon Lindholm
 * Date: 2016-12-15
 * License: CC0
 * Description: Bipartite only: adj has n left vertices listing right indices 0..m-1. Returned IDs <n are left
 * vertices; IDs n+v denote right vertex v. Vertices outside the cover form a maximum independent
 * set.
 * Status: stress-tested
 * Usage: auto vertices=cover(adj,n,m);
 * // id<n: left id; otherwise right id-n.
 */
#pragma once

#include "DFSMatching.h"
vector<int> cover(vector<vector<int>> &adj, int n, int m) {
  vector<int> matchRight(m, -1);
  int matchingSize = dfsMatching(adj, matchRight);
  vector<bool> reachableLeft(n, true), reachableRight(m);
  for (int matchedLeft : matchRight)
    if (matchedLeft != -1) reachableLeft[matchedLeft] = false;
  vector<int> stack, cover;
  for (int i = 0; i < (n); ++i)
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
  for (int i = 0; i < (n); ++i)
    if (!reachableLeft[i]) cover.push_back(i);
  for (int i = 0; i < (m); ++i)
    if (reachableRight[i]) cover.push_back(n + i);
  assert(sz(cover) == matchingSize);
  return cover;
}

/**
 * Author: Simon Lindholm
 * Date: 2016-01-14
 * License: CC0
 * Description: Given a rooted tree and a subset S of nodes, compute the minimal
 * subtree that contains all the nodes by adding all (at most $|S|-1$)
 * pairwise LCA's and compressing edges.
 * Returns a list of (par, orig\_index) representing a tree rooted at virtual index 0.
 * The root points to itself.
 * Use when a query touches only a small subset of a large tree. Build LCA once and compress each
 * subset separately. At virtual index i, result[i].second is the original vertex and
 * result[i].first is its virtual parent index. A compressed edge represents an original path;
 * compute its length from depths or weighted root distances.
 * Time: $O(|S| (\log |S| + \log N))$
 * Status: Tested at CodeForces
 * Usage: LCA tree(adj);
 * auto compressed=compressTree(tree,{u,v,w});
 * for (int i=1;i<sz(compressed);i++) {
 *   int parentIndex=compressed[i].first;
 *   int originalVertex=compressed[i].second;
 * }
 */
#pragma once

#include "LCA.h"

typedef vector<pair<int, int>> vpi;
vpi compressTree(LCA &lca, const vector<int> &subset) {
  if (subset.empty()) return {};
  vector<int> virtualIndex;
  virtualIndex.resize(sz(lca.tin));
  vector<int> vertices = subset, &entryTime = lca.tin;
  auto cmp = [&](int a, int b) { return entryTime[a] < entryTime[b]; };
  sort(all(vertices), cmp);
  int m = sz(vertices) - 1;
  for (int i = 0; i < (m); ++i) {
    int a = vertices[i], b = vertices[i + 1];
    vertices.push_back(lca.lca(a, b));
  }
  sort(all(vertices), cmp);
  vertices.erase(unique(all(vertices)), vertices.end());
  for (int i = 0; i < (sz(vertices)); ++i) virtualIndex[vertices[i]] = i;
  vpi virtualTree = {pii(0, vertices[0])};
  for (int i = 0; i < (sz(vertices) - 1); ++i) {
    int a = vertices[i], b = vertices[i + 1];
    virtualTree.emplace_back(virtualIndex[lca.lca(a, b)], b);
  }
  return virtualTree;
}

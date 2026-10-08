/**
 * Author: Benjamin Qi, Oleksandr Kulkov, chilli
 * Date: 2020-01-12
 * License: CC0
 * Source: https://codeforces.com/blog/entry/53170, https://github.com/bqi343/USACO/blob/master/Implementations/content/graphs%20(12)/Trees%20(10)/HLD%20(10.3).h
 * Description: Decomposes a tree into vertex disjoint heavy paths and light
 * edges such that the path from any leaf to the root contains at most log(n)
 * light edges. Code does additive modifications and max queries, but can
 * support commutative segtree modifications/queries on paths and subtrees.
 * Takes as input the full adjacency list. VALS\_EDGES being true means that
 * values are stored in the edges, as opposed to the nodes. All values
 * initialized to the segtree default. Root must be 0.
 * Use for online path updates/queries with a commutative aggregate. The constructor reorders adj
 * in place and assumes vertices 0..n-1 rooted at 0. modifyPath adds a delta;
 * queryPath/querySubtree return maxima. With edge values each non-root vertex stores its parent
 * edge. Initialize finite tree values before addition, since the default is -inf.
 * Time: O((\log N)^2)
 * Usage: HLD<false> hld(adj); hld.tree.set(1,sz(adj),0);
 * hld.modifyPath(u,v,5); int best=hld.queryPath(u,v);
 * int subtreeBest=hld.querySubtree(u);
 */
#pragma once

#include "../data-structures/LazySegmentTree.h"
template <bool VALS_EDGES> struct HLD {
  int n, timer = 0;
  vector<vector<int>> adj;
  vector<int> parent, subtreeSize, head, pos;
  LazySegTree tree;
  HLD(vector<vector<int>> graph)
      : n(sz(graph)), adj(graph), parent(n, -1), subtreeSize(n, 1), head(n), pos(n), tree(n) {
    dfsSz(0);
    dfsHld(0);
  }
  void dfsSz(int v) {
    for (int &u : adj[v]) {
      adj[u].erase(find(all(adj[u]), v));
      parent[u] = v;
      dfsSz(u);
      subtreeSize[v] += subtreeSize[u];
      if (subtreeSize[u] > subtreeSize[adj[v][0]]) swap(u, adj[v][0]);
    }
  }
  void dfsHld(int v) {
    pos[v] = timer++;
    for (int u : adj[v]) {
      head[u] = (u == adj[v][0] ? head[v] : u);
      dfsHld(u);
    }
  }
  template <class B> void process(int u, int v, B visitRange) {
    for (;; v = parent[head[v]]) {
      if (pos[u] > pos[v]) swap(u, v);
      if (head[u] == head[v]) break;
      visitRange(pos[head[v]], pos[v] + 1);
    }
    visitRange(pos[u] + VALS_EDGES, pos[v] + 1);
  }
  void modifyPath(int u, int v, int val) {
    process(u, v, [&](int l, int r) { tree.add(l + 1, r, val); });
  }
  int queryPath(int u, int v) { // Modify depending on problem
    int answer = INT_MIN;
    process(u, v, [&](int l, int r) { answer = max(answer, tree.query(l + 1, r)); });
    return answer;
  }
  int querySubtree(int v) { // modifySubtree is similar
    return tree.query(pos[v] + VALS_EDGES + 1, pos[v] + subtreeSize[v]);
  }
};

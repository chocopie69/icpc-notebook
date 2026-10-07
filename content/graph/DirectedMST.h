/**
 * Author: chilli, Takanori MAEHARA, Benq, Simon Lindholm
 * Date: 2019-05-10
 * License: CC0
 * Source: https://github.com/spaghetti-source/algorithm/blob/master/graph/arborescence.cc
 * and https://github.com/bqi343/USACO/blob/42d177dfb9d6ce350389583cfa71484eb8ae614c/Implementations/content/graphs%20(12)/Advanced/DirectedMST.h for the reconstruction
 * Description: Finds a minimum spanning
 * tree/arborescence of a directed graph, given a root node. If no MST exists, returns -1.
 * Time: O(E \log V)
 * Status: Stress-tested, also tested on NWERC 2018 fastestspeedrun
 */
#pragma once

#include "../data-structures/UnionFindRollback.h"
struct ArborescenceEdge {
  int a, b;
  ll w;
};
struct SkewHeapNode { /// lazy skew heap node
  ArborescenceEdge key;
  SkewHeapNode *l, *r;
  ll delta;
  void prop() {
    key.w += delta;
    if (l) l->delta += delta;
    if (r) r->delta += delta;
    delta = 0;
  }
  ArborescenceEdge top() {
    prop();
    return key;
  }
};
SkewHeapNode *merge(SkewHeapNode *a, SkewHeapNode *b) {
  if (!a || !b) return a ?: b;
  a->prop(), b->prop();
  if (a->key.w > b->key.w) swap(a, b);
  swap(a->l, (a->r = merge(b, a->r)));
  return a;
}
void pop(SkewHeapNode *&a) {
  a->prop();
  a = merge(a->l, a->r);
}
pair<ll, vector<int>> dmst(int n, int r, vector<ArborescenceEdge> &g) {
  RollbackDSU uf(n);
  vector<SkewHeapNode *> heap(n);
  for (ArborescenceEdge e : g) heap[e.b] = merge(heap[e.b], new SkewHeapNode{e});
  ll res = 0;
  vector<int> seen(n, -1), path(n), par(n);
  seen[r] = r;
  vector<ArborescenceEdge> Q(n), in(n, {-1, -1}), comp;
  deque<tuple<int, int, vector<ArborescenceEdge>>> cycs;
  for (int s = 0; s < (n); ++s) {
    int u = s, qi = 0, w;
    while (seen[u] < 0) {
      if (!heap[u]) return {-1, {}};
      ArborescenceEdge e = heap[u]->top();
      heap[u]->delta -= e.w, pop(heap[u]);
      Q[qi] = e, path[qi++] = u, seen[u] = s;
      res += e.w, u = uf.find(e.a);
      if (seen[u] == s) { /// found cycle, contract
        SkewHeapNode *cyc = 0;
        int end = qi, time = uf.time();
        do cyc = merge(cyc, heap[w = path[--qi]]);
        while (uf.join(u, w));
        u = uf.find(u), heap[u] = cyc, seen[u] = -1;
        cycs.push_front({u, time, {&Q[qi], &Q[end]}});
      }
    }
    for (int i = 0; i < (qi); ++i) in[uf.find(Q[i].b)] = Q[i];
  }

  for (auto &[u, t, comp] : cycs) { // restore sol (optional)
    uf.rollback(t);
    ArborescenceEdge inEdge = in[u];
    for (auto &e : comp) in[uf.find(e.b)] = e;
    in[uf.find(inEdge.b)] = inEdge;
  }
  for (int i = 0; i < (n); ++i) par[i] = in[i].a;
  return {res, par};
}

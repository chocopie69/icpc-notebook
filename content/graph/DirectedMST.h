/**
 * Author: chilli, Takanori MAEHARA, Benq, Simon Lindholm
 * Date: 2019-05-10
 * License: CC0
 * Source: https://github.com/spaghetti-source/algorithm/blob/master/graph/arborescence.cc
 * and https://github.com/bqi343/USACO/blob/42d177dfb9d6ce350389583cfa71484eb8ae614c/Implementations/content/graphs%20(12)/Advanced/DirectedMST.h for the reconstruction
 * Description: Finds a minimum spanning
 * tree/arborescence of a directed graph, given a root node. If no MST exists, returns -1.
 * An arborescence has a directed path from root to every vertex and one incoming edge per
 * non-root vertex. Vertices are 0..n-1. Returns (totalWeight,parent), with parent[root]=-1;
 * failure is (-1,empty vector), so inspect the vector because a valid weight can be -1. Selects
 * cheapest incoming edges, contracts cycles, then uses rollback to reconstruct parents.
 * Time: O(E \log V)
 * Status: Stress-tested, also tested on NWERC 2018 fastestspeedrun
 * Usage: vector<ArborescenceEdge> edges={{0,1,3},{0,2,5},{1,2,1}};
 * auto [weight,parent]=dmst(3,0,edges); // weight=4
 */
#pragma once

#include "../data-structures/UnionFindRollback.h"
struct ArborescenceEdge {
  int from, to;
  ll weight;
};
struct SkewHeapNode { /// lazy skew heap node
  ArborescenceEdge key;
  SkewHeapNode *left, *right;
  ll delta;
  void prop() {
    key.weight += delta;
    if (left) left->delta += delta;
    if (right) right->delta += delta;
    delta = 0;
  }
  ArborescenceEdge top() {
    prop();
    return key;
  }
};
SkewHeapNode *merge(SkewHeapNode *first, SkewHeapNode *second) {
  if (!first || !second) return first ?: second;
  first->prop(), second->prop();
  if (first->key.weight > second->key.weight) swap(first, second);
  swap(first->left, (first->right = merge(second, first->right)));
  return first;
}
void pop(SkewHeapNode *&first) {
  first->prop();
  first = merge(first->left, first->right);
}
pair<ll, vector<int>> dmst(int n, int root, vector<ArborescenceEdge> &edges) {
  RollbackDSU dsu(n);
  vector<SkewHeapNode *> heap(n);
  for (ArborescenceEdge e : edges) heap[e.to] = merge(heap[e.to], new SkewHeapNode{e});
  ll totalWeight = 0;
  vector<int> seen(n, -1), path(n), parent(n);
  seen[root] = root;
  vector<ArborescenceEdge> pathEdges(n), incoming(n, {-1, -1}), cycleEdges;
  deque<tuple<int, int, vector<ArborescenceEdge>>> cycles;
  for (int s = 0; s < (n); ++s) {
    int u = s, pathSize = 0, cycleVertex;
    while (seen[u] < 0) {
      if (!heap[u]) return {-1, {}};
      ArborescenceEdge e = heap[u]->top();
      heap[u]->delta -= e.weight, pop(heap[u]);
      pathEdges[pathSize] = e, path[pathSize++] = u, seen[u] = s;
      totalWeight += e.weight, u = dsu.find(e.from);
      if (seen[u] == s) { /// found cycle, contract
        SkewHeapNode *cycleHeap = 0;
        int end = pathSize, checkpoint = dsu.time();
        do cycleHeap = merge(cycleHeap, heap[cycleVertex = path[--pathSize]]);
        while (dsu.join(u, cycleVertex));
        u = dsu.find(u), heap[u] = cycleHeap, seen[u] = -1;
        cycles.push_front({u, checkpoint, {&pathEdges[pathSize], &pathEdges[end]}});
      }
    }
    for (int i = 0; i < (pathSize); ++i) incoming[dsu.find(pathEdges[i].to)] = pathEdges[i];
  }

  for (auto &[u, t, cycleEdges] : cycles) { // restore sol (optional)
    dsu.rollback(t);
    ArborescenceEdge inEdge = incoming[u];
    for (auto &e : cycleEdges) incoming[dsu.find(e.to)] = e;
    incoming[dsu.find(inEdge.to)] = inEdge;
  }
  for (int i = 0; i < (n); ++i) parent[i] = incoming[i].from;
  return {totalWeight, parent};
}

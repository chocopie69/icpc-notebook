/**
 * Author: Lukas Polacek, Simon Lindholm
 * Date: 2019-12-26
 * License: CC0
 * Source: folklore
 * Description: Rollback DSU on 0..n-1; allocate n+1 for labels 1..n. Save time() before temporary joins and
 * rollback(checkpoint) afterward. Checkpoints are history lengths, not join counts. Do not add
 * path compression unless its changes are also recorded.
 * Usage: RollbackDSU uf(n); int checkpoint=uf.time();
 * uf.join(u,v); bool connected=uf.find(u)==uf.find(v);
 * uf.rollback(checkpoint);
 * Time: $O(\log(N))$
 * Status: tested as part of DirectedMST.h
 */
#pragma once
struct RollbackDSU {
  vector<int> parentOrSize;
  vector<pii> history;
  RollbackDSU(int n) : parentOrSize(n, -1) {}
  int size(int x) { return -parentOrSize[find(x)]; }
  int find(int x) { return parentOrSize[x] < 0 ? x : find(parentOrSize[x]); }
  int time() { return sz(history); }
  void rollback(int checkpoint) {
    for (int i = time(); i-- > checkpoint;) parentOrSize[history[i].first] = history[i].second;
    history.resize(checkpoint);
  }
  bool join(int a, int b) {
    a = find(a), b = find(b);
    if (a == b) return false;
    if (parentOrSize[a] > parentOrSize[b]) swap(a, b);
    history.push_back({a, parentOrSize[a]});
    history.push_back({b, parentOrSize[b]});
    parentOrSize[a] += parentOrSize[b];
    parentOrSize[b] = a;
    return true;
  }
};

/**
 * Author: Simon Lindholm
 * Date: 2017-05-11
 * License: CC0
 * Source: folklore
 * Description: Offline 2D Fenwick tree. x is in [1, n]; y can be any integer.
 * Register every update coordinate with fakeUpdate before init. query(x,y) sums points
 * with first coordinate <= x and second coordinate <= y. Construct a new object to reset.
 * Usage: Fenwick2D bit(n); bit.fakeUpdate(x,y); bit.init(); bit.update(x,y,5); bit.query(x,y);
 * Time: $O(\log^2 N)$ per operation; $O(U \log N)$ memory for U registered points.
 */
#pragma once
#include "FenwickTree.h"
struct Fenwick2D {
  int n;
  vector<vector<int>> ys;
  vector<Fenwick> bit;
  Fenwick2D(int n) : n(n), ys(n + 1), bit(n + 1) {}
  void fakeUpdate(int x, int y) {
    for (int i = x; i <= n; i += i & -i) ys[i].push_back(y);
  }
  void init() {
    for (int i = 1; i <= n; i++) {
      sort(all(ys[i]));
      ys[i].erase(unique(all(ys[i])), ys[i].end());
      bit[i] = Fenwick(sz(ys[i]));
    }
  }
  void update(int x, int y, ll delta) {
    for (int i = x; i <= n; i += i & -i) {
      int pos = lower_bound(all(ys[i]), y) - ys[i].begin() + 1;
      bit[i].update(pos, delta);
    }
  }
  ll query(int x, int y) const {
    ll sum = 0;
    for (int i = x; i > 0; i -= i & -i) {
      int pos = upper_bound(all(ys[i]), y) - ys[i].begin();
      sum += bit[i].query(pos);
    }
    return sum;
  }
};

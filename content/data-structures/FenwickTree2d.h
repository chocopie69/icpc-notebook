/**
 * Author: Simon Lindholm
 * Date: 2017-05-11
 * License: CC0
 * Source: folklore
 * Description: Offline 2D Fenwick tree. x is in [1, n]; y can be any integer.
 * Register every update coordinate with fakeUpdate before init. query(x,y) sums points
 * with first coordinate <= x and second coordinate <= y. Construct a new object to reset.
 * All future update locations must be registered, even if their eventual values are unknown.
 * Query coordinates need not be registered. Sum a rectangle [x1,x2] by [y1,y2] with four prefix
 * queries using x1-1 and y1-1. Updates add a delta rather than assign a value.
 * Usage: Fenwick2D bit(n);
 * bit.fakeUpdate(2,10); bit.fakeUpdate(4,20); bit.init();
 * bit.update(2,10,5); ll sum=bit.query(3,15); // 5
 * Time: $O(\log^2 N)$ per operation; $O(U \log N)$ memory for U registered points.
 */
#pragma once
#include "FenwickTree.h"
struct Fenwick2D {
  int n;
  vector<vector<int>> yCoords;
  vector<Fenwick> bit;
  Fenwick2D(int n) : n(n), yCoords(n + 1), bit(n + 1) {}
  void fakeUpdate(int x, int y) {
    for (int i = x; i <= n; i += i & -i) yCoords[i].push_back(y);
  }
  void init() {
    for (int i = 1; i <= n; i++) {
      sort(all(yCoords[i]));
      yCoords[i].erase(unique(all(yCoords[i])), yCoords[i].end());
      bit[i] = Fenwick(sz(yCoords[i]));
    }
  }
  void update(int x, int y, ll delta) {
    for (int i = x; i <= n; i += i & -i) {
      int pos = lower_bound(all(yCoords[i]), y) - yCoords[i].begin() + 1;
      bit[i].update(pos, delta);
    }
  }
  ll query(int x, int y) const {
    ll sum = 0;
    for (int i = x; i > 0; i -= i & -i) {
      int pos = upper_bound(all(yCoords[i]), y) - yCoords[i].begin();
      sum += bit[i].query(pos);
    }
    return sum;
  }
};

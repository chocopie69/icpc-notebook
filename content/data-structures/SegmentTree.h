/**
 * Author: Lucian Bicsi
 * Date: 2017-10-31
 * License: CC0
 * Source: folklore
 * Description: Point assignment and range maximum. Positions are 1-based; query(l,r) is inclusive. Initially
 * every position equals initialValue. To change the aggregate, edit T, merge and its identity
 * unit; use a wider T if needed.
 * Usage: SegTree seg(5,0); seg.update(3,7);
 * int best=seg.query(2,4); // 7; positions 2,3,4
 * Time: $O(\log N)$ per operation; $O(N)$ memory.
 */
#pragma once
struct SegTree {
  typedef int T;
  static constexpr T unit = INT_MIN;
  int n;
  vector<T> seg;
  SegTree(int n = 0, T initialValue = unit) : n(n), seg(4 * n + 4, unit) {
    if (n > 0) build(1, 1, n, initialValue);
  }
  T merge(T a, T b) const { return max(a, b); }
  void build(int id, int lo, int hi, T val) {
    if (lo == hi) {
      seg[id] = val;
      return;
    }
    int mid = (lo + hi) / 2;
    build(id * 2, lo, mid, val);
    build(id * 2 + 1, mid + 1, hi, val);
    seg[id] = merge(seg[id * 2], seg[id * 2 + 1]);
  }
  void update(int id, int lo, int hi, int pos, T val) {
    if (lo == hi) {
      seg[id] = val;
      return;
    }
    int mid = (lo + hi) / 2;
    if (pos <= mid)
      update(id * 2, lo, mid, pos, val);
    else
      update(id * 2 + 1, mid + 1, hi, pos, val);
    seg[id] = merge(seg[id * 2], seg[id * 2 + 1]);
  }
  void update(int pos, T val) { update(1, 1, n, pos, val); }
  T query(int id, int lo, int hi, int l, int r) const {
    if (r < lo || hi < l) return unit;
    if (l <= lo && hi <= r) return seg[id];
    int mid = (lo + hi) / 2;
    return merge(query(id * 2, lo, mid, l, r), query(id * 2 + 1, mid + 1, hi, l, r));
  }
  T query(int l, int r) const {
    if (n == 0 || l > r) return unit;
    return query(1, 1, n, l, r);
  }
};

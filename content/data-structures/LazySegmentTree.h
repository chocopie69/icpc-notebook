/**
 * Author: Simon Lindholm
 * Date: 2016-10-08
 * License: CC0
 * Source: me
 * Description: Array-based segment tree for range assignment, range addition and range maximum.
 * Positions are 1-based; all ranges [l,r] are inclusive. Values and additions must fit int.
 * Vector constructor uses a[1..n] (a[0] unused). Initial value defaults to -inf.
 * hasSet distinguishes a pending assignment from no assignment, so every int value is allowed.
 * Usage: LazySegTree seg(n, 0); seg.add(1,n,3); seg.set(2,4,5); int ans = seg.query(1,n);
 * Time: $O(\log N)$ per operation; $O(N)$ memory.
 */
#pragma once
const int inf = 1000000000;
struct LazySegTree {
  struct Node {
    int val = -inf;
    int lazySet = 0;
    int lazyAdd = 0;
    bool hasSet = false;
  };
  int n;
  vector<Node> seg;
  LazySegTree(int n, int initial = -inf) : n(n), seg(4 * n + 4, Node{initial}) {}
  LazySegTree(const vector<int> &a) : LazySegTree(max(0, sz(a) - 1)) {
    if (n > 0) build(1, 1, n, a);
  }
  void build(int id, int lo, int hi, const vector<int> &a) {
    if (lo == hi) {
      seg[id].val = a[lo];
      return;
    }
    int mid = (lo + hi) / 2;
    build(id * 2, lo, mid, a);
    build(id * 2 + 1, mid + 1, hi, a);
    pull(id);
  }
  void pull(int id) { seg[id].val = max(seg[id * 2].val, seg[id * 2 + 1].val); }
  void applySet(int id, int val) {
    seg[id].val = val;
    seg[id].lazySet = val;
    seg[id].lazyAdd = 0;
    seg[id].hasSet = true;
  }
  void applyAdd(int id, int val) {
    seg[id].val += val;
    if (seg[id].hasSet)
      seg[id].lazySet += val;
    else
      seg[id].lazyAdd += val;
  }
  void push(int id) {
    // Assignment overwrites older updates; addition comes after assignment.
    if (seg[id].hasSet) {
      applySet(id * 2, seg[id].lazySet);
      applySet(id * 2 + 1, seg[id].lazySet);
      seg[id].hasSet = false;
    }
    if (seg[id].lazyAdd != 0) {
      applyAdd(id * 2, seg[id].lazyAdd);
      applyAdd(id * 2 + 1, seg[id].lazyAdd);
      seg[id].lazyAdd = 0;
    }
  }
  void update(int id, int lo, int hi, int l, int r, int val, bool assign) {
    if (r < lo || hi < l) return;
    if (l <= lo && hi <= r) {
      if (assign)
        applySet(id, val);
      else
        applyAdd(id, val);
      return;
    }
    push(id);
    int mid = (lo + hi) / 2;
    update(id * 2, lo, mid, l, r, val, assign);
    update(id * 2 + 1, mid + 1, hi, l, r, val, assign);
    pull(id);
  }
  void set(int l, int r, int val) {
    if (n > 0 && l <= r) update(1, 1, n, l, r, val, true);
  }
  void add(int l, int r, int val) {
    if (n > 0 && l <= r) update(1, 1, n, l, r, val, false);
  }
  int query(int id, int lo, int hi, int l, int r) {
    if (r < lo || hi < l) return INT_MIN;
    if (l <= lo && hi <= r) return seg[id].val;
    push(id);
    int mid = (lo + hi) / 2;
    return max(query(id * 2, lo, mid, l, r), query(id * 2 + 1, mid + 1, hi, l, r));
  }
  int query(int l, int r) {
    if (n == 0 || l > r) return INT_MIN;
    return query(1, 1, n, l, r);
  }
};

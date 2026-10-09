/**
 * Author: Simon Lindholm
 * Date: 2016-10-08
 * License: CC0
 * Source: me
 * Description: Range assignment, addition and maximum on inclusive, 1-based [l,r]. The vector constructor
 * ignores values[0]; default initial value is -inf, so initialize finite values before addition.
 * Values and additions must fit int. Keep hasSet for assignments; changing to sums also requires
 * segment lengths. For multiplication/other tags, also change their composition order.
 * Usage: LazySegTree seg(5,0); seg.add(1,3,4); seg.set(2,2,9);
 * int best=seg.query(1,5); // 9
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
  LazySegTree(int n, int initialValue = -inf) : n(n), seg(4 * n + 4, Node{initialValue}) {}
  LazySegTree(const vector<int> &values) : LazySegTree(max(0, sz(values) - 1)) {
    if (n > 0) build(1, 1, n, values);
  }
  void build(int id, int lo, int hi, const vector<int> &values) {
    if (lo == hi) {
      seg[id].val = values[lo];
      return;
    }
    int mid = (lo + hi) / 2;
    build(id * 2, lo, mid, values);
    build(id * 2 + 1, mid + 1, hi, values);
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
  void update(int id, int lo, int hi, int l, int r, int val, bool isAssignment) {
    if (r < lo || hi < l) return;
    if (l <= lo && hi <= r) {
      if (isAssignment)
        applySet(id, val);
      else
        applyAdd(id, val);
      return;
    }
    push(id);
    int mid = (lo + hi) / 2;
    update(id * 2, lo, mid, l, r, val, isAssignment);
    update(id * 2 + 1, mid + 1, hi, l, r, val, isAssignment);
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

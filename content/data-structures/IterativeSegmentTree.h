/**
 * Author: Lucian Bicsi, adapted to the notebook style
 * Date: 2017-10-31
 * License: CC0
 * Source: https://github.com/kth-competitive-programming/kactl/blob/main/content/data-structures/SegmentTree.h
 * Description: KACTL's 2N iterative maximum tree: 1-based point assignment and inclusive [l,r].
 * Initially uniform initialValue; no power-of-two padding. Empty queries return unit.
 * For another aggregate, edit T/merge/unit; preserve the two accumulator orders.
 * Initialize with unit then update leaves, or rebuild parents if the aggregate changes.
 * Usage: IterativeSegTree seg(5,0);
 * seg.update(3,7); // a[3]=7, not +=7
 * int best=seg.query(2,4); // 7; includes positions 2,3,4
 * int single=seg.query(3,3); // 7
 * // To build from a[1..n]: update(i,a[i]) for i=1..n.
 * Time: $O(N)$ construction, $O(\log N)$ per update/query; $O(N)$ memory (2N values).
 */
#pragma once
struct IterativeSegTree {
  typedef int T;
  static constexpr T unit = INT_MIN;
  T merge(T a, T b) const { return max(a, b); }
  vector<T> seg;
  int n;
  IterativeSegTree(int n = 0, T initialValue = unit) : seg(2 * n, initialValue), n(n) {}
  void update(int pos, T val) {
    for (seg[pos += n - 1] = val; pos /= 2;) seg[pos] = merge(seg[pos * 2], seg[pos * 2 + 1]);
  }
  T query(int l, int r) const {
    if (n == 0 || l > r) return unit;
    T leftResult = unit, rightResult = unit;
    for (l += n - 1, r += n - 1; l <= r; l /= 2, r /= 2) {
      if (l & 1) leftResult = merge(leftResult, seg[l++]);
      if (!(r & 1)) rightResult = merge(seg[r--], rightResult);
    }
    return merge(leftResult, rightResult);
  }
};

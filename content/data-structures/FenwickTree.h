/**
 * Author: Lukas Polacek
 * Date: 2009-10-30
 * License: CC0
 * Source: folklore/TopCoder
 * Description: 1-based sums: update(pos,delta) adds rather than assigns; query(pos) sums [1,pos] and
 * query(l,r) is inclusive. lowerBound finds the first prefix reaching a target; it requires
 * nonnegative elements and returns 0 for target<=0 or n+1 if absent. This is Fenwick walking
 * (binary lifting): skip a block only if its whole sum is still below the target. With
 * frequencies, lowerBound(k) locates the kth item, counting duplicates. Updates may be negative,
 * but every resulting element must remain nonnegative for walking to work.
 * Usage: Fenwick bit(5); bit.update(2,3); bit.update(4,7);
 * ll sum=bit.query(2,4); // 10
 * int pos=bit.lowerBound(4); // 4
 * // With 3 items at position 2 and 7 at position 4:
 * int kth=bit.lowerBound(5); // fifth item is at position 4
 * // To reach a positive target starting from position l:
 * int l=3; ll target=2;
 * ll before=bit.query(l-1);
 * pos=bit.lowerBound(before+target);
 * // n+1 means insufficient sum in [l,n].
 * Time: $O(\log N)$ per operation; $O(N)$ memory.
 */
#pragma once
struct Fenwick {
  int n;
  vector<ll> bit;
  Fenwick(int n = 0) : n(n), bit(n + 1, 0) {}
  void update(int pos, ll delta) {
    for (int i = pos; i <= n; i += i & -i) bit[i] += delta;
  }
  ll query(int pos) const {
    ll sum = 0;
    for (int i = pos; i > 0; i -= i & -i) sum += bit[i];
    return sum;
  }
  ll query(int l, int r) const {
    if (l > r) return 0;
    return query(r) - query(l - 1);
  }
  int lowerBound(ll targetSum) const {
    if (targetSum <= 0) return 0;
    int pos = 0;
    int step = 1;
    while (step <= n / 2) step *= 2;
    // Walk by decreasing powers of two; targetSum is the remaining sum needed.
    for (; step > 0; step /= 2) {
      int next = pos + step;
      if (next <= n && bit[next] < targetSum) {
        // Skip this entire block; no prefix ending inside it can reach the target.
        pos = next;
        targetSum -= bit[next];
      }
    }
    return pos + 1;
  }
};

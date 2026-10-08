/**
 * Author: Lukas Polacek
 * Date: 2009-10-30
 * License: CC0
 * Source: folklore/TopCoder
 * Description: 1-based sums: update(pos,delta) adds rather than assigns; query(pos) sums [1,pos] and
 * query(l,r) is inclusive. lowerBound finds the first prefix reaching a target; it requires
 * nonnegative elements and returns 0 for target<=0 or n+1 if absent.
 * Usage: Fenwick bit(5); bit.update(2,3); bit.update(4,7);
 * ll sum=bit.query(2,4); // 10
 * int pos=bit.lowerBound(4); // 4
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
    // pos is the last prefix whose sum is smaller than the target.
    for (; step > 0; step /= 2) {
      int next = pos + step;
      if (next <= n && bit[next] < targetSum) {
        pos = next;
        targetSum -= bit[next];
      }
    }
    return pos + 1;
  }
};

/**
 * Author: Lukas Polacek
 * Date: 2009-10-30
 * License: CC0
 * Source: folklore/TopCoder
 * Description: 1-based Fenwick tree. update(pos, delta) adds to a[pos]; query(pos) sums [1, pos].
 * lowerBound requires nonnegative elements; returns 0 for sum <= 0, or n+1 if absent.
 * Usage: Fenwick bit(n); bit.update(3, 5); ll sum = bit.query(3);
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
  int lowerBound(ll sum) const {
    if (sum <= 0) return 0;
    int pos = 0;
    int step = 1;
    while (step <= n / 2) step *= 2;
    // pos is the last prefix whose sum is smaller than the target.
    for (; step > 0; step /= 2) {
      int next = pos + step;
      if (next <= n && bit[next] < sum) {
        pos = next;
        sum -= bit[next];
      }
    }
    return pos + 1;
  }
};

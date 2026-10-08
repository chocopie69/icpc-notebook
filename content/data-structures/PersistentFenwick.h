/**
 * Author: VNOI Wiki, adapted to the notebook style
 * Source: https://wiki.vnoi.info/algo/data-structures/persistent-data-structures
 * Description: Timestamped 2D Fenwick tree: point addition and historical rectangle sums.
 * Coordinates are 1-based; rectangles are inclusive. Initially zero. Updates MUST arrive in
 * nondecreasing time order; same-time additions are combined. Queries may use any time and
 * include all updates at or before it. Only the latest state can be updated; branching is unsupported.
 * Each BIT cell stores {time,sum}; binary search selects its historical value. The dense
 * N*M history vectors can be expensive. For 1D, remove the y loops and use history[x].
 * Usage: PersistentFenwick2D bit(n,m);
 * bit.update(2,3,5,1); // add 5 at (2,3), time 1
 * bit.update(2,3,-2,2); // time 2; negative deltas are allowed
 * ll old=bit.query(1,1,1,n,m); // rectangle sum at time 1: 5
 * ll now=bit.query(2,n,m); // prefix rectangle [1,n] x [1,m] at time 2: 3
 * // Queries before the first update return zero; sums must fit ll.
 * Time: Amortized $O(\log N\log M)$ update, $O(\log N\log M\log(U+1))$ query;
 * $O(NM+U\log N\log M)$ memory for U updates.
 */
#pragma once
struct PersistentFenwick2D {
  int n, m;
  vector<vector<vector<pair<int, ll>>>> history;
  PersistentFenwick2D(int n, int m)
      : n(n), m(m), history(n + 1, vector<vector<pair<int, ll>>>(m + 1)) {}
  void update(int x, int y, ll delta, int time) {
    for (int i = x; i <= n; i += i & -i)
      for (int j = y; j <= m; j += j & -j) {
        auto &cell = history[i][j];
        ll value = (cell.empty() ? 0 : cell.back().second) + delta;
        if (!cell.empty() && cell.back().first == time)
          cell.back().second = value;
        else
          cell.push_back({time, value});
      }
  }
  ll query(int time, int x, int y) const {
    ll sum = 0;
    for (int i = x; i > 0; i -= i & -i)
      for (int j = y; j > 0; j -= j & -j) {
        const auto &cell = history[i][j];
        auto it = upper_bound(all(cell), time,
                              [](int t, const pair<int, ll> &entry) { return t < entry.first; });
        if (it != cell.begin()) sum += prev(it)->second;
      }
    return sum;
  }
  ll query(int time, int x1, int y1, int x2, int y2) const {
    if (x1 > x2 || y1 > y2) return 0;
    return query(time, x2, y2) - query(time, x1 - 1, y2) - query(time, x2, y1 - 1) +
           query(time, x1 - 1, y1 - 1);
  }
};

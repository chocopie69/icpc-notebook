/**
 * Author: Personal Code::Blocks abbreviation, adapted
 * Description: Static minimum and maximum on 1-based inclusive [l,r], with l<=r. Input a[0] is
 * ignored. Rebuild after updates; overlapping blocks work for min/max, not sums.
 * Usage: SparseTable rmq(vector<int>{0,7,2,5,1});
 * int minimum=rmq.getMin(2,3); // 2
 * int maximum=rmq.getMax(2,3); // 5
 * Time: $O(N \log N)$ construction and memory; $O(1)$ per query.
 */
#pragma once
struct SparseTable {
  vector<vector<int>> stMin, stMax;
  SparseTable(const vector<int> &a) : stMin(1, a), stMax(1, a) {
    int n = sz(a) - 1;
    for (int k = 1; (1LL << k) <= n; k++) {
      stMin.emplace_back(n + 1);
      stMax.emplace_back(n + 1);
      for (int i = 1; i + (1 << k) - 1 <= n; i++) {
        int j = i + (1 << (k - 1));
        stMin[k][i] = min(stMin[k - 1][i], stMin[k - 1][j]);
        stMax[k][i] = max(stMax[k - 1][i], stMax[k - 1][j]);
      }
    }
  }
  int getMin(int l, int r) const {
    int k = __lg(r - l + 1);
    return min(stMin[k][l], stMin[k][r - (1 << k) + 1]);
  }
  int getMax(int l, int r) const {
    int k = __lg(r - l + 1);
    return max(stMax[k][l], stMax[k][r - (1 << k) + 1]);
  }
};

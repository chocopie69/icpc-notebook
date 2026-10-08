/**
 * Author: Simon Lindholm
 * License: CC0
 * Source: Codeforces
 * Description: Given $a[i] = \min_{lo(i) \le k < hi(i)}(f(i, k))$ where the (minimal)
 * optimal $k$ increases with $i$, computes $a[i]$ for $i = L..R-1$.
 * Customization skeleton for one DP layer. Replace lo/hi with valid split bounds, f with
 * previousLayer[split]+cost(split,index), and store with destination arrays. solve(l,r) covers
 * [l,r). Each index needs at least one candidate; optimal split indices must be nondecreasing.
 * Keep the previous layer fixed while computing the current one.
 * Time: O((N + (hi-lo)) \log N)
 * Status: tested on http://codeforces.com/contest/321/problem/E
 * Usage: // Implement lo,hi,f,store and declare DP arrays first.
 * DivideConquerDP solver; solver.solve(1,n+1); // indices 1..n
 */
#pragma once
struct DivideConquerDP { // Modify at will:
  int lo(int index) { return 0; }
  int hi(int index) { return index; }
  ll f(int index, int split) { return dp[index][split]; }
  void store(int index, int split, ll value) { answer[index] = pii(split, value); }
  void rec(int l, int r, int optL, int optR) {
    if (l >= r) return;
    int mid = (l + r) >> 1;
    pair<ll, int> best(LLONG_MAX, optL);
    for (int split = max(optL, lo(mid)); split < (min(optR, hi(mid))); ++split)
      best = min(best, make_pair(f(mid, split), split));
    store(mid, best.second, best.first);
    rec(l, mid, optL, best.second + 1);
    rec(mid + 1, r, best.second, optR);
  }
  void solve(int l, int r) { rec(l, r, INT_MIN, INT_MAX); }
};

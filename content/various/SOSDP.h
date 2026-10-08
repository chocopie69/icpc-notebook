/**
 * Author: Personal notebook
 * Source: https://usaco.guide/plat/dp-sos
 * Description: In-place sums over subsets/supersets, including the mask itself and zero.
 * dp has exactly $2^B$ entries (B>=0); copy the input separately for each transform.
 * For frequencies, sub[full XOR mask] counts disjoint input masks. inverse subtracts to restore
 * input. Keep the bit loop outermost. Intermediate sums must fit ll; normalize modular results.
 * Min/max variants have no subtraction inverse.
 * Usage: vector<ll> freq={1,2,3,4}; // masks 0,1,2,3
 * auto sub=freq; subsetSOS(sub); // {1,3,4,10}
 * auto super=freq; supersetSOS(super); // {10,6,7,4}
 * int full=sz(freq)-1, mask=1;
 * ll disjoint=sub[full^mask]; // 4
 * subsetSOS(sub,true); // restores freq
 * Time: $O(B2^B)$ time; $O(1)$ auxiliary memory.
 */
#pragma once
void subsetSOS(vector<ll> &dp, bool inverse = false) {
  int bits = __lg(sz(dp));
  for (int bit = 0; bit < bits; bit++)
    for (int mask = 0; mask < sz(dp); mask++)
      if (mask >> bit & 1) dp[mask] += (inverse ? -1 : 1) * dp[mask ^ (1 << bit)];
}
void supersetSOS(vector<ll> &dp, bool inverse = false) {
  int bits = __lg(sz(dp));
  for (int bit = 0; bit < bits; bit++)
    for (int mask = 0; mask < sz(dp); mask++)
      if (!(mask >> bit & 1)) dp[mask] += (inverse ? -1 : 1) * dp[mask | (1 << bit)];
}

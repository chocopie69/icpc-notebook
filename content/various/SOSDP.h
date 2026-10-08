/**
 * Author: Personal notebook
 * Source: https://usaco.guide/plat/dp-sos
 * Description: In-place sums over subsets or supersets of each mask, including itself and mask 0.
 * dp must have exactly $2^B$ entries, with B>=0. Start from a copy of the original values for
 * each transform. For frequencies, subsetSOS gives the count of input masks contained in mask;
 * subset[full XOR mask] counts inputs disjoint from mask. The inverse restores the original
 * array by subtracting instead of adding. Intermediate sums must fit ll; for modular sums,
 * normalize each addition/subtraction. Min/max aggregation is possible but has no such inverse.
 * Keep the bit loop outside the mask loop so every value is included exactly once.
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

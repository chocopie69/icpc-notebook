/**
 * Author: Mårten Wiman
 * License: CC0
 * Source: Pisinger 1999, "Linear Time Algorithms for Knapsack Problems with Bounded Weights"
 * Description: Given N non-negative integer weights w and a non-negative target t,
 * computes the maximum S <= t such that S is the sum of some subset of the weights.
 * This is 0/1 subset sum with bounded weights: each weight is used at most once and value equals
 * weight. Returns only the best achievable sum, not chosen items. Weights/capacity must be
 * nonnegative and sums must fit int. Useful when maxWeight is small even if capacity is large.
 * This is not general profit/weight knapsack.
 * Time: O(N \max(w_i))
 * Status: Tested on kattis:eavesdropperevasion, stress-tested
 * Usage: int best=knapsack({3,5,7},10); // 10, using 3+7
 */
#pragma once
int knapsack(vector<int> weights, int capacity) {
  int total = 0, prefixSize = 0, state;
  while (prefixSize < sz(weights) && total + weights[prefixSize] <= capacity)
    total += weights[prefixSize++];
  if (prefixSize == sz(weights)) return total;
  int maxWeight = *max_element(all(weights));
  vector<int> previous, dp(2 * maxWeight, -1);
  dp[total + maxWeight - capacity] = prefixSize;
  for (int i = prefixSize; i < (sz(weights)); ++i) {
    previous = dp;
    for (int state = 0; state < (maxWeight); ++state)
      dp[state + weights[i]] = max(dp[state + weights[i]], previous[state]);
    for (state = 2 * maxWeight; --state > maxWeight;)
      for (int j = max(0, previous[state]); j < (dp[state]); ++j)
        dp[state - weights[j]] = max(dp[state - weights[j]], j);
  }
  for (total = capacity; dp[total + maxWeight - capacity] < 0; total--);
  return total;
}

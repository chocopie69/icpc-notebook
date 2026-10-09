/**
 * Author: Mattias de Zalenski, Fredrik Niemelä, Per Austrin, Simon Lindholm
 * Date: 2002-09-26
 * Source: Max Bennedich
 * Description: Counts multiset arrangements: $\frac{(\sum k_i)!}{\prod k_i!}$. counts[i] must be nonnegative.
 * Exact integer calculation without a modulus; the result and intermediate products must fit ll.
 * For large exact counts use big integers; modular counts need factorials/inverses, not integer /.
 * Status: Tested on kattis:lexicography
 * Usage: vector<int> counts={2,1}; ll ways=multinomial(counts); // 3
 */
#pragma once
ll multinomial(vector<int> &counts) {
  ll ways = 1, total = counts.empty() ? 1 : counts[0];
  for (int i = 1; i < (sz(counts)); ++i)
    for (int j = 0; j < (counts[i]); ++j) ways = ways * ++total / (j + 1);
  return ways;
}

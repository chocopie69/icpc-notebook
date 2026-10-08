/**
 * Author: User adamant on CodeForces
 * Source: http://codeforces.com/blog/entry/12143
 * Description: For each position in a string, computes p[0][i] = half length of
 *  longest even palindrome around pos i, p[1][i] = longest odd (half rounded down).
 * Indices are 0-based. Odd center i has length 2*p[1][i]+1 and covers [i-p[1][i],i+p[1][i]].
 * Even center i is the gap before s[i]: length 2*p[0][i], covering [i-p[0][i],i+p[0][i]-1]. The
 * extra even entry at i=n is zero. Radii permit constant-time palindrome checks after
 * construction.
 * Time: O(N)
 * Status: Stress-tested
 * Usage: auto p=manacher("abba");
 * int evenLength=2*p[0][2]; // 4
 */
#pragma once
array<vector<int>, 2> manacher(const string &s) {
  int n = sz(s);
  array<vector<int>, 2> radius = {vector<int>(n + 1), vector<int>(n)};
  for (int parity = 0; parity < (2); ++parity)
    for (int i = 0, windowLeft = 0, windowRight = 0; i < n; i++) {
      int remaining = windowRight - i + !parity;
      if (i < windowRight)
        radius[parity][i] = min(remaining, radius[parity][windowLeft + remaining]);
      int left = i - radius[parity][i], right = i + radius[parity][i] - !parity;
      while (left >= 1 && right + 1 < n && s[left - 1] == s[right + 1])
        radius[parity][i]++, left--, right++;
      if (right > windowRight) windowLeft = left, windowRight = right;
    }
  return radius;
}

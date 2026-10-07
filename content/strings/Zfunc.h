/**
 * Author: chilli
 * License: CC0
 * Description: z[i] is the common-prefix length of s and the suffix starting at i.
 * Positions are 0-based; z[0] = 0. Example: abacaba gives 0,0,1,0,3,0,1.
 * Usage: vector<int> z = zFunction(s);
 * Time: $O(N)$ time and memory.
 */
#pragma once
vector<int> zFunction(const string &s) {
  int n = sz(s);
  vector<int> z(n, 0);
  int l = 0;
  int r = -1;
  for (int i = 1; i < n; i++) {
    // [l,r] is the rightmost segment known to match a prefix of s.
    if (i <= r) z[i] = min(r - i + 1, z[i - l]);
    while (i + z[i] < n && s[z[i]] == s[i + z[i]]) z[i]++;
    if (i + z[i] - 1 > r) {
      l = i;
      r = i + z[i] - 1;
    }
  }
  return z;
}

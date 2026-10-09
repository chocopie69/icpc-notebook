/**
 * Author: chilli
 * License: CC0
 * Description: z[i] is the common-prefix length of the string and its suffix starting at i; z[0]=0. For
 * matching use pattern+separator+text, with a separator absent from both, and look for
 * z[i]>=pattern.size(). If no separator symbol is available, use KMP; handle empty-pattern
 * matching explicitly (all starts 0..text.size()).
 * Usage: auto z=zFunction("abacaba"); // {0,0,1,0,3,0,1}
 * Time: $O(N)$ time and memory.
 */
#pragma once
vector<int> zFunction(const string &text) {
  int n = sz(text);
  vector<int> z(n, 0);
  int left = 0;
  int right = -1;
  for (int i = 1; i < n; i++) {
    // [l,r] is the rightmost segment known to match a prefix of s.
    if (i <= right) z[i] = min(right - i + 1, z[i - left]);
    while (i + z[i] < n && text[z[i]] == text[i + z[i]]) z[i]++;
    if (i + z[i] - 1 > right) {
      left = i;
      right = i + z[i] - 1;
    }
  }
  return z;
}

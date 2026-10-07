/**
 * Author: Johan Sannemo
 * Date: 2016-12-15
 * License: CC0
 * Description: prefixFunction[i] is the longest proper prefix matching a suffix of s[0..i].
 * kmpSearch returns 0-based start positions of all matches, including overlaps.
 * Empty pattern matches all positions 0..text.size(). Works without a separator character.
 * Usage: vector<int> positions = kmpSearch("ababa", "aba"); // {0, 2}
 * Time: $O(|text|+|pattern|)$ time; $O(|pattern|)$ auxiliary memory.
 */
#pragma once
vector<int> prefixFunction(const string &s) {
  int n = sz(s);
  vector<int> prefix(n, 0);
  for (int i = 1; i < n; i++) {
    int matched = prefix[i - 1];
    // Fall back to the next shorter prefix until the new character fits.
    while (matched > 0 && s[i] != s[matched]) matched = prefix[matched - 1];
    if (s[i] == s[matched]) matched++;
    prefix[i] = matched;
  }
  return prefix;
}
vector<int> kmpSearch(const string &text, const string &pattern) {
  vector<int> positions;
  int m = sz(pattern);
  if (m == 0) {
    for (int i = 0; i <= sz(text); i++) positions.push_back(i);
    return positions;
  }
  vector<int> prefix = prefixFunction(pattern);
  int matched = 0;
  for (int i = 0; i < sz(text); i++) {
    while (matched > 0 && text[i] != pattern[matched]) matched = prefix[matched - 1];
    if (text[i] == pattern[matched]) matched++;
    if (matched == m) {
      positions.push_back(i - m + 1);
      // Keep the longest border so overlapping matches are found.
      matched = prefix[matched - 1];
    }
  }
  return positions;
}

/**
 * Author: Personal Code::Blocks abbreviation, adapted
 * Date: 2016-12-15
 * License: CC0
 * Description: kmpSearch(text,pattern) returns all 0-based match starts, including overlaps. Empty pattern
 * matches positions 0..text.size(); no separator is needed. pi[i] from prefixFunction is the longest
 * proper border of text[0..i].
 * Usage: auto positions=kmpSearch("ababa","aba"); // {0,2}
 * auto pi=prefixFunction("abab"); // {0,0,1,2}
 * Time: $O(|text|+|pattern|)$ time; $O(|pattern|)$ auxiliary memory.
 */
#pragma once
vector<int> prefixFunction(const string &text) {
  int n = sz(text);
  vector<int> pi(n);
  for (int i = 1; i < n; i++) {
    int j = pi[i - 1];
    while (j > 0 && text[i] != text[j]) j = pi[j - 1];
    if (text[i] == text[j]) j++;
    pi[i] = j;
  }
  return pi;
}
vector<int> kmpSearch(const string &text, const string &pattern) {
  vector<int> positions;
  int patternLength = sz(pattern);
  if (patternLength == 0) {
    for (int i = 0; i <= sz(text); i++) positions.push_back(i);
    return positions;
  }
  vector<int> prefix = prefixFunction(pattern);
  int matched = 0;
  for (int i = 0; i < sz(text); i++) {
    while (matched > 0 && text[i] != pattern[matched]) matched = prefix[matched - 1];
    if (text[i] == pattern[matched]) matched++;
    if (matched == patternLength) {
      positions.push_back(i - patternLength + 1);
      // Keep the longest border so overlapping matches are found.
      matched = prefix[matched - 1];
    }
  }
  return positions;
}

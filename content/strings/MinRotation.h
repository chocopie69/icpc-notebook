/**
 * Author: Stjepan Glavina
 * License: Unlicense
 * Source: https://github.com/stjepang/snippets/blob/master/min_rotation.cpp
 * Description: Returns the 0-based start of a lexicographically smallest cyclic rotation, not the rotated
 * string. Periodic input may have equivalent starts; empty input returns 0.
 * Time: O(N)
 * Usage: string s="baca"; int start=minRotation(s);
 * rotate(s.begin(),s.begin()+start,s.end()); // "abac"
 * Status: Stress-tested
 */
#pragma once
int minRotation(string s) {
  int bestStart = 0, n = sz(s);
  s += s;
  for (int candidate = 0; candidate < (n); ++candidate)
    for (int offset = 0; offset < (n); ++offset) {
      if (bestStart + offset == candidate || s[bestStart + offset] < s[candidate + offset]) {
        candidate += max(0, offset - 1);
        break;
      }
      if (s[bestStart + offset] > s[candidate + offset]) {
        bestStart = candidate;
        break;
      }
    }
  return bestStart;
}

/**
 * Author: Simon Lindholm
 * Date: 2018-07-06
 * License: CC0
 * Description: Maps a permutation of 0..n-1 to a unique ID in [0,n!), without preserving lexicographic order.
 * The return type is int; use n<=12.
 * Time: O(n)
 * Usage: vector<int> p={2,0,1}; int state=permToInt(p);
 */
#pragma once
int permToInt(vector<int> &permutation) {
  int usedMask = 0, i = 0, rank = 0;
  for (int value : permutation)
    rank = rank * ++i + __builtin_popcount(usedMask & -(1 << value)),
    usedMask |= 1 << value; // (note: minus, not ~!)
  return rank;
}

/**
 * Author: Simon Lindholm
 * Date: 2015-05-12
 * License: CC0
 * Source: own work
 * Description: Returns the smallest maximizing integer index on inclusive [lo,hi]. Require a unimodal
 * function that rises strictly before its maximum plateau, then never rises again. To minimize,
 * reverse both comparisons marked (A) and (B).
 * Usage: int best=ternSearch(0,10,[](int i) { return -(i-4)*(i-4); });
 * // best=4
 * Time: O(\log(b-a))
 * Status: tested
 */
#pragma once
template <class F> int ternSearch(int lo, int hi, F valueAt) {
  assert(lo <= hi);
  while (hi - lo >= 5) {
    int mid = (lo + hi) / 2;
    if (valueAt(mid) < valueAt(mid + 1))
      lo = mid; // (A)
    else
      hi = mid + 1;
  }
  for (int i = lo + 1; i < (hi + 1); ++i)
    if (valueAt(lo) < valueAt(i)) lo = i; // (B)
  return lo;
}

/**
 * Author: Simon Lindholm
 * Date: 2015-05-12
 * License: CC0
 * Source: own work
 * Description: Integer version returns the smallest maximizing index on inclusive [lo,hi]. Require
 * a function that rises strictly before its maximum plateau, then never rises again.
 * Double version returns an approximate maximizing position; require a continuous function
 * strictly increasing before its maximum plateau and strictly decreasing after it.
 * After 100 iterations, interval width is $(hi-lo)(2/3)^{100}$, subject to floating-point rounding.
 * To minimize, reverse (A) and (B) for integers, or (C) for doubles. Use double bounds
 * to select the double version; evaluate valueAt at the returned position to get the value.
 * Usage: int best=ternSearch(0,10,[](int i) { return -(i-4)*(i-4); });
 * // best=4
 * double x=ternSearch(0.0,10.0,[](double x) { return -(x-4.2)*(x-4.2); });
 * // x is approximately 4.2
 * Time: Integers: O(\log(hi-lo+1)); doubles: 100 iterations (200 evaluations).
 * Status: tested
 */
#pragma once
template <class F> int ternSearch(int lo, int hi, F valueAt) {
  assert(lo <= hi);
  while ((ll)hi - lo >= 5) {
    int mid = (int)((ll)lo + ((ll)hi - lo) / 2);
    if (valueAt(mid) < valueAt(mid + 1))
      lo = mid; // (A)
    else
      hi = mid + 1;
  }
  for (int i = lo; i < hi;) {
    ++i;
    if (valueAt(lo) < valueAt(i)) lo = i; // (B)
  }
  return lo;
}
template <class F> double ternSearch(double lo, double hi, F valueAt) {
  assert(lo <= hi);
  for (int i = 0; i < 100; i++) {
    double x1 = lo + (hi - lo) / 3, x2 = hi - (hi - lo) / 3;
    if (valueAt(x1) > valueAt(x2))
      hi = x2; // (C)
    else
      lo = x1;
  }
  return lo + (hi - lo) / 2;
}

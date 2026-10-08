/**
 * Author: Simon Lindholm
 * Date: 2015-03-20
 * License: CC0
 * Source: me
 * Description: Split a monotone function on [from, to) into a minimal set of half-open intervals on which it has the same value.
 *  Runs a callback g for each such interval.
 * Use when evaluating a monotone integer-indexed function is expensive and it changes value only
 * a few times. visitInterval receives (lo,hi,value) for each maximal [lo,hi).
 * Increasing/decreasing functions both work. A value must not disappear then return, or equal
 * endpoints can hide changes. valueAt must be deterministic.
 * Usage: constantIntervals(0,10,[](int i) { return i/3; },
 *   [](int lo,int hi,int value) { ... });
 * Time: O(k\log\frac{n}{k})
 * Status: tested
 */
#pragma once
template <class F, class G, class T>
void rec(int from, int to, F &valueAt, G &visitInterval, int &intervalStart, T &currentValue,
         T endValue) {
  if (currentValue == endValue) return;
  if (from == to) {
    visitInterval(intervalStart, to, currentValue);
    intervalStart = to;
    currentValue = endValue;
  } else {
    int mid = (from + to) >> 1;
    rec(from, mid, valueAt, visitInterval, intervalStart, currentValue, valueAt(mid));
    rec(mid + 1, to, valueAt, visitInterval, intervalStart, currentValue, endValue);
  }
}
template <class F, class G> void constantIntervals(int from, int to, F valueAt, G visitInterval) {
  if (to <= from) return;
  int intervalStart = from;
  auto currentValue = valueAt(intervalStart), endValue = valueAt(to - 1);
  rec(from, to - 1, valueAt, visitInterval, intervalStart, currentValue, endValue);
  visitInterval(intervalStart, to, endValue);
}

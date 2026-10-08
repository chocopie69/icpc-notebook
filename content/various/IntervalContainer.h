/**
 * Author: Simon Lindholm
 * License: CC0
 * Description: Add and remove intervals from a set of disjoint intervals.
 * Will merge the added interval with any overlapping intervals in the set when adding.
 * Intervals are [inclusive, exclusive).
 * Maintain covered integer-coordinate ranges rather than individual points. Touching intervals
 * merge too: [1,3) and [3,5) become [1,5). removeInterval can split an interval. Use l<=r; empty
 * intervals have no effect. A call touching k stored intervals costs O(log N+k), because those
 * intervals must be erased.
 * Time: $O(\log N)$ amortized; $O(\log N+k)$ for a call erasing k intervals.
 * Status: stress-tested
 * Usage: set<pii> intervals; addInterval(intervals,1,5);
 * removeInterval(intervals,2,4); // {[1,2),[4,5)}
 */
#pragma once
set<pii>::iterator addInterval(set<pii> &intervals, int l, int r) {
  if (l == r) return intervals.end();
  auto it = intervals.lower_bound({l, r}), hint = it;
  while (it != intervals.end() && it->first <= r) {
    r = max(r, it->second);
    hint = it = intervals.erase(it);
  }
  if (it != intervals.begin() && (--it)->second >= l) {
    l = min(l, it->first);
    r = max(r, it->second);
    intervals.erase(it);
  }
  return intervals.insert(hint, {l, r});
}
void removeInterval(set<pii> &intervals, int l, int r) {
  if (l == r) return;
  auto it = addInterval(intervals, l, r);
  auto oldRight = it->second;
  if (it->first == l)
    intervals.erase(it);
  else
    (int &)it->second = l;
  if (r != oldRight) intervals.emplace(r, oldRight);
}

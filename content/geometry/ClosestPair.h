/**
 * Author: Simon Lindholm
 * Date: 2019-04-17
 * License: CC0
 * Source: https://codeforces.com/blog/entry/58747
 * Description: Finds the closest pair of points.
 * Input must contain at least two points. Returns the endpoints rather than their distance; it
 * copies and sorts the input internally. Duplicate points give distance zero. Integer squared
 * distances must fit ll.
 * Time: O(n \log n)
 * Status: stress-tested
 * Usage: auto [a,b]=closest(points);
 * ll distance2=(a-b).dist2();
 */
#pragma once

#include "Point.h"

typedef Point<ll> P;
pair<P, P> closest(vector<P> points) {
  assert(sz(points) > 1);
  set<P> active;
  sort(all(points), [](P a, P b) { return a.y < b.y; });
  pair<ll, pair<P, P>> best{LLONG_MAX, {P(), P()}};
  int j = 0;
  for (P p : points) {
    P window{1 + (ll)sqrt(best.first), 0};
    while (points[j].y <= p.y - window.x) active.erase(points[j++]);
    auto lo = active.lower_bound(p - window), hi = active.upper_bound(p + window);
    for (; lo != hi; ++lo) best = min(best, {(*lo - p).dist2(), {*lo, p}});
    active.insert(p);
  }
  return best.second;
}

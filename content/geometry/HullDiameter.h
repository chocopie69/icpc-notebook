/**
 * Author: Oleksandr Bacherikov, chilli
 * Date: 2019-05-05
 * License: Boost Software License
 * Source: https://codeforces.com/blog/entry/48868
 * Description: Returns the two points with max distance on a convex hull (ccw,
 * no duplicate/collinear points).
 * Use rotating calipers after convexHull. The hull must be nonempty; a single point returns that
 * point twice. Returns endpoints, so compute dist2 of their difference for an exact squared
 * diameter. Do not pass an unordered point cloud.
 * Status: stress-tested, tested on kattis:roberthood
 * Time: O(n)
 * Usage: auto hull=convexHull(points); auto ends=hullDiameter(hull);
 * ll distance2=(ends[0]-ends[1]).dist2();
 */
#pragma once
#include "Point.h"

typedef Point<ll> P;
array<P, 2> hullDiameter(vector<P> hull) {
  int n = sz(hull), j = n < 2 ? 0 : 1;
  pair<ll, array<P, 2>> best({0, {hull[0], hull[0]}});
  for (int i = 0; i < (j); ++i)
    for (;; j = (j + 1) % n) {
      best = max(best, {(hull[i] - hull[j]).dist2(), {hull[i], hull[j]}});
      if ((hull[(j + 1) % n] - hull[j]).cross(hull[i + 1] - hull[i]) >= 0) break;
    }
  return best.second;
}

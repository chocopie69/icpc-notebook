/**
 * Author: Victor Lecomte, chilli
 * Date: 2019-04-26
 * License: CC0
 * Source: https://vlecomte.github.io/cp-geo.pdf
 * Description: Returns true if p lies within the polygon. If strict is true,
 * it returns false for points on the boundary. The algorithm uses
 * products in intermediate steps so watch out for overflow.
 * Works for a simple, possibly concave polygon in either orientation; do not repeat the first
 * vertex at the end. strict=true excludes the boundary. Use integer coordinates for exact
 * boundary decisions, or adapt the on-segment check to a tolerance.
 * Time: O(n)
 * Usage: vector<Point<ll>> polygon={{0,0},{4,0},{0,4}};
 * bool inside=inPolygon(polygon,Point<ll>(1,1));
 * Status: stress-tested and tested on kattis:pointinpolygon
 */
#pragma once

#include "Point.h"
#include "OnSegment.h"
#include "SegmentDistance.h"
template <class P> bool inPolygon(vector<P> &polygon, P point, bool strict = true) {
  int inside = 0, n = sz(polygon);
  for (int i = 0; i < (n); ++i) {
    P nextPoint = polygon[(i + 1) % n];
    if (onSegment(polygon[i], nextPoint, point)) return !strict;
    //or: if (segDist(p[i], q, a) <= eps) return !strict;
    inside ^=
        ((point.y < polygon[i].y) - (point.y < nextPoint.y)) * point.cross(polygon[i], nextPoint) >
        0;
  }
  return inside;
}

/**
 * Author: Oleksandr Bacherikov, chilli
 * Date: 2019-05-07
 * License: Boost Software License
 * Source: https://github.com/AlCash07/ACTL/blob/master/include/actl/geometry/algorithm/intersect/line_convex_polygon.hpp
 * Description: Line-convex polygon intersection. The polygon must be ccw and have no collinear points.
 * lineHull(line, poly) returns a pair describing the intersection of a line with the polygon:
 *  \begin{itemize*}
 *    \item $(-1, -1)$ if no collision,
 *    \item $(i, -1)$ if touching the corner $i$,
 *    \item $(i, i)$ if along side $(i, i+1)$,
 *    \item $(i, j)$ if crossing sides $(i, i+1)$ and $(j, j+1)$.
 *  \end{itemize*}
 *  In the last case, if a corner $i$ is crossed, this is treated as happening on side $(i, i+1)$.
 *  The points are returned in the same order as the line hits the polygon.
 * \texttt{extrVertex} returns the index of the hull point with maximum projection onto a direction.
 * Use a nondegenerate infinite line and a strictly convex counterclockwise hull with at least
 * three vertices. Results are edge/vertex indices, not coordinates; wrap i+1 modulo hull.size().
 * Intersect reported sides with the line to get coordinates. extrVertex returns the index
 * maximizing dot(direction,point); direction must be nonzero. Hulls of size <3 need
 * point/segment intersection checks instead.
 * Time: O(\log n)
 * Status: stress-tested
 * Usage: auto hit=lineHull(Point<ll>(0,0),Point<ll>(1,0),hull);
 * int rightmost=extrVertex(hull,Point<ll>(1,0));
 */
#pragma once

#include "Point.h"

#define cmp(i, j) sgn(direction.perp().cross(hull[(i)%n]-hull[(j)%n]))
#define extr(i) cmp(i + 1, i) >= 0 && cmp(i, i - 1 + n) < 0
template <class P> int extrVertex(vector<P> &hull, P direction) {
  int n = sz(hull), lo = 0, hi = n;
  if (extr(0)) return 0;
  while (lo + 1 < hi) {
    int mid = (lo + hi) / 2;
    if (extr(mid)) return mid;
    int loTrend = cmp(lo + 1, lo), midTrend = cmp(mid + 1, mid);
    (loTrend < midTrend || (loTrend == midTrend && loTrend == cmp(lo, mid)) ? hi : lo) = mid;
  }
  return lo;
}
#define cmpL(i) sgn(a.cross(hull[i], b))
template <class P> array<int, 2> lineHull(P a, P b, vector<P> &hull) {
  int maxVertex = extrVertex(hull, (a - b).perp());
  int minVertex = extrVertex(hull, (b - a).perp());
  if (cmpL(maxVertex) < 0 || cmpL(minVertex) > 0) return {-1, -1};
  array<int, 2> intersections;
  for (int i = 0; i < (2); ++i) {
    int lo = minVertex, hi = maxVertex, n = sz(hull);
    while ((lo + 1) % n != hi) {
      int mid = ((lo + hi + (lo < hi ? 0 : n)) / 2) % n;
      (cmpL(mid) == cmpL(minVertex) ? lo : hi) = mid;
    }
    intersections[i] = (lo + !cmpL(hi)) % n;
    swap(maxVertex, minVertex);
  }
  if (intersections[0] == intersections[1]) return {intersections[0], -1};
  if (!cmpL(intersections[0]) && !cmpL(intersections[1]))
    switch ((intersections[0] - intersections[1] + sz(hull) + 1) % sz(hull)) {
    case 0:
      return {intersections[0], intersections[0]};
    case 2:
      return {intersections[1], intersections[1]};
    }
  return intersections;
}

/**
 * Author: chilli
 * Date: 2019-05-17
 * License: CC0
 * Source: https://github.com/ngthanhtrung23/ACM_Notebook_new
 * Description: Determine whether a point t lies inside a convex hull (CCW
 * order, with no collinear points). Returns true if point lies within
 * the hull. If strict is true, points on the boundary aren't included.
 * The hull must be nonempty, convex, and in boundary order, without interior collinear vertices;
 * convexHull produces suitable input. Use for many containment queries rather than scanning
 * every edge. strict=false includes edges and vertices; hulls of size 1/2 work.
 * Return false before calling for an empty hull.
 * Usage: auto hull=convexHull(points);
 * bool inside=inHull(hull,Point<ll>(2,3),false);
 * Status: stress-tested
 * Time: O(\log N)
 */
#pragma once

#include "Point.h"
#include "sideOf.h"
#include "OnSegment.h"

typedef Point<ll> P;
bool inHull(const vector<P> &hull, P p, bool strict = true) {
  int lo = 1, hi = sz(hull) - 1, boundaryAllowed = !strict;
  if (sz(hull) < 3) return boundaryAllowed && onSegment(hull[0], hull.back(), p);
  if (sideOf(hull[0], hull[lo], hull[hi]) > 0) swap(lo, hi);
  if (sideOf(hull[0], hull[lo], p) >= boundaryAllowed ||
      sideOf(hull[0], hull[hi], p) <= -boundaryAllowed)
    return false;
  while (abs(lo - hi) > 1) {
    int mid = (lo + hi) / 2;
    (sideOf(hull[0], hull[mid], p) > 0 ? hi : lo) = mid;
  }
  return sgn(hull[lo].cross(hull[hi], p)) < boundaryAllowed;
}

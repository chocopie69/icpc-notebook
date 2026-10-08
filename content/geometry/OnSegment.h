/**
 * Author: Victor Lecomte, chilli
 * Date: 2019-04-26
 * License: CC0
 * Source: https://vlecomte.github.io/cp-geo.pdf
 * Description: Exact membership on a closed segment, including endpoints and zero-length segments. Prefer
 * integer coordinates; for Point<double> compare segDist with a tolerance.
 * Status:
 * Usage: bool on=onSegment(Point<ll>(0,0),Point<ll>(2,0),
 *   Point<ll>(1,0)); // true
 */
#pragma once

#include "Point.h"
template <class P> bool onSegment(P start, P finish, P p) {
  return p.cross(start, finish) == 0 && (start - p).dot(finish - p) <= 0;
}

/**
 * Author: Ulf Lundstrom
 * Date: 2009-03-21
 * License: CC0
 * Source:
 * Description: Returns +1/0/-1 for p left/on/right of start->finish. The eps overload treats distance<=eps as
 * on the line and requires distinct endpoints. Products must fit the coordinate type.
 * Usage: int side=sideOf(Point<ll>(0,0),Point<ll>(2,0),
 *   Point<ll>(1,3)); // +1: left
 * Status: tested
 */
#pragma once

#include "Point.h"
template <class P> int sideOf(P start, P finish, P p) { return sgn(start.cross(finish, p)); }
template <class P> int sideOf(P start, P finish, P p, double eps) {
  auto crossValue = (finish - start).cross(p - start);
  double tolerance = (finish - start).dist() * eps;
  return (crossValue > tolerance) - (crossValue < -tolerance);
}

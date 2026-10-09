/**
 * Author: Simon Lindholm
 * Date: 2015-09-01
 * License: CC0
 * Description: Computes the pair of points at which two circles intersect.
 * Returns false in case of no intersection.
 * On success the pair contains both intersections; at tangency they are equal. Coincident
 * circles have infinitely many intersections and trigger an assertion, so handle that case
 * before calling. Radii must be nonnegative; near tangency needs tolerant separation tests.
 * Status: stress-tested
 * Usage: pair<P,P> points;
 * bool intersects=circleInter(P(0,0),P(2,0),2,2, &points);
 */
#pragma once

#include "Point.h"

typedef Point<double> P;
bool circleInter(P center1, P center2, double r1, double r2, pair<P, P> *intersections) {
  if (center1 == center2) {
    assert(r1 != r2);
    return false;
  }
  P centerDir = center2 - center1;
  double distance2 = centerDir.dist2(), radiusSum = r1 + r2, radiusDiff = r1 - r2,
         projection = (distance2 + r1 * r1 - r2 * r2) / (distance2 * 2),
         height2 = r1 * r1 - projection * projection * distance2;
  if (radiusSum * radiusSum < distance2 || radiusDiff * radiusDiff > distance2) return false;
  P basePoint = center1 + centerDir * projection,
    offset = centerDir.perp() * sqrt(fmax(0, height2) / distance2);
  *intersections = {basePoint + offset, basePoint - offset};
  return true;
}

/**
 * Author: chilli, Takanori MAEHARA
 * Date: 2019-10-31
 * License: CC0
 * Source: https://github.com/spaghetti-source/algorithm/blob/master/geometry/_geom.cc#L744
 * Description: Returns the area of the intersection of a circle with a
 * ccw polygon.
 * The polygon may be concave, but must be simple with nonzero-length edges. It is copied and
 * left unchanged. The area is signed: counterclockwise input gives positive area; take abs if
 * needed. Radius must be positive.
 * Time: O(n)
 * Status: Tested on GNYR 2019 Gerrymandering, stress-tested
 * Usage: double area=abs(circlePoly(P(0,0),1,polygon));
 */
#pragma once

#include "../../content/geometry/Point.h"

typedef Point<double> P;
#define arg(p, q) atan2(p.cross(q), p.dot(q))
double circlePoly(P center, double radius, vector<P> polygon) {
  auto triangleArea = [&](P p, P q) {
    auto halfRadius2 = radius * radius / 2;
    P direction = q - p;
    auto linearTerm = direction.dot(p) / direction.dist2(),
         constantTerm = (p.dist2() - radius * radius) / direction.dist2();
    auto discriminant = linearTerm * linearTerm - constantTerm;
    if (discriminant <= 0) return arg(p, q) * halfRadius2;
    auto enter = max(0., -linearTerm - sqrt(discriminant)),
         exit = min(1., -linearTerm + sqrt(discriminant));
    if (exit < 0 || 1 <= enter) return arg(p, q) * halfRadius2;
    P intersection1 = p + direction * enter, intersection2 = q + direction * (exit - 1);
    return arg(p, intersection1) * halfRadius2 + intersection1.cross(intersection2) / 2 +
           arg(intersection2, q) * halfRadius2;
  };
  auto area = 0.0;
  for (int i = 0; i < (sz(polygon)); ++i)
    area += triangleArea(polygon[i] - center, polygon[(i + 1) % sz(polygon)] - center);
  return area;
}

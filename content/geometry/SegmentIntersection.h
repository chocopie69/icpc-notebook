/**
 * Author: Victor Lecomte, chilli
 * Date: 2019-04-27
 * License: CC0
 * Source: https://vlecomte.github.io/cp-geo.pdf
 * Description: \\
 * \begin{minipage}{75mm}
 * If a unique intersection point between the line segments going from s1 to e1 and from s2 to e2 exists then it is returned.
 * If no intersection point exists an empty vector is returned.
 * If infinitely many exist a vector with 2 elements is returned, containing the endpoints of the common line segment.
 * The wrong position will be returned if P is Point<ll> and the intersection point does not have integer coordinates.
 * Products of three coordinates are used in intermediate steps so watch out for overflow if using int or long long.
 * \end{minipage}
 * \begin{minipage}{15mm}
 * \includegraphics[width=\textwidth]{content/geometry/SegmentIntersection}
 * \end{minipage}
 * Endpoints are included. The returned vector has size 0, 1 or 2 for disjoint segments, one
 * intersection, or an overlapping segment. Use Point<double> for fractional coordinates; exact
 * boundary checks may need a tolerance for noisy real input.
 * Usage: auto intersection=segInter(Point<double>(0,0),
 *   Point<double>(2,2),Point<double>(0,2),Point<double>(2,0));
 * // intersection[0] is (1,1).
 * Status: stress-tested, tested on kattis:intersection
 */
#pragma once

#include "Point.h"
#include "OnSegment.h"
template <class P> vector<P> segInter(P a, P b, P c, P d) {
  auto sideA = c.cross(d, a), sideB = c.cross(d, b), sideC = a.cross(b, c), sideD = a.cross(b, d);
  // Checks if intersection is single non-endpoint point.
  if (sgn(sideA) * sgn(sideB) < 0 && sgn(sideC) * sgn(sideD) < 0)
    return {(a * sideB - b * sideA) / (sideB - sideA)};
  set<P> intersections;
  if (onSegment(c, d, a)) intersections.insert(a);
  if (onSegment(c, d, b)) intersections.insert(b);
  if (onSegment(a, b, c)) intersections.insert(c);
  if (onSegment(a, b, d)) intersections.insert(d);
  return {all(intersections)};
}

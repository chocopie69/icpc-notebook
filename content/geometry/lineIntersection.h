/**
 * Author: Victor Lecomte, chilli
 * Date: 2019-05-05
 * License: CC0
 * Source: https://vlecomte.github.io/cp-geo.pdf
 * Description: \\
 * \begin{minipage}{75mm}
 * If a unique intersection point of the lines going through s1,e1 and s2,e2 exists \{1, point\} is returned.
 * If no intersection point exists \{0, (0,0)\} is returned and if infinitely many exists \{-1, (0,0)\} is returned.
 * The wrong position will be returned if P is Point<ll> and the intersection point does not have integer coordinates.
 * Products of three coordinates are used in intermediate steps so watch out for overflow if using int or ll.
 * \end{minipage}
 * \begin{minipage}{15mm}
 * \includegraphics[width=\textwidth]{content/geometry/lineIntersection}
 * \end{minipage}
 * These are infinite lines, not bounded segments; each defining pair must contain distinct
 * points. Inspect the status before reading the point. Use Point<double> for fractional
 * coordinates; integer Point division truncates.
 * Usage: auto [status,p]=lineInter(Point<double>(0,0),
 *   Point<double>(2,2),Point<double>(0,2),Point<double>(2,0));
 * // status: 1 unique, 0 parallel, -1 coincident.
 * Status: stress-tested, and tested through half-plane tests
 */
#pragma once

#include "Point.h"
template <class P> pair<int, P> lineInter(P start1, P end1, P start2, P end2) {
  auto crossDir = (end1 - start1).cross(end2 - start2);
  if (crossDir == 0) // if parallel
    return {-(start1.cross(end1, start2) == 0), P(0, 0)};
  auto weightStart = start2.cross(end1, end2), weightEnd = start2.cross(end2, start1);
  return {1, (start1 * weightStart + end1 * weightEnd) / crossDir};
}

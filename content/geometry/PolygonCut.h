/**
 * Author: Ulf Lundstrom
 * Date: 2009-03-21
 * License: CC0
 * Source:
 * Description: \\
 * \begin{minipage}{75mm}
 *  Returns a vector with the vertices of a polygon with everything to the left of the line going from s to e cut away.
 * \end{minipage}
 * \begin{minipage}{15mm}
 * \vspace{-6mm}
 * \includegraphics[width=\textwidth]{content/geometry/PolygonCut}
 * \end{minipage}
 * Use a convex polygon when a single output polygon is required. The implementation keeps the
 * strictly right side of start->finish, discarding points exactly on the line; it inserts
 * crossing points. The cutting line must have distinct endpoints. The result may be empty.
 * To retain boundary-only pieces, use <=0 in both side tests; reverse the line to keep the left.
 * Usage: auto clipped=polygonCut(polygon,P(0,0),P(1,0));
 * // Keep y<0 plus crossing points.
 * Status: tested but not extensively
 */
#pragma once

#include "Point.h"

typedef Point<double> P;
vector<P> polygonCut(const vector<P> &polygon, P start, P finish) {
  vector<P> clipped;
  for (int i = 0; i < (sz(polygon)); ++i) {
    P cur = polygon[i], prev = i ? polygon[i - 1] : polygon.back();
    auto sideCurrent = start.cross(finish, cur), sidePrevious = start.cross(finish, prev);
    if ((sideCurrent < 0) != (sidePrevious < 0))
      clipped.push_back(cur + (prev - cur) * (sideCurrent / (sideCurrent - sidePrevious)));
    if (sideCurrent < 0) clipped.push_back(cur);
  }
  return clipped;
}

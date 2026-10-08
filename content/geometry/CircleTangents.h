/**
 * Author: Victor Lecomte, chilli
 * Date: 2019-10-31
 * License: CC0
 * Source: https://vlecomte.github.io/cp-geo.pdf
 * Description: Finds the external tangents of two circles, or internal if r2 is negated.
 * Can return 0, 1, or 2 tangents -- 0 if one circle contains the other (or overlaps it, in the internal case, or if the circles are the same);
 * 1 if the circles are tangent to each other (in which case .first = .second and the tangent line is perpendicular to the line between the centers).
 * .first and .second give the tangency points at circle 1 and 2 respectively.
 * To find the tangents of a circle with a point set r2 to 0.
 * Each returned pair is a tangent segment joining the two tangency points. Use Point<double>;
 * negating the second radius requests internal tangents rather than a physically negative
 * radius. Coincident centers return no tangents.
 * Status: tested
 * Usage: auto external=tangents(Point<double>(0,0),1,
 *   Point<double>(4,0),1); // two tangent pairs
 */
#pragma once

#include "Point.h"
template <class P> vector<pair<P, P>> tangents(P c1, double r1, P c2, double r2) {
  P centerDir = c2 - c1;
  double radiusDiff = r1 - r2, distance2 = centerDir.dist2(),
         height2 = distance2 - radiusDiff * radiusDiff;
  if (distance2 == 0 || height2 < 0) return {};
  vector<pair<P, P>> tangentPairs;
  for (double sign : {-1, 1}) {
    P normal = (centerDir * radiusDiff + centerDir.perp() * sqrt(height2) * sign) / distance2;
    tangentPairs.push_back({c1 + normal * r1, c2 + normal * r2});
  }
  if (height2 == 0) tangentPairs.pop_back();
  return tangentPairs;
}

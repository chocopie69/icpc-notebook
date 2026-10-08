/**
 * Author: Ulf Lundstrom
 * Date: 2009-03-21
 * License: CC0
 * Source: tinyKACTL
 * Description: Returns twice the signed area: positive CCW, negative clockwise. Use ordered boundary
 * vertices, at least one point, and no repeated final vertex. Geometric area is abs(area2)/2.0;
 * cross-product sums must fit T.
 * Status: Stress-tested and tested on kattis:polygonarea
 * Usage: vector<Point<ll>> p={{0,0},{4,0},{0,3}};
 * double area=abs(polygonArea2(p))/2.0; // 6
 */
#pragma once

#include "Point.h"
template <class T> T polygonArea2(vector<Point<T>> &polygon) {
  T area2 = polygon.back().cross(polygon[0]);
  for (int i = 0; i < (sz(polygon) - 1); ++i) area2 += polygon[i].cross(polygon[i + 1]);
  return area2;
}

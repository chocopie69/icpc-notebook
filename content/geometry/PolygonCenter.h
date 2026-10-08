/**
 * Author: Ulf Lundstrom
 * Date: 2009-04-08
 * License: CC0
 * Source:
 * Description: Area centroid of a simple polygon with ordered boundary vertices and nonzero area; either
 * orientation works. Zero-area input divides by zero.
 * Time: O(n)
 * Status: Tested
 * Usage: vector<P> p={{0,0},{3,0},{0,3}};
 * P center=polygonCenter(p); // (1,1)
 */
#pragma once

#include "Point.h"

typedef Point<double> P;
P polygonCenter(const vector<P> &polygon) {
  P weightedCenter(0, 0);
  double area2 = 0;
  for (int i = 0, j = sz(polygon) - 1; i < sz(polygon); j = i++) {
    weightedCenter = weightedCenter + (polygon[i] + polygon[j]) * polygon[j].cross(polygon[i]);
    area2 += polygon[j].cross(polygon[i]);
  }
  return weightedCenter / area2 / 3;
}

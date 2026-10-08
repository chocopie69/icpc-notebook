/**
 * Author: Andrew He, chilli
 * Date: 2019-05-07
 * License: CC0
 * Source: folklore
 * Description: Computes the minimum circle that encloses a set of points.
 * Input must contain at least one point. Returns (center,radius), not radius squared. Random
 * shuffling makes incremental construction fast on average, and the input is copied. Uses
 * floating tolerance to decide whether a point lies outside.
 * Time: expected O(n)
 * Status: stress-tested
 * Usage: auto [center,radius]=mec(vector<P>{P(0,0),P(2,0)});
 * // center=(1,0), radius=1.
 */
#pragma once

#include "circumcircle.h"
pair<P, double> mec(vector<P> points) {
  shuffle(all(points), mt19937(time(0)));
  P center = points[0];
  double radius = 0, tolerance = 1 + 1e-8;
  for (int i = 0; i < (sz(points)); ++i)
    if ((center - points[i]).dist() > radius * tolerance) {
      center = points[i], radius = 0;
      for (int j = 0; j < (i); ++j)
        if ((center - points[j]).dist() > radius * tolerance) {
          center = (points[i] + points[j]) / 2;
          radius = (center - points[i]).dist();
          for (int k = 0; k < (j); ++k)
            if ((center - points[k]).dist() > radius * tolerance) {
              center = ccCenter(points[i], points[j], points[k]);
              radius = (center - points[i]).dist();
            }
        }
    }
  return {center, radius};
}

/**
 * Author: Per Austrin
 * Date: 2004-02-08
 * License: CC0
 * Description: Finds the real roots to a polynomial.
 * Uses derivative roots to split the line into monotone pieces, then bisects sign changes. Use a
 * nonconstant polynomial with nonzero leading coefficient and coefficients in increasing degree
 * order. Choose bounds covering the roots of interest; this implementation may also return
 * candidates outside those bounds. Repeated roots without a sign change are not guaranteed and
 * need separate handling.
 * Usage: auto roots=polyRoots(Poly{{2,-3,1}},-10,10);
 * // approximately {1,2}
 * Time: O(n^2 \log(1/\epsilon))
 */
#pragma once

#include "Polynomial.h"
vector<double> polyRoots(Poly poly, double minX, double maxX) {
  if (sz(poly.coeff) == 2) return {-poly.coeff[0] / poly.coeff[1]};
  vector<double> roots;
  Poly derivative = poly;
  derivative.diff();
  auto criticalPoints = polyRoots(derivative, minX, maxX);
  criticalPoints.push_back(minX - 1);
  criticalPoints.push_back(maxX + 1);
  sort(all(criticalPoints));
  for (int i = 0; i < (sz(criticalPoints) - 1); ++i) {
    double lo = criticalPoints[i], hi = criticalPoints[i + 1];
    bool positiveLeft = poly(lo) > 0;
    if (positiveLeft ^ (poly(hi) > 0)) {
      for (int it = 0; it < (60); ++it) { // while (h - l > 1e-8)
        double mid = (lo + hi) / 2, value = poly(mid);
        if ((value <= 0) ^ positiveLeft)
          lo = mid;
        else
          hi = mid;
      }
      roots.push_back((lo + hi) / 2);
    }
  }
  return roots;
}

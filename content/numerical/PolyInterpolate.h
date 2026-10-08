/**
 * Author: Simon Lindholm
 * Date: 2017-05-10
 * License: CC0
 * Source: Wikipedia
 * Description: Given $n$ points (x[i], y[i]), computes an n-1-degree polynomial $p$ that
 *  passes through them: $p(x) = a[0]*x^0 + ... + a[n-1]*x^{n-1}$.
 *  For numerical precision, pick $x[k] = c*\cos(k/(n-1)*\pi), k=0 \dots n-1$.
 * Use distinct x coordinates and n matching x/y values. Returns n coefficients in increasing
 * powers; result[0] is the constant term. Floating interpolation can be unstable for large n or
 * poorly spaced x. Use small well-scaled data, or a separate modular method for exact modular
 * answers.
 * Time: O(n^2)
 * Usage: auto coeff=interpolate({0,1,2},{1,4,9},3);
 * // approximately {1,2,1}, representing (x+1)^2
 */
#pragma once

typedef vector<double> vd;
vd interpolate(vd x, vd y, int n) {
  vd coeff(n), basis(n);
  for (int k = 0; k < (n - 1); ++k)
    for (int i = k + 1; i < (n); ++i) y[i] = (y[i] - y[k]) / (x[i] - x[k]);
  double previous = 0;
  basis[0] = 1;
  for (int k = 0; k < (n); ++k)
    for (int i = 0; i < (n); ++i) {
      coeff[i] += y[k] * basis[i];
      swap(previous, basis[i]);
      basis[i] -= previous * x[k];
    }
  return coeff;
}

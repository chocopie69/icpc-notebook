/**
 * Author: David Rydh, Per Austrin
 * Date: 2003-03-16
 * Description: Polynomial coefficients coeff[i] multiply $x^i$ (constant term first).
 * Evaluation uses Horner's rule. diff changes the polynomial to its derivative. divroot(r)
 * divides by x-r and discards the remainder, so normally call it only for a known root. Use a
 * nonempty coefficient vector and trim zero leading coefficients before root finding; do not
 * differentiate an empty polynomial.
 * Usage: Poly p{{2,-3,1}}; double value=p(3); // 2
 * p.diff(); // coefficients {-3,2}
 */
#pragma once
struct Poly {
  vector<double> coeff;
  double operator()(double x) const {
    double value = 0;
    for (int i = sz(coeff); i--;) (value *= x) += coeff[i];
    return value;
  }
  void diff() {
    for (int i = 1; i < (sz(coeff)); ++i) coeff[i - 1] = i * coeff[i];
    coeff.pop_back();
  }
  void divroot(double root) {
    double carry = coeff.back(), oldCoeff;
    coeff.back() = 0;
    for (int i = sz(coeff) - 1; i--;)
      oldCoeff = coeff[i], coeff[i] = coeff[i + 1] * root + carry, carry = oldCoeff;
    coeff.pop_back();
  }
};

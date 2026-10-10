/**
 * Author: David Rydh, Per Austrin
 * Date: 2003-03-16
 * Description: Stores a real polynomial and supports evaluation, differentiation and division
 * by a linear factor. Use for evaluating formulas, finding slopes/critical points, or removing
 * a known root before solving the remaining polynomial. Coefficients coeff[i] multiply $x^i$
 * (constant term first): {2,-3,1} means $2-3x+x^2$. p(x) returns its value using Horner's rule.
 * diff changes p to its derivative; copy p first if the original is still needed. divroot(r)
 * divides by x-r and discards the remainder, so normally call it only for a known root. Use a
 * nonempty coefficient vector; after diff, constants become empty. Trim zero leading
 * coefficients and handle constants/zero polynomials before polyRoots.
 * Time: O(d) per operation, where d is the degree; O(d) storage.
 * Usage: Poly p{{2,-3,1}}; double value=p(3); // 2
 * Poly derivative=p; derivative.diff(); // {-3,2}; derivative(3)=3
 * Poly quotient=p; quotient.divroot(1); // {-2,1}: p(x)=(x-1)(x-2)
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

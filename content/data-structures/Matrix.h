/**
 * Author: Ulf Lundstrom
 * Date: 2009-08-03
 * License: CC0
 * Source: My head
 * Description: Fixed-size square matrices, initially zero; N is a compile-time dimension. Exponent must be
 * nonnegative and $A^0$ is the identity. Multiplication has no modulus: add reduction or choose
 * a suitable scalar type, with products fitting that type.
 * Usage: Matrix<ll,2> a; a.data={{{1,1},{1,0}}};
 * array<ll,2> state={1,0};
 * auto next=(a^10)*state; // {89,55}
 * Status: tested
 */
#pragma once
template <class T, int N> struct Matrix {
  typedef Matrix M;
  array<array<T, N>, N> data{};
  M operator*(const M &other) const {
    M result;
    for (int i = 0; i < (N); ++i)
      for (int j = 0; j < (N); ++j)
        for (int k = 0; k < (N); ++k) result.data[i][k] += data[i][j] * other.data[j][k];
    return result;
  }
  array<T, N> operator*(const array<T, N> &vec) const {
    array<T, N> result{};
    for (int i = 0; i < (N); ++i)
      for (int j = 0; j < (N); ++j) result[i] += data[i][j] * vec[j];
    return result;
  }
  M operator^(ll exponent) const {
    assert(exponent >= 0);
    M result, base(*this);
    for (int i = 0; i < (N); ++i) result.data[i][i] = 1;
    while (exponent) {
      if (exponent & 1) result = result * base;
      base = base * base;
      exponent >>= 1;
    }
    return result;
  }
};

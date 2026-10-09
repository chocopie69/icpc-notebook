/**
 * Author: Unknown
 * Date: 2014-11-27
 * Source: somewhere on github
 * Description: Calculates determinant using modular arithmetics.
 * Modulos can also be removed to get a pure-integer version.
 * Set global mod and normalize entries modulo it. Euclidean row steps work with composite moduli
 * too, unlike elimination requiring inverses. Input must be square and is destroyed. Products
 * before reduction must fit ll; use wider products if needed. Result lies in [0,mod).
 * Time: $O(N^3)$
 * Status: bruteforce-tested for N <= 3, mod <= 7
 * Usage: vector<vector<ll>> a={{1,2},{3,4}};
 * ll determinant=det(a); // mod-2; a is modified
 */
#pragma once

const ll mod = 12345;
ll det(vector<vector<ll>> &matrix) {
  int n = sz(matrix);
  ll determinant = 1;
  for (int i = 0; i < (n); ++i) {
    for (int j = i + 1; j < (n); ++j) {
      while (matrix[j][i] != 0) { // gcd step
        ll quotient = matrix[i][i] / matrix[j][i];
        if (quotient)
          for (int k = i; k < (n); ++k)
            matrix[i][k] = (matrix[i][k] - matrix[j][k] * quotient) % mod;
        swap(matrix[i], matrix[j]);
        determinant *= -1;
      }
    }
    determinant = determinant * matrix[i][i] % mod;
    if (!determinant) return 0;
  }
  return (determinant + mod) % mod;
}

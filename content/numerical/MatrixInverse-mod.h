/**
 * Author: Simon Lindholm
 * Date: 2016-12-08
 * Source: The regular matrix inverse code
 * Description: Invert matrix $A$ modulo a prime.
 * Returns rank; result is stored in $A$ unless singular (rank < n).
 * For prime powers, repeatedly set $A^{-1} = A^{-1} (2I - AA^{-1})\  (\text{mod }p^k)$ where $A^{-1}$ starts as
 * the inverse of A mod p, and k is doubled in each step.
 * Time: O(n^3)
 * Status: Slightly tested
 */
#pragma once

#include "../number-theory/ModPow.h"
int matInv(vector<vector<ll>> &matrix) {
  int n = sz(matrix);
  vector<int> colOrder(n);
  vector<vector<ll>> inverse(n, vector<ll>(n));
  for (int i = 0; i < (n); ++i) inverse[i][i] = 1, colOrder[i] = i;

  for (int i = 0; i < (n); ++i) {
    int pivotRow = i, pivotCol = i;
    for (int j = i; j < (n); ++j)
      for (int k = i; k < (n); ++k)
        if (matrix[j][k]) {
          pivotRow = j;
          pivotCol = k;
          goto found;
        }
    return i;
  found:
    matrix[i].swap(matrix[pivotRow]);
    inverse[i].swap(inverse[pivotRow]);
    for (int j = 0; j < (n); ++j)
      swap(matrix[j][i], matrix[j][pivotCol]), swap(inverse[j][i], inverse[j][pivotCol]);
    swap(colOrder[i], colOrder[pivotCol]);
    ll pivotInverse = modpow(matrix[i][i], mod - 2);
    for (int j = i + 1; j < (n); ++j) {
      ll factor = matrix[j][i] * pivotInverse % mod;
      matrix[j][i] = 0;
      for (int k = i + 1; k < (n); ++k) matrix[j][k] = (matrix[j][k] - factor * matrix[i][k]) % mod;
      for (int k = 0; k < (n); ++k) inverse[j][k] = (inverse[j][k] - factor * inverse[i][k]) % mod;
    }
    for (int j = i + 1; j < (n); ++j) matrix[i][j] = matrix[i][j] * pivotInverse % mod;
    for (int j = 0; j < (n); ++j) inverse[i][j] = inverse[i][j] * pivotInverse % mod;
    matrix[i][i] = 1;
  }

  for (int i = n - 1; i > 0; --i)
    for (int j = 0; j < (i); ++j) {
      ll pivotInverse = matrix[j][i];
      for (int k = 0; k < (n); ++k)
        inverse[j][k] = (inverse[j][k] - pivotInverse * inverse[i][k]) % mod;
    }

  for (int i = 0; i < (n); ++i)
    for (int j = 0; j < (n); ++j)
      matrix[colOrder[i]][colOrder[j]] = inverse[i][j] % mod + (inverse[i][j] < 0) * mod;
  return n;
}

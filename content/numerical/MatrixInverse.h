/**
 * Author: Max Bennedich
 * Date: 2004-02-08
 * Description: Invert matrix $A$. Returns rank; result is stored in $A$ unless singular (rank < n).
 * Can easily be extended to prime moduli; for prime powers, repeatedly
 * set $A^{-1} = A^{-1} (2I - AA^{-1})\  (\text{mod }p^k)$ where $A^{-1}$ starts as
 * the inverse of A mod p, and k is doubled in each step.
 * Use a square floating matrix. Only read the overwritten matrix as the inverse when the
 * returned rank equals its dimension; otherwise it is singular and partially modified. Row and
 * column pivoting use a fixed tolerance; scale input or adjust it for extreme magnitudes.
 * Copy the original if needed afterward; modular inversion needs a separate implementation.
 * Time: O(n^3)
 * Status: Slightly tested
 * Usage: vector<vector<double>> a={{2,0},{0,4}};
 * int rank=matInv(a); // rank=2, a=diag(0.5,0.25)
 */
#pragma once
int matInv(vector<vector<double>> &matrix) {
  int n = sz(matrix);
  vector<int> colOrder(n);
  vector<vector<double>> inverse(n, vector<double>(n));
  for (int i = 0; i < (n); ++i) inverse[i][i] = 1, colOrder[i] = i;

  for (int i = 0; i < (n); ++i) {
    int pivotRow = i, pivotCol = i;
    for (int j = i; j < (n); ++j)
      for (int k = i; k < (n); ++k)
        if (fabs(matrix[j][k]) > fabs(matrix[pivotRow][pivotCol])) pivotRow = j, pivotCol = k;
    if (fabs(matrix[pivotRow][pivotCol]) < 1e-12) return i;
    matrix[i].swap(matrix[pivotRow]);
    inverse[i].swap(inverse[pivotRow]);
    for (int j = 0; j < (n); ++j)
      swap(matrix[j][i], matrix[j][pivotCol]), swap(inverse[j][i], inverse[j][pivotCol]);
    swap(colOrder[i], colOrder[pivotCol]);
    double pivot = matrix[i][i];
    for (int j = i + 1; j < (n); ++j) {
      double factor = matrix[j][i] / pivot;
      matrix[j][i] = 0;
      for (int k = i + 1; k < (n); ++k) matrix[j][k] -= factor * matrix[i][k];
      for (int k = 0; k < (n); ++k) inverse[j][k] -= factor * inverse[i][k];
    }
    for (int j = i + 1; j < (n); ++j) matrix[i][j] /= pivot;
    for (int j = 0; j < (n); ++j) inverse[i][j] /= pivot;
    matrix[i][i] = 1;
  }

  /// forget A at this point, just eliminate tmp backward
  for (int i = n - 1; i > 0; --i)
    for (int j = 0; j < (i); ++j) {
      double pivot = matrix[j][i];
      for (int k = 0; k < (n); ++k) inverse[j][k] -= pivot * inverse[i][k];
    }

  for (int i = 0; i < (n); ++i)
    for (int j = 0; j < (n); ++j) matrix[colOrder[i]][colOrder[j]] = inverse[i][j];
  return n;
}

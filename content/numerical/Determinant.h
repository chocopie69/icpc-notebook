/**
 * Author: Simon Lindholm
 * Date: 2016-09-06
 * License: CC0
 * Source: folklore
 * Description: Calculates determinant of a matrix. Destroys the matrix.
 * Input must be square. Row swaps change the determinant sign; elimination modifies the matrix,
 * so copy it first if needed. The fixed pivot tolerance may classify very small determinants as
 * zero; scale input when numerical precision matters.
 * Time: $O(N^3)$
 * Status: somewhat tested
 * Usage: vector<vector<double>> a={{1,2},{3,4}};
 * double determinant=det(a); // -2; a is modified
 */
#pragma once
double det(vector<vector<double>> &matrix) {
  int n = sz(matrix);
  double determinant = 1;
  for (int i = 0; i < (n); ++i) {
    int pivotRow = i;
    for (int j = i + 1; j < (n); ++j)
      if (fabs(matrix[j][i]) > fabs(matrix[pivotRow][i])) pivotRow = j;
    if (i != pivotRow) swap(matrix[i], matrix[pivotRow]), determinant *= -1;
    determinant *= matrix[i][i];
    if (determinant == 0) return 0;
    for (int j = i + 1; j < (n); ++j) {
      double factor = matrix[j][i] / matrix[i][i];
      if (factor != 0)
        for (int k = i + 1; k < (n); ++k) matrix[j][k] -= factor * matrix[i][k];
    }
  }
  return determinant;
}

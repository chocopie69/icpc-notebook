/**
 * Author: Per Austrin, Simon Lindholm
 * Date: 2004-02-08
 * License: CC0
 * Description: Solves $A * x = b$. If there are multiple solutions, an arbitrary one is returned.
 *  Returns rank, or -1 if no solutions. Data in $A$ and $b$ is lost.
 * For n equations in m unknowns, resize solution to m before calling: its size tells the solver
 * the number of columns. Rank m means unique solution; 0<=rank<m means free variables, chosen as
 * zero. Read solution only if rank!=-1. A and b are modified; copy them if needed.
 * For poorly scaled floating input, adjust eps; modular equations need field arithmetic.
 * Time: O(n^2 m)
 * Status: tested on kattis:equationsolver, and bruteforce-tested mod 3 and 5 for n,m <= 3
 * Usage: vector<vd> a={{1,1},{1,-1}}; vd b={3,1}, x(2);
 * int rank=solveLinear(a,b,x); // rank=2, x={2,1}
 */
#pragma once

typedef vector<double> vd;
const double eps = 1e-12;
int solveLinear(vector<vd> &matrix, vd &rhs, vd &solution) {
  int n = sz(matrix), m = sz(solution), rank = 0, pivotRow, pivotCol;
  if (n) assert(sz(matrix[0]) == m);
  vector<int> colOrder(m);
  iota(all(colOrder), 0);

  for (int i = 0; i < (n); ++i) {
    double magnitude, pivotValue = 0;
    for (int r = i; r < (n); ++r)
      for (int c = i; c < (m); ++c)
        if ((magnitude = fabs(matrix[r][c])) > pivotValue)
          pivotRow = r, pivotCol = c, pivotValue = magnitude;
    if (pivotValue <= eps) {
      for (int j = i; j < (n); ++j)
        if (fabs(rhs[j]) > eps) return -1;
      break;
    }
    swap(matrix[i], matrix[pivotRow]);
    swap(rhs[i], rhs[pivotRow]);
    swap(colOrder[i], colOrder[pivotCol]);
    for (int j = 0; j < (n); ++j) swap(matrix[j][i], matrix[j][pivotCol]);
    pivotValue = 1 / matrix[i][i];
    for (int j = i + 1; j < (n); ++j) {
      double factor = matrix[j][i] * pivotValue;
      rhs[j] -= factor * rhs[i];
      for (int k = i + 1; k < (m); ++k) matrix[j][k] -= factor * matrix[i][k];
    }
    rank++;
  }

  solution.assign(m, 0);
  for (int i = rank; i--;) {
    rhs[i] /= matrix[i][i];
    solution[colOrder[i]] = rhs[i];
    for (int j = 0; j < (i); ++j) rhs[j] -= matrix[j][i] * rhs[i];
  }
  return rank; // (multiple solutions if rank < m)
}

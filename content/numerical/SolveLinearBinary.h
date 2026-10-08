/**
 * Author: Simon Lindholm
 * Date: 2016-08-27
 * License: CC0
 * Source: own work
 * Description: Solves $Ax = b$ over $\mathbb F_2$. If there are multiple solutions, one is returned arbitrarily.
 *  Returns rank, or -1 if no solutions. Destroys $A$ and $b$.
 * Use for XOR equations: each row bitset holds the first m coefficients and rhs entries are 0/1.
 * All coefficient bits from m upward must be zero and m<=1000. Returns rank or -1; free
 * variables are zero. Both matrix and rhs are modified. Each solution bit is that variable's
 * assigned value.
 * Time: O(n^2 m)
 * Status: bruteforce-tested for n, m <= 4
 * Usage: vector<bs> a={bs(3),bs(1)}; vector<int> b={1,0}; bs x;
 * int rank=solveLinear(a,b,x,2); // x[0]=0, x[1]=1
 */
#pragma once

typedef bitset<1000> bs;
int solveLinear(vector<bs> &matrix, vector<int> &rhs, bs &solution, int m) {
  int n = sz(matrix), rank = 0, pivotRow;
  assert(m <= sz(solution));
  vector<int> colOrder(m);
  iota(all(colOrder), 0);
  for (int i = 0; i < (n); ++i) {
    for (pivotRow = i; pivotRow < n; ++pivotRow)
      if (matrix[pivotRow].any()) break;
    if (pivotRow == n) {
      for (int j = i; j < (n); ++j)
        if (rhs[j]) return -1;
      break;
    }
    int pivotCol = (int)matrix[pivotRow]._Find_next(i - 1);
    swap(matrix[i], matrix[pivotRow]);
    swap(rhs[i], rhs[pivotRow]);
    swap(colOrder[i], colOrder[pivotCol]);
    for (int j = 0; j < (n); ++j)
      if (matrix[j][i] != matrix[j][pivotCol]) {
        matrix[j].flip(i);
        matrix[j].flip(pivotCol);
      }
    for (int j = i + 1; j < (n); ++j)
      if (matrix[j][i]) {
        rhs[j] ^= rhs[i];
        matrix[j] ^= matrix[i];
      }
    rank++;
  }

  solution = bs();
  for (int i = rank; i--;) {
    if (!rhs[i]) continue;
    solution[colOrder[i]] = 1;
    for (int j = 0; j < (i); ++j) rhs[j] ^= matrix[j][i];
  }
  return rank; // (multiple solutions if rank < m)
}

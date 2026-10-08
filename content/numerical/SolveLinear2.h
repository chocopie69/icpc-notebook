/**
 * Author: Simon Lindholm
 * Date: 2016-09-06
 * License: CC0
 * Source: me
 * Description: To get all uniquely determined values of $x$ back from SolveLinear, make the following changes:
 * This is an edit recipe for SolveLinear, not a separate callable solver. Eliminate each pivot
 * column from all other rows, then mark variables depending on free columns as undefined. Choose
 * an undefined marker such as NaN. A rank below m does not mean every variable is undetermined.
 * Status: tested on kattis:equationsolverplus, stress-tested
 * Usage: // Apply the changes inside solveLinear first.
 * // Then size x to m and call solveLinear(a,b,x) as usual.
 */
#pragma once

#include "SolveLinear.h"

for (int j = 0; j < (n); ++j)
  if (j != i) // instead of for (int j = i+1; j < (n); ++j)
    // ... then at the end:
    solution.assign(m, undefined);
for (int i = 0; i < (rank); ++i) {
  for (int j = rank; j < (m); ++j)
    if (fabs(matrix[i][j]) > eps) goto fail;
  solution[colOrder[i]] = rhs[i] / matrix[i][i];
fail:;
}

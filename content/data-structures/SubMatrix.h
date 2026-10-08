/**
 * Author: Johan Sannemo
 * Date: 2014-11-28
 * License: CC0
 * Source: Folklore
 * Description: Calculate submatrix sums quickly, given upper-left and lower-right corners (half-open).
 * Use on a static, nonempty rectangular matrix. Coordinates are 0-based:
 * sum(top,left,bottom,right) includes top/left and excludes bottom/right. There are no updates
 * after construction. Choose ll for large cell sums.
 * Usage: PrefixSum2D<ll> sums(matrix);
 * ll rectangle=sums.sum(0,0,2,3); // first 2 rows, 3 columns
 * Time: $O(RC)$ construction for R rows and C columns; $O(1)$ per query.
 * Status: Tested on Kattis
 */
#pragma once
template <class T> struct PrefixSum2D {
  vector<vector<T>> prefix;
  PrefixSum2D(vector<vector<T>> &values) {
    int rows = sz(values), cols = sz(values[0]);
    prefix.assign(rows + 1, vector<T>(cols + 1));
    for (int row = 0; row < (rows); ++row)
      for (int col = 0; col < (cols); ++col)
        prefix[row + 1][col + 1] =
            values[row][col] + prefix[row][col + 1] + prefix[row + 1][col] - prefix[row][col];
  }
  T sum(int top, int left, int bottom, int right) {
    return prefix[bottom][right] - prefix[bottom][left] - prefix[top][right] + prefix[top][left];
  }
};

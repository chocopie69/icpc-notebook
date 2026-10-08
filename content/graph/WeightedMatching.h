/**
 * Author: Jeremy Lim, Joshua Andersson
 * Date: 2026-07-09
 * License: CC0
 * Source: https://github.com/scipy/scipy/blob/main/scipy/optimize/rectangular_lsap/rectangular_lsap.cpp
 * Description: Given a weighted bipartite graph, matches every node on
 * the left with a node on the right such that no
 * nodes are in two matchings and the sum of the edge weights is minimal. Takes
 * cost[N][M], where cost[i][j] = cost for L[i] to be matched with R[j], and
 * returns (min cost, match), where L[i] is matched with
 * R[match[i]]. Negate costs for max cost. Requires $N \le M$.
 * Use to assign each left item to a distinct right item. Rows/columns are 0-based; every row has
 * the same length and rows<=columns. Missing edges need a sufficiently large cost, followed by
 * checking none was chosen. Use ll when total costs may exceed int. This minimizes total cost,
 * not matching cardinality.
 * Time: O(N^2M)
 * Status: Tested on kattis:cordonbleu, kattis:engaging, stress-tested
 * Usage: vector<vector<ll>> costs={{3,1,8},{2,4,6}};
 * auto [minCost,match]=weightedMatching(costs); // cost=3
 * // Row i is assigned to column match[i].
 */
#pragma once
template <class T> pair<T, vector<int>> weightedMatching(vector<vector<T>> &costs) {
  int i = sz(costs), m = i ? sz(costs[0]) : 0, col, scannedCols, row;
  vector<T> dist(m), potential(m);
  vector<int> matchLeft(i), matchRight(m, -1), colOrder(m), parentRow(m);
  T minDist = 0, newDist, cost = 0;
  while (i--) {
    for (int col = 0; col < (m); ++col)
      dist[col] = costs[i][col], colOrder[col] = col, parentRow[col] = i;
    for (scannedCols = 0;;) {
      for (int j = scannedCols; j < (m); ++j) {
        col = colOrder[j], newDist = dist[col] - potential[col];
        if (j == scannedCols || minDist > newDist)
          minDist = newDist, swap(colOrder[scannedCols], colOrder[j]);
      }
      if ((row = matchRight[col = colOrder[scannedCols++]]) == -1) break;
      for (int j = 0; j < (m); ++j)
        if (dist[j] > (newDist = costs[row][j] - costs[row][col] + dist[col]))
          dist[j] = newDist, parentRow[j] = row;
    }
    cost += dist[col];
    while (scannedCols--) potential[colOrder[scannedCols]] = dist[colOrder[scannedCols]] - minDist;
    for (; row != i; swap(col, matchLeft[row])) row = matchRight[col] = parentRow[col];
  }
  return {cost, matchLeft};
}

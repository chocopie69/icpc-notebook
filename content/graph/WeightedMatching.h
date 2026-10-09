/**
 * Author: Jeremy Lim, Joshua Andersson
 * Date: 2026-07-09
 * License: CC0
 * Source: https://github.com/scipy/scipy/blob/main/scipy/optimize/rectangular_lsap/rectangular_lsap.cpp
 * Description: Minimum-cost assignment of every left vertex to a distinct right vertex.
 * Use when each worker/job pair has a cost and every worker must be assigned once.
 * For maximum pair count without costs, use HopcroftKarp; for capacities or partial
 * assignments with costs, use MinCostMaxFlow.
 * costs has size (N+1)*(M+1), with row/column 0 unused and N<=M.
 * Returns {totalCost,match}, where match has N+1 entries, index 0 unused, and
 * match[i] is the assigned column. Negate costs for maximum cost. Missing edges need a large
 * finite cost and a check afterward. Use ll if costs/potentials/totals may exceed int.
 * N>M cannot assign every row; transpose only if assigning every vertex on the smaller side.
 * Time: O(N^2M)
 * Status: Tested on kattis:cordonbleu, kattis:engaging, stress-tested
 * Usage: vector<vector<ll>> costs={{0,0,0},{0,3,1},{0,2,4}};
 * auto [minCost,match]=weightedMatching(costs); // cost=3
 * // Row i is assigned to column match[i], both 1-based.
 */
#pragma once
template <class T> pair<T, vector<int>> weightedMatching(vector<vector<T>> &costs) {
  int i = sz(costs) - 1, m = sz(costs[0]) - 1, col, scannedCols, row;
  vector<T> dist(m + 1), potential(m + 1);
  vector<int> matchLeft(i + 1), matchRight(m + 1, -1), colOrder(m + 1), parentRow(m + 1);
  T minDist = 0, newDist, cost = 0;
  while (i > 0) {
    for (int col = 1; col <= m; ++col)
      dist[col] = costs[i][col], colOrder[col] = col, parentRow[col] = i;
    for (scannedCols = 1;;) {
      for (int j = scannedCols; j <= m; ++j) {
        col = colOrder[j], newDist = dist[col] - potential[col];
        if (j == scannedCols || minDist > newDist)
          minDist = newDist, swap(colOrder[scannedCols], colOrder[j]);
      }
      if ((row = matchRight[col = colOrder[scannedCols++]]) == -1) break;
      for (int j = 1; j <= m; ++j)
        if (dist[j] > (newDist = costs[row][j] - costs[row][col] + dist[col]))
          dist[j] = newDist, parentRow[j] = row;
    }
    cost += dist[col];
    while (--scannedCols) potential[colOrder[scannedCols]] = dist[colOrder[scannedCols]] - minDist;
    for (; row != i; swap(col, matchLeft[row])) row = matchRight[col] = parentRow[col];
    --i;
  }
  return {cost, matchLeft};
}

/**
 * Author: Jeremy Lim, Joshua Andersson
 * Date: 2026-07-09
 * License: CC0
 * Source: https://github.com/scipy/scipy/blob/main/scipy/optimize/rectangular_lsap/rectangular_lsap.cpp
 * Description: Minimum-cost assignment of every left vertex to a distinct right vertex.
 * cost is a rectangular 0-based N*M matrix with N<=M; returns {totalCost,match}, where
 * match[i] is the assigned column. Negate costs for maximum cost. Missing edges need a large
 * cost and a check afterward. Use ll if totals may exceed int.
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

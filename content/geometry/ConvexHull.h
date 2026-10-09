/**
 * Author: Stjepan Glavina, chilli
 * Date: 2019-05-05
 * License: Unlicense
 * Source: https://github.com/stjepang/snippets/blob/master/convex_hull.cpp
 * Description: \\
 * \begin{minipage}{75mm}
 * Returns extreme vertices in CCW order, omitting interior collinear boundary points. Input is
 * copied and sorted; empty/single-point inputs work, and collinear input reduces to endpoints.
 * Cross products must fit ll. To keep all boundary points, deduplicate, change <=0 to <0,
 * and handle the all-collinear case separately (return sorted unique points).
 * \end{minipage}
 * \begin{minipage}{15mm}
 * \vspace{-6mm}
 * \includegraphics[width=\textwidth]{content/geometry/ConvexHull}
 * \vspace{-6mm}
 * \end{minipage}
 * Time: O(n \log n)
 * Status: stress-tested, tested with kattis:convexhull
 * Usage: vector<P> points={{0,0},{2,0},{0,2},{1,0}};
 * auto hull=convexHull(points); // (1,0) is omitted
 */
#pragma once

#include "Point.h"

typedef Point<ll> P;
vector<P> convexHull(vector<P> points) {
  if (sz(points) <= 1) return points;
  sort(all(points));
  vector<P> hull(sz(points) + 1);
  int chainStart = 0, hullSize = 0;
  for (int pass = 2; pass--; chainStart = --hullSize, reverse(all(points)))
    for (P p : points) {
      while (hullSize >= chainStart + 2 && hull[hullSize - 2].cross(hull[hullSize - 1], p) <= 0)
        hullSize--;
      hull[hullSize++] = p;
    }
  return {hull.begin(), hull.begin() + hullSize - (hullSize == 2 && hull[0] == hull[1])};
}

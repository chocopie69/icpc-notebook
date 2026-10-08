/**
 * Author: Ulf Lundstrom
 * Date: 2009-03-21
 * License: CC0
 * Source: Basic math
 * Description: \\
 * \begin{minipage}{75mm}
 * Signed distance to the infinite line a->b: positive on the left, negative on the right.
 * Require a!=b; take abs for unsigned distance. Cross products must fit the coordinate type.
 * \end{minipage}
 * \begin{minipage}{15mm}
 * \includegraphics[width=\textwidth]{content/geometry/lineDistance}
 * \end{minipage}
 * Status: tested
 * Usage: double distance=abs(lineDist(Point<double>(0,0),
 *   Point<double>(2,0),Point<double>(1,3))); // 3
 */
#pragma once

#include "Point.h"
template <class P>
double lineDist(P a, P b, P p) {
  return (double)(b - a).cross(p - a) / (b - a).dist();
}

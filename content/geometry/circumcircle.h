/**
 * Author: Ulf Lundstrom
 * Date: 2009-04-11
 * License: CC0
 * Source: http://en.wikipedia.org/wiki/Circumcircle
 * Description: \\
 * \begin{minipage}{75mm}
 * The circumcirle of a triangle is the circle intersecting all three vertices. ccRadius returns the radius of the circle going through points A, B and C and ccCenter returns the center of the same circle.
 * \end{minipage}
 * \begin{minipage}{15mm}
 * \vspace{-2mm}
 * \includegraphics[width=\textwidth]{content/geometry/circumcircle}
 * \end{minipage}
 * The points must be distinct and noncollinear. This is the circle through the vertices, which
 * is not always the triangle's minimum enclosing circle: an obtuse triangle uses its longest
 * side as a diameter. Use Point<double> for the center.
 * Status: tested
 * Usage: P a(0,0), b(2,0), c(0,2);
 * P center=ccCenter(a,b,c); double radius=ccRadius(a,b,c);
 */
#pragma once

#include "Point.h"

typedef Point<double> P;
double ccRadius(P A, P B, P C) {
  return (B - A).dist() * (C - B).dist() * (A - C).dist() / abs((B - A).cross(C - A)) / 2;
}
P ccCenter(P A, P B, P C) {
  P dirAC = C - A, dirAB = B - A;
  return A + (dirAC * dirAB.dist2() - dirAB * dirAC.dist2()).perp() / dirAC.cross(dirAB) / 2;
}

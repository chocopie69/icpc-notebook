/**
 * Author: Ulf Lundstrom
 * Date: 2009-03-21
 * License: CC0
 * Source:
 * Description: \\
 * \begin{minipage}{75mm}
 * Distance to the closed segment, including endpoints; equal endpoints are supported. Use
 * Point<double> and a tolerance when comparing the distance with zero.
 * \end{minipage}
 * \begin{minipage}{15mm}
 * \vspace{-10mm}
 * \includegraphics[width=\textwidth]{content/geometry/SegmentDistance}
 * \end{minipage}
 * Usage: double distance=segDist(P(0,0),P(2,0),P(3,1));
 * bool on=distance<1e-9;
 * Status: tested
 */
#pragma once

#include "Point.h"

typedef Point<double> P;
double segDist(P start, P finish, P p) {
  if (start == finish) return (p - start).dist();
  auto length2 = (finish - start).dist2(),
       projection = min(length2, max(.0, (p - start).dot(finish - start)));
  return ((p - start) * length2 - (finish - start) * projection).dist() / length2;
}

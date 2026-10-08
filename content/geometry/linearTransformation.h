/**
 * Author: Per Austrin, Ulf Lundstrom
 * Date: 2009-04-09
 * License: CC0
 * Source:
 * Description: \\
 * \begin{minipage}{75mm}
 *  Apply the linear transformation (translation, rotation and scaling) which takes line p0-p1 to line q0-q1 to point r.
 * \end{minipage}
 * \begin{minipage}{15mm}
 * \vspace{-8mm}
 * \includegraphics[width=\textwidth]{content/geometry/linearTransformation}
 * \vspace{-2mm}
 * \end{minipage}
 * Use when a directed segment is mapped to another by translation, rotation and uniform scaling.
 * The same mapping is applied to point. The source segment must have nonzero length. This does
 * not implement reflection or arbitrary shear.
 * Status: not tested
 * Usage: P mapped=linearTransformation(P(0,0),P(1,0),
 *   P(2,3),P(2,5),P(1,1)); // (0,5)
 */
#pragma once

#include "Point.h"

typedef Point<double> P;
P linearTransformation(P sourceStart, P sourceEnd, P targetStart, P targetEnd, P point) {
  P sourceDir = sourceEnd - sourceStart, targetDir = targetEnd - targetStart,
    transform(sourceDir.cross(targetDir), sourceDir.dot(targetDir));
  return targetStart +
         P((point - sourceStart).cross(transform), (point - sourceStart).dot(transform)) /
             sourceDir.dist2();
}

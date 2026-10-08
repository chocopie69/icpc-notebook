/**
 * Author: Håkan Terelius
 * Date: 2009-09-25
 * License: CC0
 * Source: http://en.wikipedia.org/wiki/Euler's_totient_function
 * Description: Choose LIM and call calculatePhi once for phi[1..LIM-1]. phi[n] counts residues coprime with
 * n; $\phi(n)=n\prod_{p\mid n}(1-1/p)$. Reduce exponents modulo phi(n) directly only when base
 * and n are coprime.
 * Status: Tested
 * Usage: calculatePhi(); int count=phi[12]; // 4
 */
#pragma once

const int LIM = 5000000;
int phi[LIM];
void calculatePhi() {
  for (int i = 0; i < (LIM); ++i) phi[i] = i & 1 ? i : i / 2;
  for (int i = 3; i < LIM; i += 2)
    if (phi[i] == i)
      for (int j = i; j < LIM; j += i) phi[j] -= phi[j] / i;
}

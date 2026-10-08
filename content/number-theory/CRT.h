/**
 * Author: Simon Lindholm
 * Date: 2019-05-22
 * License: CC0
 * Description: crt(a,m,b,n) returns x with $x\equiv a\pmod m$, $x\equiv b\pmod n$. Use positive moduli and
 * normalized residues; require $(a-b)\bmod\gcd(m,n)=0$ or it asserts. Returns $0\le
 * x<\mathrm{lcm}(m,n)$, including non-coprime moduli. Requires $mn<2^{62}$.
 * Time: $\log(n)$
 * Status: Works
 * Usage: ll x=crt(2,3,3,5); // 8 modulo 15
 * // Check (a-b)%gcd(m,n)==0 before calling.
 */
#pragma once

#include "euclid.h"
ll crt(ll a, ll m, ll b, ll n) {
  if (n > m) swap(a, b), swap(m, n);
  ll x, y, gcdValue = euclid(m, n, x, y);
  assert((a - b) % gcdValue == 0); // else no solution
  x = (b - a) % n * x % n / gcdValue * m + a;
  return x < 0 ? x + m * n / gcdValue : x;
}

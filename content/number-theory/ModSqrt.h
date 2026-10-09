/**
 * Author: Simon Lindholm
 * Date: 2016-08-31
 * License: CC0
 * Source: http://eli.thegreenplace.net/2009/03/07/computing-modular-square-roots-in-python/
 * Description: Tonelli-Shanks algorithm for modular square roots. Finds $x$ s.t. $x^2 = a \pmod p$ ($-x$ gives the other solution).
 * Use an odd prime p and a quadratic residue a; test modpow(a,(p-1)/2,p)==1 for nonzero a first.
 * Nonresidues assert rather than return a failure marker. Handle p=2 separately. Requires the
 * three-argument modpow from ModMulLL.h; all direct products must fit ll. The other root is
 * (p-x)\%p. For large p, replace direct modular products with modmul.
 * Time: O(\log^2 p) worst case, O(\log p) for most $p$
 * Status: Tested for all a,p <= 10000
 * Usage: ll x=sqrt(10LL,13LL); // 6 or 7
 * ll other=(13-x)%13;
 */
#pragma once

#include "ModMulLL.h"
ll sqrt(ll a, ll prime) {
  a %= prime;
  if (a < 0) a += prime;
  if (a == 0) return 0;
  assert(modpow(a, (prime - 1) / 2, prime) == 1); // else no solution
  if (prime % 4 == 3) return modpow(a, (prime + 1) / 4, prime);
  // a^(n+3)/8 or 2^(n+3)/8 * 2^(n-1)/4 works if p % 8 == 5
  ll oddPart = prime - 1, nonResidue = 2;
  int twos = 0, order;
  while (oddPart % 2 == 0) ++twos, oddPart /= 2;
  /// find a non-square mod p
  while (modpow(nonResidue, (prime - 1) / 2, prime) != prime - 1) ++nonResidue;
  ll x = modpow(a, (oddPart + 1) / 2, prime);
  ll remainder = modpow(a, oddPart, prime), rootOfUnity = modpow(nonResidue, oddPart, prime);
  for (;; twos = order) {
    ll power = remainder;
    for (order = 0; order < twos && power != 1; ++order) power = power * power % prime;
    if (order == 0) return x;
    ll correction = modpow(rootOfUnity, 1LL << (twos - order - 1), prime);
    rootOfUnity = correction * correction % prime;
    x = x * correction % prime;
    remainder = remainder * rootOfUnity % prime;
  }
}

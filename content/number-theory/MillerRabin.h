/**
 * Author: chilli, c1729, Simon Lindholm
 * Date: 2019-03-28
 * License: CC0
 * Source: Wikipedia, https://miller-rabin.appspot.com/
 * Description: Deterministic Miller-Rabin primality test.
 * Guaranteed to work for numbers up to $7 \cdot 10^{18}$; for larger numbers, use Python and extend A randomly.
 * Use when testing individual large integers without sieving to them. Returns false for 0 and 1.
 * A fixed witness set gives the stated deterministic range, using ModMulLL for modular products.
 * The name isPrime conflicts with the sieve bitset if both snippets are pasted unchanged.
 * Time: 7 times the complexity of $a^b \mod c$.
 * Status: Stress-tested
 * Usage: bool prime=isPrime(1000000007ULL); // true
 */
#pragma once

#include "ModMulLL.h"
bool isPrime(ull n) {
  if (n < 2 || n % 6 % 4 != 1) return (n | 1) == 3;
  ull bases[] = {2, 325, 9375, 28178, 450775, 9780504, 1795265022}, twos = __builtin_ctzll(n - 1),
      oddPart = n >> twos;
  for (ull base : bases) { // ^ count trailing zeroes
    ull power = modpow(base % n, oddPart, n), squaresLeft = twos;
    while (power != 1 && power != n - 1 && base % n && squaresLeft--)
      power = modmul(power, power, n);
    if (power != n - 1 && squaresLeft != twos) return 0;
  }
  return 1;
}

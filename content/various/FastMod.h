/**
 * Author: Simon Lindholm
 * Date: 2020-05-30
 * License: CC0
 * Source: https://en.wikipedia.org/wiki/Barrett_reduction
 * Description: Compute $a \% b$ about 5 times faster than usual, where $b$ is constant but not known at compile time.
 * Returns a value congruent to $a \pmod b$ in the range $[0, 2b)$.
 * Use when reusing the same runtime modulus many times. This is a reduction helper, not modular
 * division/multiplication. For a canonical remainder subtract modulus if the result is at least
 * modulus. Use $0<modulus<2^{63}$ so the stated range fits ull. Requires GNU 128-bit integer
 * multiplication.
 * Status: proven correct, stress-tested
 * Measured as having 4 times lower latency, and 8 times higher throughput, see stress-test.
 * Details:
 * More precisely, it can be proven that the result equals 0 only if $a = 0$,
 * and otherwise lies in $[1, (1 + a/2^64) * b)$.
 * Usage: FastMod reducer(7); ull r=reducer.reduce(100);
 * if (r>=reducer.modulus) r-=reducer.modulus; // r=2
 */
#pragma once
struct FastMod {
  ull modulus, reciprocal;
  FastMod(ull modulus) : modulus(modulus), reciprocal(-1ULL / modulus) {}
  ull reduce(ull value) { // value % modulus + (0 or modulus)
    return value - (ull)((__uint128_t(reciprocal) * value) >> 64) * modulus;
  }
};

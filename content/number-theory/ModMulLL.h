/**
 * Author: chilli, Ramchandra Apte, Noam527, Simon Lindholm
 * Date: 2019-04-24
 * License: CC0
 * Source: https://github.com/RamchandraApte/OmniTemplate/blob/master/src/number_theory/modulo.hpp
 * Description: Calculate $a\cdot b\bmod c$ (or $a^b \bmod c$) for $0 \le a, b \le c \le 7.2\cdot 10^{18}$.
 * Use for large-modulus exponentiation and primality/factorization when ordinary ll
 * multiplication would overflow. The three-argument modpow takes an explicit modulus. The large
 * bound assumes an 80-bit long double; for other platforms or larger moduli use unsigned
 * \_\_int128 multiplication/reduction. Normalize operands first and use a positive modulus.
 * Time: O(1) for \texttt{modmul}, O(\log b) for \texttt{modpow}
 * Status: stress-tested, proven correct
 * Details:
 * This runs ~2x faster than the naive (__int128_t)a * b % M.
 * A proof of correctness is in doc/modmul-proof.tex. An earlier version of the proof,
 * from when the code used a * b / (long double)M, is in doc/modmul-proof.md.
 * The proof assumes that long doubles are implemented as x87 80-bit floats; if they
 * are 64-bit, as on e.g. MSVC, the implementation is only valid for
 * $0 \le a, b \le c < 2^{52} \approx 4.5 \cdot 10^{15}$.
 * Usage: ull product=modmul(1000000000000ULL,
 *   1000000000000ULL,1000000000000000003ULL);
 * ull power=modpow(2,100,1000000007);
 */
#pragma once
ull modmul(ull lhs, ull rhs, ull modulus) {
  ll remainder = lhs * rhs - modulus * (ull)(1.L / modulus * lhs * rhs);
  return remainder + modulus * (remainder < 0) - modulus * (remainder >= (ll)modulus);
}
ull modpow(ull base, ull exponent, ull mod) {
  ull result = 1;
  for (; exponent; base = modmul(base, base, mod), exponent /= 2)
    if (exponent & 1) result = modmul(result, base, mod);
  return result;
}

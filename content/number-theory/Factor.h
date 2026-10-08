/**
 * Author: chilli, SJTU, pajenegod
 * Date: 2020-03-04
 * License: CC0
 * Source: own
 * Description: Pollard-rho randomized factorization algorithm. Returns prime
 * factors of a number, in arbitrary order (e.g. 2299 -> \{11, 19, 11\}).
 * Call factor on a positive integer; factor(1) is empty and factor(0) is unsupported. Repeated
 * factors are retained and output is unsorted. Sort to group prime powers for divisor counts or
 * totients. pollard is an internal splitter for composite n, not a primality test. ModMulLL
 * platform/range limits apply.
 * Time: $O(n^{1/4})$, less for numbers with small factors.
 * Status: stress-tested
 *
 * Details: This implementation uses the improvement described here
 * (https://en.wikipedia.org/wiki/Pollard%27s_rho_algorithm#Variants), where
 * one can accumulate gcd calls by some factor (40 chosen here through
 * exhaustive testing). This improves performance by approximately 6-10x
 * depending on the inputs and speed of gcd. Benchmark found here:
 * (https://ideone.com/nGGD9T)
 *
 * GCD can be improved by a factor of 1.75x using Binary GCD
 * (https://lemire.me/blog/2013/12/26/fastest-way-to-compute-the-greatest-common-divisor/).
 * However, with the gcd accumulation the bottleneck moves from the gcd calls
 * to the modmul. As GCD only constitutes ~12% of runtime, speeding it up
 * doesn't matter so much.
 *
 * This code can probably be sped up by using a faster mod mul - potentially
 * montgomery reduction on 128 bit integers.
 * Alternatively, one can use a quadratic sieve for an asymptotic improvement,
 * which starts being faster in practice around 1e13.
 *
 * Brent's cycle finding algorithm was tested, but doesn't reduce modmul calls
 * significantly.
 *
 * Subtle implementation notes:
 * - prd starts off as 2 to handle the case n = 4; it's harmless for other n
 *   since we're guaranteed that n > 2. (Pollard rho has problems with prime
 *   powers in general, but all larger ones happen to work.)
 * - t starts off as 30 to make the first gcd check come earlier, as an
 *   optimization for small numbers.
 * - we vary f between restarts because the cycle finding algorithm does not
 *   find the first element in the cycle but rather one at distance k*|cycle|
 *   from the start, and that can result in continual failures if all cycles
 *   have the same size for all prime factors. E.g. fixing f(x) = x^2 + 1 would
 *   loop infinitely for n = 352523 * 352817, where all cycles have size 821.
 * - we operate on residues in [i, n + i) which modmul is not designed to
 *   handle, but specifically modmul(x, x) still turns out to work for small
 *   enough i. (With reference to the proof in modmul-proof.tex, the argument
 *   for "S is in [-c, 2c)" goes through unchanged, while S < 2^63 now follows
 *   from S < 2c and S = x^2 (mod c) together implying S < c + i^2.)
 * Usage: auto factors=factor(2299); sort(all(factors));
 * // {11,11,19}
 */
#pragma once

#include "ModMulLL.h"
#include "MillerRabin.h"
ull pollard(ull n) {
  ull slow = 0, fast = 0, iterations = 30, product = 2, seed = 1, nextProduct;
  auto advance = [&](ull slow) { return modmul(slow, slow, n) + seed; };
  while (iterations++ % 40 || __gcd(product, n) == 1) {
    if (slow == fast) slow = ++seed, fast = advance(slow);
    if ((nextProduct = modmul(product, max(slow, fast) - min(slow, fast), n)))
      product = nextProduct;
    slow = advance(slow), fast = advance(advance(fast));
  }
  return __gcd(product, n);
}
vector<ull> factor(ull n) {
  if (n == 1) return {};
  if (isPrime(n)) return {n};
  ull divisor = pollard(n);
  auto leftFactors = factor(divisor), rightFactors = factor(n / divisor);
  leftFactors.insert(leftFactors.end(), all(rightFactors));
  return leftFactors;
}

/**
 * Author: Lucian Bicsi, Simon Lindholm
 * Date: 2017-10-31
 * License: CC0
 * Description: Given $f$ and $N$, finds the smallest fraction $p/q \in [0, 1]$
 * such that $f(p/q)$ is true, and $p, q \le N$.
 * You may want to throw an exception from $f$ if it finds an exact solution,
 * in which case $N$ can be removed.
 * The predicate must be monotone false-to-true as p/q increases, and true at 1. limit>=1 bounds
 * both p and q. Compare fractions by cross multiplication to avoid rounding; products must fit
 * ll. Finds an exact bounded fraction rather than a floating approximation.
 * For positive fractions beyond 1, change initial hi to {1,0}; predicate must handle q=0.
 * Usage: Frac answer=fracBS([](Frac x) { return 3*x.p>=x.q; },10);
 * // answer is {1,3}
 * Time: O(\log(N))
 * Status: stress-tested for n <= 300
 */

struct Frac {
  ll p, q;
};
template <class F> Frac fracBS(F predicate, ll limit) {
  bool moveHi = 1, prevAdvanced = 1, advanced = 1;
  Frac lo{0, 1}, hi{1, 1}; // Set hi to 1/0 to search (0, N]
  if (predicate(lo)) return lo;
  assert(predicate(hi));
  while (prevAdvanced || advanced) {
    ll advance = 0, step = 1; // move hi if moveHi, else lo
    for (int shift = 0; step; (step *= 2) >>= shift) {
      advance += step;
      Frac mid{lo.p * advance + hi.p, lo.q * advance + hi.q};
      if (abs(mid.p) > limit || mid.q > limit || moveHi == !predicate(mid)) {
        advance -= step;
        shift = 2;
      }
    }
    hi.p += lo.p * advance;
    hi.q += lo.q * advance;
    moveHi = !moveHi;
    swap(lo, hi);
    prevAdvanced = advanced;
    advanced = !!advance;
  }
  return moveHi ? hi : lo;
}

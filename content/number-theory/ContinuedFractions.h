/**
 * Author: Simon Lindholm
 * Date: 2018-07-15
 * License: CC0
 * Source: Wikipedia
 * Description: Given $N$ and a real number $x \ge 0$, finds the closest rational approximation $p/q$ with $p, q \le N$.
 * It will obey $|p/q - x| \le 1/qN$.
 * 
 * For consecutive convergents, $p_{k+1}q_k - q_{k+1}p_k = (-1)^k$.
 * ($p_k/q_k$ alternates between $>x$ and $<x$.)
 * If $x$ is rational, $y$ eventually becomes $\infty$;
 * if $x$ is the root of a degree $2$ polynomial the $a$'s eventually become cyclic.
 * Use to approximate nonnegative real input by a bounded rational. limit>=1 bounds both
 * numerator and denominator, not only the denominator. Returns (p,q). Precision comes from type
 * d; use long double when increasing the limit substantially.
 * Time: O(\log N)
 * Status: stress-tested for n <= 300
 * Usage: auto [p,q]=approximate(3.141592653589793,100);
 * // {22,7}
 */

typedef double d; // for N ~ 1e7; long double for N ~ 1e9
pair<ll, ll> approximate(d x, ll limit) {
  ll prevNum = 0, prevDen = 1, numerator = 1, denominator = 0, inf = LLONG_MAX;
  d remainder = x;
  for (;;) {
    ll maxStep = min(numerator ? (limit - prevNum) / numerator : inf,
                     denominator ? (limit - prevDen) / denominator : inf),
       quotient = (ll)floor(remainder), step = min(quotient, maxStep),
       nextNum = step * numerator + prevNum, nextDen = step * denominator + prevDen;
    if (quotient > step) {
      // If step > quotient/2, we have a semi-convergent that gives us a
      // better approximation; if step = quotient/2, we *may* have one.
      // Return {numerator, denominator} here for a more canonical approximation.
      return (abs(x - (d)nextNum / (d)nextDen) < abs(x - (d)numerator / (d)denominator))
                 ? make_pair(nextNum, nextDen)
                 : make_pair(numerator, denominator);
    }
    if (abs(remainder = 1 / (remainder - (d)quotient)) > 3 * limit) return {nextNum, nextDen};
    prevNum = numerator;
    numerator = nextNum;
    prevDen = denominator;
    denominator = nextDen;
  }
}

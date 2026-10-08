/**
 * Author: Lucian Bicsi
 * Date: 2018-02-14
 * License: CC0
 * Source: Chinese material
 * Description: Generates the $k$'th term of an $n$-order
 * linear recurrence $S[i] = \sum_j S[i-j-1]tr[j]$,
 * given $S[0 \ldots \ge n-1]$ and $tr[0 \ldots n-1]$.
 * Faster than matrix multiplication.
 * Useful together with Berlekamp--Massey.
 * Use when recurrence order is small but the requested index is huge. initial contains exactly n
 * initial terms; recurrence[j] multiplies S[i-j-1]. index is 0-based and nonnegative. Supply the
 * global mod used by the code; the hidden value 5 is only for repository tests. Products must
 * fit ll.
 * Usage: ll fib=linearRec({0,1},{1,1},10);
 * // 55 modulo the configured mod
 * Time: O(n^2 \log k)
 * Status: bruteforce-tested mod 5 for n <= 5
 */
#pragma once

const ll mod = 5; /** exclude-line */

typedef vector<ll> Poly;
ll linearRec(Poly initial, Poly recurrence, ll index) {
  int n = sz(recurrence);

  auto combine = [&](Poly a, Poly b) {
    Poly result(n * 2 + 1);
    for (int i = 0; i < (n + 1); ++i)
      for (int j = 0; j < (n + 1); ++j) result[i + j] = (result[i + j] + a[i] * b[j]) % mod;
    for (int i = 2 * n; i > n; --i)
      for (int j = 0; j < (n); ++j)
        result[i - 1 - j] = (result[i - 1 - j] + result[i] * recurrence[j]) % mod;
    result.resize(n + 1);
    return result;
  };

  Poly weights(n + 1), power(weights);
  weights[0] = power[1] = 1;

  for (++index; index; index /= 2) {
    if (index % 2) weights = combine(weights, power);
    power = combine(power, power);
  }

  ll result = 0;
  for (int i = 0; i < (n); ++i) result = (result + weights[i + 1] * initial[i]) % mod;
  return result;
}

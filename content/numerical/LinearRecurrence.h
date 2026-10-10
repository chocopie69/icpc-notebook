/**
 * Author: Lucian Bicsi
 * Date: 2018-02-14
 * License: CC0
 * Source: Chinese material
 * Description: Computes one distant term of a constant-coefficient linear recurrence modulo mod:
 * $S[i] = \sum_{j=0}^{n-1} S[i-j-1]recurrence[j]$ for i>=n, from its first n terms.
 * Use for Fibonacci-like sequences or counting DP with fixed transitions when iterating to k
 * is too slow. For all terms up to a small k, ordinary O(nk) DP is simpler. This is homogeneous:
 * a constant forcing term or index-dependent coefficients need a transformed recurrence.
 * Polynomial binary exponentiation reduces powers using the characteristic polynomial, obtaining
 * weights of the initial terms. $O(n^2\log k)$ beats generic $O(n^3\log k)$ matrix exponentiation.
 * If coefficients are unknown, Berlekamp--Massey can infer them from enough initial terms.
 * Use when recurrence order is small but the requested index is huge. initial contains exactly n
 * initial terms; recurrence[j] multiplies S[i-j-1]. index is 0-based and nonnegative. Supply the
 * global mod used by the code; the hidden value 5 is only for repository tests. Products must
 * fit ll. Require n>=1 and index<LLONG\_MAX; normalize negative terms/coefficients modulo mod.
 * Usage: ll fib=linearRec({0,1},{1,1},10); // 55 modulo mod (0 with test mod=5)
 * // S[i]=2*S[i-1]+3*S[i-2], S[0]=1, S[1]=4:
 * ll answer=linearRec({1,4},{2,3},2); // 11 modulo mod; coefficients newest first
 * ll distant=linearRec({0,1},{1,1},1000000000000LL);
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

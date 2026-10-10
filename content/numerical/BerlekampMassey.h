/**
 * Author: Lucian Bicsi
 * Date: 2017-10-31
 * License: CC0
 * Source: Wikipedia
 * Description: Finds the shortest constant-coefficient linear recurrence fitting a nonempty
 * prefix s modulo the prime mod from ModPow.h. Returns coefficients c with
 * $s[i]=c[0]s[i-1]+c[1]s[i-2]+\dots$. Normalize input to [0,mod); products must fit ll.
 * Use after computing small DP/counting terms when the recurrence is unknown, then use
 * linearRec for a distant term. If the true sequence has order at most n, its first 2n terms
 * suffice to recover a valid recurrence. Without such a bound, matching a finite prefix does
 * not prove future terms; validate on additional terms. This code requires prime mod for inverses.
 * An all-zero prefix returns an empty recurrence; handle it before calling linearRec.
 * Usage: vector<ll> s={0,1,1,3,5,11}; // reduce each term modulo mod first
 * for (ll &x : s) x%=mod;
 * auto c=berlekampMassey(s); // {1,2}: S[i]=S[i-1]+2*S[i-2]
 * vector<ll> initial(s.begin(),s.begin()+sz(c));
 * // With LinearRecurrence.h and the same mod configured:
 * ll answer=c.empty() ? 0 : linearRec(initial,c,1000000000000LL);
 * Time: O(N^2)
 * Status: bruteforce-tested mod 5 for n <= 5 and all s
 */
#pragma once

#include "../number-theory/ModPow.h"
vector<ll> berlekampMassey(vector<ll> s) {
  int n = sz(s), L = 0, m = 0;
  vector<ll> C(n), B(n), T;
  C[0] = B[0] = 1;

  ll b = 1;
  for (int i = 0; i < (n); ++i) {
    ++m;
    ll d = s[i] % mod;
    for (int j = 1; j < (L + 1); ++j) d = (d + C[j] * s[i - j]) % mod;
    if (!d) continue;
    T = C;
    ll coef = d * modpow(b, mod - 2) % mod;
    for (int j = m; j < (n); ++j) C[j] = (C[j] - coef * B[j - m]) % mod;
    if (2 * L > i) continue;
    L = i + 1 - L;
    B = T;
    b = d;
    m = 0;
  }

  C.resize(L + 1);
  C.erase(C.begin());
  for (ll &x : C) x = (mod - x) % mod;
  return C;
}

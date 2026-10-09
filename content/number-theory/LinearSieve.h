/**
 * Author: Personal Code::Blocks abbreviation, adapted
 * Description: lp[x] is the smallest prime factor for 2<=x<=n; lp[0]=lp[1]=0. Each composite
 * is generated once. Uses more memory than the boolean sieve, but supports fast factorization.
 * Factor only x<=n with lp; larger x needs trial division or Pollard-rho.
 * Usage: LinearSieve sieve(100);
 * int smallest=sieve.lp[84]; // 2
 * int x=84;
 * while (x>1) { cout << sieve.lp[x] << ' '; x/=sieve.lp[x]; } // 2 2 3 7
 * Time: $O(N)$ construction and memory; $O(\log x)$ to factor x using lp.
 */
#pragma once
struct LinearSieve {
  vector<int> lp, primes;
  LinearSieve(int n) : lp(n + 1) {
    for (int i = 2; i <= n; i++) {
      if (lp[i] == 0) lp[i] = i, primes.push_back(i);
      for (int p : primes) {
        if (1LL * i * p > n) break;
        lp[i * p] = p;
        if (p == lp[i]) break;
      }
    }
  }
};

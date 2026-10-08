/**
 * Author: Personal Code::Blocks abbreviation, adapted
 * Description: Generates primes <=n; isPrime[x] tells whether x is prime. Indices 0 and 1 are
 * not prime. Use LinearSieve instead when you also need smallest prime factors.
 * Usage: PrimeSieve sieve(20);
 * bool prime=sieve.isPrime[17]; // true
 * for (int p : sieve.primes) cout << p << ' ';
 * Time: $O(N \log\log N)$ time; $O(N)$ memory.
 */
#pragma once
struct PrimeSieve {
  vector<bool> isPrime;
  vector<int> primes;
  PrimeSieve(int n) : isPrime(n + 1, true) {
    isPrime[0] = false;
    if (n >= 1) isPrime[1] = false;
    for (int i = 2; 1LL * i * i <= n; i++)
      if (isPrime[i])
        for (ll j = 1LL * i * i; j <= n; j += i) isPrime[j] = false;
    for (int i = 2; i <= n; i++)
      if (isPrime[i]) primes.push_back(i);
  }
};

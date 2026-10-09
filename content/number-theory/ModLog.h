/**
 * Author: Bjorn Martinsson
 * Date: 2020-06-03
 * License: CC0
 * Source: own work
 * Description: Returns the smallest $x > 0$ s.t. $a^x = b \pmod m$, or
 * $-1$ if no such $x$ exists. modLog(a,1,m) can be used to
 * calculate the order of $a$.
 * Use for discrete logarithms when sqrt(modulus) work/storage fit. Also supports non-coprime
 * bases. The exponent is strictly positive: target=1 asks for a multiplicative order, not
 * exponent zero. Normalize base and target to [0,modulus); modulus is positive and direct
 * modular products must fit ll. If exponent 0 is allowed, return 0 first when target==1\%modulus.
 * Time: $O(\sqrt m)$
 * Status: tested for all 0 <= a,x < 500 and 0 < m < 500.
 *
 * Details: This algorithm uses the baby-step giant-step method to
 * find (i,j) such that a^(n * i) = b * a^j (mod m), where n > sqrt(m)
 * and 0 < i, j <= n. If a and m are coprime then a^j has a modular
 * inverse, which means that a^(i * n - j) = b (mod m$).
 *
 * However this particular implementation of baby-step giant-step works even
 * without assuming a and m are coprime, using the following idea:
 *
 * Assume p^x is a prime divisor of m. Then we have 3 cases
 *   1. b is divisible by p^x
 *   2. b is divisible only by some p^y, 0<y<x
 *   3. b is not divisible by p
 * The important thing to note is that in case 2, modLog(a,b,m) (if
 * it exists) cannot be > sqrt(m), (technically it cannot be >= log2(m)).
 * So once all exponenents of a that are <= sqrt(m) has been checked, you
 * cannot have case 2. Case 2 is the only tricky case.
 *
 * So the modification allowing for non-coprime input involves checking all
 * exponents of a that are <= n, and then handling the non-tricky cases by
 * a simple gcd(a^n,m) == gcd(b,m) check.
 * Usage: ll exponent=modLog(2,8,13); // 3
 * ll absent=modLog(2,3,4); // -1
 */
#pragma once
ll modLog(ll base, ll target, ll modulus) {
  ll blockSize = (ll)sqrt(modulus) + 1, power = 1, giantStep = 1, j = 1;
  unordered_map<ll, ll> babySteps;
  while (j <= blockSize && (power = giantStep = power * base % modulus) != target % modulus)
    babySteps[power * target % modulus] = j++;
  if (power == target % modulus) return j;
  if (__gcd(modulus, power) == __gcd(modulus, target))
    for (int i = 2; i < (blockSize + 2); ++i)
      if (babySteps.count(power = power * giantStep % modulus))
        return blockSize * i - babySteps[power];
  return -1;
}

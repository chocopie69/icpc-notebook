/**
 * Author: Noam527
 * Date: 2019-04-24
 * License: CC0
 * Source: folklore
 * Description: Two-argument power modulo global mod. Use exponent>=0 and normalize base to [0,mod); products
 * must fit ll. For prime mod and nonzero a, modpow(a,mod-2) is its inverse. For large moduli use
 * the three-argument version in ModMulLL.h.
 * Status: tested
 * Usage: ll power=modpow(2,10); // 1024 modulo mod
 * ll inverse=modpow(3,mod-2); // requires prime mod, 3%mod!=0
 */
#pragma once

const ll mod = 1000000007; // faster if const
ll modpow(ll base, ll exponent) {
  ll result = 1;
  for (; exponent; base = base * base % mod, exponent /= 2)
    if (exponent & 1) result = result * base % mod;
  return result;
}

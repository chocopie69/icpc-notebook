/**
 * Author: Unknown
 * Date: 2002-09-15
 * Source: predates tinyKACTL
 * Description: Returns $g=\gcd(a,b)$ and coefficients with $ax+by=g$. Use positive a,b. For ax+by=c require g
 * to divide c, then scale coefficients by c/g. For an inverse modulo m require g=1 and normalize
 * x to [0,m). Products must fit ll. For negative inputs, solve using absolute values and
 * flip the corresponding coefficient signs; handle a=b=0 separately.
 * Usage: ll x,y; ll g=euclid(30,18,x,y); // 30*x+18*y=6
 */
#pragma once
ll euclid(ll a, ll b, ll &x, ll &y) {
  if (!b) return x = 1, y = 0, a;
  ll gcdValue = euclid(b, a % b, y, x);
  return y -= a / b * x, gcdValue;
}

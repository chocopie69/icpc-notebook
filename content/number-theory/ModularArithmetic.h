/**
 * Author: Lukas Polacek, Joshua Andersson
 * Date: 2009-09-28
 * License: CC0
 * Source: folklore
 * Description: Set global mod first; residues are normalized to [0,mod) and read via .value. Division asserts
 * unless its divisor is coprime with mod. Exponents must be nonnegative; multiplication must fit
 * ll before reduction.
 * Usage: Mod a=5, b=3; ll residue=(a*b+a).value;
 * Mod power=a^10; Mod quotient=a/b; // gcd(b,mod)=1
 */
#pragma once

#include "euclid.h"

const ll mod = 17; // change to something else
struct Mod {
  ll value;
  Mod(ll normalized) : Mod(normalized % mod + mod, 0) {}
  Mod(ll normalized, int) : value(normalized < mod ? normalized : normalized - mod) {}
  Mod operator+(Mod other) { return {value + other.value, 0}; }
  Mod operator-(Mod other) { return {value - other.value + mod, 0}; }
  Mod operator*(Mod other) { return {value * other.value % mod, 0}; }
  Mod operator/(Mod other) { return *this * invert(other); }
  Mod invert(Mod operand) {
    ll inverseCoeff, otherCoeff, gcdValue = euclid(operand.value, mod, inverseCoeff, otherCoeff);
    assert(gcdValue == 1);
    return inverseCoeff;
  }
  Mod operator^(ll exponent) {
    if (!exponent) return 1;
    Mod result = *this ^ (exponent / 2);
    result = result * result;
    return exponent & 1 ? *this * result : result;
  }
};

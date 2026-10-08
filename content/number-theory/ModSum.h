/**
 * Author: Simon Lindholm
 * Date: 2015-06-23
 * License: CC0
 * Source: own work
 * Description: Computes progression sums without iterating: modsum(count,offset,slope,modulus) is
 * $\sum_{i=0}^{count-1}((offset+slope\cdot i)\bmod modulus)$ with nonnegative residues. divsum
 * gives the corresponding sum of floored quotients for nonnegative inputs. Use for lattice-point
 * counts or periodic sums. modulus must be positive; count is nonnegative. modsum normalizes
 * negative offset/slope. Intermediate products must fit the implementation's integer arithmetic.
 * Time: $\log(m)$, with a large constant.
 * Status: Tested for all |k|,|c|,to,m <= 50, and on kattis:aladin
 * Usage: ll sum=modsum(4,1,2,5); // (1+3+0+2)=6
 * ull floors=divsum(4,1,2,5); // (0+0+1+1)=2
 */
#pragma once
ull sumsq(ull count) { return count / 2 * ((count - 1) | 1); }
/// ^ written in a weird way to deal with overflows correctly

ull divsum(ull count, ull offset, ull slope, ull modulus) {
  ull answer = slope / modulus * sumsq(count) + offset / modulus * count;
  slope %= modulus;
  offset %= modulus;
  if (!slope) return answer;
  ull nextCount = (count * slope + offset) / modulus;
  return answer + (count - 1) * nextCount - divsum(nextCount, modulus - 1 - offset, modulus, slope);
}
ll modsum(ull count, ll offset, ll slope, ll modulus) {
  offset = ((offset % modulus) + modulus) % modulus;
  slope = ((slope % modulus) + modulus) % modulus;
  return count * offset + slope * sumsq(count) - modulus * divsum(count, offset, slope, modulus);
}

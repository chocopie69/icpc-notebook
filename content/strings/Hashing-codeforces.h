/**
 * Author: Simon Lindholm
 * Date: 2015-03-15
 * License: CC0
 * Source: own work
 * Description: Various self-explanatory methods for string hashing.
 * Use on Codeforces, which lacks 64-bit support and where solutions can be hacked.
 * Status: stress-tested
 */
#pragma once

static int C; // initialized below
// Arithmetic mod two primes and 2^32 simultaneously.
// "typedef uint64_t HashValue;" instead if Thue-Morse does not apply.
template <int M, class B> struct ModHash {
  int x;
  B b;
  ModHash(int x = 0) : x(x), b(x) {}
  ModHash(int x, B b) : x(x), b(b) {}
  ModHash operator+(ModHash o) {
    int y = x + o.x;
    return {y - (y >= M) * M, b + o.b};
  }
  ModHash operator-(ModHash o) {
    int y = x - o.x;
    return {y + (y < 0) * M, b - o.b};
  }
  ModHash operator*(ModHash o) { return {(int)(1LL * x * o.x % M), b * o.b}; }
  explicit operator ull() const { return x ^ (ull)b << 21; }
  bool operator==(ModHash o) const { return (ull) * this == (ull)o; }
  bool operator<(ModHash o) const { return (ull) * this < (ull)o; }
};
typedef ModHash<1000000007, ModHash<1000000009, unsigned>> HashValue;
struct RollingHash {
  vector<HashValue> prefixHash, power;
  RollingHash(string &text) : prefixHash(sz(text) + 1), power(prefixHash) {
    power[0] = 1;
    for (int i = 0; i < (sz(text)); ++i)
      prefixHash[i + 1] = prefixHash[i] * C + text[i], power[i + 1] = power[i] * C;
  }
  HashValue hashInterval(int l, int r) { // hash [l, r)
    return prefixHash[r] - prefixHash[l] * power[r - l];
  }
};
vector<HashValue> getHashes(string &text, int length) {
  if (sz(text) < length) return {};
  HashValue hash = 0, power = 1;
  for (int i = 0; i < (length); ++i) hash = hash * C + text[i], power = power * C;
  vector<HashValue> hashes = {hash};
  for (int i = length; i < (sz(text)); ++i)
    hashes.push_back(hash = hash * C + text[i] - power * text[i - length]);
  return hashes;
}
HashValue hashString(string &s) {
  HashValue hash{};
  for (char c : s) hash = hash * C + c;
  return hash;
}
#include <sys/time.h>
int main() {
  timeval tp;
  gettimeofday(&tp, 0);
  C = (int)tp.tv_usec; // (less than modulo)
  assert((ull)(HashValue(1) * 2 + 1 - 3) == 0);
  // ...
}

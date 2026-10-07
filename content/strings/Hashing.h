/**
 * Author: Simon Lindholm
 * Date: 2015-03-15
 * License: CC0
 * Source: own work
 * Description: Self-explanatory methods for string hashing.
 * Status: stress-tested
 */
#pragma once
// Arithmetic mod 2^64-1. 2x slower than mod 2^64 and more
// code, but works on evil test data (e.g. Thue-Morse, where
// ABBA... and BAAB... of length 2^10 hash the same mod 2^64).
// "typedef ull HashValue;" instead if you think test data is random,
// or work mod 10^9+7 if the Birthday paradox is not a problem.
struct HashValue {
  ull x;
  HashValue(ull x = 0) : x(x) {}
  HashValue operator+(HashValue o) { return x + o.x + (x + o.x < x); }
  HashValue operator-(HashValue o) { return *this + ~o.x; }
  HashValue operator*(HashValue o) {
    auto m = (__uint128_t)x * o.x;
    return HashValue((ull)m) + (ull)(m >> 64);
  }
  ull get() const { return x + !~x; }
  bool operator==(HashValue o) const { return get() == o.get(); }
  bool operator<(HashValue o) const { return get() < o.get(); }
};
static const HashValue C = (ll)1e11 + 3; // (order ~ 3e9; random also ok)
struct RollingHash {
  vector<HashValue> ha, pw;
  RollingHash(string &str) : ha(sz(str) + 1), pw(ha) {
    pw[0] = 1;
    for (int i = 0; i < (sz(str)); ++i)
      ha[i + 1] = ha[i] * C + str[i],
             pw[i + 1] = pw[i] * C;
  }
  HashValue hashInterval(int a, int b) { // hash [a, b)
    return ha[b] - ha[a] * pw[b - a];
  }
};
vector<HashValue> getHashes(string &str, int length) {
  if (sz(str) < length) return {};
  HashValue h = 0, pw = 1;
  for (int i = 0; i < (length); ++i)
    h = h * C + str[i], pw = pw * C;
  vector<HashValue> ret = {h};
  for (int i = length; i < (sz(str)); ++i) {
    ret.push_back(h = h * C + str[i] - pw * str[i - length]);
  }
  return ret;
}
HashValue hashString(string &s) {
  HashValue h{};
  for (char c : s) h = h * C + c;
  return h;
}

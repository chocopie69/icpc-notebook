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
template <int M, class B>
struct ModHash {
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
#include <sys/time.h>
int main() {
  timeval tp;
  gettimeofday(&tp, 0);
  C = (int)tp.tv_usec; // (less than modulo)
  assert((ull)(HashValue(1) * 2 + 1 - 3) == 0);
  // ...
}

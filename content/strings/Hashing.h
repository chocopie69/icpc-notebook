/**
 * Author: Personal Code::Blocks abbreviation, adapted
 * Description: Polynomial prefix hash with base 31 and modulus 1000000003. getHash uses 1-based
 * inclusive [l,r], although the input string is normal 0-based. Compare equal-length substrings.
 * A single fixed hash can collide: use KMP for exact matching, or two independent moduli when
 * adversarial collisions matter. No updates; this version expects lowercase a..z.
 * Usage: StringHash hash("ababa");
 * bool same=hash.getHash(1,3)==hash.getHash(3,5); // both "aba"
 * StringHash pattern("aba");
 * bool match=hash.getHash(1,3)==pattern.getHash(1,3);
 * Time: $O(N)$ construction and memory; $O(1)$ per substring hash.
 */
#pragma once
struct StringHash {
  static constexpr ll base = 31, mod = 1000000003;
  vector<ll> power, prefix;
  StringHash(const string &text) : power(sz(text) + 1), prefix(sz(text) + 1) {
    power[0] = 1;
    for (int i = 1; i <= sz(text); i++) {
      power[i] = power[i - 1] * base % mod;
      prefix[i] = (prefix[i - 1] * base + text[i - 1] - 'a' + 1) % mod;
    }
  }
  ll getHash(int l, int r) const {
    return (prefix[r] - prefix[l - 1] * power[r - l + 1] % mod + mod) % mod;
  }
};

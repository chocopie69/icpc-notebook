/**
 * Author: Personal notebook; SplitMix64 by Sebastiano Vigna
 * Source: https://prng.di.unimi.it/splitmix64.c
 * Description: Integer-key hash map with a randomized SplitMix64 hash. A per-run seed makes
 * fixed collision attacks harder to construct; collisions can still occur and worst-case
 * time is not guaranteed. Collisions affect speed, not key equality or correctness.
 * The hash and container are separate: the same CustomHash works with unordered\_map.
 * GNU PBDS is required only for the gp hash table below. Values are int; change to ll for
 * larger counts. hashMap[key] inserts zero if absent; find does not insert. Iteration is unsorted.
 * Usage: hashMap[42]++;
 * auto it=hashMap.find(42);
 * if (it!=hashMap.end()) cout << it->second;
 * hashMap.clear(); // between test cases
 * // Standard-library alternative:
 * unordered_map<ll,int,CustomHash> freq;
 * freq.reserve(2*n); // optional, reduces rehashing
 * Time: Expected $O(1)$ per insert/find/erase; worst-case $O(N)$ per operation.
 */
#pragma once
#include <ext/pb_ds/assoc_container.hpp> /** keep-include */
struct CustomHash {
  static ull mix(ull x) {
    // Fixed constants mix all 64 bits; unsigned overflow is intentional.
    x += 0x9e3779b97f4a7c15ULL;
    x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9ULL;
    x = (x ^ (x >> 27)) * 0x94d049bb133111ebULL;
    return x ^ (x >> 31);
  }
  size_t operator()(ll key) const {
    static const ull seed = chrono::steady_clock::now().time_since_epoch().count();
    return mix((ull)key + seed);
  }
};
__gnu_pbds::gp_hash_table<ll, int, CustomHash> hashMap;

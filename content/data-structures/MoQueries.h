/**
 * Author: Simon Lindholm
 * Date: 2019-12-28
 * License: CC0
 * Source: https://github.com/hoke-t/tamu-kactl/blob/master/content/data-structures/MoQueries.h; https://codeforces.com/blog/entry/61203
 * Description: Offline queries on 0-based, inclusive intervals $[l,r]$ (both endpoints included).
 * Fill in add, del and calc; start their state empty. side is 0 for the left
 * end and 1 for the right end. No array updates between queries.
 * Answers are returned in input order. For tree paths, see MoTree.h instead.
 * Useful when an answer can be maintained as either interval end moves one position. Sorting
 * queries by precomputed Hilbert keys reduces pointer travel; no block size is needed.
 * add/del update shared state and calc reads it. Fill the placeholders before using this
 * template. Requires 0<=l<=r<N; l=r queries a single element.
 * Usage: auto answers=mo({{0,2},{1,4},{2,2}});
 * // Fill add/del/calc; [0,2] means positions 0,1,2; [2,2] means only position 2.
 * Time: $O(Q\log Q+Q\log(N+1)+N\sqrt Q)$ with $O(1)$ add/del/calc; $O(Q+\log(N+1))$ memory excluding custom state.
 */
#pragma once
#include "HilbertOrder.h"
void add(int pos, int side) { ... } // add a[pos]
void del(int pos, int side) { ... } // remove a[pos]
int calc(){...}                     // current answer
vector<int> mo(vector<pii> queries) {
  int left = 0, right = -1; // Initially empty; maintained interval is [left,right].
  int maxEndpoint = 0, bits = 0;
  for (auto [l, r] : queries) maxEndpoint = max(maxEndpoint, r);
  while ((1LL << bits) <= maxEndpoint) bits++;
  vector<int> order(sz(queries)), answers(sz(queries));
  vector<ull> key(sz(queries));
  for (int i = 0; i < sz(queries); i++)
    key[i] = hilbertOrder(queries[i].first, queries[i].second, bits);
  iota(all(order), 0);
  sort(all(order), [&](int queryA, int queryB) { return key[queryA] < key[queryB]; });
  for (int queryId : order) {
    auto [queryLeft, queryRight] = queries[queryId];
    while (left > queryLeft) add(--left, 0);
    while (right < queryRight) add(++right, 1);
    while (left < queryLeft) del(left++, 0);
    while (right > queryRight) del(right--, 1);
    answers[queryId] = calc();
  }
  return answers;
}

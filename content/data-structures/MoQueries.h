/**
 * Author: Simon Lindholm, gepardo; adapted to the notebook style
 * Date: 2019-12-28
 * License: CC0
 * Source: https://github.com/hoke-t/tamu-kactl/blob/master/content/data-structures/MoQueries.h; https://codeforces.com/blog/entry/61203
 * Description: Offline inclusive queries [l,r] on a[1..N]; require 1<=l<=r<=N.
 * Fill add/del/calc and begin with empty state; side=0/1 means left/right endpoint.
 * No value updates between queries; answers follow input order. The included Hilbert helper
 * precomputes sorting keys without block-size tuning. bits covers every endpoint; int indices
 * fit ull keys. A single-element query has l=r. Compress values for frequency arrays;
 * queries mixed with updates need Mo with a time dimension.
 * Usage: auto answers=mo({{1,3},{2,5},{3,3}});
 * // Fill add/del/calc; [1,3] means positions 1,2,3; [3,3] means only position 3.
 * Time: $O(Q\log Q+Q\log(N+1)+N\sqrt Q)$ with $O(1)$ add/del/calc; $O(Q+\log(N+1))$ memory excluding custom state.
 */
#pragma once
inline ull hilbertOrder(int x, int y, int bits, int rotation = 0) {
  if (bits == 0) return 0;
  int half = 1 << (bits - 1);
  int quadrant = x < half ? (y < half ? 0 : 3) : (y < half ? 1 : 2);
  quadrant = (quadrant + rotation) & 3;
  const int turn[4] = {3, 0, 0, 1};
  int nextRotation = (rotation + turn[quadrant]) & 3;
  ull squareSize = 1ULL << (2 * bits - 2);
  ull offset = hilbertOrder(x & (half - 1), y & (half - 1), bits - 1, nextRotation);
  if (quadrant == 0 || quadrant == 3) offset = squareSize - offset - 1;
  return quadrant * squareSize + offset;
}
void add(int pos, int side) { ... } // add a[pos]
void del(int pos, int side) { ... } // remove a[pos]
int calc(){...}                     // current answer
vector<int> mo(vector<pii> queries) {
  int left = 1, right = 0; // Initially empty; maintained interval is [left,right].
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

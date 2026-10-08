/**
 * Author: Simon Lindholm
 * Date: 2019-12-28
 * License: CC0
 * Source: https://github.com/hoke-t/tamu-kactl/blob/master/content/data-structures/MoQueries.h
 * Description: Offline queries on 0-based, half-open intervals $[l,r)$.
 * Fill in add, del and calc; start their state empty. side is 0 for the left
 * end and 1 for the right end. No array updates between queries.
 * Answers are returned in input order. For tree paths, see MoTree.h instead.
 * Useful when an answer can be maintained as either interval end moves one position. Sorting
 * queries reduces pointer travel; add/del update shared state and calc reads it. Choose
 * blockSize near N/sqrt(Q), at least 1. Fill the placeholders for the chosen statistic before
 * using this template.
 * Usage: auto answers=mo({{0,3},{1,5}},350);
 * // Fill add/del/calc; [0,3) means positions 0,1,2.
 * Time: $O(Q\log Q + N\sqrt Q)$ with $O(1)$ add/del/calc and blockSize about $N/\sqrt Q$.
 */
#pragma once
void add(int pos, int side) { ... } // add a[pos]
void del(int pos, int side) { ... } // remove a[pos]
int calc(){...}                     // current answer
vector<int> mo(vector<pii> queries, int blockSize = 350) {
  int left = 0, right = 0;
  vector<int> order(sz(queries)), answers(sz(queries));
  iota(all(order), 0);
  sort(all(order), [&](int queryA, int queryB) {
    int blockA = queries[queryA].first / blockSize;
    int blockB = queries[queryB].first / blockSize;
    if (blockA != blockB) return blockA < blockB;
    if (blockA & 1) return queries[queryA].second > queries[queryB].second;
    return queries[queryA].second < queries[queryB].second;
  });
  for (int queryId : order) {
    auto [queryLeft, queryRight] = queries[queryId];
    while (left > queryLeft) add(--left, 0);
    while (right < queryRight) add(right++, 1);
    while (left < queryLeft) del(left++, 0);
    while (right > queryRight) del(--right, 1);
    answers[queryId] = calc();
  }
  return answers;
}

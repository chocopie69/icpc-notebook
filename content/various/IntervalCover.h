/**
 * Author: Johan Sannemo
 * License: CC0
 * Description: Compute indices of smallest set of intervals covering another interval.
 * Intervals should be [inclusive, exclusive). To support [inclusive, inclusive],
 * change (A) to add \texttt{|| chosen.empty()}. Returns empty set on failure (or if G is empty).
 * A greedy sweep chooses the eligible interval reaching farthest right. Output is 0-based
 * indices into the original input, not its sorted order. Minimizes interval count rather than
 * total cost. Adjacent intervals may meet at an endpoint; a gap causes failure. Check whether
 * the target is empty before interpreting an empty result as failure.
 * Time: O(N \log N)
 * Status: Tested on kattis:intervalcover
 * Usage: vector<pii> intervals={{0,3},{2,5},{0,1}};
 * auto chosen=cover(pii(0,5),intervals); // {0,1}
 */
#pragma once
template <class T> vector<int> cover(pair<T, T> target, vector<pair<T, T>> intervals) {
  vector<int> order(sz(intervals)), chosen;
  iota(all(order), 0);
  sort(all(order), [&](int a, int b) { return intervals[a] < intervals[b]; });
  T coveredTo = target.first;
  int nextInterval = 0;
  while (coveredTo < target.second) { // (A)
    pair<T, int> farthest = make_pair(coveredTo, -1);
    while (nextInterval < sz(intervals) && intervals[order[nextInterval]].first <= coveredTo) {
      farthest =
          max(farthest, make_pair(intervals[order[nextInterval]].second, order[nextInterval]));
      nextInterval++;
    }
    if (farthest.second == -1) return {};
    coveredTo = farthest.first;
    chosen.push_back(farthest.second);
  }
  return chosen;
}

/**
 * Author: Personal notebook
 * Source: https://cp-algorithms.com/data_structures/stack_queue_modification.html
 * Description: Minimum and maximum of every length-k window in a static array. Deques store
 * indices; remove expired indices from the front and dominated values from the back. Equal
 * values keep the newest index. For 1<=k<=n, result[i] describes 0-based [i,i+k-1]. Invalid k
 * returns two empty vectors. Use a monotonic stack instead for nearest smaller/greater queries.
 * Usage: vector<int> a={4,2,2,5,1};
 * auto [minimum,maximum]=slidingWindowMinMax(a,3);
 * // minimum={2,2,1}, maximum={4,5,5}
 * // For a 1-based array, remove the unused index 0 before calling.
 * Time: $O(N)$ time; $O(k)$ deque memory plus $O(N)$ output.
 */
#pragma once
template <class T> pair<vector<T>, vector<T>> slidingWindowMinMax(const vector<T> &a, int k) {
  vector<T> minimum, maximum;
  if (k <= 0 || k > sz(a)) return {minimum, maximum};
  deque<int> minQ, maxQ;
  for (int i = 0; i < sz(a); i++) {
    while (!minQ.empty() && minQ.front() <= i - k) minQ.pop_front();
    while (!maxQ.empty() && maxQ.front() <= i - k) maxQ.pop_front();
    while (!minQ.empty() && a[minQ.back()] >= a[i]) minQ.pop_back();
    while (!maxQ.empty() && a[maxQ.back()] <= a[i]) maxQ.pop_back();
    minQ.push_back(i);
    maxQ.push_back(i);
    if (i >= k - 1) {
      minimum.push_back(a[minQ.front()]);
      maximum.push_back(a[maxQ.front()]);
    }
  }
  return {minimum, maximum};
}

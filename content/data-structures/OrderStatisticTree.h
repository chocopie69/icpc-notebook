/**
 * Author: Simon Lindholm
 * Date: 2016-03-22
 * License: CC0
 * Source: hacKIT, NWERC 2015
 * Description: GNU PBDS set with 0-based ranks. order\_of\_key(x) counts elements <x; find\_by\_order(k)
 * returns an iterator, or end if absent. For duplicates use (value,uniqueId), not less\_equal.
 * Replace null\_type for a map. join requires disjoint ordered key ranges, not interleaved sets.
 * Time: O(\log N)
 * Usage: OrderedSet<int> s; s.insert(8); s.insert(10);
 * int smaller=s.order_of_key(10); // 1
 * int kth=*s.find_by_order(0); // 8
 */
#pragma once

#include <bits/extc++.h> /** keep-include */
using namespace __gnu_pbds;

template <class T>
using OrderedSet = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
void example() {
  OrderedSet<int> ordered, other;
  ordered.insert(8);
  auto inserted = ordered.insert(10).first;
  assert(inserted == ordered.lower_bound(9));
  assert(ordered.order_of_key(10) == 1);
  assert(ordered.order_of_key(11) == 2);
  assert(*ordered.find_by_order(0) == 8);
  ordered.join(other); // assuming T < T2 or T > T2, merge t2 into t
}

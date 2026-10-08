/**
 * Author: Chen Xing
 * Date: 2009-10-13
 * License: CC0
 * Source: N/A
 * Description: Flow algorithm with guaranteed complexity $O(VE^2)$. To get edge flow values, compare
 * capacities before and after, and take the positive values only.
 * Status: stress-tested
 */
#pragma once
template <class T> T edmondsKarp(vector<unordered_map<int, T>> &graph, int source, int sink) {
  assert(source != sink);
  T flow = 0;
  vector<int> parent(sz(graph)), queue = parent;

  for (;;) {
    fill(all(parent), -1);
    parent[source] = 0;
    int queueSize = 1;
    queue[0] = source;

    for (int i = 0; i < (queueSize); ++i) {
      int u = queue[i];
      for (auto e : graph[u]) {
        if (parent[e.first] == -1 && e.second > 0) {
          parent[e.first] = u;
          queue[queueSize++] = e.first;
          if (e.first == sink) goto out;
        }
      }
    }
    return flow;
  out:
    T pushed = numeric_limits<T>::max();
    for (int v = sink; v != source; v = parent[v]) pushed = min(pushed, graph[parent[v]][v]);

    flow += pushed;
    for (int v = sink; v != source; v = parent[v]) {
      int prev = parent[v];
      if ((graph[prev][v] -= pushed) <= 0) graph[prev].erase(v);
      graph[v][prev] += pushed;
    }
  }
}

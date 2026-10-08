/**
 * Author: Simon Lindholm
 * Date: 2017-04-17
 * License: CC0
 * Source: folklore
 * Description: Finds all biconnected components in an undirected graph, and
 *  runs a callback for the edges in each. In a biconnected component there
 *  are at least two internally disjoint paths between any two nodes (a cycle
 *  exists through them). Note that a node can be in several components. An
 *  edge which is not in a component is a bridge, i.e., not part of any cycle.
 * Assign each undirected edge a unique ID and store that same ID at both endpoints, including
 * parallel edges. The callback receives edge IDs, not vertex IDs. This implementation omits
 * bridges; process the marked bridge branch separately if needed. Clear edgeStack and reset
 * timer before a new graph.
 * Usage: adj.assign(n,{}); int id=0;
 * // For each (u,v), add (v,id) and (u,id) at both ends, then id++.
 * timer=0; edgeStack.clear();
 * bicomps([](const vector<int> &ids) { ... });
 * Time: O(E + V)
 * Status: tested during MIPT ICPC Workshop 2017
 */
#pragma once

vector<int> num, edgeStack;
vector<vector<pii>> adj;
int timer;
template <class F> int dfs(int u, int parentEdge, F &visitComponent) {
  int entryTime = num[u] = ++timer, low = entryTime;
  for (auto [v, edgeId] : adj[u])
    if (edgeId != parentEdge) {
      if (num[v]) {
        low = min(low, num[v]);
        if (num[v] < entryTime) edgeStack.push_back(edgeId);
      } else {
        int stackStart = sz(edgeStack);
        int childLow = dfs(v, edgeId, visitComponent);
        low = min(low, childLow);
        if (childLow == entryTime) {
          edgeStack.push_back(edgeId);
          visitComponent(vector<int>(edgeStack.begin() + stackStart, edgeStack.end()));
          edgeStack.resize(stackStart);
        } else if (childLow < entryTime)
          edgeStack.push_back(edgeId);
        else { /* e is a bridge */
        }
      }
    }
  return low;
}
template <class F> void bicomps(F visitComponent) {
  num.assign(sz(adj), 0);
  for (int i = 0; i < (sz(adj)); ++i)
    if (!num[i]) dfs(i, -1, visitComponent);
}

/**
 * Author: Personal notebook, adapted from Cao Thanh Hau / VNOI Wiki
 * Source: https://wiki.vnoi.info/algo/graph-theory/centroid-decomposition.md
 * Description: Path-counting skeleton; example counts unordered distinct pairs at exactly k edges.
 * Customize the CHANGE blocks: state/storage, initial/extended state, query/insert/reset.
 * Query a whole child BEFORE inserting it; only the centroid and earlier children are stored.
 * Reset touched entries after each centroid. Recurse to count paths inside one child.
 * For vertex sums, match k+value[centroid]-state; for edge sums adapt adjacency/state extension.
 * Length ranges need a Fenwick range query; XOR needs mask states. Prune only if deeper states
 * cannot become valid again. Root defaults to 1 (pass 0 if needed); use a fresh object per run.
 * Single-vertex paths are excluded. Recursive DFS may have linear stack depth.
 * Usage: CentroidDecomposition tree(adj,k); // adj: vector<vector<int>>, both directions
 * ll answer=tree.solve(); // 1-based vertices; exact-k example
 * // For vertices 0..n-1: tree.solve(0).
 * // Change State, initialState/extendState, queryState/addState/clearStates for another problem.
 * // Example: a chain of 4 vertices with k=2 has answer 2.
 * Time: $O(N\log N)$ with constant-time state operations; $O(N)$ auxiliary memory.
 */
#pragma once
struct CentroidDecomposition {
  // CHANGE 1: state, parameters, storage.
  using State = int; // Depth; change to ll, mask, or struct.
  int k;
  vector<vector<int>> adj; // Adapt for weighted edges.
  vector<int> subtreeSize, freq, touched;
  vector<bool> removed;
  CentroidDecomposition(const vector<vector<int>> &graph, int length)
      : k(length), adj(graph), subtreeSize(sz(graph)), freq(sz(graph)), removed(sz(graph)) {}
  // CHANGE 2: initial state and extension.
  State initialState(int centroid) { return 0; }
  State extendState(State state, int v) { return state + 1; }
  // CHANGE 3: match, insert, reset.
  ll queryState(State state, int centroid) {
    ll need = (ll)k - state; // Vertex sums: k + value[centroid] - state.
    return 0 <= need && need < sz(freq) ? freq[need] : 0;
  }
  void addState(State state) {
    if (!freq[state]) touched.push_back(state);
    freq[state]++;
  }
  void clearStates() {
    for (int state : touched) freq[state] = 0;
    touched.clear(); // Map: clear; Fenwick: undo updates.
  }
  int countChild(int u, int parent) {
    subtreeSize[u] = 1;
    for (int v : adj[u])
      if (v != parent && !removed[v]) subtreeSize[u] += countChild(v, u);
    return subtreeSize[u];
  }
  int findCentroid(int u, int parent, int total) {
    for (int v : adj[u])
      if (v != parent && !removed[v] && subtreeSize[v] > total / 2)
        return findCentroid(v, u, total);
    return u;
  }
  void collectStates(int u, int parent, State state, vector<State> &states) {
    states.push_back(state);
    for (int v : adj[u])
      if (v != parent && !removed[v]) collectStates(v, u, extendState(state, v), states);
  }
  ll countPaths(int centroid) {
    ll answer = 0;
    State start = initialState(centroid);
    addState(start); // Include the centroid.
    for (int v : adj[centroid]) {
      if (removed[v]) continue;
      vector<State> states;
      collectStates(v, centroid, extendState(start, v), states);
      for (State state : states) answer += queryState(state, centroid);
      for (State state : states) addState(state); // Keep these two loops separate!
    }
    clearStates(); // Reset before recursion.
    return answer;
  }
  ll solve(int u = 1) {
    int total = countChild(u, -1);
    int centroid = findCentroid(u, -1, total);
    ll answer = countPaths(centroid);
    removed[centroid] = true;
    for (int v : adj[centroid])
      if (!removed[v]) answer += solve(v);
    return answer;
  }
};

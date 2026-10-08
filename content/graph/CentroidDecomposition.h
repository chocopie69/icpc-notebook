/**
 * Author: Personal notebook, adapted from Cao Thanh Hau / VNOI Wiki
 * Source: https://wiki.vnoi.info/algo/graph-theory/centroid-decomposition.md
 * Description: Path-counting skeleton; the working example counts unordered distinct-vertex
 * pairs at exactly k edges in an unweighted tree. Customize the CHANGE blocks; keep subtree
 * sizes, centroid search, and solve unchanged. Each state describes a centroid-to-vertex path.
 * Query a whole child BEFORE inserting it: stored states belong only to the centroid and
 * earlier children. Paths inside one child are counted recursively, so no path is counted twice.
 * For edge sums, use weighted adjacency and ll states; XOR uses xor instead of addition.
 * Length ranges replace frequency lookup with a Fenwick range query (an extra log factor).
 * Vertex sums include the centroid in both states: match against k+value[centroid]-state.
 * Reset the accumulator after EACH centroid; clear only touched entries or undo its updates.
 * This version collects all states without pruning. Prune only if your path state cannot
 * become valid again deeper in the tree (negative weights invalidate sum-based pruning).
 * Root defaults to 1; pass 0 for 0-based vertices. Adjacency is preserved; construct a fresh
 * object for each run. DFS may use linear stack depth. Single-vertex paths are excluded;
 * count them separately if needed. Ordered pairs need separate treatment for directional rules.
 * Usage: CentroidDecomposition tree(adj,k); // adj: vector<vector<int>>, both directions
 * ll answer=tree.solve(); // 1-based vertices; exact-k example
 * // For vertices 0..n-1: tree.solve(0).
 * // Change State, initialState/extendState, queryState/addState/clearStates for another problem.
 * // Example: a chain of 4 vertices with k=2 has answer 2.
 * Time: $O(N\log N)$ with constant-time state operations; $O(N)$ auxiliary memory.
 */
#pragma once
struct CentroidDecomposition {
  // CHANGE 1: problem parameters, path state, and accumulator storage.
  using State = int; // Example: depth. Use ll, a mask, or a struct if needed.
  int k;
  vector<vector<int>> adj; // For edge weights, also adapt the neighbor loops.
  vector<int> subtreeSize, freq, touched;
  vector<bool> removed;
  CentroidDecomposition(const vector<vector<int>> &graph, int length)
      : k(length), adj(graph), subtreeSize(sz(graph)), freq(sz(graph)), removed(sz(graph)) {}
  // CHANGE 2: state at the centroid, then how one more vertex/edge extends it.
  State initialState(int centroid) { return 0; }
  State extendState(State state, int v) { return state + 1; }
  // CHANGE 3: match against earlier children, insert a state, and reset storage.
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
    touched.clear(); // For a map: clear it; for a Fenwick tree: undo updates.
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
    // Optional problem-specific pruning goes here; none is needed for correctness.
    states.push_back(state);
    for (int v : adj[u])
      if (v != parent && !removed[v]) collectStates(v, u, extendState(state, v), states);
  }
  ll countPaths(int centroid) {
    ll answer = 0;
    State start = initialState(centroid);
    addState(start); // Allows paths with one endpoint at the centroid.
    for (int v : adj[centroid]) {
      if (removed[v]) continue;
      vector<State> states;
      collectStates(v, centroid, extendState(start, v), states);
      for (State state : states) answer += queryState(state, centroid);
      for (State state : states) addState(state); // Keep these two loops separate!
    }
    clearStates(); // Must happen before recursing into any component.
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

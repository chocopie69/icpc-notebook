/**
 * Author: Simon Lindholm, adapted to the notebook style
 * License: CC0
 * Source: https://github.com/kth-competitive-programming/kactl/blob/main/content/data-structures/MoQueries.h
 * Description: KACTL's direct endpoint walking with alternating DFS order and snake sorting.
 * Inclusive vertex paths on 1..N; adj has size N+1, both edge directions, and default root=1.
 * Fill add/del/calc; side=0/1 selects the endpoint. Begin with empty state; reset before reuse.
 * No value updates between queries. rank becomes a climb stack after sorting; no LCA table is needed.
 * Both endpoints are included, even for (u,u). Answers follow input order. DFS stack can be linear.
 * For edge values, process the traversed edge in step and omit add(root,0), keeping active[root].
 * Block size is near N/sqrt(Q); adjust if needed.
 * Usage: // Fill add/del/calc for the desired statistic (e.g. distinct vertex values).
 * vector<pii> queries={{u,v},{u,u}};
 * auto answers=moTree(queries,adj); // 1-based vertices, both path endpoints included
 * // For another root in 1..N: moTree(queries,adj,root).
 * // Compress values first if callbacks index a frequency array by value.
 * Time: $O(N+Q\log Q+N\sqrt Q)$ with $O(1)$ add/del/calc; $O(N+Q)$ memory.
 */
#pragma once
void add(int u, int side) { ... } // Add vertex u at this end of the path.
void del(int u, int side) { ... } // Remove vertex u at this end of the path.
int calc(){...}                   // Current path answer.
vector<int> moTree(const vector<pii> &queries, const vector<vector<int>> &adj, int root = 1) {
  if (queries.empty()) return {};
  int n = sz(adj) - 1, timer = 1, pos[2] = {root, root};
  int blockSize = max(1, (int)(n / sqrt(sz(queries))));
  vector<int> order(sz(queries)), answers(sz(queries));
  vector<int> rank(n + 1), tin(n + 1), tout(n + 1), parent(n + 1);
  vector<bool> active(n + 1);
  add(root, 0);
  active[root] = true;
  auto dfs = [&](int u, int p, bool oddDepth, auto &self) -> void {
    parent[u] = p;
    tin[u] = timer;
    if (oddDepth) rank[u] = timer++;
    for (int v : adj[u])
      if (v != p) self(v, u, !oddDepth, self);
    if (!oddDepth) rank[u] = timer++;
    tout[u] = timer - 1; // Inclusive subtree bounds in the alternating DFS order.
  };
  dfs(root, 0, false, dfs);
  iota(all(order), 0);
  sort(all(order), [&](int a, int b) {
    int blockA = rank[queries[a].first] / blockSize;
    int blockB = rank[queries[b].first] / blockSize;
    if (blockA != blockB) return blockA < blockB;
    int rightA = rank[queries[a].second], rightB = rank[queries[b].second];
    return blockA & 1 ? rightA > rightB : rightA < rightB;
  });
  for (int id : order) {
    for (int side = 0; side < 2; side++) {
      int &current = pos[side];
      int target = side == 0 ? queries[id].first : queries[id].second;
      int climbed = 0;
      auto step = [&](int next) {
        if (active[next]) {
          del(current, side);
          active[current] = false;
        } else {
          add(next, side);
          active[next] = true;
        }
        current = next;
      };
      // Climb target until it is an ancestor of current; save its descent path.
      while (!(tin[target] <= tin[current] && tout[current] <= tout[target])) {
        rank[++climbed] = target; // DFS ranks are no longer needed after sorting.
        target = parent[target];
      }
      while (current != target) step(parent[current]);
      while (climbed) step(rank[climbed--]);
    }
    answers[id] = calc();
  }
  return answers;
}

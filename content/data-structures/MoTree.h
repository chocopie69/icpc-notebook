/**
 * Author: 404 Not Found
 * Date: 2026-10-08
 * Source: animeshf, https://codeforces.com/blog/entry/43230; https://ideone.com/6NVoPD
 * Description: Offline distinct-value counts on tree paths, using the example's
 * arrays, DFS, LCA, vertex toggle and block-sorted queries. Vertices are 1..n;
 * compress value[u] to 1..n first. Set MAXN and LOG for the largest input.
 * Each vertex appears twice in euler: at tin[u] and tout[u]. A vertex contributes
 * only when it occurs once in the current interval. For tin[u] <= tin[v],
 * w = LCA(u,v): use [tin[u],tin[v]] if w=u; otherwise use [tout[u],tin[v]]
 * and toggle w separately before and after reading the answer.
 * Change check and the answer assignment for another statistic on the active
 * vertices. This does not preserve the order of vertices along the path.
 * Usage:
 *  // Fill n, adj[1..n], and compressed value[1..n].
 *  timer = 0; dfs(1, 1); blockSize = max(1, (int)sqrt(timer));
 *  vector<Query> queries;
 *  queries.push_back(makeQuery(u, v, sz(queries))); // repeat for each path
 *  auto answers = compute(queries); // answers in input order
 *  // For another test case, clear adj[1..n] before adding its edges.
 * Time: $O(N\log N+Q\log Q+(N+Q)\sqrt N)$; $O(N\log N+Q)$ memory.
 */
#pragma once
const int MAXN = 100005, LOG = 20;
int n, timer, blockSize, distinct;
int value[MAXN], h[MAXN], up[MAXN][LOG];
int tin[MAXN], tout[MAXN], euler[2 * MAXN], freq[MAXN];
bool active[MAXN];
vector<int> adj[MAXN];
struct Query {
  int left, right, id, extraLca;
  bool operator<(const Query &other) const {
    int block = (left - 1) / blockSize, otherBlock = (other.left - 1) / blockSize;
    if (block != otherBlock) return block < otherBlock;
    return right < other.right;
  }
};
void dfs(int u, int parent) {
  tin[u] = ++timer;
  euler[timer] = u;
  up[u][0] = parent;
  for (int k = 1; k < LOG; k++) up[u][k] = up[up[u][k - 1]][k - 1];
  for (int v : adj[u])
    if (v != parent) {
      h[v] = h[u] + 1;
      dfs(v, u);
    }
  tout[u] = ++timer;
  euler[timer] = u;
}
int lca(int u, int v) {
  if (h[u] < h[v]) swap(u, v);
  for (int k = LOG - 1; k >= 0; k--)
    if (h[u] - (1 << k) >= h[v]) u = up[u][k];
  if (u == v) return u;
  for (int k = LOG - 1; k >= 0; k--)
    if (up[u][k] != up[v][k]) {
      u = up[u][k];
      v = up[v][k];
    }
  return up[u][0];
}
Query makeQuery(int u, int v, int id) {
  if (tin[u] > tin[v]) swap(u, v);
  int w = lca(u, v);
  if (w == u) return {tin[u], tin[v], id, 0};
  return {tout[u], tin[v], id, w};
}
void check(int u) {
  if (active[u]) {
    if (--freq[value[u]] == 0) distinct--;
  } else {
    if (freq[value[u]]++ == 0) distinct++;
  }
  active[u] ^= 1;
}
vector<int> compute(vector<Query> &queries) {
  sort(all(queries));
  fill(freq, freq + n + 1, 0);
  fill(active, active + n + 1, false);
  distinct = 0;
  int left = 1, right = 0;
  vector<int> answers(sz(queries));
  for (Query query : queries) {
    while (left > query.left) check(euler[--left]);
    while (right < query.right) check(euler[++right]);
    while (left < query.left) check(euler[left++]);
    while (right > query.right) check(euler[right--]);
    if (query.extraLca) check(query.extraLca);
    answers[query.id] = distinct;
    if (query.extraLca) check(query.extraLca);
  }
  return answers;
}

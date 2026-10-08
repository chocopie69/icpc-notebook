/**
 * Author: Unknown
 * Description: DAG skeleton with vertices 1..n: define maxN and read n,m first. The stack pops vertices in
 * topological order; ans[u] is the 1-based position of u. A detected cycle prints an error and
 * exits. Clear g and visited between cases.
 * Usage: // Define maxN and read n,m before the shown main body.
 * // Reset visited and clear g for another test case.
 */
int visited[maxN], ans[maxN];
vector<int> g[maxN];
stack<int> topo; // reversed order of topo;
void dfs(int u) {
  visited[u] = 1;
  for (auto v : g[u]) {
    if (visited[v] == 1) {
      cout << "Error: graph contains a cycle";
      exit(0);
    }
    if (!visited[v]) dfs(v);
  }
  topo.push(u);
  visited[u] = 2;
}
int main() {
  while (m--) {
    int u, v; cin >> u >> v;
    g[u].push_back(v);
  }
  for (int i = 1; i <= n; ++i)
    if (!visited[i]) dfs(i);
}

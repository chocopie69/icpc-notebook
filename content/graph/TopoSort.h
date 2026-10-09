/**
 * Author: Unknown
 * Description: DAG skeleton with vertices 1..n: define maxN and read n,m first. The stack pops vertices in
 * topological order; fill ans[u] with its position when popping (the skeleton does not fill it).
 * A detected cycle prints an error and
 * exits. Clear g, visited and topo between cases. To handle cycles without exiting,
 * return a failure flag; deep graphs need iterative DFS or Kahn's algorithm.
 * Usage: // Define maxN and read n,m before the shown main body.
 * // Pop topo to obtain the order and assign ans[u]=++position.
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

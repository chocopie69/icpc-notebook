#include "../utilities/template.h"
const int maxN=100;
int n,m;
#define main snippetMain
#include "../../content/graph/TopoSort.h"
#undef main
int main(int argc, char **) {
  if (argc>1) { // test-notebook.py checks the error from this cycle.
    g[1]={2}; g[2]={1}; dfs(1);
    assert(false);
  }
  mt19937 rng(814);
  for (int it=0; it<50000; ++it) {
    n=rng()%30;
    vector<int> order(n);
    iota(all(order),1); shuffle(all(order),rng);
    for (int i=0; i<maxN; ++i) g[i].clear(), visited[i]=ans[i]=0;
    while (!topo.empty()) topo.pop();
    for (int i=0; i<n; ++i) for (int j=i+1; j<n; ++j)
      if (rng()%4==0) g[order[i]].push_back(order[j]);
    for (int u=1; u<=n; ++u) if (!visited[u]) dfs(u);
    int pos=0;
    while (!topo.empty()) {
      int u=topo.top(); topo.pop();
      assert(ans[u]==0); ans[u]=++pos;
    }
    assert(pos==n);
    for (int u=1; u<=n; ++u) for (int v:g[u]) assert(ans[u]<ans[v]);
  }
  cout << "Tests passed!\n";
}

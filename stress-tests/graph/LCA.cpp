#include "../utilities/template.h"
#include "../../content/graph/LCA.h"
#include "../../content/graph/LCAEuler.h"
#include "../../content/graph/BinaryLifting.h"
#include "../../content/graph/CompressTree.h"
int main() {
  mt19937 rng(814);
  for (int it = 0; it < 2000; ++it) {
    int n = 1 + rng()%100, base = it%2, root = base + rng()%n;
    vector<vector<int>> adj(n+base);
    vector<vector<pll>> weighted(n+base);
    for (int v = base+1; v < n+base; ++v) {
      int u = base + rng()%(v-base), w = (int)(rng()%2001)-1000;
      adj[u].push_back(v); adj[v].push_back(u);
      weighted[u].push_back({v,w}); weighted[v].push_back({u,w});
    }
    vector<int> par(n+base), depth(n+base);
    vector<ll> dist(n+base);
    auto dfs = [&](auto &self, int u, int p) -> void {
      par[u] = p;
      for (auto [v,w] : weighted[u]) if (v != p) {
        depth[v] = depth[u]+1; dist[v] = dist[u]+w;
        self(self, (int)v, u);
      }
    };
    dfs(dfs, root, root);
    auto up = buildAncestorTable(par);
    LCA binary(adj,root), weights(weighted,root);
    LCAEuler euler(adj,root);
    for (int q = 0; q < 200; ++q) {
      int u = base+rng()%n, v = base+rng()%n, a=u, b=v;
      while (depth[a] > depth[b]) a=par[a];
      while (depth[b] > depth[a]) b=par[b];
      while (a != b) a=par[a], b=par[b];
      assert(binary.lca(u,v)==a && weights.lca(u,v)==a && euler.lca(u,v)==a);
      assert(lca(up,depth,u,v)==a);
      assert(binary.distance(u,v)==depth[u]+depth[v]-2*depth[a]);
      assert(euler.distance(u,v)==binary.distance(u,v));
      assert(weights.weightedDistance(u,v)==dist[u]+dist[v]-2*dist[a]);
      int steps=rng()%(depth[u]+1), ancestor=u;
      for (int k=0; k<steps; ++k) ancestor=par[ancestor];
      assert(binary.goUp(u,steps)==ancestor && goUp(up,u,steps)==ancestor);
    }
    vector<int> subset;
    for (int q=0; q<20; ++q) subset.push_back(base+rng()%n);
    auto compressed=compressTree(binary,subset);
    set<int> vertices(subset.begin(),subset.end());
    for (int u:subset) for (int v:subset) vertices.insert(binary.lca(u,v));
    assert(compressed.size()==vertices.size());
    for (int i=0; i<sz(compressed); ++i) {
      int u=compressed[i].second, p=compressed[i].first;
      assert(vertices.erase(u)==1);
      assert(p>=0 && p<=i);
      assert(binary.lca(u,compressed[p].second)==compressed[p].second);
      if (i) {
        int nearest=root, best=-1;
        for (auto [unused,v]:compressed)
          if (v!=u && binary.lca(u,v)==v && depth[v]>best) nearest=v,best=depth[v];
        assert(compressed[p].second==nearest);
      }
    }
    assert(vertices.empty() && compressTree(binary,{}).empty());
  }
  cout << "Tests passed!\n";
}

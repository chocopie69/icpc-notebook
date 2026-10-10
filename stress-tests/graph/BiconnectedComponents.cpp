#include "../utilities/template.h"
#include "../../content/graph/BiconnectedComponents.h"
int main() {
  mt19937 rng(814);
  for(int it=0;it<5000;++it) {
    int n=1+rng()%7, m=n==1 ? 0 : rng()%13;
    adj.assign(n,{}); vector<pii> edges;
    for(int id=0;id<m;++id) {
      int u=rng()%n,v=rng()%(n-1); if(v>=u) ++v;
      edges.push_back({u,v}); adj[u].push_back({v,id}); adj[v].push_back({u,id});
    }
    vector<int> parent(m), cyclic(m); iota(all(parent),0);
    auto find=[&](auto &self,int e)->int { return parent[e]==e ? e : parent[e]=self(self,parent[e]); };
    vector<int> path; vector<bool> seen(n);
    // Brute force all simple cycles, including length-two parallel-edge cycles.
    for(int start=0;start<n;++start) {
      auto walk=[&](auto &self,int u,int previousEdge)->void {
        seen[u]=true;
        for(auto [v,id]:adj[u]) if(id!=previousEdge) {
          if(v==start && !path.empty()) {
            cyclic[id]=1;
            for(int e:path) cyclic[e]=1,parent[find(find,e)]=find(find,id);
          } else if(!seen[v]) { path.push_back(id); self(self,v,id); path.pop_back(); }
        }
        seen[u]=false;
      };
      walk(walk,start,-1);
    }
    vector<int> component(m,-1); int count=0; timer=0; edgeStack.clear();
    bicomps([&](const vector<int>& ids) {
      assert(!ids.empty());
      for(int id:ids) { assert(component[id]<0); component[id]=count; }
      ++count;
    });
    for(int e=0;e<m;++e) {
      assert((component[e]>=0)==(cyclic[e]!=0));
      for(int f=0;f<m;++f) if(cyclic[e] && cyclic[f])
        assert((component[e]==component[f])==(find(find,e)==find(find,f)));
    }
    assert(edgeStack.empty());
  }
  cout << "Tests passed!\n";
}

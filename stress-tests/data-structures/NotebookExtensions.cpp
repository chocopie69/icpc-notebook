#include "../utilities/template.h"
#include "../../content/data-structures/IterativeSegmentTree.h"
#include "../../content/data-structures/PersistentSegmentTree.h"
#include "../../content/data-structures/PersistentFenwick.h"
#include "../../content/data-structures/SlidingWindow.h"
#include "../../content/data-structures/UnionFindRollback.h"
#include "../../content/graph/CentroidDecomposition.h"
#include "../../content/graph/Dial.h"
#include "../../content/strings/Trie.h"
#include "../../content/various/SOSDP.h"
int main() {
  mt19937 rng(814);
  for (int it=0; it<1000; ++it) {
    int n=1+rng()%30;
    IterativeSegTree seg(n,-7);
    PersistentSegTree persistent(n,-7);
    vector<vector<ll>> versions(1,vector<ll>(n+1,-7));
    vector<int> a(n+1,-7);
    for (int q=0; q<100; ++q) {
      int pos=1+rng()%n, value=(int)(rng()%2001)-1000, ver=rng()%versions.size();
      seg.update(pos,value); a[pos]=value;
      auto next=versions[ver]; next[pos]=value;
      assert(persistent.update(ver,pos,value)==sz(versions)); versions.push_back(next);
      int l=1+rng()%n,r=1+rng()%n; if(l>r) swap(l,r);
      assert(seg.query(l,r)==*max_element(a.begin()+l,a.begin()+r+1));
      ver=rng()%versions.size();
      assert(persistent.query(ver,l,r)==*max_element(versions[ver].begin()+l,versions[ver].begin()+r+1));
      assert(seg.query(r,l-1)==INT_MIN && persistent.query(ver,r,l-1)==LLONG_MIN);
    }
    a.erase(a.begin());
    for(int k=0; k<=n+1; ++k) {
      auto [mn,mx]=slidingWindowMinMax(a,k);
      if(k<1 || k>n) { assert(mn.empty() && mx.empty()); continue; }
      assert(sz(mn)==n-k+1 && mn.size()==mx.size());
      for(int l=0; l+k<=n; ++l) {
        assert(mn[l]==*min_element(a.begin()+l,a.begin()+l+k));
        assert(mx[l]==*max_element(a.begin()+l,a.begin()+l+k));
      }
    }
    int bits=rng()%8;
    vector<ll> freq(1<<bits),sub,super;
    for(ll &x:freq) x=(int)(rng()%21)-10;
    sub=super=freq; subsetSOS(sub); supersetSOS(super);
    for(int mask=0; mask<sz(freq); ++mask) {
      ll s=0,t=0;
      for(int other=0; other<sz(freq); ++other) {
        if((mask&other)==other) s+=freq[other];
        if((mask&other)==mask) t+=freq[other];
      }
      assert(sub[mask]==s && super[mask]==t);
    }
    subsetSOS(sub,true); supersetSOS(super,true); assert(sub==freq && super==freq);
    int K=rng()%8, source=rng()%n;
    vector<vector<pii>> graph(n);
    for(int q=0; q<100; ++q) graph[rng()%n].push_back({(int)(rng()%n),(int)(rng()%(K+1))});
    auto actual=dial(graph,source,K);
    vector<ll> expected(n,LLONG_MAX); expected[source]=0;
    for(int round=0; round<n; ++round) for(int u=0; u<n; ++u)
      if(expected[u]!=LLONG_MAX) for(auto [v,w]:graph[u]) expected[v]=min(expected[v],expected[u]+w);
    assert(actual==expected);
    vector<vector<int>> tree(n+1);
    for(int v=2; v<=n; ++v) {
      int p=1+rng()%(v-1); tree[p].push_back(v); tree[v].push_back(p);
    }
    int k=rng()%(n+2); ll pairs=0;
    for(int s=1; s<=n; ++s) {
      vector<int> d(n+1,-1); queue<int> q; q.push(s); d[s]=0;
      while(!q.empty()) {
        int u=q.front(); q.pop();
        for(int v:tree[u]) if(d[v]<0) d[v]=d[u]+1,q.push(v);
      }
      for(int t=s+1; t<=n; ++t) pairs+=d[t]==k;
    }
    CentroidDecomposition centroid(tree,k); assert(centroid.solve()==pairs);
    RollbackDSU uf(n);
    vector<pair<int,vector<int>>> saved;
    for(int q=0; q<100; ++q) {
      if(rng()%3==0) saved.push_back({uf.time(),uf.parentOrSize});
      else if(!saved.empty() && rng()%3==0) {
        auto [time,state]=saved.back(); saved.pop_back();
        uf.rollback(time); assert(uf.parentOrSize==state);
      } else uf.join(rng()%n,rng()%n);
      for(int u=0;u<n;++u) {
        int count=0; for(int v=0;v<n;++v) count+=uf.find(u)==uf.find(v);
        assert(uf.size(u)==count);
      }
    }
  }
  for(int it=0; it<100; ++it) {
    PersistentFenwick2D bit(5,6);
    vector<array<int,4>> events; int time=-10;
    for(int q=0; q<200; ++q) {
      time+=rng()%3;
      int x=1+rng()%5,y=1+rng()%6,delta=(int)(rng()%101)-50;
      bit.update(x,y,delta,time); events.push_back({time,x,y,delta});
      int t=(int)(rng()%(time+21))-20, x1=1+rng()%5,x2=1+rng()%5,y1=1+rng()%6,y2=1+rng()%6;
      if(x1>x2) swap(x1,x2); if(y1>y2) swap(y1,y2);
      ll expected=0;
      for(auto [when,a,b,value]:events) if(when<=t && x1<=a && a<=x2 && y1<=b && b<=y2) expected+=value;
      assert(bit.query(t,x1,y1,x2,y2)==expected);
    }
  }
  Trie trie; multiset<string> strings;
  for(int q=0; q<20000; ++q) {
    string s; int len=rng()%7;
    for(int i=0;i<len;++i) s+=char('a'+rng()%3);
    if(rng()%2) { trie.addString(s); strings.insert(s); }
    else { trie.deleteString(s); auto p=strings.find(s); if(p!=strings.end()) strings.erase(p); }
    assert(trie.findString(s)==(strings.count(s)>0));
    int count=0; for(const auto &word:strings) count+=word.compare(0,s.size(),s)==0;
    assert(trie.countPrefix(s)==count && trie.countPrefix("")==sz(strings));
  }
  cout << "Tests passed!\n";
}

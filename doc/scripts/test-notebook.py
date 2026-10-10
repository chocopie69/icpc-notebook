"""Compile the selected notebook with the personal template and test Mo callbacks.
Run from any directory: python3 doc/scripts/test-notebook.py
Requires g++ and Python 3; generated drivers/logs stay in build/notebook-checks.
"""
from concurrent.futures import ThreadPoolExecutor
from pathlib import Path
import re
import subprocess
import sys

root = Path(__file__).resolve().parents[2]
out = root / 'build/notebook-checks'
out.mkdir(parents=True, exist_ok=True)
base = (root / 'content/contest/template.cpp').read_text().split('int main()')[0]
template=out/'personal-template.hpp'
template.write_text(base)
subprocess.run(['g++','-std=c++17','-Wall','-Wextra','-Wconversion','-x','c++-header',str(template)], check=True)
base='#include "'+template.as_posix()+'"\n'
all_headers = {p.name: p for p in (root / 'content').rglob('*.h')}
chapters = re.findall(r'^\s*\\kactlchapter\{([^}]+)\}', (root/'content/kactl.tex').read_text(), re.M)
names = []
for chapter in chapters:
    names += re.findall(r'^\s*\\kactlimport(?:\[[^]]*\])?\{([^}]+\.h)\}', (root/f'content/{chapter}/chapter.tex').read_text(), re.M)
if '--all' in sys.argv:
    # These excluded snippets need their own configuration or are edit recipes.
    # Their algorithm implementations are exercised by the existing stress suite.
    excluded={'Hashing-codeforces.h','NumberTheoreticTransform.h','Unrolling.h'}
    names=sorted(set(all_headers)-excluded)

def source(name):
    path = all_headers[name]
    code = path.read_text().replace('#pragma once', '')
    code = re.sub(r'#include "([^"]+)"', lambda m: '#include "'+(path.parent/m[1]).resolve().as_posix()+'"' if (path.parent/m[1]).exists() else m[0], code)
    return code

def compile_one(name):
    if name == 'SolveLinear2.h':
        return name, 'RECIPE', 'Edit recipe; checked separately from callable snippets.'
    code = source(name)
    prefix = base
    if name in ('MoQueries.h', 'MoTree.h'):
        code = code.replace('{ ... }', '{}').replace('{...}', '{return 0;}')
    elif name == 'TopoSort.h':
        prefix += 'const int maxN=100; int n,m;\n'
    elif name == 'DivideAndConquerDP.h':
        prefix += 'vector<vector<ll>> dp; vector<pair<int,ll>> answer;\n'
    elif name == 'ModInverse.h':
        code = 'const ll mod=1000000007, LIM=100; void setup() {\n'+code+'\n}\n'
    driver = out/(name+'.cpp')
    driver.write_text(prefix+code)
    result = subprocess.run(['g++','-std=c++17','-Wall','-Wextra','-Wconversion','-fsyntax-only',str(driver)], text=True, capture_output=True)
    (out/(name+'.log')).write_text(result.stdout+result.stderr)
    return name, 'PASS' if result.returncode==0 else 'FAIL', result.stderr

with ThreadPoolExecutor(max_workers=4) as pool:
    results = list(pool.map(compile_one, names))
failed = [r for r in results if r[1]=='FAIL']
print(f'{len(results)-len(failed)-1}/{len(results)-1} headers compile with documented setup; one explicit edit recipe.', flush=True)
for name,status,log in failed:
    print(name,log)
if failed:
    sys.exit(1)

mo_code = base + r'''
namespace ArrayMo {
vector<int> values, active; int sum=0;
void add(int u,int) { assert(!active[u]); active[u]=1; sum+=values[u]; }
void del(int u,int) { assert(active[u]); active[u]=0; sum-=values[u]; }
int calc() { return sum; }
'''
mo_code += re.sub(r'void add\([^\n]+\nvoid del\([^\n]+\nint calc\([^\n]+\n', '', source('MoQueries.h'))
mo_code += r'''
}
namespace TreeMo {
vector<int> values, active; deque<int> path; int sum=0;
void add(int u,int side) {
  assert(!active[u]); active[u]=1; sum+=values[u];
  if(side==0) path.push_front(u); else path.push_back(u);
}
void del(int u,int side) {
  assert(active[u]); active[u]=0; sum-=values[u];
  if(side==0) { assert(path.front()==u); path.pop_front(); }
  else { assert(path.back()==u); path.pop_back(); }
}
int calc() { return sum; }
'''
mo_code += re.sub(r'void add\([^\n]+\nvoid del\([^\n]+\nint calc\([^\n]+\n', '', source('MoTree.h'))
mo_code += r'''
}
int main() {
  mt19937 rng(814);
  for(int it=0;it<2000;++it) {
    int n=1+rng()%80, Q=rng()%100;
    vector<pii> queries; vector<int> expected;
    ArrayMo::values.assign(n+1,0); ArrayMo::active.assign(n+1,0); ArrayMo::sum=0;
    for(int i=1;i<=n;++i) ArrayMo::values[i]=(int)(rng()%201)-100;
    for(int q=0;q<Q;++q) {
      int l=1+rng()%n,r=1+rng()%n; if(l>r) swap(l,r);
      queries.push_back({l,r}); expected.push_back(accumulate(ArrayMo::values.begin()+l,ArrayMo::values.begin()+r+1,0));
    }
    assert(ArrayMo::mo(queries)==expected);
    TreeMo::values=ArrayMo::values; TreeMo::active.assign(n+1,0); TreeMo::sum=0; TreeMo::path.clear();
    vector<vector<int>> adj(n+1);
    for(int v=2;v<=n;++v) {
      int p=1+rng()%(v-1); adj[p].push_back(v); adj[v].push_back(p);
    }
    queries.clear(); expected.clear();
    for(int q=0;q<Q;++q) {
      int u=1+rng()%n,v=1+rng()%n; queries.push_back({u,v});
      vector<int> parent(n+1,-1); queue<int> bfs; bfs.push(u); parent[u]=u;
      while(!bfs.empty()) { int a=bfs.front(); bfs.pop(); for(int b:adj[a]) if(parent[b]<0) parent[b]=a,bfs.push(b); }
      int sum=TreeMo::values[u]; for(int b=v;b!=u;b=parent[b]) sum+=TreeMo::values[b];
      expected.push_back(sum);
    }
    assert(TreeMo::moTree(queries,adj,1+rng()%n)==expected);
  }
  cout << "Personal array/tree Mo: 2000 random cases passed\n";
}
'''
driver=out/'mo.cpp'
driver.write_text(mo_code)
binary=out/('mo.exe' if sys.platform=='win32' else 'mo')
subprocess.run(['g++','-std=c++17','-O2',str(driver),'-o',str(binary)], check=True)
subprocess.run([str(binary)], check=True, timeout=60)

def run_driver(name, code, args=()):
    driver=out/(name+'.cpp')
    driver.write_text(base+code)
    binary=out/(name+('.exe' if sys.platform=='win32' else ''))
    subprocess.run(['g++','-std=c++17','-O2',str(driver),'-o',str(binary)], check=True)
    return subprocess.run([str(binary),*args], check=True, capture_output=True, text=True, timeout=60)

# Apply the published SolveLinear2 edit recipe to the real SolveLinear implementation.
linear=source('SolveLinear.h')
old='for (int j = i + 1; j < (n); ++j) {'
assert old in linear
linear=linear.replace(old,'for (int j = 0; j < n; ++j) if (j != i) {')
start=linear.index('  solution.assign(m, 0);')
end=linear.index('  return rank;',start)
recipe=source('SolveLinear2.h')
recipe=recipe[recipe.index('    solution.assign(m, undefined);'):]
linear=linear[:start]+recipe+'\n'+linear[end:]
checks=r'''
int main() {
  auto check=[](vector<vd> a,vd b,vd expected,int rank) {
    vd x(expected.size()); assert(solveLinear(a,b,x)==rank);
    if(rank==-1) return;
    for(int i=0;i<sz(x);++i)
      assert(isnan(expected[i]) ? isnan(x[i]) : fabs(x[i]-expected[i])<1e-8);
  };
  double nan=numeric_limits<double>::quiet_NaN();
  check({{1,1},{1,-1}},{3,1},{2,1},2);
  check({{0,1,0},{1,0,1}},{7,3},{nan,7,nan},2);
  check({{0,0,1},{1,1,0}},{4,3},{nan,nan,4},2);
  check({{1,0},{2,0}},{3,6},{3,nan},1);
  check({{1,0},{2,0}},{3,7},{nan,nan},-1);
  check({{0,0}},{0},{nan,nan},0);
  check({}, {}, {nan,nan},0);
  cout << "SolveLinear2 recipe: unique/free/inconsistent cases passed\n";
}
'''
print(run_driver('linear-recipe','const double undefined=numeric_limits<double>::quiet_NaN();\n'+linear+checks).stdout,end='')

dp=r'''
vector<vector<ll>> dp;
vector<pair<int,ll>> answer;
'''+source('DivideAndConquerDP.h')+r'''
int main() {
  int n=200;
  dp.assign(n+1,vector<ll>(n+1)); answer.resize(n+1);
  for(int i=1;i<=n;++i) for(int j=0;j<i;++j) dp[i][j]=5000000000LL+(i-2*j)*(i-2*j);
  DivideConquerDP solver; solver.solve(1,n+1);
  for(int i=1;i<=n;++i) {
    pair<ll,int> best={LLONG_MAX,-1};
    for(int j=0;j<i;++j) best=min(best,make_pair(dp[i][j],j));
    assert(answer[i]==make_pair(best.second,best.first));
  }
  cout << "Divide-and-conquer DP: 64-bit values and tie-breaking passed\n";
}
'''
print(run_driver('dp',dp).stdout,end='')

topo='const int maxN=100; int n,m;\n#define main snippetMain\n'+source('TopoSort.h')+r'''
#undef main
int main() { g[1]={2}; g[2]={1}; dfs(1); assert(false); }
'''
assert 'graph contains a cycle' in run_driver('topo-cycle',topo).stdout
print('Topological-sort cycle detection passed')

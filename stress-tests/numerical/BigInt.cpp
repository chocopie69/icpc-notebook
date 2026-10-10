#include "../../content/number-theory/BigInt.h"
#include <cassert>
#include <algorithm>
#include <climits>
#include <random>
#include <sstream>

string decimal(__int128 x) {
  bool neg=x<0;
  if (neg) x=-x;
  string s;
  do { s+=char('0'+x%10); x/=10; } while (x);
  if (neg) s+='-';
  reverse(s.begin(),s.end());
  return s;
}
string decimal(const BigInt &x) { ostringstream out; out<<x; return out.str(); }
void check(long long x, long long y) {
  BigInt a=x,b=y;
  assert(decimal(a+b)==decimal((__int128)x+y));
  assert(decimal(a-b)==decimal((__int128)x-y));
  assert(decimal(a*b)==decimal((__int128)x*y));
  assert(a.cmp(b)==((x>y)-(x<y)));
  if (y) {
    auto [q,r]=divmod(a,b);
    assert(decimal(q)==decimal((__int128)x/y));
    assert(decimal(r)==decimal((__int128)x%y));
    assert(q*b+r==a && r.abs()<b.abs());
  }
}
int main(int argc, char **) {
  if (argc>1) { // Python's independent large-integer oracle
    BigInt a,b;
    while (cin>>a>>b) {
      auto [q,r]=divmod(a,b);
      cout<<a+b<<' '<<a-b<<' '<<a*b<<' '<<q<<' '<<r<<'\n';
    }
    return 0;
  }
  vector<long long> edge={LLONG_MIN,LLONG_MAX,0,1,-1,999999999,
    1000000000,1000000001,1000000000000000000LL};
  for (auto x:edge) for (auto y:edge) check(x,y);
  mt19937_64 rng(814);
  for (int it=0;it<30000;++it) {
    long long x=rng()>>1,y=rng()>>1;
    check(it&1 ? -x : x,it&2 ? -y : y);
  }
  for (int n:{1,9,18,100,500,1500}) {
    BigInt a(string(n,'9')),b(string("1")+string(n/2,'0')+"1");
    for (int sign:{-1,1}) {
      auto [q,r]=divmod(a*sign,b);
      assert(q*b+r==a*sign && r.abs().cmpAbs(b)<0);
    }
    assert((a+b)-b==a && (a*b)/b==a);
  }
  istringstream in("-000 +00042 -999999999999999999999");
  BigInt a,b,c; in>>a>>b>>c;
  assert(decimal(a)=="0" && decimal(b)=="42");
  assert(decimal(c)=="-999999999999999999999");
  cout<<"Tests passed!"<<endl;
}

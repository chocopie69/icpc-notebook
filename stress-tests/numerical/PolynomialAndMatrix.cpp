#include "../utilities/template.h"
#include "../../content/numerical/PolyRoots.h"
#include "../../content/numerical/PolyInterpolate.h"
#include "../../content/numerical/MatrixInverse.h"
#include "../../content/data-structures/Matrix.h"
int main() {
  mt19937 rng(814);
  for(int it=0;it<2000;++it) {
    double a=(int)(rng()%11)-5, b=a+1+rng()%5;
    Poly p{{a*b,-a-b,1}}, d=p,q=p;
    d.diff(); q.divroot(a);
    auto roots=polyRoots(p,-20,20);
    assert(roots.size()==2 && fabs(roots[0]-a)<1e-7 && fabs(roots[1]-b)<1e-7);
    assert(fabs(q.coeff[0]+b)<1e-9 && q.coeff[1]==1);
    for(int x=-10;x<=10;++x) {
      assert(fabs(p(x)-(x-a)*(x-b))<1e-9);
      assert(fabs(d(x)-(2*x-a-b))<1e-9);
    }
    auto coefficients=interpolate({-1,0,2},{p(-1),p(0),p(2)},3);
    for(int i=0;i<3;++i) assert(fabs(coefficients[i]-p.coeff[i])<1e-9);
    assert(interpolate({3},{7},1)==vector<double>{7});
    int n=1+rng()%8;
    vector<vector<double>> matrix(n,vector<double>(n));
    for(int i=0;i<n;++i) for(int j=0;j<n;++j) matrix[i][j]=(int)(rng()%7)-3;
    for(int i=0;i<n;++i) matrix[i][i]+=4*n;
    auto inverse=matrix; assert(matInv(inverse)==n);
    for(int i=0;i<n;++i) for(int j=0;j<n;++j) {
      double value=0; for(int k=0;k<n;++k) value+=matrix[i][k]*inverse[k][j];
      assert(fabs(value-(i==j))<1e-8);
    }
  }
  vector<vector<double>> singular={{1,2},{2,4}}; assert(matInv(singular)==1);
  Matrix<ll,2> fib; fib.data={{{1,1},{1,0}}};
  auto identity=fib^0; assert(identity.data[0][0]==1 && identity.data[0][1]==0);
  ll a=0,b=1;
  for(int k=0;k<60;++k) {
    array<ll,2> state={1,0}; auto result=(fib^k)*state;
    assert(result[0]==b && result[1]==a); ll next=a+b; a=b; b=next;
  }
  cout << "Tests passed!\n";
}

/**
 * Author: Compact adaptation of ngthanhtrung23's BigInt
 * Source: https://github.com/ngthanhtrung23/ACM_Notebook_new/blob/master/Math/bigint.h
 * Description: Signed big integers with +, -, *, /, \%, <, ==, != and decimal I/O. Standard C++
 * only; use for exact counts beyond ll. Input: valid decimal strings with optional sign.
 * Division truncates toward zero; remainder has dividend's sign. Divisor must be nonzero.
 * Decimal schoolbook arithmetic favors short code over speed; best for hundreds of digits.
 * Time: O(n+m) addition/comparison; O((n+1)(m+1)) multiplication/division, O(n+m) space;
 * n,m are decimal digit counts. divmod computes quotient/remainder together.
 * Usage: BigInt a(string("12345678901234567890")), b=7;
 * cout << a+b << ' ' << a-b << ' ' << a*b << endl;
 * auto [q,r]=divmod(a,b); assert(q*b+r==a); // also a/b, a%b; cin >> a
 * Status: Stress-tested against Python integers
 */
#pragma once
#include <iostream> /// keep-include
#include <string> /// keep-include
#include <utility> /// keep-include
#include <vector> /// keep-include
#include <cassert> /// keep-include
using namespace std;
struct Big {
  vector<int> a; // decimal digits, least significant first; empty means zero
  int sign=1;
  Big(long long v=0) : Big(to_string(v)) {}
  explicit Big(const string &s) {
    int p=!s.empty() && (s[0]=='-' || s[0]=='+');
    sign=!s.empty() && s[0]=='-' ? -1 : 1;
    for (int i=(int)s.size(); i>p;) a.push_back(s[--i]-'0');
    trim(); }
  void trim() {
    while (!a.empty() && !a.back()) a.pop_back();
    if (a.empty()) sign=1; }
  Big abs() const { Big r=*this; r.sign=1; return r; }
  Big operator-() const {
    Big r=*this; if (!a.empty()) r.sign=-sign; return r; }
  int cmpAbs(const Big &v) const {
    if (a.size()!=v.a.size()) return a.size()<v.a.size() ? -1 : 1;
    for (int i=(int)a.size(); i--;)
      if (a[i]!=v.a[i]) return a[i]<v.a[i] ? -1 : 1;
    return 0; }
  int cmp(const Big &v) const {
    return sign!=v.sign ? (sign<v.sign ? -1 : 1) : sign*cmpAbs(v);
  }
  bool operator<(const Big &v) const { return cmp(v)<0; }
  bool operator==(const Big &v) const { return cmp(v)==0; }
  bool operator!=(const Big &v) const { return cmp(v)!=0; }
  Big operator+(const Big &v) const {
    if (cmpAbs(v)<0) return v+*this;
    Big r=*this; int carry=0, same=sign==v.sign;
    for (int i=0; i<(int)a.size() || carry; ++i) {
      if (i==(int)r.a.size()) r.a.push_back(0);
      int d=r.a[i]+carry;
      if (i<(int)v.a.size()) d+=(same ? 1 : -1)*v.a[i];
      carry=same ? d/10 : -(d<0); r.a[i]=(d+10)%10;
    } r.trim(); return r; }
  Big operator-(const Big &v) const { return *this+(-v); }
  Big operator*(const Big &v) const {
    Big r; r.sign=sign*v.sign; r.a.resize(a.size()+v.a.size());
    for (int i=0; i<(int)a.size(); ++i)
      for (int j=0,carry=0; j<(int)v.a.size() || carry; ++j) {
        int d=r.a[i+j]+carry+(j<(int)v.a.size() ? a[i]*v.a[j] : 0);
        r.a[i+j]=d%10; carry=d/10;
      } r.trim(); return r; }
  friend pair<Big,Big> divmod(const Big &x, const Big &y) {
    assert(!y.a.empty()); Big b=y.abs(),q,r;
    q.a.resize(x.a.size());
    for (int i=(int)x.a.size(); i--;) {
      r.a.insert(r.a.begin(),x.a[i]); r.trim(); // r=r*10+x[i]
      while (r.cmpAbs(b)>=0) r=r-b, ++q.a[i]; // at most 9 subtractions per digit
    } q.sign=x.sign*y.sign; r.sign=x.sign; q.trim(); r.trim(); return {q,r};
  }
  Big operator/(const Big &v) const { return divmod(*this,v).first; }
  Big operator%(const Big &v) const { return divmod(*this,v).second; }
  friend istream &operator>>(istream &in, Big &v) {
    string s; if (in>>s) v=Big(s); return in; }
  friend ostream &operator<<(ostream &out, const Big &v) {
    if (v.sign<0) out << '-';
    if (v.a.empty()) out << '0';
    for (int i=(int)v.a.size(); i--;) out << v.a[i];
    return out; }
};
using BigInt = Big;

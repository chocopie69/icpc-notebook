/**
 * Author: Simon Lindholm
 * Date: 2017-04-20
 * License: CC0
 * Source: own work
 * Description: Add lines of the form slope*x+intercept, and query maximum values at points x.
 *  Useful for dynamic programming (``convex hull trick'').
 * Lines and queries may arrive in any order; x, slopes and intercepts are integers. Call add
 * before the first query. For minimum queries, insert (-slope,-intercept) and negate the result.
 * Products, differences and intersection arithmetic must fit ll. lastX marks the final integer x
 * where a line is best.
 * Time: O(\log N)
 * Status: stress-tested
 * Usage: CHT hull; hull.add(2,3); hull.add(-1,7);
 * ll best=hull.query(4); // max(11,3)=11
 */
#pragma once
struct CHTLine {
  mutable ll slope, intercept, lastX;
  bool operator<(const CHTLine &other) const { return slope < other.slope; }
  bool operator<(ll x) const { return lastX < x; }
};
struct CHT : multiset<CHTLine, less<>> {
  // (for doubles, use inf = 1/.0, div(a,b) = a/b)
  static const ll inf = LLONG_MAX;
  ll div(ll a, ll b) { // floored division
    return a / b - ((a ^ b) < 0 && a % b);
  }
  bool isect(iterator line, iterator nextLine) {
    if (nextLine == end()) return line->lastX = inf, 0;
    if (line->slope == nextLine->slope)
      line->lastX = line->intercept > nextLine->intercept ? inf : -inf;
    else
      line->lastX = div(nextLine->intercept - line->intercept, line->slope - nextLine->slope);
    return line->lastX >= nextLine->lastX;
  }
  void add(ll slope, ll intercept) {
    auto nextLine = insert({slope, intercept, 0}), line = nextLine++, prevLine = line;
    while (isect(line, nextLine)) nextLine = erase(nextLine);
    if (prevLine != begin() && isect(--prevLine, line)) isect(prevLine, line = erase(line));
    while ((line = prevLine) != begin() && (--prevLine)->lastX >= line->lastX)
      isect(prevLine, erase(line));
  }
  ll query(ll x) {
    assert(!empty());
    auto line = *lower_bound(x);
    return line.slope * x + line.intercept;
  }
};

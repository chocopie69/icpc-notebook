/**
 * Author: Ulf Lundstrom
 * Date: 2009-02-26
 * License: CC0
 * Source: My head with inspiration from tinyKACTL
 * Description: Use Point<ll> for exact integer cross/dot products and Point<double> for fractional
 * coordinates. p.cross(a,b) means (a-p) cross (b-p). perp rotates 90 degrees CCW; rotate takes
 * radians. unit/normal require a nonzero vector and floating T; integer division/rotation truncate.
 * Large integer predicates need wider cross/dot intermediates, e.g. \_\_int128.
 * Status: Works fine, used a lot
 * Usage: Point<ll> a(0,0), b(2,0), c(0,3);
 * ll cross=a.cross(b,c); // 6, c is left of a->b
 */
#pragma once
template <class T> int sgn(T x) { return (x > 0) - (x < 0); }
template <class T> struct Point {
  typedef Point P;
  T x, y;
  explicit Point(T x = 0, T y = 0) : x(x), y(y) {}
  bool operator<(P other) const { return tie(x, y) < tie(other.x, other.y); }
  bool operator==(P other) const { return tie(x, y) == tie(other.x, other.y); }
  P operator+(P other) const { return P(x + other.x, y + other.y); }
  P operator-(P other) const { return P(x - other.x, y - other.y); }
  P operator*(T scale) const { return P(x * scale, y * scale); }
  P operator/(T scale) const { return P(x / scale, y / scale); }
  T dot(P other) const { return x * other.x + y * other.y; }
  T cross(P other) const { return x * other.y - y * other.x; }
  T cross(P a, P b) const { return (a - *this).cross(b - *this); }
  T dist2() const { return x * x + y * y; }
  double dist() const { return sqrt((double)dist2()); }
  // angle to x-axis in interval [-pi, pi]
  double angle() const { return atan2(y, x); }
  P unit() const { return *this / dist(); } // makes dist()=1
  P perp() const { return P(-y, x); }       // rotates +90 degrees
  P normal() const { return perp().unit(); }
  // returns point rotated angle radians ccw around the origin
  P rotate(double angle) const {
    return P(x * cos(angle) - y * sin(angle), x * sin(angle) + y * cos(angle));
  }
  friend ostream &operator<<(ostream &os, P other) {
    return os << "(" << other.x << "," << other.y << ")";
  }
};

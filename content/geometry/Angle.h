/**
 * Author: Simon Lindholm
 * Date: 2015-01-31
 * License: CC0
 * Source: me
 * Description: A class for ordering angles (as represented by int points and
 *  a number of rotations around the origin). Useful for rotational sweeping.
 *  Sometimes also represents points or vectors.
 * Use nonzero integer direction vectors to sort events without atan2. turns distinguishes
 * directions after complete rotations. t90/t180/t360 rotate counterclockwise; segmentAngles
 * returns the shorter angular interval covering two directions. Intermediate integer products
 * must fit their types. angleDiff needs wider coordinate fields/products for large coordinates.
 * Equal directions need a distance/event-type tie-break if sweep order matters.
 * Usage: vector<Angle> directions={{1,0},{0,1},{-1,0}};
 * sort(all(directions));
 * auto quarterTurn=Angle(1,0).t90();
 * Status: Used, works well
 */
#pragma once
struct Angle {
  int x, y;
  int turns;
  Angle(int x, int y, int turns = 0) : x(x), y(y), turns(turns) {}
  Angle operator-(Angle b) const { return {x - b.x, y - b.y, turns}; }
  int half() const {
    assert(x || y);
    return y < 0 || (y == 0 && x < 0);
  }
  Angle t90() const { return {-y, x, turns + (half() && x >= 0)}; }
  Angle t180() const { return {-x, -y, turns + half()}; }
  Angle t360() const { return {x, y, turns + 1}; }
};
bool operator<(Angle a, Angle b) {
  // add a.dist2() and b.dist2() to also compare distances
  return make_tuple(a.turns, a.half(), a.y * (ll)b.x) <
         make_tuple(b.turns, b.half(), a.x * (ll)b.y);
}
// Given two points, this calculates the smallest angle between
// them, i.e., the angle that covers the defined line segment.
pair<Angle, Angle> segmentAngles(Angle a, Angle b) {
  if (b < a) swap(a, b);
  return (b < a.t180() ? make_pair(a, b) : make_pair(b, a.t360()));
}
Angle operator+(Angle a, Angle b) { // point a + vector b
  Angle result(a.x + b.x, a.y + b.y, a.turns);
  if (a.t180() < result) result.turns--;
  return result.t180() < a ? result.t360() : result;
}
Angle angleDiff(Angle a, Angle b) { // angle b - angle a
  int turnDiff = b.turns - a.turns;
  a.turns = b.turns;
  return {a.x * b.x + a.y * b.y, a.x * b.y - a.y * b.x, turnDiff - (b < a)};
}

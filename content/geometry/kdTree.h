/**
 * Author: Stanford
 * Date: Unknown
 * Source: Stanford Notebook
 * Description: KD-tree (2d, can be extended to 3d)
 * Static nearest-neighbor queries on a nonempty set of integer points. nearest returns (squared
 * distance,point); the query point itself is allowed if present. Bounding boxes prune search,
 * but worst-case queries can visit every point. Uncomment the leaf check to exclude equal
 * points. There are no insertions/deletions.
 * Status: Tested on excellentengineers
 * Usage: KDTree tree(points);
 * auto [distance2,nearestPoint]=tree.nearest(P(3,7));
 */
#pragma once

#include "Point.h"

typedef long long T;
typedef Point<T> P;
const T INF = numeric_limits<T>::max();
bool on_x(P a, P b) { return a.x < b.x; }
bool on_y(P a, P b) { return a.y < b.y; }
struct KDNode {
  P point;                                            // if this is a leaf, the single point in it
  T minX = INF, maxX = -INF, minY = INF, maxY = -INF; // bounds
  KDNode *first = 0, *second = 0;
  T distance(P p) { // min squared distance to a point
    T closestX = (p.x < minX ? minX : p.x > maxX ? maxX : p.x);
    T closestY = (p.y < minY ? minY : p.y > maxY ? maxY : p.y);
    return (P(closestX, closestY) - p).dist2();
  }
  KDNode(vector<P> &&points) : point(points[0]) {
    for (P p : points) {
      minX = min(minX, p.x);
      maxX = max(maxX, p.x);
      minY = min(minY, p.y);
      maxY = max(maxY, p.y);
    }
    if (points.size() > 1) {
      // split on x if width >= height (not ideal...)
      sort(all(points), maxX - minX >= maxY - minY ? on_x : on_y);
      // divide by taking half the array for each child (not
      // best performance with many duplicates in the middle)
      int half = sz(points) / 2;
      first = new KDNode({points.begin(), points.begin() + half});
      second = new KDNode({points.begin() + half, points.end()});
    }
  }
};
struct KDTree {
  KDNode *root;
  KDTree(const vector<P> &points) : root(new KDNode({all(points)})) {}
  pair<T, P> search(KDNode *node, P p) {
    if (!node->first) {
      // uncomment if we should not find the point itself:
      // if (p == node->point) return {INF, P()};
      return make_pair((p - node->point).dist2(), node->point);
    }

    KDNode *nearChild = node->first, *farChild = node->second;
    T nearDistance = nearChild->distance(p), farDistance = farChild->distance(p);
    if (nearDistance > farDistance) swap(farDistance, nearDistance), swap(nearChild, farChild);

    // search closest side first, other side if needed
    auto best = search(nearChild, p);
    if (farDistance < best.first) best = min(best, search(farChild, p));
    return best;
  }
  // find nearest point to a point, and its squared distance
  // (requires an arbitrary operator< for Point)
  pair<T, P> nearest(P p) { return search(root, p); }
};

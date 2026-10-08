/**
 * Author: VNOI Wiki, adapted to the notebook style
 * Source: https://wiki.vnoi.info/algo/data-structures/persistent-data-structures
 * Description: Persistent point assignment and range maximum on 1..N, inclusive [l,r].
 * Version 0 is uniformly initialValue (default 0). update(version,pos,val) copies the changed
 * root-to-leaf path, returns a new version ID, and preserves every old version; branching is allowed.
 * Node 0 represents an unchanged uniform subtree. Use node IDs, not references across push\_back.
 * Change max and unit for another aggregate; sums also need segment lengths for uniform subtrees.
 * Usage: PersistentSegTree seg(n); // initially all zero; require n>=1
 * int v1=seg.update(0,3,7); // assign a[3]=7
 * int v2=seg.update(v1,2,9);
 * int branch=seg.update(0,1,-5); // branch from the original version
 * ll best=seg.query(v2,2,3); // 9; seg.query(v1,2,3) is still 7
 * ll old=seg.query(0,1,n); // 0; positions and bounds are 1-based
 * Time: $O(\log N)$ per update/query; $O(1+U\log N)$ memory for U updates.
 */
#pragma once
struct PersistentSegTree {
  static constexpr ll unit = LLONG_MIN;
  struct Node {
    int left, right;
    ll val;
  };
  int n;
  vector<Node> nodes;
  vector<int> roots = {0};
  PersistentSegTree(int n, ll initialValue = 0) : n(n), nodes(1, {0, 0, initialValue}) {}
  int updateNode(int id, int lo, int hi, int pos, ll val) {
    int cur = sz(nodes);
    nodes.push_back(nodes[id]);
    if (lo == hi) {
      nodes[cur].val = val;
      return cur;
    }
    int mid = (lo + hi) / 2;
    if (pos <= mid)
      nodes[cur].left = updateNode(nodes[id].left, lo, mid, pos, val);
    else
      nodes[cur].right = updateNode(nodes[id].right, mid + 1, hi, pos, val);
    nodes[cur].val = max(nodes[nodes[cur].left].val, nodes[nodes[cur].right].val);
    return cur;
  }
  int update(int version, int pos, ll val) {
    roots.push_back(updateNode(roots[version], 1, n, pos, val));
    return sz(roots) - 1;
  }
  ll queryNode(int id, int lo, int hi, int l, int r) const {
    if (r < lo || hi < l) return unit;
    if (id == 0 || (l <= lo && hi <= r)) return nodes[id].val;
    int mid = (lo + hi) / 2;
    return max(queryNode(nodes[id].left, lo, mid, l, r),
               queryNode(nodes[id].right, mid + 1, hi, l, r));
  }
  ll query(int version, int l, int r) const {
    if (l > r) return unit;
    return queryNode(roots[version], 1, n, l, r);
  }
};

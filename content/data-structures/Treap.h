/**
 * Author: someone on Codeforces
 * Date: 2017-03-14
 * Source: folklore
 * Description: A short self-balancing tree. It acts as a
 *  sequential container with log-time splits/joins, and
 *  is easy to augment with additional data.
 * Time: $O(\log N)$
 * Status: stress-tested
 */
#pragma once
struct TreapNode {
  TreapNode *l = 0, *r = 0;
  int val, y, c = 1;
  TreapNode(int val) : val(val), y(rand()) {}
  void recalc();
};
int cnt(TreapNode *n) { return n ? n->c : 0; }
void TreapNode::recalc() { c = cnt(l) + cnt(r) + 1; }
template <class F>
void each(TreapNode *n, F f) {
  if (n) {
    each(n->l, f);
    f(n->val);
    each(n->r, f);
  }
}
pair<TreapNode *, TreapNode *> split(TreapNode *n, int k) {
  if (!n) return {};
  if (cnt(n->l) >= k) { // "n->val >= k" for lower_bound(k)
    auto [L, R] = split(n->l, k);
    n->l = R;
    n->recalc();
    return {L, n};
  } else {
    auto [L, R] = split(n->r, k - cnt(n->l) - 1); // and just "k"
    n->r = L;
    n->recalc();
    return {n, R};
  }
}
TreapNode *merge(TreapNode *l, TreapNode *r) {
  if (!l) return r;
  if (!r) return l;
  if (l->y > r->y) {
    l->r = merge(l->r, r);
    return l->recalc(), l;
  } else {
    r->l = merge(l, r->l);
    return r->recalc(), r;
  }
}
TreapNode *ins(TreapNode *t, TreapNode *n, int pos) {
  auto [l, r] = split(t, pos);
  return merge(merge(l, n), r);
}
// Example application: move the range [l, r) to index k
void move(TreapNode *&t, int l, int r, int k) {
  TreapNode *a, *b, *c;
  tie(a, b) = split(t, l);
  tie(b, c) = split(b, r - l);
  if (k <= l)
    t = merge(ins(a, b, k), c);
  else
    t = merge(a, ins(c, b, k - r));
}

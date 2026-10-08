/**
 * Author: someone on Codeforces
 * Date: 2017-03-14
 * Source: folklore
 * Description: A short self-balancing tree. It acts as a
 *  sequential container with log-time splits/joins, and
 *  is easy to augment with additional data.
 * This is an implicit treap: in-order position is the key. split(root,k) separates the first k
 * values; merge(a,b) concatenates sequences. Positions and ranges are 0-based, with ranges
 * [l,r). Save roots returned by ins/merge, and recalc after changing children. Extend recalc for
 * sums or lazy tags.
 * Time: $O(\log N)$
 * Status: stress-tested
 * Usage: TreapNode *root=nullptr;
 * root=ins(root,new TreapNode(7),0);
 * auto [a,b]=split(root,1); root=merge(a,b);
 */
#pragma once
struct TreapNode {
  TreapNode *left = 0, *right = 0;
  int val, priority, size = 1;
  TreapNode(int val) : val(val), priority(rand()) {}
  void recalc();
};
int cnt(TreapNode *node) { return node ? node->size : 0; }
void TreapNode::recalc() { size = cnt(left) + cnt(right) + 1; }
template <class F> void each(TreapNode *node, F visit) {
  if (node) {
    each(node->left, visit);
    visit(node->val);
    each(node->right, visit);
  }
}
pair<TreapNode *, TreapNode *> split(TreapNode *node, int leftCount) {
  if (!node) return {};
  if (cnt(node->left) >= leftCount) { // "node->val >= key" for lower_bound(k)
    auto [leftPart, rightPart] = split(node->left, leftCount);
    node->left = rightPart;
    node->recalc();
    return {leftPart, node};
  } else {
    auto [leftPart, rightPart] =
        split(node->right, leftCount - cnt(node->left) - 1); // and just "key"
    node->right = leftPart;
    node->recalc();
    return {node, rightPart};
  }
}
TreapNode *merge(TreapNode *left, TreapNode *right) {
  if (!left) return right;
  if (!right) return left;
  if (left->priority > right->priority) {
    left->right = merge(left->right, right);
    return left->recalc(), left;
  } else {
    right->left = merge(left, right->left);
    return right->recalc(), right;
  }
}
TreapNode *ins(TreapNode *root, TreapNode *node, int pos) {
  auto [left, right] = split(root, pos);
  return merge(merge(left, node), right);
}
// Example application: move the range [left, right) to index targetPos
void move(TreapNode *&root, int left, int right, int targetPos) {
  TreapNode *prefix, *middle, *suffix;
  tie(prefix, middle) = split(root, left);
  tie(middle, suffix) = split(middle, right - left);
  if (targetPos <= left)
    root = merge(ins(prefix, middle, targetPos), suffix);
  else
    root = merge(prefix, ins(suffix, middle, targetPos - right));
}

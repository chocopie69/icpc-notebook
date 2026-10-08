/**
 * Author: gepardo, adapted to the notebook style
 * Source: https://codeforces.com/blog/entry/61203
 * Description: Maps a query's two endpoints to a Hilbert-curve key. Sorting these keys tends
 * to keep nearby intervals together, reducing Mo pointer movement. Precompute once per query;
 * do not call this inside the sort comparator. No block-size tuning is needed.
 * Requires nonnegative coordinates smaller than $2^{bits}$, with 0<=bits<=31. Choose bits
 * so that $2^{bits}$ is STRICTLY greater than the largest endpoint, including the tree
 * Euler timer. Both Mo snippets use inclusive [l,r] and compute bits automatically.
 * Performance depends on query distribution and add/delete cost; a speedup is not guaranteed.
 * Usage: int bits=0;
 * while ((1LL<<bits)<=maxEndpoint) bits++;
 * ull key=hilbertOrder(left,right,bits);
 * // Intervals use (l,r); tree paths use converted Euler endpoints, not vertex IDs.
 * Time: $O(bits)$ per key, $O(bits)$ recursive stack space.
 */
#pragma once
inline ull hilbertOrder(int x, int y, int bits, int rotation = 0) {
  if (bits == 0) return 0;
  int half = 1 << (bits - 1);
  int quadrant = x < half ? (y < half ? 0 : 3) : (y < half ? 1 : 2);
  quadrant = (quadrant + rotation) & 3;
  const int turn[4] = {3, 0, 0, 1};
  int nextRotation = (rotation + turn[quadrant]) & 3;
  ull squareSize = 1ULL << (2 * bits - 2);
  ull offset = hilbertOrder(x & (half - 1), y & (half - 1), bits - 1, nextRotation);
  if (quadrant == 0 || quadrant == 3) offset = squareSize - offset - 1;
  return quadrant * squareSize + offset;
}

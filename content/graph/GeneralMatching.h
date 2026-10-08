/**
 * Author: Simon Lindholm
 * Date: 2016-12-09
 * License: CC0
 * Source: http://www.mimuw.edu.pl/~mucha/pub/mucha_sankowski_focs04.pdf
 * Description: Maximum-cardinality matching in an undirected general graph (not weighted).
 * Vertices are 0..n-1; list each edge once, with no self-loops. Returns matched pairs.
 * Randomized Tutte-matrix inversion can fail with probability $N/mod$.
 * Time: O(N^3)
 * Status: not very well tested
 * Usage: vector<pii> edges={{0,1},{1,2},{2,0}};
 * auto matching=generalMatching(3,edges); // one pair
 */
#pragma once

#include "../numerical/MatrixInverse-mod.h"
vector<pii> generalMatching(int n, vector<pii> &edges) {
  vector<vector<ll>> tutte(n, vector<ll>(n)), inverse;
  for (pii edge : edges) {
    int u = edge.first, v = edge.second, randomValue = rand() % mod;
    tutte[u][v] = randomValue, tutte[v][u] = (mod - randomValue) % mod;
  }

  int rank = matInv(inverse = tutte), extendedSize = 2 * n - rank, matchedU, matchedV;
  assert(rank % 2 == 0);

  if (extendedSize != n) do {
      tutte.resize(extendedSize, vector<ll>(extendedSize));
      for (int i = 0; i < (n); ++i) {
        tutte[i].resize(extendedSize);
        for (int j = n; j < (extendedSize); ++j) {
          int randomValue = rand() % mod;
          tutte[i][j] = randomValue, tutte[j][i] = (mod - randomValue) % mod;
        }
      }
    } while (matInv(inverse = tutte) != extendedSize);

  vector<int> active(extendedSize, 1);
  vector<pii> matching;
  for (int it = 0; it < (extendedSize / 2); ++it) {
    for (int i = 0; i < (extendedSize); ++i)
      if (active[i])
        for (int j = i + 1; j < (extendedSize); ++j)
          if (inverse[i][j] && tutte[i][j]) {
            matchedU = i;
            matchedV = j;
            goto done;
          }
    assert(0);
  done:
    if (matchedV < n) matching.emplace_back(matchedU, matchedV);
    active[matchedU] = active[matchedV] = 0;
    for (int pass = 0; pass < (2); ++pass) {
      ll pivotInverse = modpow(inverse[matchedU][matchedV], mod - 2);
      for (int i = 0; i < (extendedSize); ++i)
        if (active[i] && inverse[i][matchedV]) {
          ll factor = inverse[i][matchedV] * pivotInverse % mod;
          for (int j = 0; j < (extendedSize); ++j)
            inverse[i][j] = (inverse[i][j] - inverse[matchedU][j] * factor) % mod;
        }
      swap(matchedU, matchedV);
    }
  }
  return matching;
}

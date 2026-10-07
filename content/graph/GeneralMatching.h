/**
 * Author: Simon Lindholm
 * Date: 2016-12-09
 * License: CC0
 * Source: http://www.mimuw.edu.pl/~mucha/pub/mucha_sankowski_focs04.pdf
 * Description: Matching for general graphs.
 * Fails with probability $N / mod$.
 * Time: O(N^3)
 * Status: not very well tested
 */
#pragma once

#include "../numerical/MatrixInverse-mod.h"
vector<pii> generalMatching(int N, vector<pii> &ed) {
  vector<vector<ll>> mat(N, vector<ll>(N)), A;
  for (pii pa : ed) {
    int a = pa.first, b = pa.second, r = rand() % mod;
    mat[a][b] = r, mat[b][a] = (mod - r) % mod;
  }

  int r = matInv(A = mat), M = 2 * N - r, matchI, matchJ;
  assert(r % 2 == 0);

  if (M != N) do {
      mat.resize(M, vector<ll>(M));
      for (int i = 0; i < (N); ++i) {
        mat[i].resize(M);
        for (int j = N; j < (M); ++j) {
          int r = rand() % mod;
          mat[i][j] = r, mat[j][i] = (mod - r) % mod;
        }
      }
    } while (matInv(A = mat) != M);

  vector<int> has(M, 1);
  vector<pii> ret;
  for (int it = 0; it < (M / 2); ++it) {
    for (int i = 0; i < (M); ++i)
      if (has[i])
        for (int j = i + 1; j < (M); ++j)
          if (A[i][j] && mat[i][j]) {
            matchI = i;
            matchJ = j;
            goto done;
          }
    assert(0);
  done:
    if (matchJ < N) ret.emplace_back(matchI, matchJ);
    has[matchI] = has[matchJ] = 0;
    for (int sw = 0; sw < (2); ++sw) {
      ll a = modpow(A[matchI][matchJ], mod - 2);
      for (int i = 0; i < (M); ++i)
        if (has[i] && A[i][matchJ]) {
          ll b = A[i][matchJ] * a % mod;
          for (int j = 0; j < (M); ++j) A[i][j] = (A[i][j] - A[matchI][j] * b) % mod;
        }
      swap(matchI, matchJ);
    }
  }
  return ret;
}

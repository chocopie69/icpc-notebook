/**
 * Author: Simon Lindholm
 * Date: 2018-07-18
 * License: CC0
 * Source: https://en.wikipedia.org/wiki/Bron%E2%80%93Kerbosch_algorithm
 * Description: Runs a callback for all maximal cliques in a graph (given as a
 * symmetric bitset matrix; self-edges not allowed). Callback is given a bitset
 * representing the maximal clique.
 * Maximal means no vertex can be added; it does not mean largest. For a maximum clique use
 * MaximumClique, or examine every callback and keep the largest. Vertices are 0-based and there
 * are at most 128. Pass candidates containing exactly the valid vertex bits; the default mask
 * includes bits beyond n.
 * Time: O(3^{n/3}), much faster for sparse graphs
 * Status: stress-tested
 * Usage: vector<B> adj(n); B candidates;
 * for (int u=0;u<n;u++) candidates.set(u);
 * // Set adj[u][v]=adj[v][u]=1 for each edge.
 * cliques(adj,[](B clique) { ... },candidates);
 */
#pragma once
/// Possible optimization: on the top-most
/// recursion level, ignore 'cands', and go through nodes in order of increasing
/// degree, where degrees go down as nodes are removed.
/// (mostly irrelevant given MaximumClique)

typedef bitset<128> B;
template <class F>
void cliques(vector<B> &adj, F visitClique, B candidates = ~B(), B excluded = {}, B clique = {}) {
  if (!candidates.any()) {
    if (!excluded.any()) visitClique(clique);
    return;
  }
  auto pivot = (candidates | excluded)._Find_first();
  auto branches = candidates & ~adj[pivot];
  for (int i = 0; i < (sz(adj)); ++i)
    if (branches[i]) {
      clique[i] = 1;
      cliques(adj, visitClique, candidates & adj[i], excluded & adj[i], clique);
      clique[i] = candidates[i] = 0;
      excluded[i] = 1;
    }
}

/**
 * Author: chilli, SJTU, Janez Konc
 * Date: 2019-05-10
 * License: GPL3+
 * Source: https://en.wikipedia.org/wiki/MaxCliqueDyn_maximum_clique_algorithm, https://gitlab.com/janezkonc/mcqd/blob/master/mcqd.h
 * Description: Quickly finds a maximum clique of a graph (given as symmetric bitset
 * matrix; self-edges not allowed). Can be used to find a maximum independent
 * set by finding a maximum clique of the complement graph.
 * Exact branch-and-bound uses color bounds to prune search while retaining the largest clique.
 * Runtime can still be exponential. Supply a nonempty symmetric adjacency matrix with at most
 * 200 vertices and a zero diagonal. maxClique returns 0-based vertex IDs; construct a fresh
 * object for a new search.
 * Time: Runs in about 1s for n=155 and worst case random graphs (p=.90). Runs
 * faster for sparse graphs.
 * Status: stress-tested
 * Usage: vb adj(n); // set adj[u][v]=adj[v][u]=1 for each edge
 * MaximumClique solver(adj); auto vertices=solver.maxClique();
 */
typedef vector<bitset<200>> vb;
struct MaximumClique {
  double limit = 0.025, searchCount = 0;
  struct Vertex {
    int id, bound = 0; // degree during init, then a coloring upper bound
  };
  typedef vector<Vertex> vv;
  vb adj;
  vv vertices;
  vector<vector<int>> colorClasses;
  vector<int> bestClique, clique, searchStats, prevStats;
  void init(vv &candidates) {
    for (auto &v : candidates) v.bound = 0;
    for (auto &v : candidates)
      for (auto other : candidates) v.bound += adj[v.id][other.id];
    sort(all(candidates), [](auto a, auto b) { return a.bound > b.bound; });
    int maxDegree = candidates[0].bound;
    for (int i = 0; i < (sz(candidates)); ++i) candidates[i].bound = min(i, maxDegree) + 1;
  }
  void expand(vv &candidates, int level = 1) {
    searchStats[level] += searchStats[level - 1] - prevStats[level];
    prevStats[level] = searchStats[level - 1];
    while (sz(candidates)) {
      if (sz(clique) + candidates.back().bound <= sz(bestClique)) return;
      clique.push_back(candidates.back().id);
      vv neighbors;
      for (auto v : candidates)
        if (adj[candidates.back().id][v.id]) neighbors.push_back({v.id});
      if (sz(neighbors)) {
        if (searchStats[level]++ / ++searchCount < limit) init(neighbors);
        int writePos = 0, maxColor = 1, minColor = max(sz(bestClique) - sz(clique) + 1, 1);
        colorClasses[1].clear(), colorClasses[2].clear();
        for (auto v : neighbors) {
          int color = 1;
          auto isAdjacent = [&](int i) { return adj[v.id][i]; };
          while (any_of(all(colorClasses[color]), isAdjacent)) color++;
          if (color > maxColor) maxColor = color, colorClasses[maxColor + 1].clear();
          if (color < minColor) neighbors[writePos++].id = v.id;
          colorClasses[color].push_back(v.id);
        }
        if (writePos > 0) neighbors[writePos - 1].bound = 0;
        for (int color = minColor; color < (maxColor + 1); ++color)
          for (int i : colorClasses[color])
            neighbors[writePos].id = i, neighbors[writePos++].bound = color;
        expand(neighbors, level + 1);
      } else if (sz(clique) > sz(bestClique))
        bestClique = clique;
      clique.pop_back(), candidates.pop_back();
    }
  }
  vector<int> maxClique() {
    init(vertices), expand(vertices);
    return bestClique;
  }
  MaximumClique(vb adjacency)
      : adj(adjacency), colorClasses(sz(adj) + 1), searchStats(sz(colorClasses)),
        prevStats(searchStats) {
    for (int i = 0; i < (sz(adj)); ++i) vertices.push_back({i});
  }
};

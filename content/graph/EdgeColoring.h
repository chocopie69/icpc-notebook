/**
 * Author: Simon Lindholm
 * Date: 2020-10-12
 * License: CC0
 * Source: https://en.wikipedia.org/wiki/Misra_%26_Gries_edge_coloring_algorithm
 * https://codeforces.com/blog/entry/75431 for the note about bipartite graphs.
 * Description: Given a simple, undirected graph with max degree $D$, computes a
 * $(D + 1)$-coloring of the edges such that no neighboring edges share a color.
 * ($D$-coloring is NP-hard, but can be done for bipartite graphs by repeated matchings of
 * max-degree nodes.)
 * Vertices are 0..n-1; input must have no self-loops or parallel edges. colors[i] is the 0-based
 * color of input edge i. The algorithm recolors alternating chains to free a color at both
 * endpoints. It guarantees at most D+1 colors, not the minimum number.
 * Time: O(NM)
 * Status: stress-tested, tested on kattis:gamescheduling
 * Usage: vector<pii> edges={{0,1},{1,2},{2,0}};
 * auto colors=edgeColoring(3,edges);
 */
#pragma once
vector<int> edgeColoring(int n, vector<pii> edges) {
  // fanColor holds degree counts first, then the colors used by the fan.
  vector<int> fanColor(n + 1), colors(sz(edges)), fan(n), freeColor(n), colorPos;
  for (pii edge : edges) ++fanColor[edge.first], ++fanColor[edge.second];
  int u, v, colorCount = *max_element(all(fanColor)) + 1;
  vector<vector<int>> adj(n, vector<int>(colorCount, -1));
  for (pii edge : edges) {
    tie(u, v) = edge;
    fan[0] = v;
    colorPos.assign(colorCount, 0);
    int current = u, lastVertex = u, alternateColor, baseColor = freeColor[u], fanSize = 0, i = 0;
    while (alternateColor = freeColor[v],
           !colorPos[alternateColor] && (v = adj[u][alternateColor]) != -1)
      colorPos[alternateColor] = ++fanSize, fanColor[fanSize] = alternateColor, fan[fanSize] = v;
    fanColor[colorPos[alternateColor]] = baseColor;
    for (int color = alternateColor; current != -1;
         color ^= baseColor ^ alternateColor, current = adj[current][color])
      swap(adj[current][color], adj[lastVertex = current][color ^ baseColor ^ alternateColor]);
    while (adj[fan[i]][alternateColor] != -1) {
      int left = fan[i], right = fan[++i], rotatedColor = fanColor[i];
      adj[u][rotatedColor] = left;
      adj[left][rotatedColor] = u;
      adj[right][rotatedColor] = -1;
      freeColor[right] = rotatedColor;
    }
    adj[u][alternateColor] = fan[i];
    adj[fan[i]][alternateColor] = u;
    for (int y : {fan[0], u, lastVertex})
      for (int &z = freeColor[y] = 0; adj[y][z] != -1; z++);
  }
  for (int i = 0; i < (sz(edges)); ++i)
    for (tie(u, v) = edges[i]; adj[u][colors[i]] != v;) ++colors[i];
  return colors;
}

/**
 * Author: chilli
 * Date: 2019-05-17
 * Source: Wikipedia
 * Description: A maximum independent set in $G$ is a \textbf{maximum clique}
 * (largest possible size) in the complement of $G$. Use MaximumClique.
 * A \textbf{maximal clique} only means no vertex can be added; it may be smaller
 * than the maximum, so an arbitrary maximal clique is insufficient.
 * For bipartite graphs, take all vertices outside a minimum vertex cover;
 * see MinimumVertexCover.
 * Complement only pairs of distinct vertices; keep the diagonal zero. The returned clique
 * vertices are the independent-set vertices in the original graph. Maximal independent sets,
 * like maximal cliques, may be much smaller than maximum ones.
 * Usage: vb complement(n);
 * for (int u=0;u<n;u++) for (int v=0;v<n;v++)
 *   complement[u][v]=u!=v && !adj[u][v];
 * MaximumClique solver(complement);
 * auto independent=solver.maxClique();
 */

/**
 * Author: Simon Lindholm
 * Date: 2015-05-13
 * Source: Wikipedia
 * Description: To extract a minimum $s$-$t$ cut, first run max-flow to completion.
 * Let S be the vertices reachable from s using positive residual capacity; T is the rest.
 * Dinic stores this final reachability: d.leftOfMinCut(v) is true exactly for v in S.
 * The cut consists of original directed edges from S to T, and its capacity equals max flow.
 * Sum original capacities (oc), not residual capacities (c), which are zero on these edges.
 * Zero-capacity reverse edges are bookkeeping, not original cut edges. With addEdge(u,v,c,c),
 * an undirected crossing edge is counted once, in the direction from S to T.
 * For other flow implementations, BFS/DFS from s in the final residual graph gives S:
 * follow e.c > 0 in Dinic, or e.cap-e.flow > 0 in MinCostMaxFlow. Include reverse edges.
 * Time: O(V+E) after max-flow.
 * Usage: Dinic d(3); int s=0, t=2;
 * d.addEdge(0,1,5); d.addEdge(1,2,3);
 * ll flow=d.calc(s,t); // 3; finish max-flow before extracting the cut
 * vector<int> sourceSide, sinkSide;
 * for (int v=0; v<3; ++v)
 *   (d.leftOfMinCut(v) ? sourceSide : sinkSide).push_back(v);
 * // sourceSide={0,1}, sinkSide={2}
 * vector<pair<int,int>> cutEdges;
 * ll cutCapacity=0;
 * for (int u=0; u<3; ++u) if (d.leftOfMinCut(u))
 *   for (auto &e : d.adj[u])
 *     if (!d.leftOfMinCut(e.to) && e.oc>0) {
 *       cutEdges.push_back({u,e.to});
 *       cutCapacity+=e.oc;
 *     }
 * // cutEdges={{1,2}}; parallel edges appear separately
 * assert(cutCapacity==flow); // for a fresh network
 * Status: works
 */

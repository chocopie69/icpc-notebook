/**
 * Author: Simon Lindholm
 * Date: 2015-05-13
 * Source: Wikipedia
 * Description: After running max-flow, the left side of a min-cut from $s$ to $t$ is given
 * by all vertices reachable from $s$, only traversing edges with positive residual capacity.
 * Usage: After d.calc(s,t), d.leftOfMinCut(v) identifies the source side.
 * Sum original capacities of edges leaving that side to obtain the cut value (= max flow).
 * Status: works
 */

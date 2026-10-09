# Special-case audit

Reviewed all 108 algorithm headers included by the active notebook chapters, plus the contest helpers. Excluded algorithms are outside this audit.

Updated descriptions or usage in 58 entries. Executable code is unchanged by this audit; existing notes were kept where they already cover the relevant conditions. These are adaptation notes, not promises that every variant is implemented.

The short notes appear beside their algorithms in the PDF. Main additions:

- Numerical: constant/zero polynomials, repeated roots, empty interpolation, recurrence bounds, tolerance scaling, larger XOR bitsets and integer/modular arithmetic.
- Number theory: exponent zero for discrete log, negative Euclid/fraction inputs, larger modular products, sieve bounds and large combinatorial counts.
- Data structures: empty-tree updates, range BIT variants, lazy-tag composition, treap move boundaries, sparse coordinate compression and real-valued CHT variants.
- Graphs: rectangular assignments, exact-F costed flow, lower-bound circulation reductions, 64-bit scaling, self-loops, 2-SAT literal conversion, empty clique input and ordered HLD aggregates.
- Geometry: floating versus integer points, tangent degeneracies, zero-area polygons, clipping boundaries, collinear hull points, tiny/empty hulls and duplicate KD-tree points.
- Strings/DP: alphabets and separators, empty-pattern matching, hash bounds, empty SOS vectors and unreachable DP transitions.

Corrected descriptions that disagreed with the code: floating determinant uses exact zero checks, HLD modifies its own adjacency copy, and the topological-sort skeleton does not fill ans until the caller pops the stack.

For deep recursive graph/tree searches, switch to an iterative traversal or ensure sufficient stack space. For pasting multiple snippets together, rename conflicting globals/types such as mod, LIM, inf/INF, P, Poly, adj and dfs as needed.

Reference material checked for variant prerequisites: [flow lower bounds](https://cp-algorithms.com/graph/flow_with_demands.html), [collinear convex hulls](https://cp-algorithms.com/geometry/convex-hull.html), and [DP monotonicity](https://cp-algorithms.com/dynamic_programming/divide-and-conquer-dp.html).

## Coverage

| Entry | Review result |
| --- | --- |
| [Polynomial.h](../content/numerical/Polynomial.h) | Short notes added or corrected |
| [PolyRoots.h](../content/numerical/PolyRoots.h) | Short notes added or corrected |
| [PolyInterpolate.h](../content/numerical/PolyInterpolate.h) | Short notes added or corrected |
| [LinearRecurrence.h](../content/numerical/LinearRecurrence.h) | Short notes added or corrected |
| [Determinant.h](../content/numerical/Determinant.h) | Short notes added or corrected |
| [IntDeterminant.h](../content/numerical/IntDeterminant.h) | Short notes added or corrected |
| [SolveLinear.h](../content/numerical/SolveLinear.h) | Short notes added or corrected |
| [SolveLinear2.h](../content/numerical/SolveLinear2.h) | Existing notes sufficient; retained |
| [SolveLinearBinary.h](../content/numerical/SolveLinearBinary.h) | Short notes added or corrected |
| [MatrixInverse.h](../content/numerical/MatrixInverse.h) | Short notes added or corrected |
| [Tridiagonal.h](../content/numerical/Tridiagonal.h) | Existing notes sufficient; retained |
| [ModularArithmetic.h](../content/number-theory/ModularArithmetic.h) | Existing notes sufficient; retained |
| [ModInverse.h](../content/number-theory/ModInverse.h) | Existing notes sufficient; retained |
| [ModPow.h](../content/number-theory/ModPow.h) | Existing notes sufficient; retained |
| [ModLog.h](../content/number-theory/ModLog.h) | Short notes added or corrected |
| [ModSum.h](../content/number-theory/ModSum.h) | Existing notes sufficient; retained |
| [ModMulLL.h](../content/number-theory/ModMulLL.h) | Short notes added or corrected |
| [ModSqrt.h](../content/number-theory/ModSqrt.h) | Short notes added or corrected |
| [LinearSieve.h](../content/number-theory/LinearSieve.h) | Short notes added or corrected |
| [FastEratosthenes.h](../content/number-theory/FastEratosthenes.h) | Short notes added or corrected |
| [MillerRabin.h](../content/number-theory/MillerRabin.h) | Existing notes sufficient; retained |
| [Factor.h](../content/number-theory/Factor.h) | Existing notes sufficient; retained |
| [euclid.h](../content/number-theory/euclid.h) | Short notes added or corrected |
| [CRT.h](../content/number-theory/CRT.h) | Existing notes sufficient; retained |
| [phiFunction.h](../content/number-theory/phiFunction.h) | Existing notes sufficient; retained |
| [ContinuedFractions.h](../content/number-theory/ContinuedFractions.h) | Short notes added or corrected |
| [FracBinarySearch.h](../content/number-theory/FracBinarySearch.h) | Short notes added or corrected |
| [IntPerm.h](../content/combinatorial/IntPerm.h) | Short notes added or corrected |
| [multinomial.h](../content/combinatorial/multinomial.h) | Short notes added or corrected |
| [OrderStatisticTree.h](../content/data-structures/OrderStatisticTree.h) | Short notes added or corrected |
| [HashMap.h](../content/data-structures/HashMap.h) | Existing notes sufficient; retained |
| [IterativeSegmentTree.h](../content/data-structures/IterativeSegmentTree.h) | Existing notes sufficient; retained |
| [SegmentTree.h](../content/data-structures/SegmentTree.h) | Short notes added or corrected |
| [LazySegmentTree.h](../content/data-structures/LazySegmentTree.h) | Short notes added or corrected |
| [PersistentSegmentTree.h](../content/data-structures/PersistentSegmentTree.h) | Existing notes sufficient; retained |
| [UnionFind.h](../content/data-structures/UnionFind.h) | Existing notes sufficient; retained |
| [UnionFindRollback.h](../content/data-structures/UnionFindRollback.h) | Existing notes sufficient; retained |
| [Matrix.h](../content/data-structures/Matrix.h) | Short notes added or corrected |
| [LineContainer.h](../content/data-structures/LineContainer.h) | Short notes added or corrected |
| [Treap.h](../content/data-structures/Treap.h) | Short notes added or corrected |
| [FenwickTree.h](../content/data-structures/FenwickTree.h) | Short notes added or corrected |
| [FenwickTree2d.h](../content/data-structures/FenwickTree2d.h) | Existing notes sufficient; retained |
| [PersistentFenwick.h](../content/data-structures/PersistentFenwick.h) | Short notes added or corrected |
| [RMQ.h](../content/data-structures/RMQ.h) | Existing notes sufficient; retained |
| [SlidingWindow.h](../content/data-structures/SlidingWindow.h) | Existing notes sufficient; retained |
| [MoQueries.h](../content/data-structures/MoQueries.h) | Short notes added or corrected |
| [MoTree.h](../content/data-structures/MoTree.h) | Existing notes sufficient; retained |
| [Dial.h](../content/graph/Dial.h) | Short notes added or corrected |
| [BellmanFord.h](../content/graph/BellmanFord.h) | Short notes added or corrected |
| [TopoSort.h](../content/graph/TopoSort.h) | Short notes added or corrected |
| [HopcroftKarp.h](../content/graph/HopcroftKarp.h) | Existing notes sufficient; retained |
| [MinimumVertexCover.h](../content/graph/MinimumVertexCover.h) | Existing notes sufficient; retained |
| [WeightedMatching.h](../content/graph/WeightedMatching.h) | Short notes added or corrected |
| [Dinic.h](../content/graph/Dinic.h) | Short notes added or corrected |
| [MinCut.h](../content/graph/MinCut.h) | Existing notes sufficient; retained |
| [MinCostMaxFlow.h](../content/graph/MinCostMaxFlow.h) | Short notes added or corrected |
| [GlobalMinCut.h](../content/graph/GlobalMinCut.h) | Short notes added or corrected |
| [SCC.h](../content/graph/SCC.h) | Existing notes sufficient; retained |
| [BiconnectedComponents.h](../content/graph/BiconnectedComponents.h) | Short notes added or corrected |
| [2sat.h](../content/graph/2sat.h) | Short notes added or corrected |
| [EulerWalk.h](../content/graph/EulerWalk.h) | Short notes added or corrected |
| [EdgeColoring.h](../content/graph/EdgeColoring.h) | Existing notes sufficient; retained |
| [MaximalCliques.h](../content/graph/MaximalCliques.h) | Short notes added or corrected |
| [MaximumClique.h](../content/graph/MaximumClique.h) | Short notes added or corrected |
| [MaximumIndependentSet.h](../content/graph/MaximumIndependentSet.h) | Existing notes sufficient; retained |
| [LCA.h](../content/graph/LCA.h) | Short notes added or corrected |
| [LCAEuler.h](../content/graph/LCAEuler.h) | Existing notes sufficient; retained |
| [CompressTree.h](../content/graph/CompressTree.h) | Existing notes sufficient; retained |
| [HLD.h](../content/graph/HLD.h) | Short notes added or corrected |
| [CentroidDecomposition.h](../content/graph/CentroidDecomposition.h) | Existing notes sufficient; retained |
| [Point.h](../content/geometry/Point.h) | Short notes added or corrected |
| [lineDistance.h](../content/geometry/lineDistance.h) | Existing notes sufficient; retained |
| [SegmentDistance.h](../content/geometry/SegmentDistance.h) | Existing notes sufficient; retained |
| [SegmentIntersection.h](../content/geometry/SegmentIntersection.h) | Existing notes sufficient; retained |
| [lineIntersection.h](../content/geometry/lineIntersection.h) | Short notes added or corrected |
| [sideOf.h](../content/geometry/sideOf.h) | Existing notes sufficient; retained |
| [OnSegment.h](../content/geometry/OnSegment.h) | Existing notes sufficient; retained |
| [linearTransformation.h](../content/geometry/linearTransformation.h) | Existing notes sufficient; retained |
| [Angle.h](../content/geometry/Angle.h) | Short notes added or corrected |
| [CircleIntersection.h](../content/geometry/CircleIntersection.h) | Short notes added or corrected |
| [CircleTangents.h](../content/geometry/CircleTangents.h) | Short notes added or corrected |
| [CirclePolygonIntersection.h](../content/geometry/CirclePolygonIntersection.h) | Short notes added or corrected |
| [circumcircle.h](../content/geometry/circumcircle.h) | Existing notes sufficient; retained |
| [MinimumEnclosingCircle.h](../content/geometry/MinimumEnclosingCircle.h) | Existing notes sufficient; retained |
| [InsidePolygon.h](../content/geometry/InsidePolygon.h) | Existing notes sufficient; retained |
| [PolygonArea.h](../content/geometry/PolygonArea.h) | Existing notes sufficient; retained |
| [PolygonCenter.h](../content/geometry/PolygonCenter.h) | Short notes added or corrected |
| [PolygonCut.h](../content/geometry/PolygonCut.h) | Short notes added or corrected |
| [ConvexHull.h](../content/geometry/ConvexHull.h) | Short notes added or corrected |
| [HullDiameter.h](../content/geometry/HullDiameter.h) | Existing notes sufficient; retained |
| [PointInsideHull.h](../content/geometry/PointInsideHull.h) | Short notes added or corrected |
| [LineHullIntersection.h](../content/geometry/LineHullIntersection.h) | Short notes added or corrected |
| [ClosestPair.h](../content/geometry/ClosestPair.h) | Existing notes sufficient; retained |
| [kdTree.h](../content/geometry/kdTree.h) | Short notes added or corrected |
| [Trie.h](../content/strings/Trie.h) | Existing notes sufficient; retained |
| [KMP.h](../content/strings/KMP.h) | Existing notes sufficient; retained |
| [Zfunc.h](../content/strings/Zfunc.h) | Short notes added or corrected |
| [Manacher.h](../content/strings/Manacher.h) | Existing notes sufficient; retained |
| [MinRotation.h](../content/strings/MinRotation.h) | Existing notes sufficient; retained |
| [Hashing.h](../content/strings/Hashing.h) | Short notes added or corrected |
| [IntervalContainer.h](../content/various/IntervalContainer.h) | Existing notes sufficient; retained |
| [IntervalCover.h](../content/various/IntervalCover.h) | Existing notes sufficient; retained |
| [ConstantIntervals.h](../content/various/ConstantIntervals.h) | Existing notes sufficient; retained |
| [TernarySearch.h](../content/various/TernarySearch.h) | Existing notes sufficient; retained |
| [FastKnapsack.h](../content/various/FastKnapsack.h) | Existing notes sufficient; retained |
| [SOSDP.h](../content/various/SOSDP.h) | Short notes added or corrected |
| [KnuthDP.h](../content/various/KnuthDP.h) | Existing notes sufficient; retained |
| [DivideAndConquerDP.h](../content/various/DivideAndConquerDP.h) | Short notes added or corrected |

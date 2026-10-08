# Notebook usage notes

Descriptions and full usage notes cover the active algorithm entries. Simple snippets now use concise implementation notes; their Usage examples are unchanged. The contest template and shell/editor helpers are not algorithm entries.

Notes explain when to use each snippet, indexing, input assumptions, return values, changes to input data, and a concrete call or an explicit customization recipe. Familiar contest building blocks are included, as requested.

Tree Mo follows upstream KACTL's direct endpoint walking. Its header states inclusive paths, root/indexing conventions, callback setup, state reset, and adaptation to edge values.

Excluded from the current PDF: Aho-Corasick, 2D prefix sums, directed MST, the Techniques appendix, Shell setup, Vim setup, and Code checksum. Dependency captions are retained; snippet hashes and line counts are hidden. Data structures follows Combinatorial.

## Per-snippet coverage

| Snippet | Notes |
| --- | --- |
| [IntPerm.h](../content/combinatorial/IntPerm.h) | Concise description; full usage |
| [multinomial.h](../content/combinatorial/multinomial.h) | Concise description; full usage |
| [OrderStatisticTree.h](../content/data-structures/OrderStatisticTree.h) | Concise description; full usage |
| [HashMap.h](../content/data-structures/HashMap.h) | Concise description; full usage |
| [SegmentTree.h](../content/data-structures/SegmentTree.h) | Concise description; full usage |
| [LazySegmentTree.h](../content/data-structures/LazySegmentTree.h) | Concise description; full usage |
| [UnionFindRollback.h](../content/data-structures/UnionFindRollback.h) | Concise description; full usage |
| [Matrix.h](../content/data-structures/Matrix.h) | Concise description; full usage |
| [LineContainer.h](../content/data-structures/LineContainer.h) | Expanded description and usage |
| [Treap.h](../content/data-structures/Treap.h) | Expanded description and usage |
| [FenwickTree.h](../content/data-structures/FenwickTree.h) | Concise description; full usage |
| [FenwickTree2d.h](../content/data-structures/FenwickTree2d.h) | Expanded description and usage |
| [RMQ.h](../content/data-structures/RMQ.h) | Concise description; full usage |
| [MoQueries.h](../content/data-structures/MoQueries.h) | Expanded description and usage |
| [MoTree.h](../content/data-structures/MoTree.h) | Expanded; KACTL endpoint-walking implementation |
| [Point.h](../content/geometry/Point.h) | Concise description; full usage |
| [lineDistance.h](../content/geometry/lineDistance.h) | Concise description; full usage |
| [SegmentDistance.h](../content/geometry/SegmentDistance.h) | Concise description; full usage |
| [SegmentIntersection.h](../content/geometry/SegmentIntersection.h) | Expanded description and usage |
| [lineIntersection.h](../content/geometry/lineIntersection.h) | Expanded description and usage |
| [sideOf.h](../content/geometry/sideOf.h) | Concise description; full usage |
| [OnSegment.h](../content/geometry/OnSegment.h) | Concise description; full usage |
| [linearTransformation.h](../content/geometry/linearTransformation.h) | Expanded description and usage |
| [Angle.h](../content/geometry/Angle.h) | Expanded description and usage |
| [CircleIntersection.h](../content/geometry/CircleIntersection.h) | Expanded description and usage |
| [CircleTangents.h](../content/geometry/CircleTangents.h) | Expanded description and usage |
| [CirclePolygonIntersection.h](../content/geometry/CirclePolygonIntersection.h) | Expanded description and usage |
| [circumcircle.h](../content/geometry/circumcircle.h) | Expanded description and usage |
| [MinimumEnclosingCircle.h](../content/geometry/MinimumEnclosingCircle.h) | Expanded description and usage |
| [InsidePolygon.h](../content/geometry/InsidePolygon.h) | Expanded description and usage |
| [PolygonArea.h](../content/geometry/PolygonArea.h) | Concise description; full usage |
| [PolygonCenter.h](../content/geometry/PolygonCenter.h) | Concise description; full usage |
| [PolygonCut.h](../content/geometry/PolygonCut.h) | Expanded description and usage |
| [ConvexHull.h](../content/geometry/ConvexHull.h) | Concise description; full usage |
| [HullDiameter.h](../content/geometry/HullDiameter.h) | Expanded description and usage |
| [PointInsideHull.h](../content/geometry/PointInsideHull.h) | Expanded description and usage |
| [LineHullIntersection.h](../content/geometry/LineHullIntersection.h) | Expanded description and usage |
| [ClosestPair.h](../content/geometry/ClosestPair.h) | Expanded description and usage |
| [kdTree.h](../content/geometry/kdTree.h) | Expanded description and usage |
| [BellmanFord.h](../content/graph/BellmanFord.h) | Expanded description and usage |
| [TopoSort.h](../content/graph/TopoSort.h) | Concise description; full usage |
| [HopcroftKarp.h](../content/graph/HopcroftKarp.h) | Concise description; full usage |
| [DFSMatching.h](../content/graph/DFSMatching.h) | Concise description; full usage |
| [MinimumVertexCover.h](../content/graph/MinimumVertexCover.h) | Concise description; full usage |
| [WeightedMatching.h](../content/graph/WeightedMatching.h) | Expanded description and usage |
| [GeneralMatching.h](../content/graph/GeneralMatching.h) | Expanded description and usage |
| [SCC.h](../content/graph/SCC.h) | Concise description; full usage |
| [BiconnectedComponents.h](../content/graph/BiconnectedComponents.h) | Expanded description and usage |
| [2sat.h](../content/graph/2sat.h) | Concise description; full usage |
| [EulerWalk.h](../content/graph/EulerWalk.h) | Expanded description and usage |
| [EdgeColoring.h](../content/graph/EdgeColoring.h) | Expanded description and usage |
| [MaximalCliques.h](../content/graph/MaximalCliques.h) | Expanded description and usage |
| [MaximumClique.h](../content/graph/MaximumClique.h) | Expanded description and usage |
| [MaximumIndependentSet.h](../content/graph/MaximumIndependentSet.h) | Expanded description and usage |
| [LCA.h](../content/graph/LCA.h) | Concise description; full usage |
| [CompressTree.h](../content/graph/CompressTree.h) | Expanded description and usage |
| [HLD.h](../content/graph/HLD.h) | Expanded description and usage |
| [ModularArithmetic.h](../content/number-theory/ModularArithmetic.h) | Concise description; full usage |
| [ModInverse.h](../content/number-theory/ModInverse.h) | Concise description; full usage |
| [ModPow.h](../content/number-theory/ModPow.h) | Concise description; full usage |
| [ModLog.h](../content/number-theory/ModLog.h) | Expanded description and usage |
| [ModSum.h](../content/number-theory/ModSum.h) | Expanded description and usage |
| [ModMulLL.h](../content/number-theory/ModMulLL.h) | Expanded description and usage |
| [ModSqrt.h](../content/number-theory/ModSqrt.h) | Expanded description and usage |
| [FastEratosthenes.h](../content/number-theory/FastEratosthenes.h) | Expanded description and usage |
| [MillerRabin.h](../content/number-theory/MillerRabin.h) | Expanded description and usage |
| [Factor.h](../content/number-theory/Factor.h) | Expanded description and usage |
| [euclid.h](../content/number-theory/euclid.h) | Concise description; full usage |
| [CRT.h](../content/number-theory/CRT.h) | Concise description; full usage |
| [phiFunction.h](../content/number-theory/phiFunction.h) | Concise description; full usage |
| [ContinuedFractions.h](../content/number-theory/ContinuedFractions.h) | Expanded description and usage |
| [FracBinarySearch.h](../content/number-theory/FracBinarySearch.h) | Expanded description and usage |
| [Polynomial.h](../content/numerical/Polynomial.h) | Expanded description and usage |
| [PolyRoots.h](../content/numerical/PolyRoots.h) | Expanded description and usage |
| [PolyInterpolate.h](../content/numerical/PolyInterpolate.h) | Expanded description and usage |
| [LinearRecurrence.h](../content/numerical/LinearRecurrence.h) | Expanded description and usage |
| [Determinant.h](../content/numerical/Determinant.h) | Expanded description and usage |
| [IntDeterminant.h](../content/numerical/IntDeterminant.h) | Expanded description and usage |
| [SolveLinear.h](../content/numerical/SolveLinear.h) | Expanded description and usage |
| [SolveLinear2.h](../content/numerical/SolveLinear2.h) | Expanded description and usage |
| [SolveLinearBinary.h](../content/numerical/SolveLinearBinary.h) | Expanded description and usage |
| [MatrixInverse.h](../content/numerical/MatrixInverse.h) | Expanded description and usage |
| [Tridiagonal.h](../content/numerical/Tridiagonal.h) | Expanded description and usage |
| [KMP.h](../content/strings/KMP.h) | Concise description; full usage |
| [Zfunc.h](../content/strings/Zfunc.h) | Concise description; full usage |
| [Manacher.h](../content/strings/Manacher.h) | Expanded description and usage |
| [MinRotation.h](../content/strings/MinRotation.h) | Concise description; full usage |
| [SuffixArray.h](../content/strings/SuffixArray.h) | Expanded description and usage |
| [Hashing.h](../content/strings/Hashing.h) | Expanded description and usage |
| [IntervalContainer.h](../content/various/IntervalContainer.h) | Expanded description and usage |
| [IntervalCover.h](../content/various/IntervalCover.h) | Expanded description and usage |
| [ConstantIntervals.h](../content/various/ConstantIntervals.h) | Expanded description and usage |
| [TernarySearch.h](../content/various/TernarySearch.h) | Concise description; full usage |
| [FastKnapsack.h](../content/various/FastKnapsack.h) | Expanded description and usage |
| [KnuthDP.h](../content/various/KnuthDP.h) | Expanded description and usage |
| [DivideAndConquerDP.h](../content/various/DivideAndConquerDP.h) | Expanded description and usage |
| [FastMod.h](../content/various/FastMod.h) | Expanded description and usage |
| [FastInput.h](../content/various/FastInput.h) | Expanded description and usage |

## Personal Code::Blocks versions

KMP prefix function, DSU, inclusive min/max sparse table, polynomial hashing, ordinary prime sieve, and linear sieve use the personal abbreviations as their starting point. Dijkstra and topo abbreviations were not imported. Binary-lifting LCA supports weighted root distances and kth ancestors; Euler-tour + RMQ LCA is a separate constant-time-query alternative. Existing advanced fast sieve remains available.

Binary lifting and binary-lifting LCA are now one self-contained `LCA.h` snippet, with a single DFS for weighted and unweighted trees. The standalone BinaryLifting.h is excluded from the PDF; Euler-tour + RMQ LCA remains separate.

Added `ZeroOneBFS.h` (weights 0/1, INT_MAX for unreachable vertices) and `SlidingWindow.h` (0-based fixed-length windows, both extrema, supports int/ll values). Suffix Array is excluded from the PDF.

## SOS DP and centroid decomposition

SOSDP.h provides subset/superset sum transforms and inverses, with frequency and disjoint-mask examples. It replaces the duplicate SOS loop under Bit hacks. CentroidDecomposition.h follows the VNOI subtree-size / centroid / process-paths / recurse flow. Its concrete application counts unordered distinct-vertex pairs at exactly k edges on an unweighted tree. Query-before-insert avoids same-child paths; only used frequency entries are cleared. Notes explain adapting the processing for length ranges and weighted sums. The nearest-marked application and centroid-ancestor storage have been replaced. Fast Modular, Fast Input, and Debugging tricks are excluded from the PDF. HashMap.h has its GNU include corrected and uses unsigned multiplication in its hash function.

Custom Hash Map now uses one active randomized SplitMix64 hash, a normal gp_hash_table declaration, and a standard unordered_map alternative. Notes distinguish collision-related slowdown from correctness and explain that randomization gives no worst-case guarantee. The previous fixed multiplier and duplicate commented variant were removed.

Centroid decomposition is now a reusable path-counting skeleton with three marked CHANGE blocks: state/parameters/storage; initial and extended path state; query/insert/reset operations. The decomposition and query-before-insert traversal stay unchanged. Exact-edge-length counting remains a complete working example; collection no longer depends on k or prunes states. Notes cover XOR, weighted/vertex sums, ranges, touched-entry cleanup, and single-vertex/ordered-path conventions.

## Contest comparator

Added `content/contest/Comparator.cpp` immediately after the contest template, copied from `D:/Coding/CP-Training/Useful Stuffs/Comparator/comparator.cpp`. Only whitespace formatting is changed in the code; original identifiers, random generator, conditions, commands, braces, and return values are preserved. Notebook description/usage notes explain the Windows file setup. The original source is unchanged.

## Pointer trie and tree walking

Prime Sieve (`Eratosthenes.h`) is excluded from the PDF; Linear Sieve and Fast Prime Sieve remain. `Trie.h` adapts the VNOI pointer-based lowercase trie, with readable names, duplicate-aware insertion/deletion, exact lookup, prefix counts, and node cleanup. Root prefix counts include all copies; copying is disabled to preserve pointer ownership.

The existing maximum segment tree adds `firstAtLeast(l,r,val)`, an O(log N) left-first walk returning the first qualifying index or -1. The search depends on maximum aggregation. Fenwick's existing O(log N) `lowerBound` walk is explained with kth-frequency and suffix-target examples; point values must remain nonnegative. Both headings identify their walk operations. No duplicate Fenwick search implementation was added.

## Dial shortest paths

Replaced the active 0-1 BFS snippet with `Dial.h`, following Codeforces entry 88408. The implementation uses K+1 cyclic queues, an actual-distance cursor, stale-entry checks, and a pending-entry count. Weights must be integers in [0,K]; zero-weight edges and K=0 are supported. Distances use ll with LLONG_MAX for unreachable vertices. The original ZeroOneBFS.h remains available as source but is excluded from the PDF.

There are exactly two Mo sections. MoQueries.h includes the Hilbert-order helper inline, followed by 1-based inclusive [l,r] array Mo. The standalone HilbertOrder.h source remains available but is excluded from the PDF and is no longer a dependency of either Mo snippet.

MoTree.h adapts upstream KACTL's direct tree-endpoint walking and snake sorting. It uses a single alternating-depth DFS with inclusive subtree bounds, reuses ranks as a climb stack after sorting, and has no LCA table or twice-entered Euler array. Root initialization uses the chosen root, including the initial active vertex and both endpoint positions. Callbacks add/del/calc are generic, receive the endpoint side, and require empty shared state at the start. Paths include both vertices, and answers are returned in input order. Automatic block size is near N/sqrt(Q); vertices are 1..N with adjacency size N+1 and root defaulting to 1. README, titles, descriptions, examples and complexity match the two implementations.

Both Mo snippets use 1-based array positions / tree vertices and inclusive endpoints. Array Mo starts empty at [1,0]; tree DFS ranks, subtree bounds and the reused climb stack start at 1. Query/answer vectors keep their ordinary C++ input order. Titles are Mo's Algorithm on Arrays and Mo's Algorithm on Trees. Mathematics excludes Quadrilaterals, Trigonometry and Series, and removes only the sum of the first n positive integers; geometric and square/cube/fourth-power sums remain.

## Iterative segment tree

Added IterativeSegmentTree.h from upstream KACTL's compact 2N iterative maximum tree, printed alongside the existing recursive tree and walk. Its public interface uses positions 1..N and inclusive query(l,r). update shifts positions by N-1; the query shifts both endpoints by N-1 and uses closed-boundary traversal. Names and formatting follow the notebook; two ordered accumulators preserve the upstream support for noncommutative aggregates. Notes explain point assignment, identity, initial values, and adapting the aggregate.


## Persistent structures and 26-page budget

Added PersistentSegmentTree.h: path-copying, point assignment and inclusive range maximum, with zero-based version IDs and 1-based positions. New versions can branch from any existing version; a uniform null subtree avoids an initial full build.

Added PersistentFenwick.h: the VNOI article's timestamped 2D BIT, with 1-based coordinates, inclusive historical rectangle sums and same-time update coalescing. Updates must arrive in nondecreasing time order; this structure does not branch. History lookup compares timestamps only, avoiding a sentinel bound on values. Notes state dense-grid memory cost and how to reduce it to one dimension.

Kept the PDF at 26 pages by shortening descriptions of centroid decomposition, interval/tree Mo, SOS DP, weighted/general matching, iterative segment tree, custom hash map and Dial; removed repeated centroid comments. Usage examples and customization hooks remain. No algorithms were removed and no font-size reduction was used.

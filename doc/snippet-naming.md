# Snippet naming review

The naming pass reviewed the 106 entries included at that time.
The notebook now excludes the four flow entries and splits Mo into interval and
tree-path snippets. The tree version uses `tin`, `tout`, `euler`, `active`, `freq`,
and `extraLca` to expose the Euler-tour and LCA handling directly.
Names describe roles while keeping conventional `u`, `v`, `n`, loop indices,
point coordinates `x/y`, and familiar names such as `adj`, `up`, `num`, and `low`.
The naming pass retained algorithm behavior, ranges and public function signatures.
The later Mo split replaces `moTree` with the distinct-value example in `MoTree.h`,
now using arrays and free functions (`dfs`, `lca`, `check`, `makeQuery`, `compute`);
`mo` keeps its interval behavior and accepts an optional block size.
Some public data fields have new names; their repository consumers were updated.

## Naming conventions

- Graph state: `parent`, `head`, `subtreeSize`, `excess`, `height`, `potential`.
- Matching: `matchLeft`, `matchRight`, `matchingSize`, `parentRow`.
- Strings: `prefixHash`, `power`, `rank`, `failureLink`, `prevMatch`.
- Numerical code: `matrix`, `rhs`, `solution`, `pivotRow`, `pivotCol`, `coeff`.
- Geometry: `center`, `radius`, `hull`, `polygon`, `projection`, `distance2`.
- Keep compact statements, two-space indentation, and no blank separators between functions.

## Per-snippet review

The table records the original naming pass, including flow files now excluded
from the notebook. `MoTree.h` was added afterward as described above.

| Snippet | Renames / review |
| --- | --- |
| [IntPerm.h](../content/combinatorial/IntPerm.h) | `v` → `permutation`, `use` → `usedMask`, `r` → `rank`, `x` → `value` |
| [multinomial.h](../content/combinatorial/multinomial.h) | `v` → `counts`, `c` → `ways`, `m` → `total` |
| [template.cpp](../content/contest/template.cpp) | Reviewed; existing mathematical names and identifiers are already clear. |
| [OrderStatisticTree.h](../content/data-structures/OrderStatisticTree.h) | `t` → `ordered`, `t2` → `other`, `it` → `inserted` |
| [HashMap.h](../content/data-structures/HashMap.h) | `C` → `MULTIPLIER`, `x` → `key`, `h` → `hashMap` |
| [SegmentTree.h](../content/data-structures/SegmentTree.h) | `def` → `initialValue` |
| [LazySegmentTree.h](../content/data-structures/LazySegmentTree.h) | `a` → `values`, `initial` → `initialValue`, `assign` → `isAssignment` |
| [UnionFindRollback.h](../content/data-structures/UnionFindRollback.h) | `e` → `parentOrSize`, `st` → `history`, `t` → `checkpoint` |
| [SubMatrix.h](../content/data-structures/SubMatrix.h) | `p` → `prefix`, `v` → `values`, `R` → `rows`, `C` → `cols`, `u` → `top`, `l` → `left`, `d` → `bottom`, `r` → `right`, `r` → `row` (PrefixSum2D), `c` → `col` (PrefixSum2D) |
| [Matrix.h](../content/data-structures/Matrix.h) | `d` → `data`, `m` → `other`, `a` → `result`, `b` → `base`, `p` → `exponent`, `ret` → `result` |
| [LineContainer.h](../content/data-structures/LineContainer.h) | `k` → `slope`, `m` → `intercept`, `p` → `lastX`, `o` → `other`, `l` → `line`, `x` → `line` (bool isect), `y` → `nextLine` (bool isect), `x` → `prevLine` (void add), `y` → `line` (void add), `z` → `nextLine` (void add) |
| [Treap.h](../content/data-structures/Treap.h) | `y` → `priority`, `c` → `size`, `l` → `left`, `r` → `right`, `n` → `node`, `t` → `root`, `L` → `leftPart`, `R` → `rightPart`, `f` → `visit`, `k` → `leftCount` (pair<TreapNode *, TreapNode *> split), `a` → `prefix` (void move), `b` → `middle` (void move), `c` → `suffix` (void move), `k` → `targetPos` (void move) |
| [FenwickTree.h](../content/data-structures/FenwickTree.h) | `sum` → `targetSum` (int lowerBound) |
| [FenwickTree2d.h](../content/data-structures/FenwickTree2d.h) | `ys` → `yCoords` |
| [RMQ.h](../content/data-structures/RMQ.h) | `jmp` → `table`, `V` → `values`, `pw` → `halfLen`, `dep` → `level`, `a` → `l`, `b` → `r`, `j` → `pos` |
| [MoQueries.h](../content/data-structures/MoQueries.h) | `Q` → `queries`, `blk` → `blockSize`, `res` → `answers`, `ind` → `pos`, `end` → `side`, `ed` → `adj`, `in` → `active`, `par` → `parent`, `L` → `left` (vector<int> mo), `R` → `right` (vector<int> mo), `s` → `order` (vector<int> mo), `qi` → `queryId` (vector<int> mo), `q` → `query` (vector<int> mo), `N` → `timer` (vector<int> moTree), `I` → `entry` (vector<int> moTree), `L` → `tin` (vector<int> moTree), `R` → `tout` (vector<int> moTree), `s` → `order` (vector<int> moTree), `qi` → `queryId` (vector<int> moTree), `x` → `u` (vector<int> moTree), `p` → `parentVertex` (vector<int> moTree), `dep` → `parity` (vector<int> moTree), `y` → `v` (vector<int> moTree), `a` → `current` (vector<int> moTree), `b` → `target` (vector<int> moTree), `sort s/t` → `queryA/queryB`, `DFS f` → `self` |
| [Point.h](../content/geometry/Point.h) | `p` → `other`, `d` → `scale`, `a` → `angle` (P rotate) |
| [lineDistance.h](../content/geometry/lineDistance.h) | Reviewed; existing mathematical names and identifiers are already clear. |
| [SegmentDistance.h](../content/geometry/SegmentDistance.h) | `s` → `start`, `e` → `finish`, `d` → `length2`, `t` → `projection` |
| [SegmentIntersection.h](../content/geometry/SegmentIntersection.h) | `oa` → `sideA`, `ob` → `sideB`, `oc` → `sideC`, `od` → `sideD`, `s` → `intersections` |
| [lineIntersection.h](../content/geometry/lineIntersection.h) | `s1` → `start1`, `e1` → `end1`, `s2` → `start2`, `e2` → `end2`, `d` → `crossDir`, `p` → `weightStart`, `q` → `weightEnd` |
| [sideOf.h](../content/geometry/sideOf.h) | `s` → `start`, `e` → `finish`, `a` → `crossValue`, `l` → `tolerance` |
| [OnSegment.h](../content/geometry/OnSegment.h) | `s` → `start`, `e` → `finish` |
| [linearTransformation.h](../content/geometry/linearTransformation.h) | `p0` → `sourceStart`, `p1` → `sourceEnd`, `q0` → `targetStart`, `q1` → `targetEnd`, `r` → `point`, `dp` → `sourceDir`, `dq` → `targetDir`, `num` → `transform` |
| [Angle.h](../content/geometry/Angle.h) | `t` → `turns`, `tu` → `turnDiff`, `r` → `result` |
| [CircleIntersection.h](../content/geometry/CircleIntersection.h) | `a` → `center1`, `b` → `center2`, `vec` → `centerDir`, `d2` → `distance2`, `sum` → `radiusSum`, `dif` → `radiusDiff`, `p` → `projection`, `h2` → `height2`, `mid` → `basePoint`, `per` → `offset`, `out` → `intersections` |
| [CircleTangents.h](../content/geometry/CircleTangents.h) | `d` → `centerDir`, `dr` → `radiusDiff`, `d2` → `distance2`, `h2` → `height2`, `out` → `tangentPairs`, `v` → `normal` |
| [CirclePolygonIntersection.h](../content/geometry/CirclePolygonIntersection.h) | `c` → `center`, `r` → `radius`, `ps` → `polygon`, `tri` → `triangleArea`, `r2` → `halfRadius2`, `d` → `direction`, `a` → `linearTerm`, `b` → `constantTerm`, `det` → `discriminant`, `s` → `enter`, `t` → `exit`, `u` → `intersection1`, `v` → `intersection2`, `sum` → `area` |
| [circumcircle.h](../content/geometry/circumcircle.h) | `b` → `dirAC`, `c` → `dirAB` |
| [MinimumEnclosingCircle.h](../content/geometry/MinimumEnclosingCircle.h) | `ps` → `points`, `o` → `center`, `r` → `radius`, `EPS` → `tolerance` |
| [InsidePolygon.h](../content/geometry/InsidePolygon.h) | `p` → `polygon`, `a` → `point`, `q` → `nextPoint`, `cnt` → `inside` |
| [PolygonArea.h](../content/geometry/PolygonArea.h) | `v` → `polygon`, `a` → `area2` |
| [PolygonCenter.h](../content/geometry/PolygonCenter.h) | `v` → `polygon`, `res` → `weightedCenter`, `A` → `area2` |
| [PolygonCut.h](../content/geometry/PolygonCut.h) | `poly` → `polygon`, `s` → `start`, `e` → `finish`, `res` → `clipped`, `a` → `sideCurrent`, `b` → `sidePrevious` |
| [ConvexHull.h](../content/geometry/ConvexHull.h) | `pts` → `points`, `h` → `hull`, `s` → `chainStart`, `t` → `hullSize`, `it` → `pass` |
| [HullDiameter.h](../content/geometry/HullDiameter.h) | `S` → `hull`, `res` → `best` |
| [PointInsideHull.h](../content/geometry/PointInsideHull.h) | `l` → `hull`, `a` → `lo`, `b` → `hi`, `c` → `mid`, `r` → `boundaryAllowed` |
| [LineHullIntersection.h](../content/geometry/LineHullIntersection.h) | `poly` → `hull`, `dir` → `direction`, `m` → `mid`, `ls` → `loTrend`, `ms` → `midTrend`, `res` → `intersections`, `endA` → `maxVertex`, `endB` → `minVertex` |
| [ClosestPair.h](../content/geometry/ClosestPair.h) | `v` → `points`, `S` → `active`, `ret` → `best`, `d` → `window` |
| [kdTree.h](../content/geometry/kdTree.h) | `pt` → `point`, `x0` → `minX`, `x1` → `maxX`, `y0` → `minY`, `y1` → `maxY`, `vp` → `points`, `bfirst` → `nearDistance`, `bsec` → `farDistance`, `f` → `nearChild`, `s` → `farChild`, `x` → `closestX` (T distance), `y` → `closestY` (T distance) |
| [BellmanFord.h](../content/graph/BellmanFord.h) | `a` → `from`, `b` → `to`, `w` → `weight`, `eds` → `edges`, `s` → `source`, `lim` → `rounds`, `cur` → `fromState`, `dest` → `toState`, `d` → `newDist`, `ed` → `edge`, `e` → `edge`, `s()` → `sortKey()` |
| [TopoSort.h](../content/graph/TopoSort.h) | `gr` → `adj`, `indeg` → `inDegree`, `q` → `order`, `li` → `neighbors`, `x` → `v` |
| [PushRelabel.h](../content/graph/PushRelabel.h) | `dest` → `to`, `back` → `rev`, `f` → `flow`, `c` → `cap`, `g` → `adj`, `ec` → `excess`, `cur` → `currentEdge`, `hs` → `activeByHeight`, `H` → `height`, `co` → `heightCount`, `hi` → `maxHeight`, `rcap` → `reverseCap`, `v` → `n` |
| [MinCostMaxFlow.h](../content/graph/MinCostMaxFlow.h) | `N` → `n`, `ed` → `adj`, `pi` → `potential`, `par` → `parentEdge`, `di` → `adjustedDist`, `q` → `pq`, `its` → `handles`, `val` → `newDist`, `totflow` → `totalFlow`, `totcost` → `totalCost`, `fl` → `pushed`, `it` → `roundsLeft`, `ch` → `changed`, `v` → `newPotential`, `x` → `edge`, `edge (type)` → `Edge` |
| [EdmondsKarp.h](../content/graph/EdmondsKarp.h) | `par` → `parent`, `q` → `queue`, `ptr` → `queueSize`, `x` → `u`, `y` → `v`, `p` → `prev`, `inc` → `pushed` |
| [MinCut.h](../content/graph/MinCut.h) | Explanation only; no code variables to rename. |
| [HopcroftKarp.h](../content/graph/HopcroftKarp.h) | `g` → `adj`, `r` → `matchRight`, `l` → `matchLeft`, `q` → `queue`, `d` → `dist`, `res` → `matchingSize`, `f` → `self` (auto dfs), `t` → `nextDist` (auto dfs), `t` → `queueSize` (for ), `f` → `foundPath` (for ) |
| [DFSMatching.h](../content/graph/DFSMatching.h) | `g` → `adj`, `btoa` → `matchRight`, `vis` → `visited`, `di` → `matchedLeft`, `j` → `v`, `e` → `nextRight` |
| [MinimumVertexCover.h](../content/graph/MinimumVertexCover.h) | `g` → `adj`, `match` → `matchRight`, `res` → `matchingSize`, `lfound` → `reachableLeft`, `seen` → `reachableRight`, `q` → `stack`, `it` → `matchedLeft`, `e` → `v` |
| [WeightedMatching.h](../content/graph/WeightedMatching.h) | `C` → `costs`, `pot` → `potential`, `match` → `matchLeft`, `rev` → `matchRight`, `cols` → `colOrder`, `prev` → `parentRow`, `nd` → `newDist`, `d` → `minDist`, `s` → `scannedCols`, `c` → `col`, `r` → `row` |
| [GeneralMatching.h](../content/graph/GeneralMatching.h) | `N` → `n`, `ed` → `edges`, `mat` → `tutte`, `A` → `inverse`, `M` → `extendedSize`, `r` → `rank`, `pa` → `edge`, `has` → `active`, `ret` → `matching`, `a` → `pivotInverse`, `b` → `factor`, `matchI` → `matchedU`, `matchJ` → `matchedV`, `sw` → `pass`, `r` → `randomValue` (for ), `a` → `u` (for ), `b` → `v` (for ), `r` → `randomValue` (for ) |
| [SCC.h](../content/graph/SCC.h) | `st` → `activeStack` |
| [BiconnectedComponents.h](../content/graph/BiconnectedComponents.h) | `ed` → `adj`, `st` → `edgeStack`, `Time` → `timer`, `at` → `u`, `par` → `parentEdge`, `me` → `entryTime`, `top` → `low`, `y` → `v`, `e` → `edgeId`, `si` → `stackStart`, `up` → `childLow`, `f` → `visitComponent` |
| [2sat.h](../content/graph/2sat.h) | `N` → `variableCount`, `n` → `variableCount`, `gr` → `adj`, `f` → `literalA`, `j` → `literalB`, `li` → `literals`, `cur` → `currentLiteral`, `next` → `auxiliaryVar` |
| [EulerWalk.h](../content/graph/EulerWalk.h) | `gr` → `adj`, `nedges` → `edgeCount`, `src` → `source`, `D` → `balance`, `its` → `nextEdge`, `eu` → `usedEdge`, `ret` → `walk`, `s` → `stack`, `x` → `u`, `y` → `v`, `e` → `edgeId`, `end` → `degree`, `balance loop x` → `degreeDelta` |
| [EdgeColoring.h](../content/graph/EdgeColoring.h) | `N` → `n`, `eds` → `edges`, `cc` → `fanColor`, `ret` → `colors`, `free` → `freeColor`, `loc` → `colorPos`, `ncols` → `colorCount`, `at` → `current`, `end` → `lastVertex`, `ind` → `fanSize`, `cd` → `color`, `d` → `alternateColor`, `c` → `baseColor`, `e` → `edge`, `inner e` → `rotatedColor` |
| [MaximalCliques.h](../content/graph/MaximalCliques.h) | `eds` → `adj`, `P` → `candidates`, `X` → `excluded`, `R` → `clique`, `q` → `pivot`, `cands` → `branches`, `f` → `visitClique` |
| [MaximumClique.h](../content/graph/MaximumClique.h) | `pk` → `searchCount`, `e` → `adj`, `V` → `vertices`, `C` → `colorClasses`, `qmax` → `bestClique`, `q` → `clique`, `S` → `searchStats`, `old` → `prevStats`, `r` → `candidates`, `R` → `candidates`, `T` → `neighbors`, `lev` → `level`, `mxD` → `maxDegree`, `mxk` → `maxColor`, `mnk` → `minColor`, `conn` → `adjacency`, `f` → `isAdjacent`, `i` → `id` (struct Vertex), `d` → `bound` (struct Vertex), `Vertex.i` → `id`, `Vertex.d` → `bound`, `expand j` → `writePos`, `expand k` → `color`, `init j` → `other` |
| [MaximumIndependentSet.h](../content/graph/MaximumIndependentSet.h) | Explanation only; no code variables to rename. |
| [BinaryLifting.h](../content/graph/BinaryLifting.h) | Reviewed; existing mathematical names and identifiers are already clear. |
| [LCA.h](../content/graph/LCA.h) | `time` → `tin` |
| [CompressTree.h](../content/graph/CompressTree.h) | `time` → `tin`, `rev` → `virtualIndex`, `li` → `vertices`, `T` → `entryTime`, `ret` → `virtualTree` |
| [HLD.h](../content/graph/HLD.h) | `N` → `n`, `tim` → `timer`, `par` → `parent`, `siz` → `subtreeSize`, `rt` → `head`, `adj_` → `graph`, `op` → `visitRange`, `res` → `answer` |
| [DirectedMST.h](../content/graph/DirectedMST.h) | `a` → `from`, `b` → `to`, `w` → `weight`, `l` → `left`, `r` → `root`, `g` → `edges`, `uf` → `dsu`, `res` → `totalWeight`, `par` → `parent`, `Q` → `pathEdges`, `in` → `incoming`, `comp` → `cycleEdges`, `cycs` → `cycles`, `qi` → `pathSize`, `cyc` → `cycleHeap`, `time` → `checkpoint`, `a` → `first` (SkewHeapNode *merge), `b` → `second` (SkewHeapNode *merge), `w` → `cycleVertex` (int u = s), `w` → `cycleVertex` (do cyc), `SkewHeapNode.r` → `right` |
| [ModularArithmetic.h](../content/number-theory/ModularArithmetic.h) | `x` → `value`, `y` → `normalized`, `b` → `other`, `a` → `operand`, `g` → `gcdValue`, `e` → `exponent`, `r` → `result`, `x` → `inverseCoeff` (Mod invert), `y` → `otherCoeff` (Mod invert) |
| [ModInverse.h](../content/number-theory/ModInverse.h) | `inv` → `inverse` |
| [ModPow.h](../content/number-theory/ModPow.h) | `b` → `base`, `e` → `exponent`, `ans` → `result` |
| [ModLog.h](../content/number-theory/ModLog.h) | `a` → `base`, `b` → `target`, `m` → `modulus`, `n` → `blockSize`, `e` → `power`, `f` → `giantStep`, `A` → `babySteps` |
| [ModSum.h](../content/number-theory/ModSum.h) | `to` → `count`, `to2` → `nextCount`, `c` → `offset`, `k` → `slope`, `m` → `modulus`, `res` → `answer` |
| [ModMulLL.h](../content/number-theory/ModMulLL.h) | `a` → `lhs` (ull modmul), `b` → `rhs` (ull modmul), `M` → `modulus` (ull modmul), `ret` → `remainder` (ull modmul), `b` → `base` (ull modpow), `e` → `exponent` (ull modpow), `ans` → `result` (ull modpow) |
| [ModSqrt.h](../content/number-theory/ModSqrt.h) | `p` → `prime`, `s` → `oddPart`, `n` → `nonResidue`, `r` → `twos`, `m` → `order`, `b` → `remainder`, `g` → `rootOfUnity`, `t` → `power`, `gs` → `correction` |
| [FastEratosthenes.h](../content/number-theory/FastEratosthenes.h) | `S` → `blockSize`, `R` → `oddCount`, `pr` → `primes`, `cp` → `sievingPrimes`, `L` → `blockStart`, `idx` → `nextMultiple` |
| [MillerRabin.h](../content/number-theory/MillerRabin.h) | `A` → `bases`, `s` → `twos`, `d` → `oddPart`, `a` → `base`, `p` → `power`, `i` → `squaresLeft` |
| [Factor.h](../content/number-theory/Factor.h) | `x` → `slow` (ull pollard), `y` → `fast` (ull pollard), `t` → `iterations` (ull pollard), `prd` → `product` (ull pollard), `i` → `seed` (ull pollard), `q` → `nextProduct` (ull pollard), `f` → `advance` (ull pollard), `x` → `divisor` (vector<ull> factor), `l` → `leftFactors` (vector<ull> factor), `r` → `rightFactors` (vector<ull> factor) |
| [euclid.h](../content/number-theory/euclid.h) | `d` → `gcdValue` |
| [CRT.h](../content/number-theory/CRT.h) | `g` → `gcdValue` |
| [phiFunction.h](../content/number-theory/phiFunction.h) | Reviewed; existing mathematical names and identifiers are already clear. |
| [ContinuedFractions.h](../content/number-theory/ContinuedFractions.h) | `LP` → `prevNum`, `LQ` → `prevDen`, `P` → `numerator`, `Q` → `denominator`, `NP` → `nextNum`, `NQ` → `nextDen`, `N` → `limit`, `lim` → `maxStep`, `a` → `quotient`, `b` → `step`, `y` → `remainder` |
| [FracBinarySearch.h](../content/number-theory/FracBinarySearch.h) | `N` → `limit`, `dir` → `moveHi`, `A` → `prevAdvanced`, `B` → `advanced`, `adv` → `advance`, `si` → `shift`, `f` → `predicate` |
| [Polynomial.h](../content/numerical/Polynomial.h) | `a` → `coeff`, `val` → `value`, `x0` → `root`, `b` → `carry`, `c` → `oldCoeff` |
| [PolyRoots.h](../content/numerical/PolyRoots.h) | `p` → `poly`, `a` → `coeff`, `xmin` → `minX`, `xmax` → `maxX`, `ret` → `roots`, `der` → `derivative`, `dr` → `criticalPoints`, `l` → `lo`, `h` → `hi`, `m` → `mid`, `f` → `value`, `sign` → `positiveLeft` |
| [PolyInterpolate.h](../content/numerical/PolyInterpolate.h) | `res` → `coeff`, `temp` → `basis`, `last` → `previous` |
| [LinearRecurrence.h](../content/numerical/LinearRecurrence.h) | `S` → `initial`, `tr` → `recurrence`, `k` → `index`, `res` → `result`, `pol` → `weights`, `e` → `power` |
| [Determinant.h](../content/numerical/Determinant.h) | `a` → `matrix`, `res` → `determinant`, `b` → `pivotRow`, `v` → `factor` |
| [IntDeterminant.h](../content/numerical/IntDeterminant.h) | `a` → `matrix`, `ans` → `determinant`, `t` → `quotient` |
| [SolveLinear.h](../content/numerical/SolveLinear.h) | `A` → `matrix`, `b` → `rhs`, `x` → `solution`, `br` → `pivotRow`, `bc` → `pivotCol`, `col` → `colOrder`, `v` → `magnitude`, `bv` → `pivotValue`, `fac` → `factor` |
| [SolveLinear2.h](../content/numerical/SolveLinear2.h) | `A` → `matrix`, `b` → `rhs`, `x` → `solution`, `col` → `colOrder` |
| [SolveLinearBinary.h](../content/numerical/SolveLinearBinary.h) | `A` → `matrix`, `b` → `rhs`, `x` → `solution`, `br` → `pivotRow`, `bc` → `pivotCol`, `col` → `colOrder` |
| [MatrixInverse.h](../content/numerical/MatrixInverse.h) | `A` → `matrix`, `col` → `colOrder`, `tmp` → `inverse`, `r` → `pivotRow`, `c` → `pivotCol`, `v` → `pivot`, `f` → `factor` |
| [Tridiagonal.h](../content/numerical/Tridiagonal.h) | `b` → `rhs`, `tr` → `swapped` |
| [KMP.h](../content/strings/KMP.h) | `s` → `text`, `m` → `patternLength` |
| [Zfunc.h](../content/strings/Zfunc.h) | `s` → `text`, `l` → `left`, `r` → `right` |
| [Manacher.h](../content/strings/Manacher.h) | `p` → `radius`, `z` → `parity`, `t` → `remaining`, `L` → `left`, `R` → `right`, `l` → `windowLeft`, `r` → `windowRight` |
| [MinRotation.h](../content/strings/MinRotation.h) | `a` → `bestStart`, `N` → `n`, `b` → `candidate`, `k` → `offset` |
| [SuffixArray.h](../content/strings/SuffixArray.h) | `lim` → `alphabetSize`, `x` → `rank`, `y` → `order`, `ws` → `count`, `k` → `commonLength`, `a` → `prevSuffix`, `b` → `suffix`, `j` → `length` (for ), `p` → `classes` (for ) |
| [Hashing.h](../content/strings/Hashing.h) | `x` → `value`, `o` → `other`, `m` → `product`, `C` → `HASH_BASE`, `ha` → `prefixHash`, `pw` → `power`, `h` → `hash`, `ret` → `hashes`, `str` → `text`, `a` → `l`, `b` → `r` |
| [AhoCorasick.h](../content/strings/AhoCorasick.h) | `alpha` → `ALPHABET`, `first` → `FIRST_CHAR`, `back` → `failureLink`, `start` → `firstMatch`, `end` → `lastMatch`, `nmatches` → `matchCount`, `N` → `nodes`, `backp` → `prevMatch`, `s` → `pattern`, `j` → `patternId`, `n` → `state`, `m` → `nextState`, `prev` → `failureState`, `ed` → `transition`, `y` → `fallback`, `pat` → `patterns`, `q` → `queue`, `r` → `matches`, `ind` → `patternId`, `res` → `positions` |
| [IntervalContainer.h](../content/various/IntervalContainer.h) | `is` → `intervals`, `L` → `l`, `R` → `r`, `before` → `hint`, `r2` → `oldRight` |
| [IntervalCover.h](../content/various/IntervalCover.h) | `G` → `target`, `I` → `intervals`, `S` → `order`, `R` → `chosen`, `cur` → `coveredTo`, `at` → `nextInterval`, `mx` → `farthest` |
| [ConstantIntervals.h](../content/various/ConstantIntervals.h) | `f` → `valueAt`, `g` → `visitInterval`, `i` → `intervalStart`, `p` → `currentValue`, `q` → `endValue` |
| [TernarySearch.h](../content/various/TernarySearch.h) | `a` → `lo`, `b` → `hi`, `f` → `valueAt` |
| [FastKnapsack.h](../content/various/FastKnapsack.h) | `w` → `weights`, `t` → `capacity`, `a` → `total`, `b` → `prefixSize`, `m` → `maxWeight`, `u` → `previous`, `v` → `dp`, `x` → `state` |
| [KnuthDP.h](../content/various/KnuthDP.h) | Explanation only; no code variables to rename. |
| [DivideAndConquerDP.h](../content/various/DivideAndConquerDP.h) | `ind` → `index`, `k` → `split`, `v` → `value`, `res` → `answer`, `L` → `l`, `R` → `r`, `LO` → `optL`, `HI` → `optR` |
| [FastMod.h](../content/various/FastMod.h) | `b` → `modulus`, `m` → `reciprocal`, `a` → `value` |
| [FastInput.h](../content/various/FastInput.h) | `buf` → `buffer`, `bc` → `bufferPos`, `be` → `bufferSize`, `a` → `value`, `c` → `digit` |

## Dependencies and examples

- Updated the modular matrix inverse used by general matching.
- Kept the alternate rolling-hash implementation consistent with `prefixHash` and `power`.
- Updated existing consumers of treap children, modular values, inverse tables, flow-edge fields, and directed-MST edges.
- LCA uses `tin` for DFS entry order; virtual-tree construction uses the same field.
- Existing algorithm tests were not executed for this naming pass.

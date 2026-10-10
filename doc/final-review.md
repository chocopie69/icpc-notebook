# Final notebook review — 2026-10-10

The selected notebook was reviewed against its personal C++17 template, randomized
reference tests, and online algorithm references. The PDF retains the existing
algorithm selection and the 26-page target, including the cover.

## Fixes

- **Modular inverse:** removed `new ll[LIM] - 1`, which formed a pointer before the
  allocated array. Indexing now uses the allocated array directly; the description
  requires `2 <= LIM <= mod`.
- **Divide-and-conquer DP:** removed conversion through `pair<int,int>`, which
  truncated 64-bit DP values. The example destination uses `pair<int,ll>`.
- **Integer ternary search:** widened midpoint and interval arithmetic and removed
  `hi+1` from the final scan. Full `INT_MIN..INT_MAX` bounds now work.
- **BigInt:** replaced the nonstandard `bits/stdc++.h` include with the standard
  headers actually needed by the implementation.
- **Formula notes:** fixed the summand in the Bernoulli power-sum formula, restored
  the coefficients in the mean of a linear combination of normal variables,
  stated independence, and repaired the missing operand in Bézout's prerequisites.
- **Test harnesses:** updated RMQ, LCA, topological sort, sieve, hashing, and DSU
  tests to the personalized APIs. Modular square-root tests now use the included
  modular exponentiation function and handle modulus 2 separately. These were
  stale harness failures, rather than evidence of algorithm failures.

## Validation

- All **83 pre-existing C++ stress programs passed**, including the restored flow
  algorithms, bipartite matching, geometry, factorization, and recurrence tests.
- Three new C++ programs passed independent reference checks: custom notebook
  data structures/tree algorithms, biconnected components, and polynomial/matrix
  operations. This gives **86 passing C++ stress programs** in total.
- **105 selected headers** passed compilation with the personal template and
  documented setup. The additional `SolveLinear2` entry is an edit recipe;
  the checker applies it to the real solver and tests uniquely determined,
  free, and inconsistent variables. Explanatory headers also count in this total.
- The broader repository check passed for **151 eligible headers**, with setup
  supplied for the documented customization snippets.
- The personal array and tree Mo implementations were tested directly, with
  filled callbacks, on **2,000 random cases**, including empty query batches,
  single-vertex paths, arbitrary roots, and endpoint removal assertions.
- The DP customization was checked against exhaustive split searches with
  values exceeding `INT_MAX`; topological cycle detection was checked separately.
- BigInt passed **1,068 cases against Python integers**, including signed division
  and inputs up to 1,500 decimal digits, plus its C++ arithmetic tests.
- Undefined-behavior sanitizer checks passed for BigInt, integer ternary search,
  and the custom notebook extensions. Four page-header renderer tests passed.
- The final two-pass PDF build produced **26 nonempty A4 landscape pages** with
  **109 snippet bookmarks**. Extracted text stayed within page bounds; LaTeX
  reported no overfull boxes or unresolved references. Changed pages were also
  visually checked, and the exported PDF matches the build artifact byte for byte.

The reusable checker is [test-notebook.py](scripts/test-notebook.py).
`make test` runs the C++ suite and the extra Python checks. `make test-compiles`
checks the broader repository with the personal template. The excluded
Hashing-codeforces and NTT snippets need separate configuration, and Unrolling
is an edit recipe; these are not counted as standalone compile successes.
Detailed generated drivers and compiler logs are in `build/notebook-checks/`.

Compilation and stress testing increase confidence; they do not prove correctness
for every input. Respect each snippet's stated indexing, overflow limits,
recursion depth, floating-point tolerances, and customization requirements.

## Algorithm coverage

Compared the active chapter imports, not merely the files on disk, with
[upstream KACTL](https://github.com/kth-competitive-programming/kactl),
[CP-Algorithms](https://cp-algorithms.com/), and the
[AtCoder Library](https://atcoder.github.io/ac-library/production/document_en/index.html).
The following priorities are my recommendations based on the capabilities missing
from this edition, rather than a required ICPC checklist.

| Priority | Gap in the PDF | Existing source / recommended action |
| --- | --- | --- |
| Highest | Multi-pattern matching | Restore [Aho-Corasick](../content/strings/AhoCorasick.h) if the team needs simultaneous matching of many patterns. A plain trie or KMP does not provide the same scanning capability. [Reference](https://cp-algorithms.com/string/aho_corasick.html). |
| Highest | Fast polynomial convolution | Restore [NTT](../content/numerical/NumberTheoreticTransform.h), or FFT/FFTMod for the required coefficient domain. Interpolation and `Polynomial` do not provide fast multiplication. All three existing convolution stress programs passed. [Reference](https://cp-algorithms.com/algebra/fft.html). |
| High | Suffix indexing / substring statistics | Suffix Array is intentionally excluded; consider restoring it, or adding a suffix automaton for distinct substrings and substring occurrence tasks. There is no suffix automaton implementation in this repository. [Reference](https://cp-algorithms.com/string/suffix-automaton.html). |
| High | Recovering unknown recurrences | [Berlekamp–Massey](../content/numerical/BerlekampMassey.h) exists and passed its tests, but is excluded from the PDF even though LinearRecurrence mentions it. Restore it if recurrence inference is expected. |
| Useful adaptation | Offline dynamic connectivity | Rollback DSU is present; the segment tree over edge-lifetime intervals is missing. Add a reduction recipe if needed. [Reference](https://cp-algorithms.com/data_structures/deleting_in_log_n.html). |
| Useful adaptation | Flow with lower bounds | Dinic mentions the circulation reduction but does not show it. Add demand balances, a super-source/sink, and the feasibility test as a compact recipe. [Reference](https://cp-algorithms.com/graph/flow_with_demands.html). |
| Specialist | Half-plane intersection | No implementation exists here. Polygon clipping can handle small cases, but repeated clipping is not the same complexity as the standard sorted half-plane algorithm. [Reference](https://cp-algorithms.com/geometry/halfplane-intersection.html). |
| Short notes | Game theory | Add Nim xor, mex, Sprague–Grundy composition, and misère Nim rules if the team wants a reminder. [Reference](https://cp-algorithms.com/game_theory/sprague-grundy-nim.html). |

Dijkstra, Kruskal/Prim, binary exponentiation, basic BFS/DFS, standard knapsack,
and elementary prefix sums are reasonable memory-based omissions for a compact
notebook. Floyd–Warshall exists in the repository but is not selected.
Bridges/articulation points require adapting the included biconnected-component
DFS. A separate Li Chao tree is lower priority because the existing CHT already
supports dynamic integer lines; it is useful for other function/domain variants.
[Reference](https://cp-algorithms.com/geometry/convex_hull_trick.html).

The highest-value space tradeoff would be restoring Aho-Corasick and one convolution
implementation before adding more specialist algorithms. Existing deliberate
exclusions remain unchanged in the rebuilt PDF.

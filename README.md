# KACTL

This repo hosts KACTL, [KTH](https://en.wikipedia.org/wiki/KTH_Royal_Institute_of_Technology)'s ICPC team reference document.
This personalized edition consists of 26 pages including the cover, for use in ICPC-style programming competitions.

See [kactl.pdf](./kactl.pdf) for the final, browsable version, and [content/](./content/) for raw source code.

The page immediately after the cover contains the full ICPC strategy article from
`doc/strategy.tex`, arranged in three columns. The Markov chains section is excluded.

## Aspirations

KACTL algorithms should be: useful, short, fast enough, well tested, and if relevant, readable and easy to modify.
They should *not* be overly generic, since code is manually typed and that just adds overhead.
Due to space issues, we also exclude algorithms that are very common/simple (e.g., Dijkstra), or very uncommon (general weighted matching).

If you feel that something is missing, could be cleaned up, or notice a bug, please file an issue or [send a pull request](https://help.github.com/articles/fork-a-repo/)!

## Customizing KACTL

While KACTL is usable as is, it's also easy to modify if you want to create a personalized copy.
In particular, you may want to change the cover page, or make your own choice of algorithms to include --
due to space concerns, not all algorithms in the repo are included in the pdf.
You may also want to enable colored syntax highlighting.

`content/kactl.tex` is the main file of KACTL, and can be edited to change team name, logo, syntax highlighting, etc.
It imports `chapter.tex` files from each of the `content/` subdirectories, which define the contents of each chapter.
These include source code, text and math in the form of LaTeX.
To add/remove code from a chapter, add/remove a corresponding `\kactlimport` line from the `chapter.tex` file.
For nicer alignment you might want to insert `\hardcolumnbreak`, `\columnbreak` or `\newpage` commands,
though this is usually only done before important contests, and not on the main branch.
The algorithms that are not included in the pdf are left commented out in `chapter.tex`.

To build KACTL, type `make kactl` (or `make fast`) on a \*nix machine -- this will update `kactl.pdf`.
(Windows might work as well, but is not tested.) `doc/README` has a few more notes about this.

Tips:
1. Check out what's excluded by default by running `make showexcluded`.
The default configuration is chosen to be a reasonable balance for beginners
and advanced teams.
2. Use `hash.sh` or the `:Hash` command from the `.vimrc` to compare typed copies
with source files. Hashing ignores whitespace and comments. The PDF omits snippet
hashes and line counts, while retaining dependency captions. Shell setup, Vim setup,
and Code checksum are excluded from the PDF; their source files remain available.
3. Use the PDF's bookmark sidebar to jump to a chapter, section, or individual snippet.
Each snippet has its own bookmark; the main printed contents stays compact.
4. Snippet headings and bookmarks use readable algorithm names, with aliases such as
BIT, DSU, RMQ, and CHT. Edit `content/tex/snippet-names.tex` to change a displayed name.

## Coding style

This edition uses the macros defined in the [personal template](./content/contest/template.cpp).
Snippets use explicit `for` loops and `vector<int>` instead of KACTL's `rep` and `vi` helpers,
with two spaces for indentation and no empty separators between function definitions.
The formatting rules are stored in `.clang-format`. The template defines `ll` and `ull` as macros, so snippets
use casts such as `(ll)(value)` and rely on the template's integer type definitions.
Common types use descriptive names: `SegTree`, `LazySegTree`, `Fenwick`, `Fenwick2D`,
`DSU`, `RollbackDSU`, `SparseTable`, `OrderedSet`, `CHT`, and `StringHash`.

The personal Code::Blocks versions supply KMP's prefix function, DSU, inclusive
min/max RMQ, polynomial hashing, and both ordinary and linear prime sieves.
RMQ and substring hashing use 1-based inclusive bounds. The tree section includes
one self-contained Binary Lifting + LCA snippet (with weighted distances) and
the separate Euler-tour + RMQ LCA version.

The notebook also includes 0–1 BFS and fixed-length sliding-window minimum/maximum.
Suffix Array is excluded from the PDF.

The rewritten core snippets use opening braces on the same line, omit braces for
simple single-statement branches and loops, and keep small wrappers on one line.
Branches with multiple operations remain explicit; comma expressions are avoided.
Fenwick and segment trees use 1-based positions and inclusive query ranges `[l, r]`.
`Fenwick::lowerBound(sum)` returns 0 for a nonpositive target and n+1 if no prefix reaches it.
`LazySegTree(a)` expects a 1-based vector with a[0] unused; `LazySegTree(n, 0)` starts with zeros.
LCA and SCC default to 1-based adjacency lists. Use `LCA(adj, 0)` or `SCC(adj, 0)`
for a 0-based graph. The ancestor table is `up[u][k]`; `buildAncestorTable` replaces `treeJump`.
SCC exposes `comp` and `components` directly, without a callback.
String indices and KMP match positions are 0-based. Each rewritten header states its
indexing, assumptions, complexity and a small usage example.

All notebook snippets have a [per-snippet naming review](./doc/snippet-naming.md).
State names describe their roles, such as `parent`, `matchRight`, `extraLca`,
`prefixHash`, `coeff`, and `pivotRow`. Standard vertex names, indices and point
coordinates stay compact. LCA's DFS entry order is stored in `tin`.

Mo is split into two snippets: `mo` handles 0-based, inclusive array intervals `[l,r]`,
and `MoTree.h` handles inclusive paths on a 1-based tree. The tree version follows
the linked example's arrays and free functions: `dfs` builds ancestors and the
entry/exit Euler tour together, `makeQuery` converts paths, and `compute` answers
them. Compress values to `1..n` first; edit `check` and the answer assignment for
other statistics that do not depend on path order.
The notebook excludes all network-flow algorithms; their source files remain in
the repository alongside the other excluded algorithms.

Every included algorithm has description and usage notes; see the
[coverage list](./doc/snippet-usage.md). Notes state setup, indexing, assumptions,
return values, and changes to input data. Entries that are customization recipes
are explicitly identified. Usage examples are printed in the PDF as well as kept
in the source headers. Familiar algorithms use concise implementation notes;
their full usage examples are retained. Aho-Corasick, 2D prefix sums, directed MST,
and the Techniques appendix are excluded from this edition.

Each algorithm contains a header with the author of the code, the date it
was added, a description of the algorithm, its testing status, and preferably also
source, license and time complexity.

This personalized edition includes explanatory notes; its page count follows the selected algorithms and notes.
Occasionally the generated kactl.pdf is committed to the repo for convenience, but not too often because it makes git operations slower.

## Testing

KACTL aims for a high level of confidence in algorithm correctness.
Testing is done both on online judges and (for newer algorithms) with stress tests
that compare output to a more naive algorithm for a large amount of randomly generated cases.
These tests live in the `stress-tests` directory, and are run with CI on every commit. The CI also verifies that all headers compile (except for an exclude list in `docs/scripts/skip_headers`) and that the latex compiles.

`old-unit-tests` contains a couple of broken unit tests, last touched about ten years ago.

## License

As usual for competitive programming, the licensing situation is a bit unclear.
Many source files are marked with license (we try to go with
[CC0](https://creativecommons.org/share-your-work/public-domain/cc0/)), but many also aren't.
Presumably good will is to be assumed from other authors, though, and in many cases permission should not be needed since the code is not distributed.
To help trace things back, sources and authors are noted in source files.

Everything in `stress-tests` is implicitly CC0, except reference implementations taken from around the Internet.

The DP section includes SOS subset/superset transforms and inverses. The tree section
includes centroid decomposition with a nearest-marked-vertex example. Fast Modular,
Fast Input, and Debugging tricks are excluded from the PDF.

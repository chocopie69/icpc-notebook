/**
 * Author: Simon Lindholm
 * License: CC0
 * Source: http://codeforces.com/blog/entry/8219
 * Description: When doing DP on intervals: $a[i][j] = \min_{i < k < j}(a[i][k] + a[k][j]) + f(i, j)$, where the (minimal) optimal $k$ increases with both $i$ and $j$,
 *  one can solve intervals in increasing order of length, and search $k = p[i][j]$ for $a[i][j]$ only between $p[i][j-1]$ and $p[i+1][j]$.
 *  This is known as Knuth DP. Sufficient criteria for this are if $f(b,c) \le f(a,d)$ and $f(a,c) + f(b,d) \le f(a,d) + f(b,c)$ for all $a \le b \le c \le d$.
 *  Consider also: CHT (ch. Data structures), monotone queues, ternary search.
 * This is a recurrence recipe, not a callable function. Typical use is optimal merging of
 * adjacent segments with f(i,j) equal to interval sum. Initialize base intervals and optimal
 * split positions, then process increasing lengths. The required monotonicity concerns optimal
 * splits, not DP values; prove it or establish the sufficient inequalities before using the
 * bound.
 * Time: O(N^2)
 * Usage: // For each increasing interval [i,j], try only splits
 * // opt[i][j-1]<=k<=opt[i+1][j], also restricted to i<k<j.
 * // Save dp[i][j] and its smallest minimizing split.
 */

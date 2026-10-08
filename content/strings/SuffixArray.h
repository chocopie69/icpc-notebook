/**
 * Author: 罗穗骞, chilli
 * Date: 2019-04-11
 * License: Unknown
 * Source: Suffix array - a powerful tool for dealing with strings
 * (Chinese IOI National team training paper, 2009)
 * Description: Builds suffix array for a string.
 * \texttt{sa[i]} is the starting index of the suffix which
 * is $i$'th in the sorted suffix array.
 * The returned vector is of size $n+1$, and \texttt{sa[0] = n}.
 * The \texttt{lcp} array contains longest common prefixes for
 * neighbouring strings in the suffix array:
 * \texttt{lcp[i] = lcp(sa[i], sa[i-1])}, \texttt{lcp[0] = 0}.
 * The input string must not contain any nul chars.
 * Use for lexicographic suffix queries, repeated substrings, or distinct-substring counts.
 * Indices are 0-based; skip sa[0] when iterating nonempty suffixes. For arbitrary suffix LCP
 * queries, build RMQ over lcp between their ranks. The default alphabet is byte-sized and
 * assumes nonnegative character values.
 * Time: O(n \log n)
 * Status: stress-tested
 * Usage: SuffixArray suffixes("banana");
 * // sa={6,5,3,1,0,4,2}; lcp={0,0,1,3,0,0,2}
 */
#pragma once
struct SuffixArray {
  vector<int> sa, lcp;
  SuffixArray(string s, int alphabetSize = 256) { // or vector<int>
    s.push_back(0);
    int n = sz(s), commonLength = 0, prevSuffix, suffix;
    vector<int> rank(all(s)), order(n), count(max(n, alphabetSize));
    sa = lcp = order, iota(all(sa), 0);
    for (int length = 0, classes = 0; classes < n;
         length = max(1, length * 2), alphabetSize = classes) {
      classes = length, iota(all(order), n - length);
      for (int i = 0; i < (n); ++i)
        if (sa[i] >= length) order[classes++] = sa[i] - length;
      fill(all(count), 0);
      for (int i = 0; i < (n); ++i) count[rank[i]]++;
      for (int i = 1; i < (alphabetSize); ++i) count[i] += count[i - 1];
      for (int i = n; i--;) sa[--count[rank[order[i]]]] = order[i];
      // After swapping, order holds the previous ranks.
      swap(rank, order), classes = 1, rank[sa[0]] = 0;
      for (int i = 1; i < (n); ++i)
        prevSuffix = sa[i - 1], suffix = sa[i],
        rank[suffix] = (order[prevSuffix] == order[suffix] &&
                        order[prevSuffix + length] == order[suffix + length])
                           ? classes - 1
                           : classes++;
    }
    for (int i = 0, j; i < n - 1; lcp[rank[i++]] = commonLength)
      for (commonLength &&commonLength--, j = sa[rank[i] - 1];
           s[i + commonLength] == s[j + commonLength]; commonLength++);
  }
};

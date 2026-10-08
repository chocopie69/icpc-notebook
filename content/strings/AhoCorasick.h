/**
 * Author: Simon Lindholm
 * Date: 2015-02-18
 * License: CC0
 * Source: marian's (TC) code
 * Description: Aho-Corasick automaton, used for multiple pattern matching.
 * Initialize with AhoCorasick ac(patterns); the automaton start node will be at index 0.
 * find(word) returns for each position the index of the longest word that ends there, or -1 if none.
 * findAll($-$, word) finds all words (up to $N \sqrt N$ many if no duplicate patterns)
 * that start at each position (shortest first).
 * Duplicate patterns are allowed; empty patterns are not.
 * To find the longest words that start at each position, reverse all input.
 * For large alphabets, split each symbol into chunks, with sentinel bits for symbol boundaries.
 * The default alphabet is uppercase A..Z; set FIRST\_CHAR to lowercase a for lowercase input,
 * and adjust ALPHABET for another contiguous alphabet. All characters must fit. Build from the
 * full pattern list once; later insertions do not rebuild failure links. find groups matches by
 * ending position, findAll by starting position.
 * Time: construction takes $O(26N)$, where $N =$ sum of length of patterns.
 * find(x) is $O(N)$, where N = length of x. findAll is $O(NM)$.
 * Status: stress-tested
 * Usage: vector<string> patterns={"ABA","BA"};
 * AhoCorasick ac(patterns); auto ends=ac.find("ABABA");
 * auto starts=ac.findAll(patterns,"ABABA");
 */
#pragma once
struct AhoCorasick {
  enum { ALPHABET = 26, FIRST_CHAR = 'A' }; // change this!
  struct Node {
    // (matchCount is optional)
    int failureLink, next[ALPHABET], firstMatch = -1, lastMatch = -1, matchCount = 0;
    Node(int v) { memset(next, v, sizeof(next)); }
  };
  vector<Node> nodes;
  vector<int> prevMatch;
  void insert(string &pattern, int patternId) {
    assert(!pattern.empty());
    int state = 0;
    for (char c : pattern) {
      int &nextState = nodes[state].next[c - FIRST_CHAR];
      if (nextState == -1) {
        state = nextState = sz(nodes);
        nodes.emplace_back(-1);
      } else
        state = nextState;
    }
    if (nodes[state].lastMatch == -1) nodes[state].firstMatch = patternId;
    prevMatch.push_back(nodes[state].lastMatch);
    nodes[state].lastMatch = patternId;
    nodes[state].matchCount++;
  }
  AhoCorasick(vector<string> &patterns) : nodes(1, -1) {
    for (int i = 0; i < (sz(patterns)); ++i) insert(patterns[i], i);
    nodes[0].failureLink = sz(nodes);
    nodes.emplace_back(0);

    queue<int> queue;
    for (queue.push(0); !queue.empty(); queue.pop()) {
      int state = queue.front(), failureState = nodes[state].failureLink;
      for (int i = 0; i < (ALPHABET); ++i) {
        int &transition = nodes[state].next[i], fallback = nodes[failureState].next[i];
        if (transition == -1)
          transition = fallback;
        else {
          nodes[transition].failureLink = fallback;
          (nodes[transition].lastMatch == -1 ? nodes[transition].lastMatch
                                             : prevMatch[nodes[transition].firstMatch]) =
              nodes[fallback].lastMatch;
          nodes[transition].matchCount += nodes[fallback].matchCount;
          queue.push(transition);
        }
      }
    }
  }
  vector<int> find(string word) {
    int state = 0;
    vector<int> positions; // ll count = 0;
    for (char c : word) {
      state = nodes[state].next[c - FIRST_CHAR];
      positions.push_back(nodes[state].lastMatch);
      // count += nodes[state].matchCount;
    }
    return positions;
  }
  vector<vector<int>> findAll(vector<string> &patterns, string word) {
    vector<int> matches = find(word);
    vector<vector<int>> positions(sz(word));
    for (int i = 0; i < (sz(word)); ++i) {
      int patternId = matches[i];
      while (patternId != -1) {
        positions[i - sz(patterns[patternId]) + 1].push_back(patternId);
        patternId = prevMatch[patternId];
      }
    }
    return positions;
  }
};

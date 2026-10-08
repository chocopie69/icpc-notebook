/**
 * Author: VNOI Wiki, adapted to the notebook style
 * Source: https://wiki.vnoi.info/algo/string/trie
 * Description: Pointer trie for lowercase a..z, with duplicate strings. endCount counts strings
 * ending at a node; passCount counts strings with that prefix (including exact matches).
 * addString inserts one copy; deleteString removes one copy, doing nothing if absent.
 * Unused nodes are freed during deletion; the destructor frees the remaining trie.
 * Empty strings are supported; countPrefix("") counts all inserted copies. Change the alphabet
 * size and character mapping for other symbols. Recursive deletion/destruction may use stack
 * depth equal to the longest string. Copying is disabled because the trie owns its pointers.
 * Usage: Trie trie;
 * trie.addString("abc"); trie.addString("abc"); trie.addString("abd");
 * bool found=trie.findString("abc"); // true; a prefix alone is not an exact match
 * int count=trie.countPrefix("ab"); // 3, including duplicates
 * trie.deleteString("abc"); // one copy remains
 * // Use a fresh object per test case; its destructor releases the nodes.
 * Time: $O(L)$ per operation for string length L; $O(26S)$ memory for S distinct prefixes.
 */
#pragma once
struct Trie {
  struct Node {
    Node *child[26] = {};
    int endCount = 0, passCount = 0;
    ~Node() {
      for (Node *next : child) delete next;
    }
  };
  Node *root = new Node();
  Trie() = default;
  Trie(const Trie &) = delete;
  Trie &operator=(const Trie &) = delete;
  ~Trie() { delete root; }
  void addString(const string &s) {
    Node *node = root;
    node->passCount++;
    for (char ch : s) {
      int letter = ch - 'a';
      if (!node->child[letter]) node->child[letter] = new Node();
      node = node->child[letter];
      node->passCount++;
    }
    node->endCount++;
  }
  Node *findNode(const string &s) const {
    Node *node = root;
    for (char ch : s) {
      node = node->child[ch - 'a'];
      if (!node) return nullptr;
    }
    return node;
  }
  bool findString(const string &s) const {
    Node *node = findNode(s);
    return node && node->endCount;
  }
  int countPrefix(const string &s) const {
    Node *node = findNode(s);
    return node ? node->passCount : 0;
  }
  void deleteString(Node *&node, const string &s, int pos) {
    node->passCount--;
    if (pos == sz(s))
      node->endCount--;
    else
      deleteString(node->child[s[pos] - 'a'], s, pos + 1);
    if (node != root && node->passCount == 0) {
      delete node;
      node = nullptr; // Detach the deleted child from its parent.
    }
  }
  void deleteString(const string &s) {
    if (findString(s)) deleteString(root, s, 0);
  }
};

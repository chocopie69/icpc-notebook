/**
 * Author: Emil Lenngren, Simon Lindholm
 * Date: 2011-11-29
 * License: CC0
 * Source: folklore
 * Description: 0-based variables; literals x and \texttt{\tilde{}x} mean true and false. either(a,b) adds a
 * OR b; implication a=>b is either(\texttt{\tilde{}a},b). setValue fixes a literal true. Read
 * values only if solve() succeeds. atMostOne can add auxiliary variables.
 * Usage: TwoSat ts(3); ts.either(0,~1); ts.setValue(2);
 * bool possible=ts.solve();
 * if (possible) { int valueOfZero=ts.values[0]; }
 * Time: O(N+E), where N is the number of boolean variables, and E is the number of clauses.
 */
#pragma once
#include "SCC.h"
struct TwoSat {
  int variableCount;
  vector<vector<int>> adj;
  vector<int> values; // 0 = false, 1 = true
  TwoSat(int variableCount = 0) : variableCount(variableCount), adj(2 * variableCount) {}
  int addVar() { // (optional)
    adj.emplace_back();
    adj.emplace_back();
    return variableCount++;
  }
  void either(int literalA, int literalB) {
    literalA = max(2 * literalA, -1 - 2 * literalA);
    literalB = max(2 * literalB, -1 - 2 * literalB);
    adj[literalA].push_back(literalB ^ 1);
    adj[literalB].push_back(literalA ^ 1);
  }
  void setValue(int x) { either(x, x); }
  void atMostOne(const vector<int> &literals) { // (optional)
    if (sz(literals) <= 1) return;
    int currentLiteral = ~literals[0];
    for (int i = 2; i < (sz(literals)); ++i) {
      int auxiliaryVar = addVar();
      either(currentLiteral, ~literals[i]);
      either(currentLiteral, auxiliaryVar);
      either(~literals[i], auxiliaryVar);
      currentLiteral = ~auxiliaryVar;
    }
    either(currentLiteral, ~literals[1]);
  }
  bool solve() {
    SCC scc(adj, 0);
    values.assign(variableCount, 0);
    for (int i = 0; i < variableCount; i++) {
      if (scc.comp[2 * i] == scc.comp[2 * i + 1]) return false;
      // Node 2*i means false; node 2*i+1 means true.
      values[i] = scc.comp[2 * i] > scc.comp[2 * i + 1];
    }
    return true;
  }
};

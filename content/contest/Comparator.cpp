/**
 * Author: Personal comparator
 * Description: Windows comparator: generate input, run two solutions, then compare their output
 * files with fc. Stops at the first reported difference; leaves files for inspection.
 * The code below is the original personal comparator with whitespace formatting only.
 * Usage: Compile this as a separate program and run it in the solutions' directory.
 * Set NAME and NTEST; compile the solutions as problem.exe and problem-2.exe.
 * Both read problem.INP; the first writes problem.OUT, the second problem.ANS (via freopen).
 * Replace the generator under Generate tests here with valid inputs for your problem.
 */
#include <bits/stdc++.h>
#define ll long long
using namespace std;
const string NAME = "problem";
const int NTEST = 500;
mt19937 rd(chrono::steady_clock::now().time_since_epoch().count());
#define rand rd
long long Rand(long long l, long long h) { return l + rd() % (h - l + 1); }
int main() {
  srand(time(NULL));
  for (int iTest = 1; iTest <= NTEST; iTest++) {
    ofstream inp((NAME + ".INP").c_str());
    /// Generate tests here
    ll n = Rand(49, 50);
    inp << n;
    inp.close();
    system((NAME + ".exe").c_str());
    system((NAME + "-2.exe").c_str());
    if (system(("fc " + NAME + ".OUT " + NAME + ".ANS").c_str()) != 0) {
      cout << "Test " << iTest << ": WRONG!\n";
      return 0;
    }
    cout << "Test " << iTest << ": CORRECT!\n";
  }
  return 0;
}

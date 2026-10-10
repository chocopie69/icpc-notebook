#include "../utilities/template.h"
#include <cassert>
#include "../../content/various/TernarySearch.h"

int main() {
  mt19937 rng(123);
  uniform_real_distribution<double> coord(-1e6, 1e6);
  for (int i = 0; i < 10000; i++) {
    double lo = coord(rng), hi = coord(rng), peak = coord(rng);
    if (lo > hi) swap(lo, hi);
    auto f = [=](double x) { return -(x - peak) * (x - peak); };
    double x = ternSearch(lo, hi, f);
    assert(lo <= x && x <= hi);
    assert(abs(x - clamp(peak, lo, hi)) < 1e-7);
  }
  assert(ternSearch(2.5, 2.5, [](double x) { return x; }) == 2.5);
  double x = ternSearch(-10.0, 10.0, [](double x) {
    return -max(0.0, abs(x) - 2);
  });
  assert(abs(x) <= 2 + 1e-12);
  x = ternSearch(1e12, 1e12 + 100, [](double x) {
    return -(x - (1e12 + 40)) * (x - (1e12 + 40));
  });
  assert(abs(x - (1e12 + 40)) < 1e-3);
  for (int peak : {INT_MIN, INT_MIN+1, -1, 0, 1, INT_MAX-1, INT_MAX}) {
    assert(ternSearch(INT_MIN, INT_MAX, [=](int i) {
      return -abs((ll)i-peak);
    }) == peak);
    assert(ternSearch(peak, peak, [](int i) { return i; }) == peak);
  }
  for (int peak = -20; peak <= 20; peak++) {
    for (int lo = -20; lo <= 20; lo++) {
      for (int hi = lo; hi <= 20; hi++) {
        int x = ternSearch(lo, hi, [=](int x) {
          return -max(0, abs(x - peak) - 2);
        });
        int best = lo;
        for (int j = lo + 1; j <= hi; j++)
          if (max(0, abs(j - peak) - 2) < max(0, abs(best - peak) - 2)) best = j;
        assert(x == best);
      }
    }
  }
  cout << "Tests passed!" << endl;
}

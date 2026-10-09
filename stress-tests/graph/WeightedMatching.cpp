#include "../utilities/template.h"
#include "../utilities/utils.h"
#include "../utilities/random.h"

#include "../../content/graph/WeightedMatching.h"
#include <bits/extc++.h> /// include-line, keep-include
#include "../../content/graph/MinCostMaxFlow.h"

void test(int N, int mxCost, int iters) {
	for (int it = 0; it < iters; it++) {
		int n = randIncl(0, N), m = randIncl(0, N);
		if (n > m)
			swap(n, m);

		MinCostMaxFlow mcmf(n + m + 2);
		int s = 0;
		int t = 1;
		for (int i = 0; i < n; i++)
			mcmf.addEdge(s, i + 2, 1, 0);
		for (int i = 0; i < m; i++)
			mcmf.addEdge(2 + n + i, t, 1, 0);

		vector<vi> cost(n + 1, vi(m + 1));
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++) {
				cost[i + 1][j + 1] = randRange(-mxCost, mxCost);
				mcmf.addEdge(i + 2, 2 + n + j, 1, cost[i + 1][j + 1]);
			}
		}
		mcmf.setpi(s);
		auto maxflow = mcmf.maxflow(s, t);
		auto matching = weightedMatching(cost);
		assert(maxflow.first == n);
		assert(maxflow.second == matching.first);
		int matchSum = 0;
		set<int> used;
		for (int i = 1; i <= n; i++) {
			matchSum += cost[i][matching.second[i]];
			assert(1 <= matching.second[i] && matching.second[i] <= m);
			assert(used.count(matching.second[i]) == 0);
			used.insert(matching.second[i]);
		}
		assert(matchSum == matching.first);
	}
}
signed main() {
	test(25, 5, 1000);
	test(100, 1000, 100);
	test(100, 1, 50);
	test(5, 5, 10000);
	cout << "Tests passed!" << endl;
}

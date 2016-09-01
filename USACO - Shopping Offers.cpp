/*

     |\   |  `|` |``\  ```|` |   |  /```\  |``\
     | \  |   |  |__/     |  |___| |     | |__/
     |  \ |   |  |  \     |  |   | |     | |  \
    _|   \|  _|_ |   \ \__)  |   |  \___/  |   \

        USACO - Shopping Offers (IOI '95)

        Category: Dynamic Programming

        Keys: Generalizing States

*/

#include <bits/stdc++.h>

using namespace std;

const int N = 6;
const int S = 110;
const int C = 1010;
const int INF = 1e9 + 10;

int s, b, size[S], cost[C], take[N], init[N];
int package[S][C], offerPrice[S], dp[N][N][N][N][N];

int call (int a, int b, int c, int d, int e) {
	if (a < 0 or b < 0 or c < 0 or d < 0 or e < 0) return INF;
	if (a == 0 and b == 0 and c == 0 and d == 0 and e == 0) return 0;
	if (dp[a][b][c][d][e] != -1) return dp[a][b][c][d][e];

	int ret = INF;

	for (int i = 1; i <= s; ++i) {
		int na, nb, nc, nd, ne;
		na = a - package[i][take[1]];
		nb = b - package[i][take[2]];
		nc = c - package[i][take[3]];
		nd = d - package[i][take[4]];
		ne = e - package[i][take[5]];
		ret = min(ret, offerPrice[i] + call(na, nb, nc, nd, ne));
	}

	for (int i = 1; i <= a; ++i) ret = min(ret, i * cost[1] + call(a - i, b, c, d, e));
	for (int i = 1; i <= b; ++i) ret = min(ret, i * cost[2] + call(a, b - i, c, d, e));
	for (int i = 1; i <= c; ++i) ret = min(ret, i * cost[3] + call(a, b, c - i, d, e));
	for (int i = 1; i <= d; ++i) ret = min(ret, i * cost[4] + call(a, b, c, d - i, e));
	for (int i = 1; i <= e; ++i) ret = min(ret, i * cost[5] + call(a, b, c, d, e - i));

	return dp[a][b][c][d][e] = ret;
}

int main (int argc, char const *argv[]) {
	freopen("shopping.in", "r", stdin);
	freopen("shopping.out", "w", stdout);

	scanf("%d", &s);
	for (int i = 1; i <= s; ++i) {
		scanf("%d", size + i);
		for (int j = 1; j <= size[i]; ++j) {
			int x, y;
			scanf("%d %d", &x, &y);
			package[i][x] = y;
		}
		scanf("%d", offerPrice + i);
	}
	scanf("%d", &b);
	for (int i = 1; i <= b; ++i) scanf("%d %d %d", take + i, init + i, cost + i);

	memset(dp, -1, sizeof dp);
	printf("%d\n", call(init[1], init[2], init[3], init[4], init[5]));
	return 0;
}


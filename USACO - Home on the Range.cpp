/*

     |\   |  `|` |``\  ```|` |   |  /```\  |``\
     | \  |   |  |__/     |  |___| |     | |__/
     |  \ |   |  |  \     |  |   | |     | |  \
    _|   \|  _|_ |   \ \__)  |   |  \___/  |   \

        USACO - Home on the Range

        Category: Dynamic Programming

        Keys: Bottom Up

*/

#include <bits/stdc++.h>

using namespace std;

const int N = 255;

char g[N][N];
int n, dp[N][N], res[N];

int main (int argc, char const *argv[]) {
	freopen("range.in", "r", stdin);
	freopen("range.out", "w", stdout);

	scanf("%d", &n);
	for (int i = 1; i <= n; ++i) scanf("%s", g[i] + 1);
		
	for (int i = 1; i <= n; ++i) 
		dp[1][i] = (g[1][i] - '0'), dp[i][1] = (g[i][1] - '0');
	
	for (int i = 2; i <= n; ++i)
		for (int j = 2; j <= n; ++j)
			dp[i][j] = g[i][j] == '0' ? 0 : 1 + min(dp[i - 1][j - 1], min(dp[i][j - 1], dp[i - 1][j]));

	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= n; ++j) 
			++res[1], --res[dp[i][j] + 1];

	for (int i = 1; i <= n; ++i) {
		res[i] += res[i - 1];
		if (i > 1 and res[i]) printf("%d %d\n", i, res[i]);
	}
	return 0;
}


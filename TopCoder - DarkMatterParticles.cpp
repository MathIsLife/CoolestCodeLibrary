/*

     |\   |  `|` |``\  ```|` |   |  /```\  |``\
     | \  |   |  |__/     |  |___| |     | |__/
     |  \ |   |  |  \     |  |   | |     | |  \
    _|   \|  _|_ |   \ \__)  |   |  \___/  |   \
    
    	TopCoder - DarkMatterParticles
    	
    	Category: Dynamic Programming
    	
    	Keys: Coin Change
    	
*/

#include <bits/stdc++.h>

using namespace std;

class DarkMatterParticles {public: string SplitParticles (int n, int k, vector <int> x, vector <int> y);};

const int N = 1010;

int currSize;
bool vis[N], dp[N][N];
vector <int> g[N], comp;

void dfs (int u) {
    if (vis[u]) return;
    ++currSize, vis[u] = 1;
    for (int j = 0; j < g[u].size(); ++j) {
	int v = g[u][j];
	dfs(v);
    }
}

string DarkMatterParticles :: SplitParticles (int n, int k, vector <int> x, vector <int> y) {
    for (int i = 0; i < x.size(); ++i) {
	g[x[i]].push_back(y[i]);
	g[y[i]].push_back(x[i]);
    }

    comp.push_back(-1);
    for (int i = 0; i < n; ++i) if (not vis[i]) {
	currSize = 0, dfs(i);
	comp.push_back(currSize);
    }

    dp[0][0] = 1;
    int m = comp.size() - 1;
    for (int i = 1; i <= m; ++i) 
	for (int j = 0; j < N; ++j)
	    if (j - comp[i] >= 0 and dp[i - 1][j - comp[i]])
		dp[i][j - comp[i]] = dp[i][j] = 1;

    if (dp[m][k]) return "Possible";
    return "Impossible";
}


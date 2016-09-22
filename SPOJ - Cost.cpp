/*

     |\   |  `|` |``\  ```|` |   |  /```\  |``\
     | \  |   |  |__/     |  |___| |     | |__/
     |  \ |   |  |  \     |  |   | |     | |  \
    _|   \|  _|_ |   \ \__)  |   |  \___/  |   \
    
    	SPOJ - Cost (KOICOST)
    	
    	Category: Data Structures
    	
    	Keys: Union Find, Sorting, Observation
    	
*/

#include <bits/stdc++.h>

using namespace std;

const int N = 1e5 + 10;
const int MOD = 1000000000;

struct edge {
    int u, v; long long w;
    bool operator < (const edge &e) const {
	return w < e.w;
    }
};

edge e[N];
int n, m, p[N];
long long sum[N], size[N];

int find (int x) {
    return p[x] == x ? x : p[x] = find(p[x]);
}

long long merge (int u, int v) {
    int x = find(u), y = find(v);
    if (x == y) return 0;

    long long ret = (size[x] * size[y]) % MOD;
    p[x] = y, size[y] += size[x];
	
    return ret;
}

int main (int argc, char const *argv[]) {
    scanf("%d %d", &n, &m);
    for (int i = 1; i <= m; ++i) 
	scanf("%d %d %lld", &e[i].u, &e[i].v, &e[i].w);

    sort(e + 1, e + m + 1);
    for (int i = 1; i <= m; ++i) sum[i] = (sum[i - 1] + e[i].w) % MOD;

    for (int i = 1; i <= n; ++i) p[i] = i, size[i] = 1;

    long long res = 0;
    for (int i = m; i; --i) res += merge(e[i].u, e[i].v) * sum[i], res %= MOD;

    printf("%lld\n", res);
    return 0;
}


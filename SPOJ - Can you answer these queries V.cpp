/*

     |\   |  `|` |``\  ```|` |   |  /```\  |``\
     | \  |   |  |__/     |  |___| |     | |__/
     |  \ |   |  |  \     |  |   | |     | |  \
    _|   \|  _|_ |   \ \__)  |   |  \___/  |   \
    
    	SPOJ - Can you answer these queries V (GSS5)
    	
    	Category: Data Structures
    	
    	Keys: Segment Tree, Observation
    	
*/

#include <bits/stdc++.h> 

using namespace std;

const int N = 1e4 + 10;
const int INF = 1e9 + 10;

struct node {
    int pre, suf, sum, best;
    node () {}
    node (int a, int b, int c, int d) {
	pre = a, suf = b, sum = c, best = d;
    }
    node operator + (const node &x) const {
	node z;
	z.pre = max(pre, sum + x.pre);
	z.suf = max(x.suf, x.sum + suf);
	z.sum = x.sum + sum;
	z.best = max(max(x.best, best), suf + x.pre);
	return z;
    }
};

int t, n, m, a[N], sum[N];
int rangeMin[4 * N], rangeMax[4 * N];
node rangeMaxSum[4 * N];

node merge (node x, node y) {
    node z;
    z.pre = max(x.pre, x.sum + y.pre);
    z.suf = max(y.suf, y.sum + x.suf);
    z.sum = x.sum + y.sum;
    z.best = max(max(x.best, y.best), x.suf + y.pre);
    return z;
}

void init_rmq (int u, int b, int e) {
    if (b == e) {
	rangeMin[u] = rangeMax[u] = sum[b - 1];
	return;
    }
    int l = u << 1, r = l | 1, m = b + e >> 1;
    init_rmq(l, b, m), init_rmq(r, m + 1, e);
    rangeMin[u] = min(rangeMin[l], rangeMin[r]);
    rangeMax[u] = max(rangeMax[l], rangeMax[r]);
}

void init_maxSum (int u, int b, int e) {
    if (b == e) {
	rangeMaxSum[u] = node(a[b], a[b], a[b], a[b]);
	return;
    }
    int l = u << 1, r = l | 1, m = b + e >> 1;
    init_maxSum(l, b, m), init_maxSum(r, m + 1, e);
    rangeMaxSum[u] = rangeMaxSum[l] + rangeMaxSum[r];
}

int query_rmq (int u, int b, int e, int p, int q, int flag) {
    if (b > q or e < p) return flag ? INF : -INF;
    if (b >= p and e <= q) return flag ? rangeMin[u] : rangeMax[u];
    int l = u << 1, r = l | 1, m = b + e >> 1;
    int left = query_rmq(l, b, m, p, q, flag);
    int right = query_rmq(r, m + 1, e, p, q, flag);
    return flag ? min(left, right) : max(left, right);
}

node query_maxSum (int u, int b, int e, int p, int q) {
    if (b > q or e < p) return node(-INF, -INF, 0, -INF);
    if (b >= p and e <= q) return rangeMaxSum[u];
    int l = u << 1, r = l | 1, m = b + e >> 1;
    node left = query_maxSum(l, b, m, p, q);
    node right = query_maxSum(r, m + 1, e, p, q);
    return left + right;
}

int solve_disjoint (int w, int x, int y, int z) {
    int after = query_rmq(1, 1, n + 1, y + 1, z + 1, 0);
    int before = query_rmq(1, 1, n + 1, w, x, 1);
    return after - before;
}

int main (int argc, char const *argv[]) {
    scanf("%d", &t); while (t--) {
	scanf("%d", &n);
	for (int i = 1; i <= n; ++i) {
   	    scanf("%d", a + i);
	    sum[i] = sum[i - 1] + a[i];
	}
	init_rmq(1, 1, n + 1);
	init_maxSum(1, 1, n);
	scanf("%d", &m); while (m--) {
	    int w, x, y, z;
	    scanf("%d %d %d %d", &w, &x, &y, &z);
	    if (x < y) {
		printf("%d\n", solve_disjoint(w, x, y, z));
	    } else {
		int p = y, q = x;
		swap(x, y), --x, ++y;
		int one = solve_disjoint(w, x, p, z);
		int two = solve_disjoint(w, q, y, z);
		int three = query_maxSum(1, 1, n, p, q).best;
		int res = max(max(one, two), three);
		printf("%d\n", res); 
	    }
	}
	memset(rangeMin, 0, sizeof rangeMin);
	memset(rangeMax, 0, sizeof rangeMax);
	memset(rangeMaxSum, 0, sizeof rangeMaxSum);
    }
    return 0;
}


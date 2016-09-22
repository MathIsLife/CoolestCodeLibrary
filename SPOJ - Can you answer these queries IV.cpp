/*

     |\   |  `|` |``\  ```|` |   |  /```\  |``\
     | \  |   |  |__/     |  |___| |     | |__/
     |  \ |   |  |  \     |  |   | |     | |  \
    _|   \|  _|_ |   \ \__)  |   |  \___/  |   \
    
    	SPOJ - Can you answer these queries IV (GSS4)
    	
    	Category: Data Structures
    	
    	Keys: Segment Tree, Ad-hoc Optimization, Observation
    	
*/

#include <bits/stdc++.h>

using namespace std;

const int N = 1e5 + 10;

int n, m, cs = 0;
long long a[N], t[4 * N];

void build (int u, int b, int e) {
	if (b == e) {
		t[u] = a[b];
		return;
	}

	int l = u << 1, r = l | 1, m = b + e >> 1;
	build(l, b, m), build(r, m + 1, e);
	t[u] = t[l] + t[r];
}

void update (int u, int b, int e, int p, int q) {
	if (t[u] == e - b + 1) return;
	if (b > q or e < p) return;
	if (b == e) {
		t[u] = floor(sqrt(t[u]));
		return;
	}

	int l = u << 1, r = l | 1, m = b + e >> 1;
	update(l, b, m, p, q), update(r, m + 1, e, p, q);
	t[u] = t[l] + t[r];
}

long long query (int u, int b, int e, int p, int q) {
	if (b > q or e < p) return 0;
	if (b >= p and e <= q) return t[u];

	int l = u << 1, r = l | 1, m = b + e >> 1;
	return query(l, b, m, p, q) + query(r, m + 1, e, p, q);
}

int main (int argc, char const *argv[]) {
	while (scanf("%d", &n) != EOF) {
		for (int i = 1; i <= n; ++i) scanf("%lld", a + i);
		memset(t, 0, sizeof t);
		build(1, 1, n);
		
		printf("Case #%d:\n", ++cs);
		scanf("%d", &m); while (m--) {
			int cmd, l, r;
			scanf("%d %d %d", &cmd, &l, &r);
			if (l > r) swap(l, r);

			if (cmd) printf("%lld\n", query(1, 1, n, l, r));
			else update(1, 1, n, l, r);
		}

		puts("");
	}
	return 0;
}


/*

     |\   |  `|` |``\  ```|` |   |  /```\  |``\
     | \  |   |  |__/     |  |___| |     | |__/
     |  \ |   |  |  \     |  |   | |     | |  \
    _|   \|  _|_ |   \ \__)  |   |  \___/  |   \
    
    	SPOJ - DQUERY - O(n + q lg n)
    	
    	Category: Data Structures
    	
    	Keys: Offline Processing, Fenwick Tree, Sorting, Two Pointer
    	
*/

#include <bits/stdc++.h>

using namespace std;

const int N = 1e6 + 10;

struct query {
    int l, r, id;
	
    query () {}
    query (int a, int b, int c) : id(a), l(b), r(c) {}

    bool operator < (const query &q) const {
	return r < q.r;
    }
};

query x[N];
int n, q, a[N], bit[N], last[N], res[N];

void update (int p, int v) {
    while (p < N) bit[p] += v, p += (p & -p);
}

int prefix (int p) {
    int sum = 0;
    while (p > 0) sum += bit[p], p -= (p & -p);
    return sum;
}

int query (int l, int r) {
    return prefix(r) - prefix(l - 1);
}

int main (int argc, char const *argv[]) {
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i) scanf("%d", a + i);
	
    scanf("%d", &q);
    for (int i = 1; i <= q; ++i) {
	scanf("%d %d", &x[i].l, &x[i].r);
  	x[i].id = i;
    }

    sort(x + 1, x + q + 1);
    memset(last, -1, sizeof last);

    for (int i = 1, j = 1; i <= n and j <= q; ++i) {
 	if (last[a[i]] != -1) update(last[a[i]], -1);
 	last[a[i]] = i, update(i, 1);

	while (j <= q and x[j].r == i) 
    	    res[x[j].id] = query(x[j].l, x[j].r), ++j;
    }

    for (int i = 1; i <= q; ++i) printf("%d\n", res[i]);
    return 0;
}


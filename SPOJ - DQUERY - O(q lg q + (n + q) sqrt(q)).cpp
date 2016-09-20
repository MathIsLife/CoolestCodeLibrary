/*

     |\   |  `|` |``\  ```|` |   |  /```\  |``\
     | \  |   |  |__/     |  |___| |     | |__/
     |  \ |   |  |  \     |  |   | |     | |  \
    _|   \|  _|_ |   \ \__)  |   |  \___/  |   \
    
    	SPOJ - DQUERY - O(q lg q + (n + q) sqrt(q))
    	
    	Category: Data Structures
    	
    	Keys: Offline Processing, Square Root Decomposition, Mo's Algorithm
    	
*/

#include <bits/stdc++.h>

using namespace std;

int SQRT;
const int N = 1e6 + 10;

struct query {
	int l, r, id;
	
	query () {}
	query (int a, int b, int c) : id(a), l(b), r(c) {}

	bool operator < (const query &q) const {
		if (l/SQRT == q.l/SQRT) return r/SQRT < q.r/SQRT;
		return l/SQRT < q.l/SQRT;
	}
};

query x[N];
int n, q, ans = 0, a[N], res[N], cnt[N];

void add (int p) {
	if (cnt[a[p]] == 0) ++ans;
	++cnt[a[p]];
}

void remove (int p) {
	--cnt[a[p]];
	if (cnt[a[p]] == 0) --ans;
}

int main (int argc, char const *argv[]) {
	scanf("%d", &n);
	for (int i = 1; i <= n; ++i) scanf("%d", a + i);
	
	scanf("%d", &q);
	for (int i = 1; i <= q; ++i) {
		scanf("%d %d", &x[i].l, &x[i].r);
		x[i].id = i;
	}

	SQRT = sqrt(n);
	sort(x + 1, x + q + 1);

	int l = 0, r = 0;
	for (int i = 1; i <= q; ++i) {
		while (r < x[i].r) add(++r);
		while (l > x[i].l) add(--l);
		while (l < x[i].l) remove(l++);
		while (r > x[i].r) remove(r--);
		
		res[x[i].id] = ans;
	}

	for (int i = 1; i <= q; ++i) printf("%d\n", res[i]);
	return 0;
}


/*

     |\   |  `|` |``\  ```|` |   |  /```\  |``\
     | \  |   |  |__/     |  |___| |     | |__/
     |  \ |   |  |  \     |  |   | |     | |  \
    _|   \|  _|_ |   \ \__)  |   |  \___/  |   \
    
    	SPOJ - K-Query (KQUERY)
    	
    	Category: Data Structures
    	
    	Keys: Offline Processing, Fenwick Tree, Pointer Walk, Sorting
    	
*/

#include <bits/stdc++.h>

using namespace std;

const int N = 30010;
const int Q = 2e5 + 10;

struct query {
    int id, l, r, value;
    bool operator < (const query &q) const {
	return value > q.value;
    }
};

query x[Q];
pair <int, int> a[N];
int n, q, bit[N], res[Q];

void update (int p, int v) {
    while (p < N) bit[p] += v, p += (p & -p);
}

int query (int p) {
    int sum = 0;
    while (p > 0) sum += bit[p], p -= (p & -p);
    return sum;
}

int main (int argc, char const *argv[]) {
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i) {
	scanf("%d", &a[i].first);
	a[i].second = i;
    }

    sort(a + 1, a + n + 1);
    int pointer = n;

    scanf("%d", &q);
    for (int i = 1; i <= q; ++i) {
	scanf("%d %d %d", &x[i].l, &x[i].r, &x[i].value);
	x[i].id = i;
    }

    sort(x + 1, x + q + 1);

    for (int i = 1; i <= q;) {
	int now = x[i].value;
		
	while (pointer >= 1 and a[pointer].first > now) 
	    update(a[pointer].second, 1), --pointer;
		
	while (i <= q and x[i].value == now) 
	    res[x[i].id] = query(x[i].r) - query(x[i].l - 1), ++i;
    }

    for (int i = 1; i <= q; ++i) printf("%d\n", res[i]);
    return 0;
}


/*

     |\   |  `|` |``\  ```|` |   |  /```\  |``\
     | \  |   |  |__/     |  |___| |     | |__/
     |  \ |   |  |  \     |  |   | |     | |  \
    _|   \|  _|_ |   \ \__)  |   |  \___/  |   \
    
    	SPOJ - Inversion Count (INVCNT)
    	
    	Category: Data Structures
    	
    	Keys: Fenwick Tree, Sorting
    	
*/

#include <bits/stdc++.h>

using namespace std;

const int N = 2e5 + 10;

int t, n, bit[N];
pair <int, int> p[N];

void update (int p, int v) {
	while (p < N) bit[p] += v, p += (p & -p);
}

int query (int p) {
	int sum = 0;
	while (p > 0) sum += bit[p], p -= (p & -p);
	return sum;
}

int main (int argc, char const *argv[]) {
	scanf("%d", &t); while (t--) {
		scanf("%d", &n);
		for (int i = 1; i <= n; ++i) 
			scanf("%d", &p[i].first), p[i].second = i;
		
		sort(p + 1, p + n + 1);
		reverse(p + 1, p + n + 1);

		long long tot = 0;
		for (int i = 1; i <= n; ++i) {
			tot += (long long) query(p[i].second);
			update(p[i].second, 1);
		}

		printf("%lld\n", tot);
		memset(bit, 0, sizeof bit);
	}
	return 0;
}


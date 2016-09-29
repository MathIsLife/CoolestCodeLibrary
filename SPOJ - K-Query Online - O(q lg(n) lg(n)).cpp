/*

     |\   |  `|` |``\  ```|` |   |  /```\  |``\
     | \  |   |  |__/     |  |___| |     | |__/
     |  \ |   |  |  \     |  |   | |     | |  \
    _|   \|  _|_ |   \ \__)  |   |  \___/  |   \
    
    	SPOJ - K-Query Online (KQUERYO) - O(q lg(n) lg(n))
    	
    	Category: Data Structures
    	
    	Keys: Segment Tree, Merge Sort, Binary Search
    	
*/

#include <bits/stdc++.h>

using namespace std;

const int N = 30010;
const int INF = 2e9 + 10;

int n, q, x, res;
vector <int> t[N + N];

void merge (int u, int l, int r) {
    int L = t[l].size(), R = t[r].size();
    t[l].push_back(INF), t[r].push_back(INF);

    for (int i = 0, j = 0; i < L or j < R;) {
	if (t[l][i] < t[r][j]) t[u].push_back(t[l][i++]);
	else t[u].push_back(t[r][j++]);
    }

    t[l].pop_back(), t[r].pop_back();
}

void init (void) {
    for (int i = n - 1; i; --i) merge(i, i << 1, i << 1 | 1);
}

int query (int l, int r, int x) {
    int res = 0;

    for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
	if (l & 1) {
	    int pos = upper_bound(t[l].begin(), t[l].end(), x) - t[l].begin();
	    res += (int) t[l].size() - pos;
	    ++l;
	}

	if (r & 1) {
	    --r;
	    int pos = upper_bound(t[r].begin(), t[r].end(), x) - t[r].begin();
	    res += (int) t[r].size() - pos;
	}
    }

    return res;
}

int main (int argc, char const *argv[]) {
    scanf("%d", &n);
    for (int i = 0; i < n; ++i) {
    	scanf("%d", &x);
    	t[n + i].push_back(x);
    }

    init();

    scanf("%d", &q); while (q--) {
	int l, r, x;
	scanf("%d %d %d", &l, &r, &x);
	l ^= res, r ^= res, x ^= res;
	res = query(max(0, l - 1), min(n, r), x);
	printf("%d\n", res);
    }
    return 0;
}


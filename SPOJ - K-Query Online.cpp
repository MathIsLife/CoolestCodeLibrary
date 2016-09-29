/*

     |\   |  `|` |``\  ```|` |   |  /```\  |``\
     | \  |   |  |__/     |  |___| |     | |__/
     |  \ |   |  |  \     |  |   | |     | |  \
    _|   \|  _|_ |   \ \__)  |   |  \___/  |   \
    
    	SPOJ - K-Query Online (KQUERYO)
    	
    	Category: Data Structures
    	
    	Keys: Square Root Decomposition, Sorting, Binary Search
    	
*/

#include <bits/stdc++.h>

using namespace std;

int BUCKET;
const int N = 30010;

int n, q, res;
pair <int, int> a[N];

int main (int argc, char const *argv[]) {
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i) 
	scanf("%d", &a[i].first), a[i].second = i;
    BUCKET = sqrt(n);
	
    for (int i = 1; i <= n; i += BUCKET) 
	sort(a + i, a + min(n + 1, i + BUCKET));
	
    scanf("%d", &q); while (q--) {
	int l, r, x;
	scanf("%d %d %d", &l, &r, &x);
	l ^= res, r ^= res, x ^= res, res = 0;
	l = max(l, 1), r = min(r, n);
	    
	int blockL = (l - 1)/BUCKET, blockR = (r - 1)/BUCKET;
	int startL = 1 + BUCKET * blockL, startR = 1 + BUCKET * blockR;

	for (int i = startL; i <= min(n, startL + BUCKET - 1); ++i) 
	    if (a[i].second >= l and a[i].second <= r and a[i].first > x) ++res;

	if (blockL != blockR) {
	    for (int i = startR; i <= min(n, startR + BUCKET - 1); ++i) 
		if (a[i].second >= l and a[i].second <= r and a[i].first > x) ++res;	

	    for (int i = blockL + 1; i < blockR; ++i) {
		int start = 1 + BUCKET * i;
		int tot = upper_bound(a + start, a + start + BUCKET, make_pair(x, n + 1)) - a - start;
		res += max(0, BUCKET - tot);
	    }
	}

	printf("%d\n", res);
    }
    return 0;
}


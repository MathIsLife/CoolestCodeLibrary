/*

     |\   |  `|` |``\  ```|` |   |  /```\  |``\
     | \  |   |  |__/     |  |___| |     | |__/
     |  \ |   |  |  \     |  |   | |     | |  \
    _|   \|  _|_ |   \ \__)  |   |  \___/  |   \
    
    	SPOJ - K-Query II (KQUERY2)
    	
    	Category: Data Structures
    	
    	Keys: Square Root Decomposition, Sorting, Binary Search
    	
*/

#include <bits/stdc++.h>

using namespace std;

int BUCKET;
const int N = 30010;

int n, q;
pair <int, int> a[N];

int main (int argc, char const *argv[]) {
	scanf("%d", &n);
	for (int i = 1; i <= n; ++i) 
		scanf("%d", &a[i].first), a[i].second = i;
	BUCKET = 2 * sqrt(n);
	
	for (int i = 1; i <= n; i += BUCKET) 
		sort(a + i, a + min(n + 1, i + BUCKET));
	
	scanf("%d", &q); while (q--) {
		int cmd, p, q, x;
		scanf("%d", &cmd);

		if (cmd == 0) {
			scanf("%d %d", &p, &x);
			int start = 1 + BUCKET * ((p - 1)/BUCKET);
			
			for (int i = start; i <= min(n, start + BUCKET - 1); ++i)
				if (a[i].second == p) {a[i].first = x; break;}
			
			sort(a + start, a + min(n + 1, start + BUCKET));
		} else {
			scanf("%d %d %d", &p, &q, &x);
			int blockP = (p - 1)/BUCKET, blockQ = (q - 1)/BUCKET, res = 0;
			int startP = 1 + BUCKET * blockP, startQ = 1 + BUCKET * blockQ;

			for (int i = startP; i <= min(n, startP + BUCKET - 1); ++i) 
				if (a[i].second >= p and a[i].second <= q and a[i].first > x) ++res;

			if (blockP != blockQ) {
				for (int i = startQ; i <= min(n, startQ + BUCKET - 1); ++i) 
					if (a[i].second >= p and a[i].second <= q and a[i].first > x) ++res;	

				for (int i = blockP + 1; i < blockQ; ++i) {
					int start = 1 + BUCKET * i;
					int tot = upper_bound(a + start, a + start + BUCKET, make_pair(x, n + 1)) - a - start;
					res += max(0, BUCKET - tot);
				}
			}

			printf("%d\n", res);
		}
	}
	return 0;
}


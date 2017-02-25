/*

     |\   |  `|` |``\  ```|` |   |  /```\  |``\
     | \  |   |  |__/     |  |___| |     | |__/
     |  \ |   |  |  \     |  |   | |     | |  \
    _|   \|  _|_ |   \ \__)  |   |  \___/  |   \
    
        Codeforces 455E - Function
        
        Category: Data Structures
        
        Keys: Observation, Merge Sort Tree, Segment Tree, Convex Hull Trick
        
*/

#include <bits/stdc++.h>
 
using namespace std;

const int N = 1e5 + 10;
const long long INF = 1e16 + 10;

struct line {
	long long m, c;
	line () {}
	line (long long _m, long long _c) {
		m = _m, c = _c;
	}
	long long at (long long x) {
		return m * x + c;
	}
	bool operator < (const line &l) const {
		return m < l.m;
	}
};

int n, m;
long long a[N];
long long sum[N];
vector <line> mst[4 * N]; // Merge Sort Tree
vector <line> tree[4 * N]; // Segment Tree

bool bad (line l1, line l2, line l3) {
	return (l1.c - l2.c) * (l3.m - l1.m) >= (l1.c - l3.c) * (l2.m - l1.m);
}

void add (vector <line> &v, line l) {
	v.push_back(l);
	int size = v.size();
	while (size >= 3 and bad(v[size - 3], v[size - 2], v[size - 1])) {
		--size; 
		v.erase(v.end() - 2);
	}
}

void init (int u, int b, int e) {
	if (b == e) {
		mst[u].push_back(line(a[b], sum[b] - b * a[b]));
		tree[u].push_back(line(a[b], sum[b] - b * a[b]));
		return;
	}
	int l = u << 1, r = l | 1, m = b + e >> 1;
	init(l, b, m), init(r, m + 1, e);
	merge(mst[l].begin(), mst[l].end(), mst[r].begin(), mst[r].end(), back_inserter(mst[u]));
	for (unsigned i = 0; i < mst[u].size(); ++i) {
		add(tree[u], mst[u][i]);
	}
}

long long query (vector <line> &v, long long x) {
	int size = v.size();
	long long res = v[size - 1].at(x);
	int lo = 0, hi = size - 2;
	while (lo < hi) {
		int mid = lo + hi >> 1;
		if (v[mid].at(x) < v[mid + 1].at(x)) {
			lo = mid + 1;
		} else {
			hi = mid;
		}
	}
	return v[lo].at(x);
}

long long query (int u, int b, int e, int p, int q, long long x) {
	if (b > q or e < p) return -INF;
	if (b >= p and e <= q) return query(tree[u], x);
	int l = u << 1, r = l | 1, m = b + e >> 1;
	long long left = query(l, b, m, p, q, x);
	long long right = query(r, m + 1, e, p, q, x);
	return max(left, right);
}

int main (int argc, char const *argv[]) {
	scanf("%d", &n);
	for (int i = 1; i <= n; ++i) {
		scanf("%lld", a + i);
		sum[i] = sum[i - 1] + a[i];
	}
	init(1, 1, n);
	scanf("%d", &m); while (m--) {
		int x, y; 
		scanf("%d %d", &x, &y);
		long long offset = query(1, 1, n, y - x + 1, y, y - x);
		printf("%lld\n", sum[y] - offset);
	}
    return 0;
}


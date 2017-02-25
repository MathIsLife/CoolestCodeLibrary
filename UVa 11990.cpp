/*

     |\   |  `|` |``\  ```|` |   |  /```\  |``\
     | \  |   |  |__/     |  |___| |     | |__/
     |  \ |   |  |  \     |  |   | |     | |  \
    _|   \|  _|_ |   \ \__)  |   |  \___/  |   \
    
    	UVa 11990 - Dynamic Inversion - O(n lg(n) lg(n))
    	
    	Category: Data Structures
    	
    	Keys: Merge Sort Tree, Fenwick Tree
    	
*/

#include <bits/stdc++.h>
 
using namespace std;
 
const int H = 20;
const int N = 200010;
const int INF = 1e9 + 10;
 
int n, m, a[N], pos[N], size[3 * N];
vector <int> t[3 * N], bit[3 * N], inv_bit(N);
 
void updateBIT (vector <int> &bit, int p, int v, int MAX) {
    while (p <= MAX) bit[p - 1] += v, p += (p & -p);
}
 
int queryBIT (vector <int> &bit, int p) {
    int sum = 0;
    while (p > 0) sum += bit[p - 1], p -= (p & -p);
    return sum;
}
 
void merge (int u, int b, int e) {
    int l = u << 1, r = l | 1;
    int L = size[l], R = size[r];
    t[l].push_back(INF), t[r].push_back(INF);
 
    size[u] = L + R, bit[u].clear(), bit[u].resize(size[u], 0);
    for (int i = 1; i <= size[u]; ++i) updateBIT(bit[u], i, 1, size[u]);
 
    t[u].clear();
    for (int i = 0, j = 0; i < L or j < R;) {
        if (t[l][i] < t[r][j]) t[u].push_back(t[l][i++]);
        else t[u].push_back(t[r][j++]);
    }
 
    t[l].pop_back(), t[r].pop_back();
}
 
void init (int u, int b, int e) {
    if (b == e) {
        t[u].clear(), bit[u].clear();
        size[u] = 1, bit[u].resize(size[u], 0);
        updateBIT(bit[u], 1, 1, size[u]);
        t[u].push_back(a[b]);
        return;
    }
 
    int l = u << 1, r = l | 1, m = b + e >> 1;
    init(l, b, m), init(r, m + 1, e);
    merge(u, b, e);
}
 
void updateSegTree (int u, int b, int e, int p, int x) {
    if (p > e or p < b) return;
    if (p >= b and p <= e) {
        int pos = lower_bound(t[u].begin(), t[u].end(), x) - t[u].begin();
        updateBIT(bit[u], pos + 1, -1, size[u]);
        if (b == e) return;
    }
 
    int l = u << 1, r = l | 1, m = b + e >> 1;
    updateSegTree(l, b, m, p, x), updateSegTree(r, m + 1, e, p, x);
}
 
int querySegTree (int u, int b, int e, int p, int q, int x, int side) {
    if (p > q or b > q or e < p) return 0;
    if (b >= p and e <= q) {
        int tot = upper_bound(t[u].begin(), t[u].end(), x) - t[u].begin();
        if (side) return queryBIT(bit[u], tot);
        return queryBIT(bit[u], size[u]) - queryBIT(bit[u], tot); 
    }
 
    int l = u << 1, r = l | 1, m = b + e >> 1;
    return querySegTree(l, b, m, p, q, x, side) + querySegTree(r, m + 1, e, p, q, x, side);
}
 
int main (int argc, char const *argv[]) {
    while (scanf("%d %d", &n, &m) == 2) {
        for (int i = 1; i <= n; ++i) {
            scanf("%d", a + i);
            pos[a[i]] = i;
        }
 
        init(1, 1, n);
        fill(inv_bit.begin(), inv_bit.end(), 0);
 
        long long inversions = 0;
        for (int i = n; i; --i) {
            inversions += (long long) queryBIT(inv_bit, pos[i]);
            updateBIT(inv_bit, pos[i], 1, N - 1);
        }
 
        while (m--) {
            printf("%lld\n", inversions);
            int x; scanf("%d", &x);
            inversions -= querySegTree(1, 1, n, 1, pos[x] - 1, x, 0);
            inversions -= querySegTree(1, 1, n, pos[x] + 1, n, x, 1);
            updateSegTree(1, 1, n, pos[x], x);
        }
    }
    return 0;
}
 
 

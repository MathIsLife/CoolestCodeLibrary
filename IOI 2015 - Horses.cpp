/*

     |\   |  `|` |``\  ```|` |   |  /```\  |``\
     | \  |   |  |__/     |  |___| |     | |__/
     |  \ |   |  |  \     |  |   | |     | |  \
    _|   \|  _|_ |   \ \__)  |   |  \___/  |   \
    
        IOI 2015 - Horses
        
        Category: Data Structures
        
        Keys: Observation, Algebra, Segment Tree
        
*/

#include <bits/stdc++.h> 

using namespace std;

typedef long long ll;
typedef long double ld;

const ld EPS = 1e-9;
const int N = 5e5 + 10;
const int MOD = 1e9 + 7;

int n, m;
ll x[N], y[N];
int tree[4 * N];
ld xlog[N], ylog[N];
ll product[N + N];
ld logsum[N + N];

void init_product (void) {
    for (int i = 0; i < n; ++i) {
        product[n + i] = x[i] % MOD;
    }
    for (int i = n - 1; i; --i) {
        product[i] = (product[i << 1] * product[i << 1 | 1]) % MOD;
    }
}

void modify_product (int p, ll v) {
    for (product[p += n] = v; p > 1; p >>= 1) {
        product[p >> 1] = (product[p] * product[p ^ 1]) % MOD;
    }
}

ll find_product (int l, int r) {
    ll ret = 1LL;
    for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
        if (l & 1) ret *= product[l++], ret %= MOD;
        if (r & 1) ret *= product[--r], ret %= MOD;
    }
    return ret;
}

void init_logsum (void) {
    for (int i = 0; i < n; ++i) {
        logsum[n + i] = xlog[i];
    }
    for (int i = n - 1; i; --i) {
        logsum[i] = logsum[i << 1] + logsum[i << 1 | 1];
    }
}

void modify_logsum (int p, ld v) {
    for (logsum[p += n] = v; p > 1; p >>= 1) {
        logsum[p >> 1] = logsum[p] + logsum[p ^ 1];
    }
}

ld find_logsum (int l, int r) {
    ld ret = 0.0;
    for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
        if (l & 1) ret += logsum[l++];
        if (r & 1) ret += logsum[--r];
    }
    return ret;
}

int merged (int p, int q) {
    if (p > q) swap(p, q);
    return (find_logsum(p + 1, q + 1) - ylog[p] + ylog[q] > -EPS) ? q : p;
}

void init_tree (int u, int b, int e) {
    if (b == e) {
        tree[u] = b;
        return;
    }
    int l = u << 1, r = l | 1, m = b + e >> 1;
    init_tree(l, b, m), init_tree(r, m + 1, e);
    tree[u] = merged(tree[l], tree[r]);
}

void modify_tree (int u, int b, int e, int p) {
    if (b > p or e < p) return;
    if (b == e) return;
    int l = u << 1, r = l | 1, m = b + e >> 1;
    modify_tree(l, b, m, p), modify_tree(r, m + 1, e, p);
    tree[u] = merged(tree[l], tree[r]);
}

ll value (int index) {
    return (find_product(0, index + 1) * y[index]) % MOD;
}

int main (int argc, char const *argv[]) {
    scanf("%d", &n);
    for (int i = 0; i < n; ++i) {
        scanf("%lld", x + i);
        xlog[i] = log(x[i]);
    }
    for (int i = 0; i < n; ++i) {
        scanf("%lld", y + i);
        ylog[i] = log(y[i]);
    }
    init_product();
    init_logsum();
    init_tree(1, 0, n - 1);
    printf("%lld\n", value(tree[1]));
    scanf("%d", &m); while (m--) {
        int cmd, pos; ll val;
        scanf("%d %d %lld", &cmd, &pos, &val);
        if (cmd == 1) {
            x[pos] = val, xlog[pos] = log(val);
            modify_product(pos, x[pos]);
            modify_logsum(pos, xlog[pos]);
            modify_tree(1, 0, n - 1, pos);
        } else {
            y[pos] = val, ylog[pos] = log(val);
            modify_tree(1, 0, n - 1, pos);
        }
        printf("%lld\n", value(tree[1]));
    }
    return 0;  
}


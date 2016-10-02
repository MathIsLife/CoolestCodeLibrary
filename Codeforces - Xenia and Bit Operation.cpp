/*

     |\   |  `|` |``\  ```|` |   |  /```\  |``\
     | \  |   |  |__/     |  |___| |     | |__/
     |  \ |   |  |  \     |  |   | |     | |  \
    _|   \|  _|_ |   \ \__)  |   |  \___/  |   \

    	   Codeforces 339D - Xenia and Bit Operation

    	   Category: Data Structure

        Keys: Segment Tree, I/O Optimization

*/

#include <bits/stdc++.h>

using namespace std;

typedef long long i64;
typedef unsigned long long ui64;

#define checkbit(n, b) ((n >> b) & 1)
#define gcd __gcd
#define bitcount __bultin_popcount
#define inf (i64) 1e14
#define eps 1e-9
#define pi acos(-1)
#define mod 1000000007

const int MAX = (1 << 17) + 50;

int A[MAX], T[4 * MAX], n, lim, q, p, v;

void Build (int node, int b, int e, int dist) {
    if (b == e) {
        T[node] = A[b];
        return;
    }

    int mid = (b + e) >> 1;
    int left = node + node;
    int right = left + 1;

    Build (left, b, mid, dist - 1);
    Build (right, mid + 1, e, dist - 1);

    if (dist & 1) T[node] = T[left] | T[right];
    else T[node] = T[left] ^ T[right];
}

void Update (int node, int b, int e, int pos, int val, int dist) {
    if (b > pos or e < pos) return;
    if (b == e and b == pos) {
        T[node] = val;
        return;
    }

    int mid = (b + e) >> 1;
    int left = node + node;
    int right = left + 1;

    Update (left, b, mid, pos, val, dist - 1);
    Update (right, mid + 1, e, pos, val, dist - 1);

    if (dist & 1) T[node] = T[left] | T[right];
    else T[node] = T[left] ^ T[right];
}

int main() {
    scanf("%d %d", &n, &q);
    lim = 1 << n;
    for (int i = 1; i <= lim; i++) scanf("%d", A + i);

    Build (1, 1, lim, n);

    while (q--) {
        scanf("%d %d", &p, &v);
        Update (1, 1, lim, p, v, n);
        printf("%d\n", T[1]);
    }
    return 0;
}


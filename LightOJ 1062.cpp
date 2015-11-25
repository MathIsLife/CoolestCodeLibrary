/*

     |\   |  `|` |``\  ```|` |   |  /```\  |``\
     | \  |   |  |__/     |  |___| |     | |__/
     |  \ |   |  |  \     |  |   | |     | |  \
    _|   \|  _|_ |   \ \__)  |   |  \___/  |   \

        LightOJ 1062 - Crossed Ladders

        Category: Computational Geometry

        Keys: Similar Triangles, Binary Search

*/

#include <bits/stdc++.h>

using namespace std;

typedef long long i64;
typedef unsigned long long ui64;

#define checkbit(n, b) ((n >> b) & 1)
#define gcd __gcd
#define bitcount __bultin_popcount
#define inf (int)1e9
#define eps 1e-9
#define pi acos(-1)
#define mod 1000000007

double x, y, c, d, lo, hi, p, q, cmp; 

void Kill (void) {
    int T, k; scanf("%d", &T);
    for (k = 1; k <= T; k++) {
        scanf("%lf %lf %lf", &x, &y, &c);
        lo = 0, hi = min(x, y);
        while (lo < hi) {
            d = (lo + hi)/2;
            p = sqrt(x * x - d * d), q = sqrt(y * y - d * d);
            cmp = (p * q)/(p + q);
            if (abs(cmp - c) <= eps) break;
            else if (cmp > c) lo = d;
            else hi = d;
        }
        printf("Case %d: %lf\n", k, d);
    }
}

int main () {
    Kill();
    return 0;
}

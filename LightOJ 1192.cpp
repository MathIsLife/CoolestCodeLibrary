/*

     |\   |  `|` |``\  ```|` |   |  /```\  |``\
     | \  |   |  |__/     |  |___| |     | |__/
     |  \ |   |  |  \     |  |   | |     | |  \
    _|   \|  _|_ |   \ \__)  |   |  \___/  |   \

        LightOJ 1192 - Left Right

        Category: Game Theory

        Keys: Nim Transformation

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
#define mod 100000007

int T, Nim_Sum, k, i, a, b, cs = 1;

int main() {
    scanf("%d", &T); while (T--) {
        scanf("%d", &k); Nim_Sum = 0;
        for (i = 1; i <= k; i++) {
            scanf("%d %d", &a, &b);
            Nim_Sum ^= (b - a - 1);
        }
        printf("Case %d: %s\n", cs++, Nim_Sum ? "Alice" : "Bob");
    }
    return 0;
}


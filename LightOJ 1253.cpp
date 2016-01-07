/*

     |\   |  `|` |``\  ```|` |   |  /```\  |``\
     | \  |   |  |__/     |  |___| |     | |__/
     |  \ |   |  |  \     |  |   | |     | |  \
    _|   \|  _|_ |   \ \__)  |   |  \___/  |   \

        LightOJ 1253 - Misere Nim

        Category: Game Theory

        Keys: Sprague Grundy Numbers

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

int T, Sum, i, Num, k, Not_One, cs = 1;

int main() {
    scanf("%d", &T); while (T--) {
        scanf("%d", &k);
        Sum = 0, Not_One = 0;
        for (i = 1; i <= k; i++) {
            scanf("%d", &Num);
            if (Num > 1) ++Not_One;
            Sum ^= Num;
        }
        printf("Case %d: %s\n", cs++, Not_One ? Sum ? "Alice" : "Bob" : Sum ? "Bob" : "Alice");
    }
    return 0;
}


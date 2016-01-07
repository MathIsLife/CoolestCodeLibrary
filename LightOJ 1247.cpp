/*

     |\   |  `|` |``\  ```|` |   |  /```\  |``\
     | \  |   |  |__/     |  |___| |     | |__/
     |  \ |   |  |  \     |  |   | |     | |  \
    _|   \|  _|_ |   \ \__)  |   |  \___/  |   \

        LightOJ 1247 - Matrix Game

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

int T, Nim_Sum, i, j, Row, Num, m, n, cs = 1;

int main() {
    scanf("%d", &T); while (T--) {
        scanf("%d %d", &m, &n); Nim_Sum = 0;
        for (i = 1; i <= m; i++) {
            Row = 0;
            for (j = 1; j <= n; j++) {
                scanf("%d", &Num);
                Row += Num;
            }
            Nim_Sum ^= Row;
        }
        printf("Case %d: %s\n", cs++, Nim_Sum ? "Alice" : "Bob");
    }
    return 0;
}


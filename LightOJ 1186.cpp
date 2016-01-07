/*

     |\   |  `|` |``\  ```|` |   |  /```\  |``\
     | \  |   |  |__/     |  |___| |     | |__/
     |  \ |   |  |  \     |  |   | |     | |  \
    _|   \|  _|_ |   \ \__)  |   |  \___/  |   \
    
        LightOJ 1186 - Incredible Chess
        
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
#define MAX 105

int T, Nim_Sum, A[MAX], n, i, Num, cs = 1;

int main() {
    scanf("%d", &T); while (T--) {
        scanf("%d", &n); Nim_Sum = 0;
        for (i = 1; i <= n; i++) scanf("%d", A + i);
        for (i = 1; i <= n; i++) {
            scanf("%d", &Num);
            Nim_Sum ^= (Num - A[i] - 1);
        }
        printf("Case %d: %s wins\n", cs++, Nim_Sum ? "white" : "black");
    }
    return 0;
}


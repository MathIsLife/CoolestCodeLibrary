/*

     |\   |  `|` |``\  ```|` |   |  /```\  |``\
     | \  |   |  |__/     |  |___| |     | |__/
     |  \ |   |  |  \     |  |   | |     | |  \
    _|   \|  _|_ |   \ \__)  |   |  \___/  |   \

        USACO - Score Inflation
        
        Category: Dynamic Programming
        
        Keys: Bottom Up (Iterative DP)

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
#define MAX 10005

int DP[MAX], M, N, a, b, i;

int main () {
    freopen("inflate.in", "r", stdin);
    freopen("inflate.out", "w", stdout);

    memset(DP, 0, sizeof DP);
    cin >> M >> N; while (N--) {
        cin >> a >> b;
        for (i = 0; i + b <= MAX; i++)
            DP[i + b] = max(DP[i + b], DP[i] + a);
    }
    cout << DP[M] << endl;

    return 0;
}


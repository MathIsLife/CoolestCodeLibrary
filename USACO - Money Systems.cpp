/*

     |\   |  `|` |``\  ```|` |   |  /```\  |``\
     | \  |   |  |__/     |  |___| |     | |__/
     |  \ |   |  |  \     |  |   | |     | |  \
    _|   \|  _|_ |   \ \__)  |   |  \___/  |   \

        USACO - Money Systems

        Category: Dynamic Programming

        Keys: Coin Change, Top Down (Recursive DP)

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
#define MAX 10002

ifstream fin ("money.in");
ofstream fout ("money.out");

i64 DP[MAX][30], V, N, i, Coin[30];

i64 Call (i64 n, i64 k) {
    if (n == 0) return 1;
    if (n < 0) return 0;
    if (k <= 0) return 0;
    if (DP[n][k] != -1) return DP[n][k];
    return DP[n][k] = Call(n, k - 1) + Call(n - Coin[k], k);
}

void Kill (void) {
    fin >> V >> N;
    for (i = 1; i <= V; i++) fin >> Coin[i];
    memset(DP, -1, sizeof DP);
    fout << Call(N, V) << endl;
}

int main() {
    Kill();
    return 0;
}

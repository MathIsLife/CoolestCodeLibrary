/*

     |\   |  `|` |``\  ```|` |   |  /```\  |``\
     | \  |   |  |__/     |  |___| |     | |__/
     |  \ |   |  |  \     |  |   | |     | |  \
    _|   \|  _|_ |   \ \__)  |   |  \___/  |   \

        USACO - Cow Pedigrees

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

#define mod 9901
#define MAX 205

int DP[MAX][MAX], N, K, i, j, k;

ifstream fin ("nocows.in");
ofstream fout ("nocows.out");

void Kill (void) {
    fin >> N >> K;
    memset(DP, 0, sizeof DP);
    for (i = 1; i <= K; i++) DP[1][i] = 1;
    for (i = 2; i <= N; i++)
        for (j = 2; j <= K; j++)
            for (k = 1; k + 2 <= i; k++)
                DP[i][j] = (DP[i][j] + DP[k][j - 1] * DP[i - k - 1][j - 1]) % mod;
    fout << (DP[N][K] - DP[N][K - 1] + mod) % mod << endl;
}

int main() {
    Kill();
    return 0;
}


/*

     |\   |  `|` |``\  ```|` |   |  /```\  |``\
     | \  |   |  |__/     |  |___| |     | |__/
     |  \ |   |  |  \     |  |   | |     | |  \
    _|   \|  _|_ |   \ \__)  |   |  \___/  |   \
    
        USACO - Humble Numbers
        
        Category: Ad hoc, Implementation
        
        Keys: Brute Force, Greedy

*/

#include <bits/stdc++.h>

using namespace std;

typedef long long i64;
typedef unsigned long long ui64;

#define checkbit(n, b) ((n >> b) & 1)
#define gcd __gcd
#define bitcount __bultin_popcount
#define inf (int)2e9
#define eps 1e-9
#define pi acos(-1)
#define mod 1000000007
#define MAX_K 105
#define MAX_N 100005

vector<int> V;
int K, N, i, j, ID[MAX_K], P[MAX_K], H[MAX_N];

void Read (void) {
    cin >> K >> N;
    for (i = 1; i <= K; i++) cin >> P[i];
    memset(ID, 0, sizeof ID); H[0] = 1;
}

int Next_Humble_Number (void) {
    int Ret = inf; V.clear();
    for (i = 1; i <= K; i++) {
        if (P[i] * H[ID[i]] <= Ret) {
            if (P[i] * H[ID[i]] < Ret) V.clear();
            V.push_back(i); Ret = P[i] * H[ID[i]];
        }
    }
    for (i = 0; i < V.size(); i++) ++ID[V[i]];
    return Ret;
}

int main () {
    freopen("humble.in", "r", stdin);
    freopen("humble.out", "w", stdout);

    Read();
    for (j = 1; j <= N; j++) H[j] = Next_Humble_Number();
    cout << H[N] << endl;

    return 0;
}


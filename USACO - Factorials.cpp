/*

     |\   |  `|` |``\  ```|` |   |  /```\  |``\
     | \  |   |  |__/     |  |___| |     | |__/
     |  \ |   |  |  \     |  |   | |     | |  \
    _|   \|  _|_ |   \ \__)  |   |  \___/  |   \
    
        USACO - Factorials
        
        Category: Mathematics
        
        Keys: Recursive Descent, Observation

*/

#include <bits/stdc++.h>

using namespace std;

typedef long long i64;
typedef unsigned long long ui64;
typedef pair<int, int> pii;

#define checkbit(n, b) ((n >> b) & 1)
#define gcd __gcd
#define bitcount __bultin_popcount
#define inf (int)2e9
#define eps 1e-9
#define pi acos(-1)
#define mod 1000000007
#define MAX 4225

int N, F[] = {1, 1, 2, 6, 4}, Two[] = {6, 2, 4, 8};

int Ans (int n) {
    if (n < 5) return F[n];
    int q = n / 5, r = n % 5;
    return (Ans(q) * Two[q % 4] * F[r]) % 10;
}

int main () {
    freopen("fact4.in", "r", stdin);
    freopen("fact4.out", "w", stdout);
    cin >> N; cout << Ans(N) << endl;
    return 0;
}


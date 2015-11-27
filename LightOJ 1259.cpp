/*

     |\   |  `|` |``\  ```|` |   |  /```\  |``\
     | \  |   |  |__/     |  |___| |     | |__/
     |  \ |   |  |  \     |  |   | |     | |  \
    _|   \|  _|_ |   \ \__)  |   |  \___/  |   \

        LightOJ 1259 - Goldbach's Conjecture

        Category - Mathematics, Number Theory

        Keys: Sieve of Eratosthenes

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
#define MAX 10000000

vector<int> primes; bool Mark[MAX];

void Sieve (void) {
    memset(Mark, true, sizeof Mark);
    int i, j; Mark[1] = false;
    for (i = 2; i * i <= MAX; i++)
        if (Mark[i])
            for (j = i * i; j <= MAX; j += i)
                Mark[j] = false;
    for (i = 2; i <= MAX; i++)
        if (Mark[i]) primes.push_back(i);
}

void Kill (void) {
    int T, k, n, t, lim, ret; Sieve();
    lim = primes.size(); scanf("%d", &T);
    for (k = 1; k <= T; k++) {
        scanf("%d", &n); ret = 0;
        for (t = 0; t < lim && primes[t] <= n/2; t++)
            if (Mark[n - primes[t]]) ret++;
        printf("Case %d: %d\n", k, ret);
    }
}

int main () {
    Kill();
    return 0;
}


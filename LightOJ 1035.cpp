/*

     |\   |  `|` |``\  ```|` |   |  /```\  |``\
     | \  |   |  |__/     |  |___| |     | |__/
     |  \ |   |  |  \     |  |   | |     | |  \
    _|   \|  _|_ |   \ \__)  |   |  \___/  |   \

        LightOJ 1035 - Intelligent Factorial Factorization

        Category: Number Theory, Implementation

        Keys: Legendre's Formula, Sieve of Eratosthenes

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

int T, N, i, j, k, cnt, e, p;
vector<int> primes; bool mark[150];

void sieve (void) {
    memset(mark, true, sizeof mark);
    for (i = 2; i < 120; i++)
        for (j = i * i; j < 120; j += i) 
          mark[j] = false;
    for (i = 2; i < 120; i++)
        if (mark[i]) primes.push_back(i);
}

void Kill (void) {
    sieve(); scanf("%d", &T);
    for (k = 1; k <= T; k++) {
        scanf("%d", &N); cnt = 0;
        printf("Case %d: %d = ", k, N);
        for (i = 0; i < primes.size(); i++) {
            p = primes[i], e = 0;
            if (p > N) break;
            double tmp = N * 1.0;
            while (tmp >= 1)
               tmp /= (p * 1.0), e += floor(tmp);
            if (cnt++ != 0) printf(" * ");
            printf("%d (%d)", p, e);
        }
        printf("\n");
    }
}

int main () {
    Kill();
    return 0;
}


/*

     |\   |  `|` |``\  ```|` |   |  /```\  |``\
     | \  |   |  |__/     |  |___| |     | |__/
     |  \ |   |  |  \     |  |   | |     | |  \
    _|   \|  _|_ |   \ \__)  |   |  \___/  |   \

        LightOJ 1234 - Harmonic Number

        Category: Mathematics, Number Theory 

        Keys: Asymptotic Expansion

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

#define MAX 10000
#define gamma 0.5772156649
// Euler-Mascheroni constant 

int T, n, j, k; double H[MAX + 5];

void Fill (void) {
    H[1] = 1;
    for (j = 2; j <= MAX; j++) H[j] = H[j - 1] + 1/(1.0 * j);
}

void Kill (void) {
    scanf("%d", &T);
    for (k = 1; k <= T; k++) {
        scanf("%d", &n);
        printf("Case %d: ", k); 
        double bernouli = 1/(2.0 * n) - 1/(12.0 * n * n) + 1.0/(120.0 * n * n * n * n);
        if (n <= MAX) printf("%0.10lf\n", H[n]);
        else printf("%0.10lf\n", log(n) + gamma + bernouli);
    }
}

int main () {
    Fill(), Kill();
    return 0;
}

/*

     |\   |  `|` |``\  ```|` |   |  /```\  |``\
     | \  |   |  |__/     |  |___| |     | |__/
     |  \ |   |  |  \     |  |   | |     | |  \
    _|   \|  _|_ |   \ \__)  |   |  \___/  |   \

        LightOJ 1098 - A New Function

        Category: Mathematics, Number Theory

        Keys: Observation, Counting

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

i64 CSOD (i64 n) {
    i64 s, t, sq = floor(sqrt(n)), ret = 0;
    for (s = 2; s <= sq; s++) 
	t = n / s, 
	ret += s * (t - s + 1) + t * (t + 1)/2 - s * (s + 1)/2;
    return ret;
}

void Kill (void) {
    i64 T, N, k; scanf("%lld", &T);
    for (k = 1; k <= T; k++)
	scanf("%lld", &N), 
	printf("Case %lld: %lld\n", k, CSOD(N));
}

int main () {
    Kill();
    return 0;
}


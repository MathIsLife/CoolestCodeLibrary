/*

     |\   |  `|` |``\  ```|` |   |  /```\  |``\
     | \  |   |  |__/     |  |___| |     | |__/
     |  \ |   |  |  \     |  |   | |     | |  \
    _|   \|  _|_ |   \ \__)  |   |  \___/  |   \

        LightOJ 1307 - Counting Triangles

        Category: Ad hoc 

        Keys: Triangle Inequality, Binary Search

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

vector<int> V;
int T, N, i, j, k, t, ret;

void Kill (void) {
	scanf("%d", &T);
	for (k = 1; k <= T; k++) {
		scanf("%d", &N); ret = 0; V.clear();
		for (j = 0; j < N; j++) scanf("%d", &t), V.push_back(t);
		sort(V.begin(), V.end());
		for (i = 0; i < N; i++) {
			for (j = i + 1; j < N; j++) {
				t = lower_bound(V.begin(), V.end(), V[i] + V[j]) - V.begin();
				ret += (t - j - 1);
			}
		}
		printf("Case %d: %d\n", k, ret);
	}
}

int main () {
    Kill();
    return 0;
}


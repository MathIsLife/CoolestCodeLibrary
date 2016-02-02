/*

     |\   |  `|` |``\  ```|` |   |  /```\  |``\
     | \  |   |  |__/     |  |___| |     | |__/
     |  \ |   |  |  \     |  |   | |     | |  \
    _|   \|  _|_ |   \ \__)  |   |  \___/  |   \

*/

#include <bits/stdc++.h>

using namespace std;

typedef long long i64;
typedef unsigned long long ui64;
typedef pair <long long, long long> pii;

#define checkbit(n, b) ((n >> b) & 1)
#define gcd __gcd
#define bitcount __bultin_popcount
#define inf (i64) 1e14
#define eps 1e-9
#define pi acos(-1)
#define mod 1000000007
#define MAX 1000005

i64 N, u, v, Ret = 0, R[MAX], P[MAX], F[MAX];

void MakeSet (void) {
	for (int i = 0; i < MAX; i++) P[i] = i, R[i] = 0, F[i] = 1;
}

i64 Find (i64 x) {
    return P[x] == x ? x : P[x] = Find(P[x]);
}

void Union (i64 x, i64 y) {
	i64 x_root = Find(x), y_root = Find(y);
	if (x_root == y_root) return;
	
	if (R[x_root] < R[y_root]) 
		P[x_root] = y_root, F[y_root] += F[x_root];
	
	else if (R[x_root] > R[y_root]) 
		P[y_root] = x_root, F[x_root] += F[y_root];
	
	else 
		P[y_root] = x_root, ++R[x_root], F[x_root] += F[y_root];
}

int main () {
	MakeSet(); scanf ("%lld", &N); 
	while (N--) {
		scanf ("%lld %lld", &u, &v);
		if (Find(u) != Find(v)) Ret += F[Find(u)] * F[Find(v)];
		Union(u, v); printf ("%lld\n", Ret);
	}
    return 0;
}


/*

     |\   |  `|` |``\  ```|` |   |  /```\  |``\
     | \  |   |  |__/     |  |___| |     | |__/
     |  \ |   |  |  \     |  |   | |     | |  \
    _|   \|  _|_ |   \ \__)  |   |  \___/  |   \
    
        USACO - Cow Tours
        
        Category: Graph Theory, All Pairs Shortest Path
        
        Keys: Floyd Warshall, Flood Fill

*/

#include <bits/stdc++.h>

using namespace std;

typedef long long i64;
typedef unsigned long long ui64;

#define checkbit(n, b) ((n >> b) & 1)
#define gcd __gcd
#define bitcount __bultin_popcount
#define inf (double)1e9
#define eps 1e-9
#define pi acos(-1)
#define mod 1000000007
#define MAX 154

struct node {int x, y;};

int N, i, j, k;
node A[MAX]; string row; 
double Dist[MAX][MAX], Far[MAX], Ret;

double Length (node A, node B) {
	return hypot(A.x - B.x, A.y - B.y);
}

void Fill (void) {
	for (i = 0; i < MAX; i++)
		for (j = 0; j < MAX; j++)
			Dist[i][j] = inf;
}

void Read (void) {
	cin >> N;
	for (i = 1; i <= N; i++) cin >> A[i].x >> A[i].y;
	for (i = 1; i <= N; i++) {
		cin >> row;
		for (j = 1; j <= N; j++) if (row[j - 1] - '0') 
			Dist[i][j] = Length(A[i], A[j]);
	}
}

void Floyd_Warshall (void) {
	for (k = 1; k <= N; k++)
		for (i = 1; i <= N; i++)
			for (j = 1; j <= N; j++)
				Dist[i][j] = min(Dist[i][j], Dist[i][k] + Dist[k][j]);
	for (i = 1; i <= N; i++) Dist[i][i] = 0;
}

void Farthest (void) {
    memset(Far, 0, sizeof Far);
    for (i = 1; i <= N; i++)
	    for (j = 1; j <= N; j++)
		    if (Dist[i][j] != inf)
                Far[i] = max(Far[i], Dist[i][j]);
}

void Connect_And_Check (void) {
	Ret = inf;
	for (i = 1; i <= N; i++)
		for (j = 1; j <= N; j++)
			if (Dist[i][j] == inf) 
				Ret = min(Ret, Far[i] + Length(A[i], A[j]) + Far[j]);
}

void Print (void) {
	for (i = 1; i <= N; i++) Ret = max(Ret, Far[i]);
	printf("%0.6lf\n", Ret);
}

int main() {
    freopen("cowtour.in", "r", stdin);
    freopen("cowtour.out", "w", stdout);
    
    Fill();
    Read();
    Floyd_Warshall();
    Farthest();
    Connect_And_Check();
    Print();
    
    return 0;
}

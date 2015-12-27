/*

     |\   |  `|` |``\  ```|` |   |  /```\  |``\
     | \  |   |  |__/     |  |___| |     | |__/
     |  \ |   |  |  \     |  |   | |     | |  \
    _|   \|  _|_ |   \ \__)  |   |  \___/  |   \
    
        USACO - The Tamworth Two
        
        Category: Ad hoc
        
        Keys: Simulation, Brute Force

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

#define lim 100000

char Grid[11][11];
int i, j, a, b, c, d, F, C, t;

int dx[] = {-1, 0, 1, 0};
int dy[] = {0, 1, 0, -1};

bool Valid (int x, int y) {
    return x >= 1 && x <= 10 && y >= 1 && y <= 10 && Grid[x][y] != '*';
}

void Move (void) {
	if (Valid(a + dx[F], b + dy[F])) a += dx[F], b += dy[F];
	else F = (F + 1) % 4;
	
	if (Valid(c + dx[C], d + dy[C])) c += dx[C], d += dy[C];
	else C = (C + 1) % 4;
}

int main () {
	freopen("ttwo.in", "r", stdin);
	freopen("ttwo.out", "w", stdout);
	
	for (i = 1; i <= 10; i++) {
		for (j = 1; j <= 10; j++) {
			cin >> Grid[i][j];
			if (Grid[i][j] == 'F') a = i, b = j;
			else if (Grid[i][j] == 'C') c = i, d = j;
		}
	}
	
	F = 0, C = 0, t = 0;
	for (i = 0; i < lim; i++) {
		Move(), t++;
		if (a == c && b == d) {
			cout << t << endl;
			return 0;
		}
	}
	
	cout << 0 << endl;
    return 0;
}

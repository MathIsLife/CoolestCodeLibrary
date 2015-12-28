/*

     |\   |  `|` |``\  ```|` |   |  /```\  |``\
     | \  |   |  |__/     |  |___| |     | |__/
     |  \ |   |  |  \     |  |   | |     | |  \
    _|   \|  _|_ |   \ \__)  |   |  \___/  |   \
    
        USACO - Overfencing
        
        Category: Graph Theory, Shortest Path
        
        Keys: Breadth First Search

*/

#include <bits/stdc++.h>

using namespace std;

typedef long long i64;
typedef unsigned long long ui64;
typedef pair<int, int> pii;
typedef vector< vector<int> > vii;

#define checkbit(n, b) ((n >> b) & 1)
#define gcd __gcd
#define bitcount __bultin_popcount
#define inf (int)1e9
#define eps 1e-9
#define pi acos(-1)
#define mod 1000000007

#define f first
#define s second

char G[205][80]; string row;
int a, b, c, d, i, j, k, H, W, ret;
int Dist1[205][80], Dist2[205][80];

int dx[] = {-1, 0, 1, 0};
int dy[] = {0, 1, 0, -1};

bool Valid (int x, int y) {
	return x >= 1 && x <= 2 * H + 1 && y >= 1 && y <= 2 * W + 1 && G[x][y] != '*';
}

void Read (void) {
	cin >> W >> H; bool flag = 0;
	getline(cin, row);
	
	for (i = 1; i <= 2 * H + 1; i++) {
		getline(cin, row);
		for (j = 1; j <= 2 * W + 1; j++) {
			if (row[j - 1] == ' ') G[i][j] = '.';
			else G[i][j] = '*';
			
			if (i == 1 or i == 2 * H + 1 or j == 1 or j == 2 * W + 1) {
				if (G[i][j] == '.') {
					if (flag) c = i, d = j; 
					else a = i, b = j, flag = 1;
				}
			}
		}
	}
}

void BFS (int a, int b, int (&Dist)[205][80]) {
	int now_x, now_y; 
	queue< pii > Q; pii P, C;
	Dist[a][b] = 0, Q.push(make_pair(a,b));
	
	while (!Q.empty()) {
		C = Q.front(); Q.pop();
		for (k = 0; k < 4; k++) {
			now_x = C.f + dx[k], now_y = C.s + dy[k];
			if (Valid(now_x, now_y))
				if (Dist[now_x][now_y] == -1) 
					Dist[now_x][now_y] = Dist[C.f][C.s] + 1,
					Q.push(make_pair(now_x, now_y));
		}
 	}
}

void Kill (void) {
	ret = 0;
	memset(Dist1, -1, sizeof Dist1);
	memset(Dist2, -1, sizeof Dist2);
	
	BFS(a, b, Dist1); BFS(c, d, Dist2);
	
	for (i = 1; i <= 2 * H + 1; i++) 
		for (j = 1; j <= 2 * W + 1; j++) 
			if (G[i][j] != '*')
				ret = max(ret, min(Dist1[i][j], Dist2[i][j]));
	
	cout << ceil(ret / 2.0) << endl;
}

int main() {
    freopen("maze1.in", "r", stdin);
    freopen("maze1.out", "w", stdout);
    
    Read(), Kill();
    return 0;
}


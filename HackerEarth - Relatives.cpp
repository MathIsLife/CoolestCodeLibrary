/*

     |\   |  `|` |``\  ```|` |   |  /```\  |``\
     | \  |   |  |__/     |  |___| |     | |__/
     |  \ |   |  |  \     |  |   | |     | |  \
    _|   \|  _|_ |   \ \__)  |   |  \___/  |   \
    
    	HackerEarth - Relatives
    	
    	Category: Dynamic Programming
    	
    	Keys: Pointer Walk
    	
*/

#include <bits/stdc++.h>

using namespace std;

const int N = 105;
const int OO = 2e9 + 50; 

pair <int, int> DP[N][N][N];
int K, a, b, c, A[N], B[N], C[N];

int main (int argc, char const *argv[]) {
    scanf("%d %d %d %d", &a, &b, &c, &K);
    for (int i = 0; i < a; ++i) scanf("%d", A + i);
    for (int i = 0; i < b; ++i) scanf("%d", B + i);
    for (int i = 0; i < c; ++i) scanf("%d", C + i);

    for (int i = 0; i <= a; ++i)
	for (int j = 0; j <= b; ++j)
	    for (int k = 0; k <= c; ++k)
		DP[i][j][k] = make_pair(OO, OO);

    DP[0][0][0] = make_pair(1, 0);

    for (int i = 0; i <= a; ++i)
	for (int j = 0; j <= b; ++j)
	    for (int k = 0; k <= c; ++k) {
		if (i < a) {
	    	    int Min = DP[i][j][k].first, Cost = DP[i][j][k].second + A[i];
		    if (Cost > K) Cost = A[i], ++Min;
		    DP[i + 1][j][k] = min(DP[i + 1][j][k], make_pair(Min, Cost));
		}

		if (j < b) {
	    	    int Min = DP[i][j][k].first, Cost = DP[i][j][k].second + B[j];
		    if (Cost > K) Cost = B[j], ++Min;
		    DP[i][j + 1][k] = min(DP[i][j + 1][k], make_pair(Min, Cost));
		}

		if (k < c) {
		    int Min = DP[i][j][k].first, Cost = DP[i][j][k].second + C[k];
		    if (Cost > K) Cost = C[k], ++Min;
		    DP[i][j][k + 1] = min(DP[i][j][k + 1], make_pair(Min, Cost));
		}
	    }

    printf("%d\n", DP[a][b][c]);
    return 0;
}


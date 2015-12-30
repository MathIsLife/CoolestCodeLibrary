/*

     |\   |  `|` |``\  ```|` |   |  /```\  |``\
     | \  |   |  |__/     |  |___| |     | |__/
     |  \ |   |  |  \     |  |   | |     | |  \
    _|   \|  _|_ |   \ \__)  |   |  \___/  |   \
    
        USACO - Agri-Net
        
        Category: Graph Theory
        
        Keys: Minimal Spanning Tree, Prim's Algorithm

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
#define MAX 105

bool Mark[MAX];
int Adj[MAX][MAX], N, i, j, Dist[MAX], Mate[MAX];

void Read (void) {
    scanf("%d", &N);
    for (i = 1; i <= N; i++)
        for (j = 1; j <= N; j++)
            scanf("%d", *(Adj + i) + j);
}

int Find_Node (void) {
    int MinDist = inf, ID;
    for (j = 1; j <= N; j++)
        if (!Mark[j] && Dist[j] < MinDist)
            MinDist = Dist[j], ID = j;
    return ID;
}

int Prim (void) {
    memset(Mark, 0, sizeof Mark);
    memset(Mate, -1, sizeof Mate);
    for (i = 1; i <= N; i++) Dist[i] = inf;

    int Cost = 0, Size = 1; Mark[1] = true;
    for (j = 2; j <= N; j++) if (Adj[1][j])
        Dist[j] = Adj[1][j], Mate[j] = 1;

    while (Size < N) {
        i = Find_Node();
        Size++, Cost += Dist[i], Mark[i] = true;
        for (j = 1; j <= N; j++)
            if (Adj[i][j] && Dist[j] > Adj[i][j])
                Dist[j] = Adj[i][j], Mate[j] = i;
    }
    return Cost;
}

int main () {
    freopen("agrinet.in", "r", stdin);
    freopen("agrinet.out", "w", stdout);

    Read();
    printf("%d\n", Prim());

    return 0;
}


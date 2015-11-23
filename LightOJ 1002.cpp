/*

     |\   |  `|` |``\  ```|` |   |  /```\  |``\
     | \  |   |  |__/     |  |___| |     | |__/
     |  \ |   |  |  \     |  |   | |     | |  \
    _|   \|  _|_ |   \ \__)  |   |  \___/  |   \

        LightOJ 1002 - Country Roads

        Category: Graph Theory, Shortest Path

        Keys: Modified Dijkstra

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

struct node {int label, dist;};

vector<node> Graph[505];
int T, n, m, u, v, w, t, i, k;

void Read (void) {
    for (i = 0; i < 503; i++) Graph[i].clear();
    scanf("%d %d", &n, &m); node N;
    while (m--) {
        scanf("%d %d %d", &u, &v, &w);
        N.label = u, N.dist = w;
        Graph[v].push_back(N);
        N.label = v;
        Graph[u].push_back(N);
    }
    scanf("%d", &t);
}

vector<int> Mod_Dijkstra (void) {
    vector<int> Q, Dist(505);
    for (i = 0; i < n; i++)
        Dist[i] = inf, Q.push_back(i);
    Dist[t] = 0; int V, Val, s;
    while (!Q.empty()) {
        V = 0, Val = inf;
        for (i = 0; i < Q.size(); i++)
            if (Dist[Q[i]] <= Val) V = Q[i], Val = Dist[Q[i]];
        Q.erase(remove(Q.begin(), Q.end(), V), Q.end());
        for (s = 0; s < Graph[V].size(); s++) {
            node vertex = Graph[V][s];
            int alt = max(Dist[V], vertex.dist);
            Dist[vertex.label] = min(alt, Dist[vertex.label]);
        }
    }
    return Dist;
}

void Kill (void) {
    scanf("%d", &T);
    for (k = 1; k <= T; k++) {
        Read(); printf("Case %d:\n", k);
        vector<int> Ret = Mod_Dijkstra();
        for (i = 0; i < n; i++) {
            if (Ret[i] == inf) printf("Impossible\n");
            else printf("%d\n", Ret[i]);
        }
    }
}

int main () {
    Kill();
    return 0;
}


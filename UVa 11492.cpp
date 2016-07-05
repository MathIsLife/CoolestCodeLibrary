/*

     |\   |  `|` |``\  ```|` |   |  /```\  |``\
     | \  |   |  |__/     |  |___| |     | |__/
     |  \ |   |  |  \     |  |   | |     | |  \
    _|   \|  _|_ |   \ \__)  |   |  \___/  |   \
    
    	UVa 11492 - Babel
    	
    	Category: Graph Theory, Shortest Path
    	
    	Keys: Graph Modeling
    	
*/

#include <bits/stdc++.h>

using namespace std;

const int N = 4010;
const int INF = 2e9 + 100;

struct data {
    int to, weight, start;
    data () {}
    data (int _t, int _w, int _s) : to(_t), weight(_w), start(_s) {}
};

struct state {
    int label, cost, letter;
    state () {}
    state (int _l, int _c, int _f) : label(_l), cost(_c), letter(_f) {}
    bool operator < (const state &s) const {
        return cost > s.cost;
    }
};

vector <data> g[N];
map <string, int> Map;
int m, n, s, d, dist[N][30];
string O, D;

int Dijkstra (void) {
    for (int i = 1; i <= n; ++i)
        for (int j = 0; j < 26; ++j) dist[i][j] = INF;
    priority_queue <state> PQ;
    PQ.push(state(Map[O], 0, 26));
    for (int i = 0; i < 26; ++i) dist[0][i] = 0;

    while (not PQ.empty()) {
        state S = PQ.top(); PQ.pop();
        for (data d : g[S.label]) {
            if (d.start == S.letter) continue;
            if (S.cost + d.weight < dist[d.to][d.start]) {
                dist[d.to][d.start] = S.cost + d.weight;
                PQ.push(state(d.to, dist[d.to][d.start], d.start));
            }
        }
    }

    int result = INF;
    for (int i = 0; i < 26; ++i) result = min(result, dist[Map[D]][i]);
    if (result == INF) result = -1;
    return result;
}

int main (int argc, char const *argv[]) {
    #ifndef ONLINE_JUDGE
        freopen("input.txt", "r", stdin);
    #endif // ONLINE_JUDGE

    while (scanf("%d", &m) and m) {
        Map.clear();
        for (int i = 0; i < N; ++i) g[i].clear();
        n = 0;

        cin >> O >> D;
        Map[O] = ++n;
        if (O == D) Map[D] = Map[O];
        else Map[D] = ++n;

        for (int i = 0; i < m; ++i) {
            string u, v, w;
            cin >> u >> v >> w;

            if (not Map.count(u)) Map[u] = ++n;
            if (not Map.count(v)) Map[v] = ++n;

            g[Map[u]].push_back(data(Map[v], w.size(), w[0] - 'a'));
            g[Map[v]].push_back(data(Map[u], w.size(), w[0] - 'a'));
        }

        int cost = Dijkstra();

        if (cost == -1) printf("impossivel\n");
        else printf("%d\n", cost);
    }
    return 0;
}


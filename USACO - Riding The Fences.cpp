/*

     |\   |  `|` |``\  ```|` |   |  /```\  |``\
     | \  |   |  |__/     |  |___| |     | |__/
     |  \ |   |  |  \     |  |   | |     | |  \
    _|   \|  _|_ |   \ \__)  |   |  \___/  |   \

        USACO - Riding The Fences

        Category: Graph Theory

        Keys: Euler Circuit/Path

*/

#include <bits/stdc++.h>

using namespace std;

const int N = 505;

stack <int> tour;
int f, g[N][N], deg[N];

void eulerTour (int u) {
	if (deg[u] == 0) {
		tour.push(u);
		return;
	}

	while (deg[u]) {
		int v = 1;
		while (!g[u][v]) ++v;
		--g[u][v], --g[v][u], --deg[u], --deg[v];
		eulerTour(v);
	}

	tour.push(u);
}

int main (int argc, char const *argv[]) {
	freopen("fence.in", "r", stdin);
	freopen("fence.out", "w", stdout);

	scanf("%d", &f); while (f--) {
		int u, v;
		scanf("%d %d", &u, &v);
		++g[u][v], ++g[v][u], ++deg[u], ++deg[v];
	}

	int start;
	for (int i = 1; i < N; ++i) if (deg[i]) {start = i; break;}
	for (int i = 1; i < N; ++i) if (deg[i] & 1) {start = i; break;}

	eulerTour(start);
	while (not tour.empty()) printf("%d\n", tour.top()), tour.pop();
	return 0;
}


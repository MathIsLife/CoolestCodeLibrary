/*

     |\   |  `|` |``\  ```|` |   |  /```\  |``\
     | \  |   |  |__/     |  |___| |     | |__/
     |  \ |   |  |  \     |  |   | |     | |  \
    _|   \|  _|_ |   \ \__)  |   |  \___/  |   \
    
        IOI 2016 - Roller Coaster Railroad
        
        Category: Graph Theory
        
        Keys: Observation, Minimum Spanning Tree
        
*/

#include <bits/stdc++.h>
#include "railroad.h"

using namespace std;

struct data {
	int x, y, z;
	data () {} 
	data (int _x, int _y, int _z) {
		x = _x, y = _y, z = _z;
	}
	bool operator < (const data &d) const {
		return x < d.x;
	}
};

const int INF = 2e9 + 10;

vector <int> p;

int find (int x) {
	return p[x] == x ? x : p[x] = find(p[x]);
}

bool merge (int x, int y) {
	x = find(x), y = find(y);
	return p[x] = y, x != y;
}

long long plan_roller_coaster (vector <int> s, vector <int> t) {
	s.push_back(INF);
	t.push_back(1);
	int n = (int) s.size();
	for (int i = 0; i < n; ++i) {
		p.push_back(i);
	}
	vector <data> good, edge;
	for (int i = 0; i < n; ++i) {
		good.emplace_back(s[i], i, 1);
		good.emplace_back(t[i], i, -1);
	}
	sort(good.begin(), good.end());
	long long ans = 0;
	for (int i = 0, diff = 0; i + 1 < n + n; ++i) {
		diff += good[i].z;
		ans += max(0, diff) * 1LL * (good[i + 1].x - good[i].x);
		edge.emplace_back(good[i + 1].x - good[i].x, good[i].y, good[i + 1].y);
		if ((diff != 0) or (good[i].x == good[i + 1].x)) {
			merge(good[i].y, good[i + 1].y);
		}
	}
	sort(edge.begin(), edge.end());
	for (int i = 0; i + 1 < n + n; ++i) {
		if (merge(edge[i].y, edge[i].z)) {
			ans += 1LL * edge[i].x;
		}
	}
	return ans;
}


/*

     |\   |  `|` |``\  ```|` |   |  /```\  |``\
     | \  |   |  |__/     |  |___| |     | |__/
     |  \ |   |  |  \     |  |   | |     | |  \
    _|   \|  _|_ |   \ \__)  |   |  \___/  |   \
    
        SPOJ - Leaves (NKLEAVES)
        
        Category: Data Structures
        
        Keys: Dynamic Programming, Convex Hull Trick
        
*/

#include <bits/stdc++.h>
 
using namespace std;

const int K = 14;
const int N = 1e5 + 10;

int n, k;
long long w[N];
long long s[N];
long long dp[K][N];
vector <long long> m;
vector <long long> c;
int size, pointer;

bool bad (int l1, int l2, int l3) {
	return (m[l1] - m[l2]) * (c[l3] - c[l1]) <= (c[l2] - c[l1]) * (m[l1] - m[l3]);
}

void add (long long m0, long long c0) {
	++size;
	m.push_back(m0);
	c.push_back(c0);
	while (size >= 3 and bad(size - 3, size - 2, size - 1)) {
		--size;
		m.erase(m.end() - 2);
		c.erase(c.end() - 2);
	}
}

long long query (long long x) {
	if (pointer >= size) pointer = size - 1;
	while (pointer < size - 1 and m[pointer] * x + c[pointer] >= m[pointer + 1] * x + c[pointer + 1]) {
		++pointer;
	}
	return m[pointer] * x + c[pointer];
}

int main (int argc, char const *argv[]) {
	scanf("%d %d", &n, &k);
	for (int i = 1; i <= n; ++i) {
		scanf("%lld", s + i);
		w[i] = w[i - 1] + s[i] * i;
		s[i] += s[i - 1];
	}
	for (int i = 1; i <= n; ++i) {
		dp[1][i] = w[i] - s[i];
	}
	for (int i = 2; i <= k; ++i) {
		pointer = 0;
		for (int j = i; j <= n; ++j) {
			add(-j, dp[i - 1][j - 1] - w[j - 1] + j * s[j - 1]);
			dp[i][j] = w[j] + query(s[j]);
		}
		m.clear(), c.clear(), size = 0;
	} 
	printf("%lld\n", dp[k][n]);
    return 0;
}


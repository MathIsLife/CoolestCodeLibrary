/*

     |\   |  `|` |``\  ```|` |   |  /```\  |``\
     | \  |   |  |__/     |  |___| |     | |__/
     |  \ |   |  |  \     |  |   | |     | |  \
    _|   \|  _|_ |   \ \__)  |   |  \___/  |   \
    
    	Codeforces 631E - Product Sum
    	
    	Category: Data Structures
    	
    	Keys: Algebraic Manipulation, Convex Hull Trick
    	
*/

#include <bits/stdc++.h>
 
using namespace std;

const int N = 2e5 + 10;

int n;
long long a[N];
long long sum[N];
vector <long long> m;
vector <long long> c;
int size;

bool bad (int l1, int l2, int l3, int forward) {
    if (forward) return (c[l1] - c[l2]) * (m[l3] - m[l1]) >= (c[l1] - c[l3]) * (m[l2] - m[l1]);
    return (c[l2] - c[l1]) * (m[l1] - m[l3]) <= (c[l3] - c[l1]) * (m[l1] - m[l2]);
}

void add (long long m0, long long c0, int forward) {
    ++size;
    m.push_back(m0);
    c.push_back(c0);
    while (size >= 3 and bad(size - 3, size - 2, size - 1, forward)) {
	--size;
	m.erase(m.end() - 2);
	c.erase(c.end() - 2);
    }
}

long long query (long long x) {
    long long last = m[size - 1] * x + c[size - 1];
    int lo = 0, hi = size - 2;
    while (lo < hi) {
	int mid = lo + hi >> 1;
	long long now = m[mid] * x + c[mid];
	long long after = m[mid + 1] * x + c[mid + 1];
	if (now < after) lo = mid + 1;
	else hi = mid; 
    }
    return max(last, m[lo] * x + c[lo]);
}

int main (int argc, char const *argv[]) {
    scanf("%d", &n);
    long long res = 0;
    for (int i = 1; i <= n; ++i) {
	scanf("%lld", a + i);
	sum[i] = a[i] + sum[i - 1];
	res += a[i] * i;
    }
    long long delta = 0;
    size = 0;
    add(n, -sum[n], 0);
    for (int i = n - 1; i; --i) {
	delta = max(delta, sum[i] - a[i] * i + query(a[i]));
	add(i, -sum[i], 0);
    }
    m.clear(), c.clear();
    size = 0;
    add(1, -sum[0], 1);
    for (int i = 2; i <= n; ++i) {
	delta = max(delta, sum[i - 1] - a[i] * i + query(a[i]));
	add(i, -sum[i - 1], 1);
    }
    printf("%lld\n", res + delta);
    return 0;
}


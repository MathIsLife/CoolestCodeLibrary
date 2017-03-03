/*

     |\   |  `|` |``\  ```|` |   |  /```\  |``\
     | \  |   |  |__/     |  |___| |     | |__/
     |  \ |   |  |  \     |  |   | |     | |  \
    _|   \|  _|_ |   \ \__)  |   |  \___/  |   \
    
        NCPC 2015 - Palindromic Bases (UVa 12994)
        
        Category: Mathematics
        
        Keys: Prime Factorization, Backtracking
        
*/

#include <bits/stdc++.h> 

using namespace std;

typedef long long ll;
typedef pair <ll, int> pii;

const int M = 70;
const int N = 1e7 + 10;

int t, cs = 0;
bitset <N> vis;
ll n, m, tmp[M];
int size, tot, res;
vector <ll> primes;
vector <pii> factors;

void sieve (void) {
	for (int i = 2; i * i < N; ++i) if (!vis[i]) {
		for (int j = i * i; j < N; j += i) vis[j] = 1;
	}
	for (int i = 2; i < N; ++i) {
		if (!vis[i]) primes.push_back((ll) i);
	}
	size = primes.size();
}

bool check (ll x, ll base) {
	if (base < 2) return false;
	int l = 0;
	while (x) {
		tmp[++l] = x % base;
		x /= base;
	}
	if (l & 1) return false;
	for (int i = 1, j = l; i < j; ++i, --j) {
		if (tmp[i] != tmp[j]) return false;
	}
	return true;
}

void backtrack (int pos, ll d) {
	if (pos == tot) {
		if (check(m, d - 1)) ++res;
		return;
	}
	for (int j = 0; j <= factors[pos].second; ++j) {
		backtrack(pos + 1, d);
		d *= factors[pos].first;
	}
}

int main (int argc, char const *argv[]) {
	sieve();
    scanf("%d", &t); while (t--) {
    	scanf("%lld", &n);
    	m = n, res = 0;
    	for (int i = 0; i < size; ++i) {
    		if (primes[i] * primes[i] > n) break;
    		int e = 0;
    		while (n % primes[i] == 0) ++e, n /= primes[i];
    		factors.push_back(pii(primes[i], e)); 
    	}
    	if (n > 1) factors.push_back(pii(n, 1));
    	tot = factors.size();
    	backtrack(0, 1);
    	factors.clear();
    	printf("Case %d: %d\n", ++cs, res);
    }
    return 0;
}


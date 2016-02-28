/*

     |\   |  `|` |``\  ```|` |   |  /```\  |``\
     | \  |   |  |__/     |  |___| |     | |__/
     |  \ |   |  |  \     |  |   | |     | |  \
    _|   \|  _|_ |   \ \__)  |   |  \___/  |   \
    
    	Codeforces 466C - Number of Ways
    	
    	Category: Ad hoc
    	
    	Keys: Simplification
    	
*/

#include <bits/stdc++.h>

using namespace std;

typedef long long i64;
typedef unsigned long long ui64;

#define checkbit(n, b) ((n >> b) & 1)
#define gcd __gcd
#define bitcount __bultin_popcount
#define inf (i64) 1e14
#define eps 1e-9
#define pi acos(-1)
#define mod 1000000007
#define MAX 500005

vector <i64> V;
i64 A[MAX], C[MAX], S, n, i, Count, Ret;

int main() {	
    cin.tie(nullptr);
    ios_base::sync_with_stdio(0);
	
	cin >> n;
	for (i = 1; i <= n; i++)
		cin >> A[i], 
		C[i] = C[i - 1] + A[i];
	
	if (C[n] % 3 || n <= 2) {
		cout << 0 << endl;
		return 0;
	}
	
	S = C[n]/3, Count = Ret = 0;
	
	if (S == 0) {
		for (i = 1; i < n; i++)
			if (C[i] == 0) ++Count;
			
		Ret = Count * (Count - 1)/2;
		cout << Ret << endl;
		return 0;
	}
	
	for (i = 1; i < n; i++) {
		if (C[i] == S) V.push_back(0);
		
		else if (C[i] == S + S && !V.empty()) 
			V.push_back(1), ++Count;
	}
	
	S = V.size();
	
	for (i = 0; i < S; i++) {
		if (V[i] == 0) Ret += Count;
		else --Count;
	}
	
	cout << Ret << endl;
	
    cout.flush(); 
    return 0;
}


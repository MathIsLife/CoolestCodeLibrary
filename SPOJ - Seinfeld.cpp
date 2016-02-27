/*

     |\   |  `|` |``\  ```|` |   |  /```\  |``\
     | \  |   |  |__/     |  |___| |     | |__/
     |  \ |   |  |  \     |  |   | |     | |  \
    _|   \|  _|_ |   \ \__)  |   |  \___/  |   \
    
    	SPOJ ANARC09A - Seinfeld
    	
    	Category: Ad hoc
    	
    	Keys: Compression, Simplification
    	
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

string S; int L, i, Ret, Case = 1; 

int main() {	
    cin.tie(nullptr);
    ios_base::sync_with_stdio(0);
	
    while (Case++) {
	cin >> S; if (S[0] == '-') break;
		
	stack <char> Stack; L = S.length();
		
	for (i = 0; i < L; i++) {
	    if (Stack.empty()) Stack.push(S[i]);
	    else if (S[i] == '}' && Stack.top() == '{') Stack.pop();
	    else Stack.push(S[i]);
	} 
		
	S = ""; int open = 0, close = 0;
	
	while (!Stack.empty()) 
	    Stack.top() == '{' ? open++ : close++, Stack.pop();
		
	Ret = open/2 + close/2 + 2 * (open % 2);
	cout << Case - 1 << ". " << Ret << endl;
    }
	
    cout.flush();
    return 0;
}


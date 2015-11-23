/*

     |\   |  `|` |``\  ```|` |   |  /```\  |``\
     | \  |   |  |__/     |  |___| |     | |__/
     |  \ |   |  |  \     |  |   | |     | |  \
    _|   \|  _|_ |   \ \__)  |   |  \___/  |   \

        LightOJ 1093 - Ghajini

        Category: Ad hoc, Data Structure

        Keys: Sliding Window, Range Min/Max Query

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

struct elem {int val, idx;}; 

deque<elem> DQ;  
vector<int> V, Min, Max; 
int T, n, d, i, k, tmp, ret;

void Find_Min (void) {
    Min.clear(), DQ.clear(); 
    for (i = 0; i < n; i++) {
        while (!DQ.empty() && DQ.front().val >= V[i]) DQ.pop_front(); 
        elem E; E.val = V[i], E.idx = i; DQ.push_front(E); 
        while (!DQ.empty() && DQ.back().idx <= i - d) DQ.pop_back(); 
        if (i >= d - 1) Min.push_back(DQ.back().val); 
    }
}

void Find_Max (void) {
    Max.clear(), DQ.clear(); 
    for (i = 0; i < n; i++) {
        while (!DQ.empty() && DQ.front().val <= V[i]) DQ.pop_front(); 
        elem E; E.val = V[i], E.idx = i; DQ.push_front(E); 
        while (!DQ.empty() && DQ.back().idx <= i - d) DQ.pop_back(); 
        if (i >= d - 1) Max.push_back(DQ.back().val); 
    }
}

void Kill (void) {
    scanf("%d", &T); 
    for (k = 1; k <= T; k++) {
        V.clear(); scanf("%d %d", &n, &d); 
        for (i = 0; i < n; i++) scanf("%d", &tmp), V.push_back(tmp); 
        Find_Min(), Find_Max(); ret = 0; 
        for (i = 0; i < n - d + 1; i++) ret = max(ret, Max[i] - Min[i]); 
        printf("Case %d: %d\n", k, ret); 
    }
}

int main () {
    Kill();
    return 0;
}

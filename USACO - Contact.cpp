/*

     |\   |  `|` |``\  ```|` |   |  /```\  |``\
     | \  |   |  |__/     |  |___| |     | |__/
     |  \ |   |  |  \     |  |   | |     | |  \
    _|   \|  _|_ |   \ \__)  |   |  \___/  |   \

        USACO - Contact
        
        Category: Implementation, String
        
        Keys: C++ STL, Brute Force

*/

#include <bits/stdc++.h>

using namespace std;

typedef long long i64;
typedef unsigned long long ui64;

#define checkbit(n, b) ((n >> b) & 1)
#define gcd __gcd
#define bitcount __bultin_popcount
#define inf (int)2e9
#define eps 1e-9
#define pi acos(-1)
#define mod 1000000007
#define MAX 200005

string S, in;
map<string, int> M;
int A, B, N, i, j, L, cnt, k;
vector< pair<int, string> > V;
map<string, int>::iterator it;
vector< pair< int, vector<string> > > R;

bool cmp (pair<int, string> A, pair<int, string> B) {
    if (A.first == B.first) {
        if (A.second.length() == B.second.length())
            return (A.second < B.second);
        return A.second.length() < B.second.length();
    }
    return A.first > B.first;
}

int main () {
    freopen("contact.in", "r", stdin);
    freopen("contact.out", "w", stdout);

    cin >> A >> B >> N; S = "";
    while (cin >> in) S += in;
    L = S.length();

    for (i = A; i <= B; i++)
        for (j = 0; j <= L - i; j++)
            ++M[S.substr(j, i)];

    for (it = M.begin(); it != M.end(); ++it)
        V.push_back(make_pair(it -> second, it -> first));
    sort(V.begin(), V.end(), cmp);

    i = 1, j = 0; R.resize(MAX);
    R[0].first = V[0].first, R[0].second.push_back(V[0].second);
    while (i < V.size()) {
        if (V[i].first != V[i - 1].first) R[++j].first = V[i].first;
        R[j].second.push_back(V[i++].second);
    }

    for (i = 0; i < N && i <= j; i++) {
        cnt = 0; cout << R[i].first << endl;
        for (k = 0; k < R[i].second.size(); k++) {
            if (cnt == 6) {
                cout << endl;
                cnt = 0;
            }
            if (cnt != 0) cout << " ";
            cout << R[i].second[k]; ++cnt;
        } cout << endl;
    }
    return 0;
}


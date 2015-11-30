/*

     |\   |  `|` |``\  ```|` |   |  /```\  |``\
     | \  |   |  |__/     |  |___| |     | |__/
     |  \ |   |  |  \     |  |   | |     | |  \
    _|   \|  _|_ |   \ \__)  |   |  \___/  |   \

        USACO - Longest Prefix (IOI 1996)

        Category: Dynamic Programming

        Keys: Bottom Up

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

#define MAX 200005
#define max(a, b) (a > b ? a : b)

bool DP[MAX];
string S, inp;
vector<string> Prims;
int i, j, len, cnt, Res;

ifstream fin ("prefix.in");
ofstream fout ("prefix.out");

void Read (void) {
    cnt = 0, S = "";
    while (fin >> inp && inp != ".")
        Prims.push_back(inp), ++cnt;
    while (fin >> inp) S += inp;
}

void Kill (void) {
    memset(DP, false, sizeof DP);
    DP[0] = true, Res = 0, len = S.length();
    for (i = 0; i < len; i++)
        if (DP[i])
            for (j = 0; j < cnt; j++)
                if (S.substr(i, Prims[j].length()) == Prims[j])
                    Res = max(Res, i + Prims[j].length()),
                    DP[i + Prims[j].length()] = true;
    fout << Res << endl;
}

int main() {
    Read();
    Kill();
    return 0;
}


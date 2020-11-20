#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int N = 300010;

int n, m, p[N];
vector <int> g[N];
ll w[N], a[N], b[N];
priority_queue <ll> *pq[N];

int main() {
  cin >> m >> n; n += m;
  for (int i = 2; i <= n; ++i) {
    scanf("%d %lld", p + i, w + i);
    g[p[i]].emplace_back(i);
  }
  for (int i = m + 1; i <= n; ++i) {
    a[i] = 1, b[i] = -w[i];
    pq[i] = new priority_queue <ll> ();
    pq[i] -> emplace(w[i]); pq[i] -> emplace(w[i]);
  }
  for (int i = m; i >= 1; --i) {
    pq[i] = new priority_queue <ll> ();
    for (int j : g[i]) {
      if (pq[j] -> size() > pq[i] -> size()) swap(pq[i], pq[j]);
      while (!(pq[j] -> empty())) pq[i] -> emplace(pq[j] -> top()), pq[j] -> pop();
      a[i] += a[j], b[i] += b[j];
    }
    while (a[i] > 1) b[i] += pq[i] -> top(), --a[i], pq[i] -> pop(); b[i] -= w[i];
    ll one = pq[i] -> top(); pq[i] -> pop();
    ll zero = pq[i] -> top(); pq[i] -> pop();
    pq[i] -> emplace(one + w[i]); pq[i] -> emplace(zero + w[i]);
  }
  cout << a[1] * pq[1] -> top() + b[1] << '\n';
  return 0;
}



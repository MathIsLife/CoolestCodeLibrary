/*

     |\   |  `|` |``\  ```|` |   |  /```\  |``\
     | \  |   |  |__/     |  |___| |     | |__/
     |  \ |   |  |  \     |  |   | |     | |  \
    _|   \|  _|_ |   \ \__)  |   |  \___/  |   \
    
    	Codeforces 660F - Bear and Bowling 4
    	
    	Category: Data Structures
    	
    	Keys: Convex Hull Trick
    	
*/

#include <bits/stdc++.h>
 
using namespace std;

const int N = 2e5 + 10;

int n;
long long sum[N];
long long wsum[N];
long long val[N];
vector <long long> m;
vector <long long> c;
int size = 0;

bool bad (int l1, int l2, int l3) {
  return (c[l1] - c[l2]) * (m[l3] - m[l1]) <= (c[l1] - c[l3]) * (m[l2] - m[l1]);
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
  long long last = m[size - 1] * x + c[size - 1];
  int lo = 0, hi = size - 2;
  while (lo < hi) {
    int mid = lo + hi >> 1;
    long long now = m[mid] * x + c[mid];
    long long after = m[mid + 1] * x + c[mid + 1];
    if (now > after) lo = mid + 1;
    else hi = mid; 
  }
  return min(last, m[lo] * x + c[lo]);
}

int main (int argc, char const *argv[]) {
  scanf("%d", &n);
  for (int i = 1; i <= n; ++i) {
    scanf("%lld", sum + i);
    wsum[i] = i * sum[i];
    sum[i] += sum[i - 1];
    wsum[i] += wsum[i - 1];
    val[i] = wsum[i] - i * sum[i];
  }
  add(0, 0);
  long long ans = 0;
  for (int i = 1; i <= n; ++i) {
    ans = max(ans, wsum[i] - query(sum[i]));
    add(i, val[i]);
  }
  printf("%lld\n", ans);
  return 0;
}


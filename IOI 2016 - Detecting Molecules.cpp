/*

     |\   |  `|` |``\  ```|` |   |  /```\  |``\
     | \  |   |  |__/     |  |___| |     | |__/
     |  \ |   |  |  \     |  |   | |     | |  \
    _|   \|  _|_ |   \ \__)  |   |  \___/  |   \
    
        IOI 2016 - Detecting Molecules
        
        Category: Ad hoc
        
        Keys: Observation, Two Pointers
        
*/

#include <bits/stdc++.h>
#include "molecules.h"

using namespace std;

typedef long long ll;
typedef pair <ll, int> pii;

vector <int> find_subset (int l, int u, vector <int> w) {
  int n = w.size();
  vector <pii> v;
  for (int i = 0; i < n; ++i) {
    v.push_back(pii(w[i], i));
  }
  sort(v.begin(), v.end());
  ll sum = 0;
  vector <int> r;
  for (int i = 0, j = 0; j < n; ++j) {
    sum += v[j].first;
    while (sum > u) {
      sum -= v[i++].first;
    }
    if (sum >= l) {
      for (int k = i; k <= j; ++k) {
	r.push_back(v[k].second);
      }
      break;
    }
  }
  return r;
}


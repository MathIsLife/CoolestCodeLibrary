/*

     |\   |  `|` |``\  ```|` |   |  /```\  |``\
     | \  |   |  |__/     |  |___| |     | |__/
     |  \ |   |  |  \     |  |   | |     | |  \
    _|   \|  _|_ |   \ \__)  |   |  \___/  |   \
    
        APIO 2016 - Gap
        
        Category: Ad hoc
        
        Keys: Constructive Algorithm, Pigeonhole Principle
        
*/

#include <bits/stdc++.h>
#include "gap.h"

using namespace std;

typedef long long ll;

ll findGap (int subTask, int n) {
  ll l, r, ret = 0; 
  MinMax(0, 1e18, &l, &r);
  if (subTask == 1) {
    for (int done = 2; done < n; done += 2) {
      ll new_l, new_r;
      MinMax(l + 1, r - 1, &new_l, &new_r);
      if (new_l == -1) break;
      ret = max(ret, new_l - l);
      ret = max(ret, r - new_r);
      l = new_l, r = new_r;
    }
    ret = max(ret, r - l);
  } else {
    ll block = (r - l + n - 3)/(n - 1);
    for (ll i = l + 1, j = i + block; i < r; i += block, j += block) {
      ll new_l, new_r;
      if (j > r) j = r;
      MinMax(i, j - 1, &new_l, &new_r);
      if (new_l != -1) {
        ret = max(ret, new_l - l);
        l = new_r;
      }
    }
    ret = max(ret, r - l);
  }
  return ret;
}

